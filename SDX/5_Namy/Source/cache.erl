-module(cache).
-export([lookup/2, add/4, remove/2]).

% busca una entrada en la cache y devueve:
% uknown (si no está), 
% invalid (si está caducada),
% reply (si la encuentra y está válida).
% consultar temps actual i convertirlo a segons (trobarlo en una altre part del codi).
% Now = erlang:monotonic_time(), Expire = erlang:convert_time_unit(Now, native, second) + TTL
lookup (Name, Cache) ->
    case lists:keyfind(Name, 1, Cache) of
        false -> 
            unknown;
        {Name, Reply, Expire} -> 
            Now = erlang:monotonic_time(),
            TActual = erlang:convert_time_unit(Now, native, second),
            case TActual < Expire of 
                true ->
                    Reply;
                false ->
                    invalid
            end
    end.

% Reply es el PID
% añade la entrada NAME a la cache.
add (Name, Expire, Reply, Cache) ->
    lists:keystore(Name, 1, Cache, {Name, Reply, Expire}).

% elimina la entrada NAME de la cache.
remove (Name, Cache) -> 
    lists:keydelete(Name, 1, Cache).
