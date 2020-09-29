-module(node2).
-export([start/1, start/2]).

-define(Stabilize, 1000).
-define(Timeout, 5000).

start(MyKey) ->
    start(MyKey, nil).

start(MyKey, PeerPid) ->
    timer:start(),
    spawn(fun() -> init(MyKey, PeerPid) end).

init(MyKey, PeerPid) ->
    Predecessor = nil,
    {ok, Successor} = connect(MyKey, PeerPid),
    schedule_stabilize(),    
    node(MyKey, Predecessor, Successor,storage:create()).

connect(MyKey, nil) ->
    {ok, {MyKey , self()}};    %% TODO: ADD SOME CODE
connect(_, PeerPid) ->
    Qref = make_ref(),
    PeerPid ! {key, Qref, self()},
    receive
        {Qref, Skey} ->
            {ok, {Skey , PeerPid}}    %% TODO: ADD SOME CODE
    after ?Timeout ->
        io:format("Timeout: no response from ~w~n", [PeerPid])
    end.

schedule_stabilize() ->
    timer:send_interval(?Stabilize, self(), stabilize).

    
    
    
    
    
%%Cambios versión 2
    
node(MyKey, Predecessor, Successor, Store) ->
    receive 
        {key, Qref, Peer} ->
            Peer ! {Qref, MyKey},
            node(MyKey, Predecessor, Successor, Store);
        {notify, NewPeer} ->
            {NewPredecessor, NewStore} = notify(NewPeer, MyKey, Predecessor, Store),
            node(MyKey, NewPredecessor, Successor, NewStore);
        {request, Peer} ->
            request(Peer, Predecessor),
            node(MyKey, Predecessor, Successor, Store);
        {status, Pred} ->
            NewSuccessor = stabilize(Pred, MyKey, Successor),
            node(MyKey, Predecessor, NewSuccessor, Store);
        stabilize ->
            stabilize(Successor),
            node(MyKey, Predecessor, Successor, Store);
        stop ->
            ok;
        probe ->
            create_probe(MyKey, Successor, Store),
            node(MyKey, Predecessor, Successor, Store);
        {probe, MyKey, Nodes, T} ->
            remove_probe(MyKey, Nodes, T),
            node(MyKey, Predecessor, Successor, Store);
        {probe, RefKey, Nodes, T} ->
            forward_probe(RefKey, [MyKey|Nodes], T, Successor),
            node(MyKey, Predecessor, Successor, Store);
       %% Hemos añadido estos mensajes y las correspondientes funciones
        {add, Key, Value, Qref, Client} ->
            Added = add(Key, Value, Qref, Client,
                        MyKey, Predecessor, Successor, Store),
            node(MyKey, Predecessor, Successor, Added);
        {lookup, Key, Qref, Client} ->
            lookup(Key, Qref, Client, MyKey, Predecessor, Successor, Store),
            node(MyKey, Predecessor, Successor, Store);
        {handover, Elements} ->
            Merged = storage:merge(Store, Elements),
            node(MyKey, Predecessor, Successor, Merged)
   end.

add(Key, Value, Qref, Client, MyKey, {Pkey, _}, {_, Spid}, Store) ->
    case key:between(Key, Pkey , MyKey) of %% TODO: ADD SOME CODE
        true ->
            Added = storage:add(Key, Value, Store),
            %% TODO: ADD SOME CODE
            Client ! {Qref, ok},
            Added;
        false ->
            %% TODO: ADD SOME CODE
            Spid ! {add, Key, Value, Qref, Client},
            Store
    end.

lookup(Key, Qref, Client, MyKey, {Pkey, _}, {_, Spid}, Store) ->
    case key:between(Key , Pkey , MyKey) of %% TODO: ADD SOME CODE
        true ->
           
            Result = storage:lookup(Key, Store),
            %% TODO: ADD SOME CODE
            Client ! {Qref, Result};
        false ->
            %% TODO: ADD SOME CODE
            Spid ! {lookup, Key, Qref, Client}
    end.

notify({Nkey, Npid}, MyKey, Predecessor, Store) ->
        case Predecessor of
            nil ->
                Keep = handover(Store, MyKey, Nkey, Npid),
                %% TODO: ADD SOME CODE
                NewP = {Nkey, Npid},
                {NewP, Keep};
            {Pkey, _} ->
                case key:between(Nkey, Pkey, MyKey) of
                    true ->
                        %% TODO: ADD SOME CODE
                        %% TODO: ADD SOME CODE
                        Keep = handover(Store, MyKey, Nkey, Npid),
                        NewP = {Nkey, Npid},
                        {NewP, Keep};
                    false ->
                            {Predecessor, Store}
                end
        end.
        
handover(Store, MyKey, Nkey, Npid) ->
    {Keep, Leave} = storage:split(MyKey, Nkey, Store),
    Npid ! {handover, Leave},
    Keep.

%%Fin cambios versión 2
   
   
   
   
   
   
   
   
   
   
   
   
   
stabilize(Pred, MyKey, Successor) ->
    %% consiste en que el node envia request al successor, espera rebre un status i veure si es manté consistent.
  {Skey, Spid} = Successor,
  case Pred of
      nil ->
          %% TODO: ADD SOME CODE
          %%No té valor, per tant, informo de la meva existencia
          Spid ! {notify, {MyKey, self()}},
          Successor;
      {MyKey, _} ->
        %%M'apunta a mi i no cal fer-res
          Successor;
      {Skey, _} ->
          %% TODO: ADD SOME CODE
           %%S'apunta a ell mateix, per tant notifico de la meva existencia
           Spid ! {notify, {MyKey, self()}},
           Successor;
      {Xkey, Xpid} ->
            case key:between(Xkey, MyKey, Skey) of
                true ->
                    %% TODO: ADD SOME CODE 
                    %% TODO: ADD SOME CODE 
                    %%El node es troba entre la nostra clau i la del successor acutal  per tant l'hem de prendre com el nostre nou successor.
                    self() ! stabilize,
                    {Xkey, Xpid};
                false ->
                    %% TODO: ADD SOME CODE
                    Spid ! {notify, {MyKey, self()}},
                    Successor
            end
    end.
    
stabilize({_, Spid}) ->
    Spid ! {request, self()}.

request(Peer, Predecessor) ->
    case Predecessor of
        nil ->
            Peer ! {status, nil};
        {Pkey, Ppid} ->
            Peer ! {status, {Pkey, Ppid}}
    end.

create_probe(MyKey, {_, Spid}, Store) ->
    Spid ! {probe, MyKey, [MyKey], erlang:monotonic_time()},
    io:format("Create probe ~w, Store: ~w items !~n", [MyKey, length(Store)]).
	
remove_probe(MyKey, Nodes, T) ->
    T2 = erlang:monotonic_time(),
    Time = erlang:convert_time_unit(T2-T, native, millisecond),
    io:format("Received probe ~w in ~w ms Ring: ~w~n", [MyKey, Time, Nodes]).
	
forward_probe(RefKey, Nodes, T, {_, Spid}) ->
    Spid ! {probe, RefKey, Nodes, T},
    io:format("Forward probe ~w!~n", [RefKey]).
