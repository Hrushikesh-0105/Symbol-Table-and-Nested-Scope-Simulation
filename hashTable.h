#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<string>
#include "linkedList.h"
using namespace std;

#define MAXSIZE 151

class HashTable{
    private:
    LinkedList hashArray[MAXSIZE];//array of linked lists
    int generateHash(string);
    public:
    bool insertUpdate(string,string);
    bool search(string,string&);
};

#endif