#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "HashMap.hpp"
#include <unordered_map>

namespace prmain {
using namespace std;

template<typename iterator>
size_t count (iterator begin, iterator end){
		size_t count = 0;
		while(begin != end){
			++begin; ++count;
		}
		return count;
};
	
	
template<typename iterator, typename T>
	size_t count_if_equal(iterator begin, iterator end, const T &val){
		size_t count = 0;
		while(begin != end){
			if(*begin == val) ++count;
			++begin;
		}
		return count;
};
}


int main () {
	using namespace std;
	using namespace std::chrono;
	using namespace pr;
	using namespace prmain;


	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	vector<pair<string, int>> dict;
	//size_t ret = 0;
	//vector<string> dict;
	unordered_map<string, int> otherHashMap(2000);
	


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
		auto val = otherHashMap.find(word); 
		if (val != otherHashMap.end()){
			val->second++;
		}

		otherHashMap.insert({word, 1});

		nombre_lu++;
	}
	input.close();

	unordered_map<int,forward_list<string>> sortedUM(40000);
	for ( auto it = otherHashMap.begin(); it != otherHashMap.end(); ++it ){
		dict.push_back(make_pair(it->first, it->second));
	}
	

	cout << "Finished Parsing War and Peace" << endl;


	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

	/*for (int i = 0; i<hm.size(); ++i){
		for (const auto& ent : hm.vechash(i)){ 
			dict.push_back(std::make_pair(ent.clef, ent.val));
			//cout << ent.clef << " : " << ent.val << endl;
		};
	};*/


    cout << "count : " << count(dict.begin(), dict.end()) << " words." << endl;
    //cout << "Nombre de mots différents : " << ret << endl;

	/*for (auto it = otherHashMap.begin() ; it != otherHashMap.end(); ++it){
			dict.push_back(std::make_pair(it.first, it.second));
			cout << it.first << " : " << it.second << endl;
			cout << dict.size() << endl;
	};*/


	
	cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Found a total of " << nombre_lu << " words." << endl;


    return 0;
}

