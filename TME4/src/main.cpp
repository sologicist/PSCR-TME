#include <chrono>
#include <thread>
#include "Banque.h"
#include <iostream>

using namespace std;
using namespace pr;

void work(Banque &bank){
	for(int it = 0; it < 1000; ++it){
		int i = (rand() % bank.size());
		int j = (rand() % bank.size());
		int m = 1 + (rand() % 100);
		bank.transfert(i, j, m);
		int t = (rand() % 21);
		//this_thread::sleep_for(chrono::milliseconds(t));
	}
}

const int NB_THREAD = 10;
const int NB_COMPTE = 10;
int main () {
	vector<thread> threads;
	vector<thread> comptables;

	Banque bank(NB_COMPTE, 500);
	// TODO : creer des threads qui font ce qui est demandé
	for(int i = 0; i < NB_THREAD; ++i){
		threads.emplace_back(work, ref(bank));	
		comptables.emplace_back(&Banque::comptabiliser, ref(bank), bank.size()*500);
	}

	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	cout << bank.comptabiliser(bank.size()*500) << endl; 

	return 0;
}
