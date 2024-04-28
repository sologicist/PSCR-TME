#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>

using namespace std;
int main(int argc, char ** argv){

    char ** part1;
    char ** part2;

    part1 = (char **) malloc( argc * sizeof(char *) );
    part2 = (char **) malloc( argc * sizeof(char *) );

    int i = 1;
    for (; i < argc; i++){
        if (strcmp(argv[i],"|")) {
            part1[i-1] = argv[i];
        }
            
        else{ 
            i++;
            break;
        };
    }
    part1[i] = nullptr;

    int k = 0;
    for (int j = i; j < argc; j++){
        part2[k] = argv[j];
        k++;
    }    
    
    int tubeDesc[2]; pid_t pid_fils;
    if (pipe (tubeDesc) == -1) {
        perror ("pipe");
        exit (1);
    }
    if ( (pid_fils = fork ( )) == -1 ){
        perror ("fork");
        exit (2);
    }
    if (pid_fils == 0) { //fils
        dup2(tubeDesc[1],STDOUT_FILENO);
        close (tubeDesc[1]); close (tubeDesc[0]);
    
        if (execv (part1[0], part1) == -1) { // /bin/cat
            perror ("execv"); exit (3);
        }


    } else { //pere
        if ( (pid_fils = fork ( )) == -1 ){
            perror ("fork");
            exit (2);
        }
        if (pid_fils == 0) { //fils
            dup2(tubeDesc[0],STDIN_FILENO);
            close (tubeDesc[0]);
            close (tubeDesc[1]);
            if (execv (part2[0], part2) == -1) { // /bin/wc
                perror ("execv2"); exit (3);
            }
        }

        wait(nullptr); wait(nullptr);
        
    }

    return (EXIT_SUCCESS);
}
