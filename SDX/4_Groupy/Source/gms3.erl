-module(gms3).
-export([start/1, start/2]).

start(Name) ->
    Self = self(),
    spawn_link(fun()-> init(Name, Self) end).

init(Name, Master) ->
    leader(Name, Master, [], 1).

start(Name, Grp) ->
    Self = self(),
    spawn_link(fun()-> init(Name, Grp, Self) end).    

init(Name, Grp, Master) ->
    Self = self(),
    Grp ! {join, Self},

    receive
        {view, Leader, Slaves, N} ->
            NewRef=erlang:monitor(process, Leader),
            Master ! joined,
            slave(Name, Master, Leader, Slaves, NewRef, N+1, {view, Leader, Slaves, N})
        after 1000 -> 
            Master ! {error, "no reply from leader"}
    end.

leader(Name, Master, Slaves, N) ->    
    receive
        {mcast, Msg} ->
            bcast(Name, {msg, Msg, N}, Slaves),  %% TODO: COMPLETE
            Master ! {deliver,Msg}, %% TODO: ADD SOME CODE
            leader(Name, Master, Slaves,N+1);
        {join, Peer} ->
            NewSlaves = lists:append(Slaves, [Peer]),           
            bcast(Name, {view, self(), NewSlaves, N}, NewSlaves),  %% TODO: COMPLETE
            leader(Name, Master, NewSlaves,N+1);  %% TODO: COMPLETE
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
    case rand:uniform(200) of
        200 ->
            io:format("leader ~s CRASHED: msg ~w ~n", [Name, Msg]),
            exit(no_luck);
        _ ->
            ok
    end.
    
slave(Name, Master, Leader, Slaves, Ref, N, Last) ->    
    receive
        {mcast, Msg} ->
            Leader ! {mcast, Msg}, %% TODO: ADD SOME CODE
            slave(Name, Master, Leader, Slaves, Ref, N, Last);
        {join, Peer} ->
            Leader ! {join, Peer}, %% TODO: ADD SOME CODE
            slave(Name, Master, Leader, Slaves, Ref, N, Last);
        {msg, _, Nseq} when Nseq < N ->
            slave(Name, Master, Leader, Slaves, Ref, N, Last);
        {msg, Msg, N} ->
            Master ! {deliver,Msg}, %% TODO: ADD SOME CODE
            slave(Name, Master, Leader, Slaves, Ref, N+1, {msg, Msg, N});
        {view, _, _, Nseq} when Nseq < N ->
            slave(Name, Master, Leader, Slaves, Ref, N, Last);
        {view, Leader, NewSlaves, N}->
            slave(Name, Master, Leader, NewSlaves, Ref, N+1 ,{view, Leader, NewSlaves, N});  %% TODO: COMPLETE
        {view, NewLeader, NewSlaves, N} ->
            erlang:demonitor(Ref, [flush]),
            NewRef = erlang:monitor(process, NewLeader),
            slave(Name, Master, NewLeader, NewSlaves, NewRef, N+1 ,{view, NewLeader, NewSlaves, N});
        {'DOWN', _Ref, process, Leader, _Reason} -> 
            election(Name, Master, Slaves, N, Last);
        stop ->
            ok;
        Error ->
            io:format("slave ~s: strange message ~w~n", [Name, Error])
    end.
    
election(Name, Master, Slaves, N, Last) ->
    Self = self(),
    case Slaves of
        [Self|Rest] -> %% TODO: ADD SOME CODE
            bcast(Name, Last, Rest),
            bcast(Name, {view, Self, Rest, N}, Rest),
            leader(Name, Master, Rest, N+1); %% TODO: COMPLETE
        [NewLeader|Rest] ->
            NewRef = erlang:monitor(process,NewLeader),%% TODO: ADD SOME CODE
            slave(Name, Master, NewLeader, Rest, NewRef, N, Last) %% TODO: COMPLETE
    end.

