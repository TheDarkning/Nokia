//Author:    Zhamshitov Rinat
//Date:      2022.03.22
//Title:     PhoneBook

#include <bits/stdc++.h>
#include "phonebook.h"

using namespace std;

//#define NORMAL_MODE
#ifdef NORMAL_MODE

class Menu{
    public:
        Menu(){};
        void Run();
    private:
        void searchSub();
        void searchNum();
        int MenuPrint();
        void add();
        void del();
        phonebook list;
};

int main(){
    Menu menu;
    menu.Run();
}

void Menu::Run(){
    int v;
    do{
        v = MenuPrint();
        switch(v){
            case 1:
                searchSub();
                break;
            case 2:
                searchNum();
                break;
            case 3:
                add();
                break;
            case 4:
                del();
                break;
            default:
                cout<<"\nGoodbye!\n";
                break;
        }
    }while(v != 0);
}

int Menu::MenuPrint(){
    int choice;
    cout<<"\n****************************************\n";
    cout<<"0. Exit\n";
    cout<<"1. Search by phone number function\n";
    cout<<"2. search by subscriber function\n";
    cout<<"3. Add new Person\n";
    cout<<"4. Delete Person\n";
    cout<<"****************************************\n";
    
    cin >> choice;

    return choice;
}

void Menu::searchSub(){
    try{
        cout << "Give a phonenumber: ";
        int nm;
        cin >> nm;
        cout << list.getSubcriber(nm);
    }
    catch(phonebook::NotFound err){
        cerr<<"Subcriber does not exist!\n";
    }
}


void Menu::searchNum(){
    try{
        cout << "Give a name: ";
        string nam;
        cin >> nam;
        vector<int> ans;
        list.getPhone(nam, list, ans);
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i]<< ' ';
        }
        ans.clear();
    }
    catch(phonebook::NotFound err){
        cerr<<"Subcriber does not exist!\n";
    }
}

void Menu::add(){
    try{
        Person p;
        cin >> p;
        list.set(p);
        cout<<"Success!\n"<<endl;
    }
    catch(phonebook::AlreadyExist err){
        cerr<<"Insert is unsuccessful. The number already exists!\n";
    }
}

void Menu::del(){
    try{
        Person p;
        cin >> p;
        list.Delete(p);
        cout<<"Success!\n"<<endl;
    }
    catch(phonebook::NotFound err){
        cerr<<"Removing is unsuccessful, the Number or Name does not exist!\n";
    }
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "phonebook.h"

TEST_CASE("Adding","PhoneBook")
{
    phonebook list;
    Person p1("a", 123); Person p2("b", 234);

    list.set(p2);
    CHECK( list.getSubcriber(p2.number) == p2.name );

    list.set(p1);
    vector <int> numb;
    list.getPhone(p1.name, list, numb);
    CHECK( numb[0] == p1.number ); 
}

TEST_CASE("Delete","PhoneBook")
{
    Person p1("a", 123); Person p2("b", 234); Person p3("c", 345); Person p4("d", 456);
    SECTION("erase first")
    {
        phonebook list;

        list.set(p2);
        list.set(p3);
        list.set(p1);

        list.Delete(p1);
        CHECK(list.getSubcriber(p2.number) == p2.name); 
        CHECK_THROWS(list.getSubcriber(p1.number)); 
    }
    SECTION("erase last")
    {
        phonebook list;

        list.set(p2);
        list.set(p3);
        list.set(p1);

        list.Delete(p3);
        CHECK(list.getSubcriber(p1.number) == p1.name); 
        CHECK_THROWS(list.getSubcriber(p3.number));
    }
    SECTION("erase middle")
    {
        phonebook list;

        list.set(p2);
        list.set(p3);
        list.set(p1);

        list.Delete(p2);
        CHECK(list.getSubcriber(p3.number) == p3.name); 
        CHECK_THROWS(list.getSubcriber(p2.number));
    }
}

TEST_CASE("exceptions","PhoneBook")
{
    Person p1("a", 123); Person p2("b", 234); Person p3("c", 345); Person p4("d", 123); Person p5("e", 654);
    phonebook list;
    CHECK_THROWS(list.Delete(p2));
    list.set(p4); list.set(p2); list.set(p3);
    CHECK_THROWS(list.set(p3));
    CHECK_THROWS(list.set(p2));
    CHECK_THROWS(list.set(p1));
    CHECK_THROWS(list.getSubcriber(p5.number));
}

#endif