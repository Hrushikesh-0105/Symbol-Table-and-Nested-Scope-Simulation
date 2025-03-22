//Created by- Hrushikesh Musaloj (BT23CSE024)
#include<bits/stdc++.h>
#include <fstream>
#include "hashTable.h"
using namespace std;

typedef enum status_code_tag{Fail,Success,UndefinedScope,UndefinedVar,SyntaxError} status_code;

//A scope class contains pointer to the next outer scope and a symbol table (HashTable<string,string>)

#define FILENAME "code_file.txt"

class Scope{
    public:
    HashTable symbolTable;
    Scope* next;
    Scope(Scope* next){
        this->next=next;
    }
};


class ScopeList{
    private:
    Scope* head;
    public:
    ScopeList(){
        this->head=NULL;
    }
    status_code addScope(){
        status_code sc=Fail;
        Scope* newScope=new Scope(head);//setting the next pointer to head
        if(newScope!=NULL){
            sc=Success;
            head=newScope;
        }
        return sc;
    }
    status_code removeScope(){
        status_code sc=UndefinedScope;
        if(head!=NULL){
            Scope* scopeToBeRemoved=head;
            head=head->next;
            delete scopeToBeRemoved;
            sc=Success;
        }
        return sc;
    }
    status_code assignValue(string variableName,string value){
        status_code sc=UndefinedScope;
        if(head!=NULL){
            if((head->symbolTable).insertUpdate(variableName,value)){
                sc=Success;//if the insertion in symbol table is successful
            }
            else{
                sc=Fail;
            }
        }
        return sc;
    }

    status_code getValue(string variableName,string& value){
        status_code sc=UndefinedVar;
        bool found=false;
        Scope* currentScope=head;
        if(head==NULL){
            sc=UndefinedScope;
        }
        else{
            while(currentScope!=NULL && !found){
                if((currentScope->symbolTable).search(variableName,value)){
                    found=true;
                    sc=Success;
                }
                currentScope=currentScope->next;
            }
        }
        return sc;
    }

    int numberOfScopes(){
        int num=0;
        Scope* currentScope=head;
        while(currentScope!=NULL){
            num++;
            currentScope=currentScope->next;
        }
        return num;
    }

    ~ScopeList(){
        while(head!=NULL){
            removeScope();
        }
    }
};

void printError(int lineNumber,status_code type,string varName=""){
    switch(type){
        case UndefinedScope:{
            cout<<"Error: Line - "<<lineNumber<<" scope is undefined"<<endl;
        }
        break;
        case UndefinedVar:{
            cout<<"Error: Line - "<<lineNumber<<" variable '"<<varName<<"' is undefined"<<endl;
        }
        break;
        case SyntaxError:{
            cout<<"Error: Line - "<<lineNumber<<" syntax Error"<<endl;
        }
        break;
        default:{ 
            cout<<"Error: Line - "<<lineNumber<<" unexpected error occured"<<endl;
        }
    }
}

void printWords(vector<string> & words){
    cout<<"|";
    for(auto word:words){
        cout<<word<<"|";
    }
    cout<<endl;
}

bool decodeAndExecuteLine(ScopeList& programScope, vector<string> & words, int lineNumber){
    //after reading a line, it will decode it and perform the function
    //if any error occurs, it will return false to end the program
    //words will contain atleast one word, the lenght og the vector is checked before the function call
    status_code sc=Success;
    bool executed=true;
    int n=words.size();
    string varName="";//variable name if there is an undefined variable
    if(n>3){
        sc=SyntaxError;
        executed=false;
    }
    else{
        if(words[0]=="begin"){
            if(n!=1){
                sc=SyntaxError;
            }else{
                sc=programScope.addScope();
            }
        }
        else if(words[0]=="end"){
            if(n!=1){
                sc=SyntaxError;
            }else{
                sc=programScope.removeScope();
            }
        }
        else if(words[0]=="assign"){
            if(n!=3){
                sc=SyntaxError;
            }
            else{
                varName=words[1];
                string value=words[2];
                sc=programScope.assignValue(varName,value);
            }
        }
        else if(words[0]=="print"){
            if(n!=2){
                sc=SyntaxError;
            }
            else{
                varName=words[1];
                string value;
                sc=programScope.getValue(varName,value);
                if(sc==Success){
                    cout<<value<<endl;
                }
            }
        }
        else{
            sc=SyntaxError;
            executed=false;
        }
    }
    if(sc!=Success){
        printError(lineNumber,sc,varName);
        executed=false;
    }
    else{
        executed=true;
    }
    return executed;
}

void tokenizeLine(string line, vector<string>& words) {
    words.clear();
    int n = line.length();
    int i = 0;
    while (i < n) {
        while (i < n && (line[i] == ' ' || line[i] == '\r')) {  // \r is ascii 13, which appears in windows based text editor at end of line
            i++;
        }
        string word = "";
        while (i < n && (line[i] != ' ' && line[i] != '\r')) {
            word += line[i];
            i++;
        }
        if (!word.empty()) {
            words.push_back(word);
        }
    }
}

void startInterpreter(){
    ScopeList programScope;
    ifstream file(FILENAME);
    if(!file){
        cout<<"Couldn't open file."<<endl;
    }
    else{
        int lineNumber=0;
        string line;
        bool continueReading=true;
        vector<string> words;
        while(getline(file,line) && continueReading){
            lineNumber++;
            tokenizeLine(line,words);
            if(words.size()!=0){
                continueReading = decodeAndExecuteLine(programScope,words,lineNumber);
            }
        }
        if(continueReading && programScope.numberOfScopes()!=0){
            // if the scope is not closed then there should be an error
            printError(lineNumber,UndefinedScope);
        }
    }
}

int main(){
    startInterpreter();
}