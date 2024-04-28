#include <sys/wait.h>
#include <unistd.h>
#include <ostream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include "rsleep.cpp"


using namespace std;

int PV = 100;


void handler(int sig){
    if (sig == SIGINT){
        PV--;
        cout << "PV restants : " << PV << " de : " << getpid() << endl;
    }

    if (PV == 0){
        cout << "Mort de : " << getpid() << endl;
        exit(1);
    }

}
void attaque (pid_t adversaire){
    signal(SIGINT, handler);
    if (kill(adversaire,SIGINT) == -1){
        cout << "Mort de : " << adversaire << endl;
        exit(0);
    }
    randsleep();
}

void defense(){
    signal(SIGINT,SIG_IGN);
}

void combat(pid_t adversaire){
    while(1){
        defense();
        attaque(adversaire);
    }
    
    
}


int main() {
    pid_t vador = getpid();
    pid_t luke = fork();
    srand(time(0));
    if (luke == 0) {
        combat(vador);
    } else {
        combat(luke);
    }
    return 0;
}