-module(wait).
-export([hello/0]).

hello() ->
    receive
        X -> io:format("Oh, sorpresa! Un mensaje: ~s~n", [X])
    end.
    
