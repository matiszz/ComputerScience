-module(causal).
-export([start/3]).

start(Id, Master, Jitter) ->
    spawn(fun() -> init(Id, Master, Jitter) end).

init(Id, Master, Jitter) ->
    
    receive
        {peers, Nodes} ->
            VC = newVC(length(Nodes), []),
            server(Id, Master, lists:delete(self(), Nodes), Jitter, VC, [])
    end.

server(Id, Master, Nodes, Jitter, VC, Queue) ->
    receive
        {send, Msg} ->
            Valor = element(Id,VC),
            NewerVC = setelement(Id, VC, Valor+1),
            multicast(Msg, Nodes, Jitter, Id, NewerVC),
            Master ! {deliver, Msg},
            server(Id, Master, Nodes, Jitter, NewerVC, Queue);
        {multicast, Msg, FromId, MsgVC} ->
            case checkMsg(FromId, MsgVC, VC, size(VC)) of
                ready ->
                    Master ! {deliver, Msg},
                    Valor = element(FromId, VC),
                    NewVC = setelement(FromId, VC, Valor+1), %% TODO: COMPLETE 
                    {NewerVC, NewQueue} = deliverReadyMsgs(Master, NewVC, Queue, Queue),
                    server(Id, Master, Nodes, Jitter, NewerVC, NewQueue);
                wait ->
                    server(Id, Master, Nodes, Jitter, VC, [{FromId, MsgVC, Msg}|Queue])
            end;
        stop ->
            ok
    end.

multicast(Msg, Nodes, 0, FromId, MsgVC) ->
    lists:foreach(fun(Node) -> 
                      Node ! {multicast, Msg, FromId, MsgVC} 
                  end, 
                  Nodes);
multicast(Msg, Nodes, Jitter, FromId, MsgVC) ->
    lists:foreach(fun(Node) -> 
                      T = rand:uniform(Jitter),
                      timer:send_after(T, Node, {multicast, Msg, FromId, MsgVC})
                  end, 
                  Nodes).

newVC(0, List) -> 
    list_to_tuple(List);
newVC(N, List) ->
    newVC(N-1, [0|List]).

%% Check if a message can be delivered to the master
checkMsg(_, _, _, 0) -> ready;
checkMsg(FromId, MsgVC, VC, FromId) ->
    ValorLocal = element(FromId, VC),
    ValorMissatge = element(FromId, MsgVC),
    if (ValorLocal+1 == ValorMissatge) -> %% TODO: COMPLETE - Si es el siguiente que espero de ese sender
        checkMsg(FromId, MsgVC, VC, FromId-1);
        true -> wait
    end;
checkMsg(FromId, MsgVC, VC, N) ->
    ValorLocal = element(N, VC),
    ValorMissatge = element(N, MsgVC),
    if (ValorMissatge =< ValorLocal) -> %% TODO: COMPLETE - Si he visto todos los mensajes del sender
        checkMsg(FromId, MsgVC, VC, N-1);
        true -> wait
    end.

%% Deliver to the master all the ready messages in the hold-back queue
deliverReadyMsgs(_, VC, [], Queue) ->
    {VC, Queue};
deliverReadyMsgs(Master, VC, [{FromId, MsgVC, Msg}|Rest], Queue) ->
    case checkMsg(FromId, MsgVC, VC, size(VC)) of
            ready ->
            Master ! {deliver, Msg},
            ValorLocal = element(FromId,VC),
            NewVC = setelement(FromId, VC, ValorLocal+1),%% TODO: COMPLETE -->> newVC(length(Nodes), []) aumentando uno en el sender
            NewQueue = lists:delete({FromId, MsgVC, Msg}, Queue),
            deliverReadyMsgs(Master, NewVC, NewQueue, NewQueue);
        wait ->
            deliverReadyMsgs(Master, VC, Rest, Queue)
    end.
