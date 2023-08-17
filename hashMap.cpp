#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
    hashfn = hash1;
    collfn = coll1;
    hashcoll = 0;
    collisions = 0;
    mapSize = 17;
    numKeys = 0;
    map =new hashNode*[mapSize];
    for(int i = 0; i<mapSize; i++){
        map[i]=NULL;
    }
}
void hashMap::addKeyValue(string k, string v) {
    // adds a node to the map at the correct index
    // based on the key string, and then inserts the
    // value into the value field of the hashNode
    int h = getIndex(k);

    float check = (float)numKeys/(float)mapSize;
    // Must check to see whether there's already a
    // node at that location. If there's nothing
    // there(it's NULL), add the hashNode with the
    // keyword and value.
    if(map[h]==NULL){
        map[h]= new hashNode(k,v);
        numKeys++;
    }
    // If the node has the same keyword, just add
    // the value to the list of values.
    else if(map[h]->keyword == k){
        map[h]->addValue(v);
    }
    // If the node has a different keyword, keep
    // calculating a new hash index until either the
    // keyword matches the node at that index's
    // keyword, or until the map at that index is
    // NULL, in which case you'll add the node
    // there.
    else{
    	int n;
    	if(collfn){
    		n =  coll1(h,collisions,k);
    		//collisions++;
    	}
    	else{
    		n = coll2(h,collisions,k);
    		//collisions++;
    	}


        if(map[n] == NULL){
            map[n] = new hashNode(k,v);
            numKeys++;
        }
        else if(map[n]->keyword == k){
            map[n]->addValue(v);
        }

    }
    // This method also checks for load, and if the
    // load is over 70%, it calls the reHash method
    // to create a new longer map array and rehash
    // the values
    //cout<<check<<endl;
    if(check > 0.7){
        reHash();
    }
}

int hashMap::getIndex(string k) {
	int i;
	//checks which hash function to use to find index
	if(hashfn){
		i = calcHash1(k);
	}
	else{
		i = calcHash2(k);
	}
	//Not a collision
	if(map[i]==NULL||map[i]->keyword==k){
		return i;
	}
	//collision
	else{
		if(collfn){
			return coll1(i,collisions,k);
		}
		else{
			return coll2(i,collisions,k);
		}
		hashcoll++;
	}
}
int hashMap::calcHash2(string k){
	int index, tmp = 0, len = k.length();
	for (int i=0; i<len; i++) {
		tmp += int(k[i]);
	}
	index = tmp%mapSize;
	return index;
}
int hashMap::calcHash1(string k){
	int len = k.length();
	    int hash = 0;
	    for(int i = 0; i < len; i++){
	        if (i < len/4){
	            hash += (int)k[i] * 4;
	        }else if(i > len/4 && i < len/2){
	            hash += (int)k[i] * 3;
	        }else {
	            hash += (int)k[i];
	        }
	    }
	    return hash%mapSize;
}
void hashMap::getClosestPrime() {
    for (int n = mapSize + 1; n < 2 * n - 2; n++) {
        if (isPrime(n)) {
            mapSize = n; //find the next largest prime and assign it to the mapSize
            break;
        }
    }
    }

void hashMap::reHash() {
    int h; //initialize index for hash index
    int oldSize = mapSize; //store the old map size
    getClosestPrime(); //size up the prime number
    hashNode **oldMap = map; //store the old map

    //create new map
    map = new hashNode*[mapSize];
    //initialize all values in map to NULL
    for (int i = 0; i < mapSize; i++) {
        map[i] = NULL;
    }

    //go through the old hashMap and rehash to new hashMap
    for (int i = 0; i < oldSize; i++) {
        if (oldMap[i] != NULL) {
            h = getIndex(oldMap[i]->keyword);
            map[h] = oldMap[i];
        }
    }
}

int hashMap::coll2(int h, int i, string k) {
	int a = h;

	while (map[a] != NULL) {
		if (k == map[a]->keyword) {
			break;
		}
		else {
			if (a != mapSize-1) {
				a += 1;
				//collisions++;
				//i++;
			}
			else {
				a = 0;
			}
		}
	}

	return a;
}
int hashMap::coll1(int h, int i, string k) {

	while(map[h]!=NULL){
		if(map[h]->keyword==k){
			break;
		}
		//i++;
		collisions++;
		h = (h+(collisions*collisions))%mapSize;
	}
	return h;
}
void hashMap::printMap() {
    cout << "In printMap()" << endl;
    for (int i = 0; i < mapSize; i++) {
        //cout << "In loop" << endl;
        if (map[i] != NULL) {
            cout << map[i]->keyword << ": ";
            for (int j = 0; j < map[i]->currSize;j++) {
                cout << map[i]->values[j] << ", ";
            }
            cout << endl;
        }
    }
}
bool hashMap::isPrime(int n) {
    //prime numbers must be non-negative 0 isn't prime
    if (n <= 0) {
        return false;
    }
    bool b = true;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            b = false;
            break;
        }
    }
    return b;
}
