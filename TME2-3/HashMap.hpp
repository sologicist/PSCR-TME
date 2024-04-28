#include <algorithm>
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <forward_list>

namespace pr {
using namespace std;


template<typename K, typename V>
class HashMap{
	public:
	struct Entry{
		const K clef;
		V val;
		Entry(const K c, V v) : clef(c), val(v) {}
	};

    class Iterator{
        
        private:
            size_t index;
            typename std::forward_list<Entry>::iterator it;
            vector<forward_list<Entry>> &buckets;
        
		public:

            Iterator(vector<forward_list<Entry>> &buckets, size_t index, typename std::forward_list<Entry>::iterator it) :index(index), buckets(buckets), it(it) {}

            Entry& operator*(){
                return *it;
            }

            Iterator& operator++(){
                if(++it == buckets[index].end()){
                    while(buckets[index++].empty()){
					
					}
					if(index == (buckets.size())){	
							return *this;
					}
					else{
						it = buckets[index].begin();
					}	
                }
                return *this;
            }

            bool operator!=(Iterator other){
                return (it != other.it) | (index != other.index);
            }

			
			
    };
	private:
	size_t sz;
	size_t nb_elem;
	

	public:
	vector<forward_list<Entry>> ptr;
	HashMap(int size) : ptr(size), sz(size), nb_elem(0){};

	forward_list<Entry>& vechash(int i) {
		return ptr[i];
	}

	V* get(const K & key){
		size_t h = std::hash<K>()(key);
		size_t target = h%(ptr.size());
		if(!ptr[target].empty()){
			for (Entry &ent : ptr[target]){
				if(ent.clef == key){
					return &ent.val;
				}
			}
		}
		return nullptr;

	};

	Entry* getEntry(const K & key){
		size_t h = std::hash<K>()(key);
		size_t target = h%(ptr.size());
		if(!ptr[target].empty()){
			for (Entry &ent : ptr[target]){
				if(ent.clef == key){
					return &ent;
				}
			}
		}
		return nullptr;

	};

	bool put (const K & key, const V & value){
		int* aux = get(key);
		
		if (aux){
			Entry *e = getEntry(key);
			(*e).val++;
			nb_elem++;
			return true;
		}
		
		size_t h = std::hash<K>()(key);
		size_t target = h%(ptr.size());
		ptr[target].emplace_front(Entry(key, value));
		nb_elem++;
		return false;

	};

	size_t nb_elements() const {
		return nb_elem;

	};

	size_t size() const {
		return ptr.size();

	};

	Iterator begin(){
		if (sz == 0) return end();

		size_t index = 0;
		for(;index < sz; ++index){
			if(!ptr[index].empty()){
				break;  
			}
		}
		return Iterator(ptr, index, ptr[index].begin());
	}
	
	Iterator end(){
		return Iterator(ptr, sz, ptr[sz-1].end());
	}

	 ~HashMap(){
		for (int i = 0; i<sz; ++i){
			ptr[i].clear();
		}
		ptr.clear();
	}



 };


};


