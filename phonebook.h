#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <vector>
#include <iostream>

struct Person{
    ///public attributes
    std::string name;
    int number;

    ///constructors
    Person() {}
    Person(std::string name, int number): name(name), number(number) {}

    /// Operator overload
    friend std::istream& operator>>(std::istream& s, Person& e){
        std::cout << "Enter name: ";
        s >> e.name;
        std::cout << "Enter phonenumber: ";
        s >> e.number;
        return s;
    }
    friend std::ostream& operator<<(std::ostream& s, const Person& e){
        s << "(" << e.name << ", " << e.number << ")";
        return s;
    }
    bool operator == (const Person& b){
        return (name == b.name && number == b.number);
    }
};

class phonebook{
    public:
        class NotFound : public std::exception{};
        class AlreadyExist : public std::exception{};

        /// Constructors
        
        //phonebook();
        
        /// Getters (Search)
        std::string getSubcriber(int num);
        void getPhone(std::string name, phonebook ls, std::vector<int> &ans);

        /// Setter
        void set(Person a);

        //Deletting
        void Delete(Person a);

    private:
        /// Private attributes
        std::vector<Person> subscribers;
        std::vector<std :: vector <std::pair<int, std::string>>> phonenumbers;

        std::pair<bool, int> Search(int num) const;
};

#endif