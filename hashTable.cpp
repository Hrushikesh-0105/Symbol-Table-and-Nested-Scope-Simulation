#include "hashTable.h"

int HashTable :: generateHash(string s) {
    int n=s.length();
    const int mod = MAXSIZE;//defined in hashtable.h
    int p=31;
    int prod=1;
    int hashValue=0;
    for(int i=0;i<n;i++){
        hashValue=(hashValue+((int)s[i]) *prod)%mod;
        prod=(prod*p)%mod;
    }
    //prod ensures "acb" and "abc" will not get same hash value
    return hashValue;
}

bool HashTable::insertUpdate(string key ,string value){
    int hashValue=generateHash(key);
    return hashArray[hashValue].insertUpdate(key,value);
}

bool HashTable::search(string key,string& value){
    int hashValue=generateHash(key);
    return hashArray[hashValue].search(key,value);
}