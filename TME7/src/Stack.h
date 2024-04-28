#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t mutex;
	sem_t pushs;
	sem_t pops;
public :
	Stack () : sz(0) { 
		sem_init(&mutex, 1, 1);
		sem_init(&pushs, 1, STACKSIZE);
		sem_init(&pops, 1, 0);
		memset(tab, 0, sizeof(tab)) ;
	}

	T pop () {
		// bloquer si vide
		sem_wait(&pops);
		sem_wait(&mutex);
		T toret = tab[--sz];
		sem_post(&mutex);
		sem_post(&pushs);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&pushs);
		sem_wait(&mutex);
		tab[sz++] = elt;
		sem_post(&mutex);
		sem_post(&pops);
	}

	~Stack() {
		sem_destroy(&mutex);
		sem_destroy(&pushs);
		sem_destroy(&pops);
	}


};

}
