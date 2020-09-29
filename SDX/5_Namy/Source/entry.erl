-module(entry).
-export([lookup/2, add/3, remove/2]).


% Busca en la tabla de entradas del server la entrada solicitada. Entrada -> (key-value) / si es un host {host,PID} si es otro server {domain, PID}
% keyfind(Key, N, TupleList) -> Tuple | false
lookup (Req, Entries) -> 
    case lists:keyfind(Req, 1, Entries) of
        false -> 
            unknown;
        {Req, Pid} -> 
            Pid
    end.

% Añade la entrada NAME en la lista de entradas del server.
% keystore(Key, N, TupleList1, NewTuple) -> TupleList2
add (Name, Entry, Entries) -> 
    lists:keystore(Name, 1, Entries, {Name, Entry}).
    

% Elimina la entrada NAME de la lista de entradas del server.
% keydelete(Key, N, TupleList1) -> TupleList2
remove (Name, Entries) -> 
    lists:keydelete(Name, 1, Entries).
    
