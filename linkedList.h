#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

struct Node {
    string key;
    string value;
    Node* next;

    Node(string k, string v) : key(k), value(v), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();
    bool insertUpdate(string key, string value);
    bool search(string key, string &value);
    void display();
};

#endif 
