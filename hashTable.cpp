#include "hashTable.h"

int HashTable :: generateHash(string s) {
    const int mod = MAXSIZE;//defined in hashtable.h
    uint32_t hashValue=2166136261u;
    int n=s.length();
    for(int i=0;i<n;i++){
        hashValue ^= (unsigned char)s[i];
        hashValue *= 16777619;  
    }
    return hashValue % mod;
}

bool HashTable::insertUpdate(string key ,string value){
    int hashValue=generateHash(key);
    return hashArray[hashValue].insertUpdate(key,value);
}

bool HashTable::search(string key,string& value){
    int hashValue=generateHash(key);
    return hashArray[hashValue].search(key,value);
}