Q1. Il y'a 10 processus en tout.

main pid=8385
                pid=8386 ppid=8385 i:j 1:3
                            |
                        ---------
                        |       |
pid=8387 ppid=8386 k:j 1:0  pid=8388 ppid=8386 i:j 2:3
                                              |
                                          ---------
                                          |       |
                    pid=8390 ppid=8388 k:j 1:0  pid=8392 ppid=8388 i:j 3:3
                        |                                      |
        pid=8391 ppid=8388 k:j 2:0          -------------------------------------------
                                            |                  |                      |
                            
                    pid=8393 ppid=8392 k:j 1:0      pid=8394 ppid=8392 k:j 2:0      pid=8395 ppid=8392 k:j 3:0


q4.

if the call is interrupted by a signal handler, nanosleep() returns -1, sets errno to EINTR, and writes the remaining time into the structure pointed to by rem unless rem is NULL. On doit boucler pour continuer à dormir.


q5. Avec srand(time(0))



