-module(gms2).
-export([start/1, start/2]).

start(Name) ->
    Self = self(),
    spawn_link(fun()-> init(Name, Self) end).

init(Name, Master) ->
    leader(Name, Master, []).

start(Name, Grp) ->
    Self = self(),
    spawn_link(fun()-> init(Name, Grp, Self) end).    

init(Name, Grp, Master) ->
    Self = self(),
    Grp ! {join, Self},

    receive
        {view, Leader, Slaves} ->
            NewRef=erlang:monitor(process, Leader),
            Master ! joined,
            slave(Name, Master, Leader, Slaves, NewRef)
        after 1000 -> 
            Master ! {error, "no reply from leader"}
    end.

leader(Name, Master, Slaves) ->    
    receive
        {mcast, Msg} ->
            bcast(Name, {msg, Msg}, Slaves),  %% TODO: COMPLETE
            Master ! {deliver,Msg}, %% TODO: ADD SOME CODE
            leader(Name, Master, Slaves);
        {join, Peer} ->
            NewSlaves = lists:append(Slaves, [Peer]),           
            bcast(Name, {view, self(), NewSlaves}, NewSlaves),  %% TODO: COMPLETE
            leader(Name, Master, NewSlaves);  %% TODO: COMPLETE
        stop ->
            ok;
        Error ->
            io:format("leader ~s: strange message ~w~n", [Name, Error])
    end.
    
bcast(Name, Msg, Nodes) ->
    lists:foreach(fun(Node) ->
                    Node ! Msg,
                    crash(Name,Msg)
                    end, 
                    Nodes).

crash(Name, Msg) ->
    case rand:uniform(10) of
        10 ->
            io:format("leader ~s CRASHED: msg ~w ~n", [Name, Msg]),
            exit(no_luck);
        _ ->
            ok
    end.
    
slave(Name, Master, Leader, Slaves, Ref) ->    
    receive
        {mcast, Msg} ->
            Leader ! {mcast, Msg}, %% TODO: ADD SOME CODE
            slave(Name, Master, Leader, Slaves, Ref);
        {join, Peer} ->
            Leader ! {join, Peer}, %% TODO: ADD SOME CODE
            slave(Name, Master, Leader, Slaves, Ref);
        {msg, Msg} ->
            Master ! {deliver,Msg}, %% TODO: ADD SOME CODE
            slave(Name, Master, Leader, Slaves, Ref);
        {view, Leader, NewSlaves} ->
            slave(Name, Master, Leader, NewSlaves, Ref);  %% TODO: COMPLETE
        {view, NewLeader, NewSlaves} ->
            erlang:demonitor(Ref, [flush]),
            NewRef = erlang:monitor(process, NewLeader),
            slave(Name, Master, NewLeader, NewSlaves, NewRef);
        {'DOWN', _Ref, process, Leader, _Reason} -> 
            election(Name, Master, Slaves);
        stop ->
            ok;
        Error ->
            io:format("slave ~s: strange message ~w~n", [Name, Error])
    end.
    
election(Name, Master, Slaves) ->
    Self = self(),
    case Slaves of
        [Self|Rest] -> %% TODO: ADD SOME CODE
            bcast(Name, {view, Self, Rest}, Rest),
            leader(Name,Master, Rest); %% TODO: COMPLETE
        [NewLeader|Rest] ->
            NewRef = erlang:monitor(process,NewLeader),%% TODO: ADD SOME CODE
            slave(Name, Master, NewLeader, Rest, NewRef) %% TODO: COMPLETE
    end.

