#include<iostream>
#include<string>

using namespace std;

const int SIZE = 10;

class Word{
public:
    Word *next;
    string w,m;
    Word(){
        this->next = nullptr;
        this->w = "";
        this->m = "";
    }
    Word(string word,string meaning ){
        this->next = nullptr;
        this->w= word;
        this->m = meaning;
    }
};

class Dictionary{
private:
    Word** arr;
public:
    Dictionary(){
        arr = new Word*[SIZE];
        for (int i=0;i<SIZE;i++){
            arr[i] = nullptr;
        }
    }

    int getHash(string word) {
        int hash = 0;
        for (char c : word) {
            hash += c; 
        }
        return hash % SIZE;
    }


    void insert(string word,string meaning){
        int index = getHash(word);

        Word* newword = new Word(word,meaning);
        if (arr[index]==nullptr){
            arr[index] = newword;
        }
        else{
            newword->next = arr[index];
            arr[index] = newword;
        }
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            cout << "Bucket " << i << ": ";
            Word* temp = arr[i];
            while (temp != nullptr) {
                cout << temp->w<< "->";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void search(string searchWord){
        cout<<endl;
        int index = getHash(searchWord);
        Word *temp = arr[index];
        bool found = 0;

        while (temp!=nullptr){
            if (temp->w==searchWord){
                cout<<temp->w<<": "<<temp->m<<endl;
                found = 1;
                break;
            }
            temp = temp->next;
        }
        
        if (!found) {
            cout<<"The word "<<searchWord<<" could not be found"<<endl;
        }
    }
};

int main(){
    Dictionary d;
    d.insert("apple","a type of fruit");
    d.insert("red","a colour");
    d.insert("loud","having a strong sound");
    d.insert("fast","moving quickly");
    d.insert("cold","having a low temperature");
    d.insert("potato","a type of root vegetable");
    d.insert("orange","a colour;a fruit");

    d.display();
    d.search("apple");
    d.search("orange");
    d.search("rat");
    return 0;
}