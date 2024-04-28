#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "HashMap.hpp"

int main () {
	using namespace std;
	using namespace std::chrono;
	using namespace pr;


	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	vector<pair<string, int>> dict;
	//size_t ret = 0;
	//vector<string> dict;
	pr::HashMap<string, int> hm(2000);
	


	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		//if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			//cout << nombre_lu << ": "<< word << endl;
		
		/*
		string ide = "";
		for (int i = 0; i < dict.size(); ++i){
			if(dict.data()[i] == word) ide = word;
		}

		if (ide == ""){
			dict.push_back(word);
			ret++;
		}
		ide = "";
		*/
		hm.put(word, 1);

		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	string occ[3] = {"war", "toto", "peace"};

	for(string word: occ){
		int* Count = hm.get(word);
		if (Count != nullptr) {
        	cout << "Mot: " << word << "Nb occurences: " << *Count << endl;
    	} else {
        	cout << "Mot: " << word << "Nb occurences: " << 0 << endl;
    	}

	}

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    //cout << "Found a total of " << nombre_lu << " words." << endl;
    //cout << "Nombre de mots différents : " << ret << endl;

	for (int i = 0; i<hm.size(); ++i){
		for (const auto& ent : hm.vechash(i)){ 
			dict.push_back(std::make_pair(ent.clef, ent.val));
			//cout << ent.clef << " : " << ent.val << endl;
		};
	};

	sort(dict.begin(), dict.end(), [](const std::pair<string, int> &x, const std::pair<string, int> &y)
	{
    return x.second > y.second;
	});

	std::cout << "myvector contains:";
  	for (int i = 0; i<10; ++i){
    	std::cout << dict[i].first << ' ' << endl;
	}
  	std::cout << '\n';






    return 0;
}

