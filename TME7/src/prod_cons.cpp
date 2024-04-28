#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <fcntl.h>


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

vector<pid_t> tokill;
void killshem (int) {
		for (pid_t p : tokill) {
			kill(p, SIGINT);
		}
	}

int main () {
	size_t shmsize = sizeof(Stack<char>);

	int fd;
	void * addr;

	bool useAnonymous = false;
	if (useAnonymous) {
		addr = mmap(nullptr /*Laisser le noyau choisir*/, 
		shmsize /*Taille de la zone mémoire*/, 
		PROT_READ /*On peut lire dans la zone mémoire*/ | 
		PROT_WRITE /*On peut écrire dans la zone mémoire*/, 
		MAP_SHARED /*Toutes les modifs sont visible par les co MAP_SHARED*/ |
		MAP_ANONYMOUS /*La  projection  n'est supportée par aucun fichier*/,
		-1 /*fd = -1, anonyme*/, 
		0 /*Début offset*/);

		if (addr == MAP_FAILED) {
			perror("mmap anonymous");
			exit(1);
		}
	} else {
		fd = shm_open("/myshm",
			O_CREAT /*Create the shared memory object if it does not exist*/ |
			O_EXCL /*Si O_CREAT et que le fichier existe, renvoie une erreur*/ |
			O_RDWR /*Open the object for read-write access*/,
			0666 ) /*user:aucun droit, groupe:rw, other:rw, all:rw */;

		if (fd < 0) {
			perror("shm_open");
			return 1;
		}
		addr = mmap(nullptr, shmsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (addr == MAP_FAILED) {
			perror("mmap anonymous");
			exit(1);
		}
	}

	Stack<char> * s = new (addr) Stack<char>(); //new à l'adresse addr


	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}
	else{
		tokill.push_back(pc);
	}

	signal(SIGINT, killshem);

	
	
	wait(0);
	wait(0);

	s->~Stack();
	if (munmap(addr,shmsize) != 0) {
		perror("munmap");
		exit(1);
	}

	if (!useAnonymous) {
		if (shm_unlink("/myshm") != 0) {
			perror("sem unlink");
		}
	}

	return 0;
}

