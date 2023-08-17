

#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

hashNode::hashNode(string s){
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(){
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(string s, string v){
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v){
    if (currSize>=valuesSize){
        dblArray();
    }

    values[currSize] = v;
    currSize++;
}
void hashNode::dblArray(){
    string *tmpArr = new string[valuesSize*2];
    for (int i=0; i<valuesSize; i++){
        tmpArr[i]=values[i];
    }
    valuesSize = valuesSize*2;
    values = tmpArr;
}

string hashNode::getRandValue() {
	//Every key has a values array - an array of words that
	// follow that key in the text document.  You're going to
	//randomly select one of those words and return it.  That
	//will be the word that follows your key in your output
	//function, and it will also be the next key.
    if (currSize==0){
        return "";
    } else{
        return values[rand()%currSize];
    }

}
