-module(lock3).
-export([start/1]).

start(MyId) ->
    Tlocal = 0,
    spawn(fun() -> init(MyId, Tlocal) end).

init(MyId, Tlocal) ->
    receive
        {peers, Nodes} ->
            open(Nodes, MyId, Tlocal);
        stop ->
            ok
    end.

open(Nodes, MyId, Tlocal) ->
    receive
        {take, Master, Ref} ->
			NewTlocal = Tlocal + 1,
			NewTreq = NewTlocal,
            Refs = requests(Nodes, MyId, NewTlocal),
            wait(Nodes, Master, Refs, [], Ref, MyId, NewTlocal, NewTreq);
        {request, From,  Ref, _, Tmessage} ->
            From ! {ok, Ref},
            open(Nodes, MyId, max(Tlocal,Tmessage));
        stop ->
            ok
    end.

requests(Nodes, MyId, Tlocal) ->
    lists:map(
      fun(P) -> 
        R = make_ref(), 
        P ! {request, self(), R, MyId, Tlocal}, 
        R 
      end, 
      Nodes).

wait(Nodes, Master, [], Waiting, TakeRef, MyId, Tlocal, Treq) ->
    Master ! {taken, TakeRef},
    held(Nodes, Waiting, MyId, Tlocal, Treq);
wait(Nodes, Master, Refs, Waiting, TakeRef, MyId, Tlocal, Treq) ->
    receive
        {request, From, Ref, ID, Tmessage} ->
           if
                Tmessage < Treq -> 
                    From ! {ok, Ref},
                    wait(Nodes, Master, Refs, Waiting, TakeRef, MyId, max(Tlocal,Tmessage), Treq);
                Tmessage > Treq ->
                    wait(Nodes, Master, Refs, [{From, Ref}|Waiting], TakeRef, MyId, max(Tlocal,Tmessage), Treq); %% Encolamos
                true ->
                    if 
                        ID < MyId -> 
                            From ! {ok, Ref},
                            wait(Nodes, Master, Refs, Waiting, TakeRef, MyId, max(Tlocal,Tmessage), Treq);
                        ID > MyId ->
                            wait(Nodes, Master, Refs, [{From, Ref}|Waiting], TakeRef, MyId, max(Tlocal,Tmessage), Treq) %% Encolamos
                    end
            end;
        {ok, Ref} ->
            NewRefs = lists:delete(Ref, Refs),
            wait(Nodes, Master, NewRefs, Waiting, TakeRef, MyId, Tlocal, Treq);
        release ->
            ok(Waiting),            
            open(Nodes, MyId, Tlocal)
    end.

ok(Waiting) ->
    lists:map(
      fun({F,R}) -> 
        F ! {ok, R} 
      end, 
      Waiting).

held(Nodes, Waiting, MyId, Tlocal) ->
    receive
        {request, From, Ref, _, Tmessage} ->
            held(Nodes, [{From, Ref}|Waiting], MyId, max(Tlocal,Tmessage));
        release ->
            ok(Waiting),
            open(Nodes, MyId, Tlocal)
    end.
