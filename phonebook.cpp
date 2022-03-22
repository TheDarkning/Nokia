#include <iostream>
#include <iomanip>
#include "phonebook.h"

using namespace std;



/// Getters (Search)
string phonebook::getSubcriber(int num){ 
    pair<bool, int> out = Search(num); /// bool -> is there such number, int -> index of number
    if (out.first){
        return subscribers[out.second].name;
    }
    else{
        throw NotFound();
    }
}

void phonebook::getPhone(string name, phonebook ls, vector<int> &ans){
    for(int i = 0; i < subscribers.size(); i++){
        if(name == ls.getSubcriber(subscribers[i].number)){
            for(int j = 0; j < subscribers.size(); j++)
                ans.push_back(subscribers[i].number);
            break;
        }
    }
    if(!ans.size()){
        throw NotFound();
    }
}

/// Setter

/*
    I am inserting Person to sorted record;
    to be able to implement binary search 
    for faster get the data
*/
void phonebook::set(Person a){
    pair<bool, int> out = Search(a.number); /// bool -> is there such number, int -> index of number

    if (!out.first){
        subscribers.resize(subscribers.size() + 1);
        for (int i = subscribers.size() - 2; i >= out.second; i--){
            subscribers[i + 1] = subscribers[i]; // moving everything from the right size to one step right
        }
        subscribers[out.second] = a; // adding new Person
    }
    else{
        throw AlreadyExist();
    }
}

//Deletting
void phonebook::Delete(Person a){
    
    std::pair<bool, int> out = Search(a.number);
    
    if (out.first){
        for (unsigned int i = out.second + 1; i < subscribers.size(); i++){
            subscribers[i - 1] = subscribers[i]; // moving everything from the right size to one step left
        }
        subscribers.pop_back(); /// and deleting last element
    }
    else{
        throw NotFound();
    }
}

// binary search
pair<bool, int> phonebook::Search(int num) const{ 
    bool l = false;
    int lb = 0;
    int ub = subscribers.size()-1;
    int ind;

    while (!l && lb <= ub){
        ind = (lb + ub) / 2;
        if (subscribers[ind].number > num) { ub = ind - 1; }
        else if (subscribers[ind].number < num) { lb = ind + 1; }
        else { l = true; }
    }

    if (!l){
        ind = lb;
    }
    return pair<bool,int> (l, ind); /// l -> is there such number, ind -> index of number
}
