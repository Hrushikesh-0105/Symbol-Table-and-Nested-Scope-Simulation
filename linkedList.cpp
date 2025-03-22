#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    // cout<<"Deleting linked list"<<endl;
    Node* current = head;
    while (current) {
        Node* temp = current;
        // cout<<"Deleting: "<<temp->value<<endl;
        current = current->next;
        delete temp;
    }
}

bool LinkedList::insertUpdate(std::string key, std::string value) {
    bool sc=true;
    Node* current = head;
    bool keyFound=false;
    while (current != nullptr && !keyFound) {
        if (current->key == key) { 
            current->value = value;
            keyFound=true;
        }
        current = current->next;
    }
    if(!keyFound){
        Node* newNode = new Node(key, value);
        if(newNode==NULL){
            sc=false;
        }
        else{
            newNode->next = head;
            head = newNode;
        }
    }
    return sc;
}

bool LinkedList::search(std::string key, string &value) {
    Node* current = head;
    bool found=false;
    while (current && !found) {
        if (current->key == key) {
            value = current->value;
            found=true;
        }
        current = current->next;
    }
    return found;
}

void LinkedList::display() {
    Node* current = head;
    while (current) {
        std::cout << "[" << current->key << " : " << current->value << "] -> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}
