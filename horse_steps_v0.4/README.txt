KNIGHT'S TOUR problem

To build use Makefile.
Program takes two parameters - beginning position of knight by x and y.
So
./main 1 2
will set knight at position 2 by horizontal and 3 by vertical.
By default the size of board is 15x15.

This problem is about to find a sequence of moves of a knight on 
chessboard so knight visits every square only once.

This is version 0.4 (so it is the final version).
This version uses Warnsdorff's rule. Shortly - choose next step so 
that for this square number of possible squares to further 
move is lowest.
This rule works almost perfect, also for big boards 
(for 30x30 board calculation took about 7 seconds).
For board 15x15 result returns after less then 1 (one) second.

Previous version was just simple brut force, 
and works very, very, VERY slow.
