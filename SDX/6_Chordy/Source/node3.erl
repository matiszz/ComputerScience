-module(node3).
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
    schedule_stabilize(),    %% TODO: Que va aquí? ↓
    node(MyKey, Predecessor, Successor, nil , storage:create()).

connect(MyKey, nil) ->
    {ok, {MyKey, monit(self()), self()}};

connect(_, PeerPid) ->
    Qref = make_ref(),
    PeerPid ! {key, Qref, self()},
    receive
        {Qref, Skey} ->
            {ok, {Skey , monit(PeerPid), PeerPid}}
    after ?Timeout ->
        io:format("Timeout: no response from ~w~n", [PeerPid])
    end.

schedule_stabilize() ->
    timer:send_interval(?Stabilize, self(), stabilize).
    
node(MyKey, Predecessor, Successor, Next, Store) -> %% DONE: Add parameter
    receive 
        {key, Qref, Peer} ->
            Peer ! {Qref, MyKey},
            node(MyKey, Predecessor, Successor, Next, Store);
        {notify, NewPeer} ->
            {NewPredecessor, NewStore} = notify(NewPeer, MyKey, Predecessor, Store),
            node(MyKey, NewPredecessor, Successor, Next, NewStore);
        {request, Peer} ->
            request(Peer, Predecessor, Successor), %% DONE: Add parameter
            node(MyKey, Predecessor, Successor, Next, Store);
        {status, Pred, Nx} ->
            {NewSuccessor, NewNext} = stabilize(Pred, Nx, MyKey, Successor), %% DONE: Add parameter
            node(MyKey, Predecessor, NewSuccessor, NewNext, Store);
        stabilize ->
            stabilize(Successor),
            node(MyKey, Predecessor, Successor, Next, Store);
        stop ->
            ok;
        probe ->
            create_probe(MyKey, Successor, Store),
            node(MyKey, Predecessor, Successor, Next, Store);
        {probe, MyKey, Nodes, T} ->
            remove_probe(MyKey, Nodes, T),
            node(MyKey, Predecessor, Successor, Next, Store);
        {probe, RefKey, Nodes, T} ->
            forward_probe(RefKey, [MyKey|Nodes], T, Successor),
            node(MyKey, Predecessor, Successor, Next, Store);
        %% Hemos añadido estos mensajes y las correspondientes funciones
        {add, Key, Value, Qref, Client} ->
            Added = add(Key, Value, Qref, Client,
                        MyKey, Predecessor, Successor, Store),
            node(MyKey, Predecessor, Successor, Next, Added);
        {lookup, Key, Qref, Client} ->
            lookup(Key, Qref, Client, MyKey, Predecessor, Successor, Store),
            node(MyKey, Predecessor, Successor, Next, Store);
        {handover, Elements} ->
            Merged = storage:merge(Store, Elements),
            node(MyKey, Predecessor, Successor, Next, Merged);
        %% DONE: Add this message ↓
        {'DOWN', Ref, process, _, _} ->
            {NewPred, NewSucc, NewNext} = down(Ref, Predecessor, Successor, Next),
            node(MyKey, NewPred, NewSucc, NewNext, Store)
   end.

add(Key, Value, Qref, Client, MyKey, {Pkey,_, _}, {_,_, Spid}, Store) ->
    case key:between(Key, Pkey , MyKey) of
        true ->
            Added = storage:add(Key, Value, Store),
            Client ! {Qref, ok},
            Added;
        false ->
            Spid ! {add, Key, Value, Qref, Client},
            Store
    end.

lookup(Key, Qref, Client, MyKey, {Pkey, _,_}, {_, _,Spid}, Store) ->
    case key:between(Key , Pkey , MyKey) of 
        true ->
            Result = storage:lookup(Key, Store),
            Client ! {Qref, Result};
        false ->
            
            Spid ! {lookup, Key, Qref, Client}
    end.

notify({Nkey, Npid}, MyKey, Predecessor, Store) ->
        case Predecessor of
            nil ->
                Keep = handover(Store, MyKey, Nkey, Npid),
                NewP = {Nkey, monit(Npid), Npid},
                {NewP, Keep};
            {Pkey,Pref, _} ->
                case key:between(Nkey, Pkey, MyKey) of
                    true ->
                        Keep = handover(Store, MyKey, Nkey, Npid),
                        demonit(Pref),
                        NewP = {Nkey, monit(Npid),Npid},
                        {NewP, Keep};
                    false ->
                            {Predecessor, Store}
                end
        end.
        
handover(Store, MyKey, Nkey, Npid) ->
    {Keep, Leave} = storage:split(MyKey, Nkey, Store),
    Npid ! {handover, Leave},
    Keep.
   
stabilize(Pred, Next, MyKey, Successor) ->
   %% Consisteix en que el node envia request al successor, espera rebre un status i
   %% veure si es manté consistent.
   %io:format("---- STABILIZE. Pred: ~w Next: ~w Mykey: ~w Succesor: ~w ~n", [Pred, Next, MyKey, Successor]),

   %% TODO: Si mi sucesor no cambia, adopto a Next como Sucesor
   %% TODO: Si se mete un nuevo nodo entre yo y Succesor, devolver el Successor y Next correctos.
  {Skey, Sref, Spid} = Successor,
  case Pred of
      nil ->
          %%No té valor, per tant, informo de la meva existencia
          Spid ! {notify, {MyKey, self()}},
          {Successor, Next};
      {MyKey,_} ->
          %%M'apunta a mi i no cal fer-res
          {Successor, Next};
      {Skey, _} ->
           %%S'apunta a ell mateix, per tant notifico de la meva existencia
           Spid ! {notify, {MyKey, self()}},
          {Successor, Next};
      {Xkey, Xpid} ->
            case key:between(Xkey, MyKey, Skey) of
                true ->
                    %% El node es troba entre la nostra clau i la del successor acutal
                    %% per tant l'hem de prendre com el nostre nou successor.
                    self() ! stabilize,
                    demonit(Sref),
                    {{Xkey, monit(Xpid), Xpid}, {Skey, Spid}};
                false ->
                    Spid ! {notify, {MyKey, self()}},
                    {Successor, Next}
            end
    end.
    
stabilize({_, _, Spid}) ->
    Spid ! {request, self()}.

request(Peer, Predecessor, {Skey,_, Spid}) ->
    case Predecessor of
        nil ->
            Peer ! {status, nil, {Skey, Spid}};
        {Pkey, _, Ppid} ->
            Peer ! {status, {Pkey, Ppid}, {Skey, Spid}}
    end.

create_probe(MyKey, {_, _, Spid}, Store) ->
    Spid ! {probe, MyKey, [MyKey], erlang:monotonic_time()},
    io:format("Create probe ~w, Store: ~w ~n", [MyKey, length(Store)]).
	
remove_probe(MyKey, Nodes, T) ->
    T2 = erlang:monotonic_time(),
    Time = erlang:convert_time_unit(T2-T, native, millisecond),
    io:format("Received probe ~w in ~w ms Ring: ~w~n", [MyKey, Time, Nodes]).
	
forward_probe(RefKey, Nodes, T, {_, _, Spid}) ->
    Spid ! {probe, RefKey, Nodes, T},
    io:format("Forward probe ~w!~n", [RefKey]).

%% Added this functions in node3
monit(Pid) ->
	erlang:monitor(process, Pid).

demonit(nil) ->
	ok;

demonit(MonitorRef) ->
	erlang:demonitor(MonitorRef, [flush]).

	%% TODO: Añadir referencia a monit del predecesor y sucesor.
	%% TODO: Demonit el antiguo nodo cuando se adopta un nuevo nodo como sucesor o predecesor.

down(Ref, {_, Ref, _}, Successor, Next) ->
    %% TODO: ADD SOME CODE. Si muere Predecessor, pongo mi predecesor a nil.
	{nil, Successor, Next};

down(Ref, Predecessor, {_, Ref, _}, {Nkey, Npid}) ->
	%% TODO: ADD SOME CODE. Si muere Successor, Next pasa a ser mi Successor. Monit nuevo nodo
	%% y enviarnos stabilize a nosotros mismos. 
	Nref = monit(Npid),
	self() ! stabilize,
	{Predecessor, {Nkey, Nref, Npid}, nil}.
