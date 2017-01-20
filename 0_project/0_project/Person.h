//
//  Person.h
//  0_project
//
//  Created by Luke Nittmann on 9/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

const char * const person_exists_c = "There is already a person with this last name!\n";
const char * const name_not_found_c = "No person with that name!\n";
const char * const people_list_empty_c = "List of people is empty\n";
const char * const delete_all_persons_c = "All persons deleted\n";

class Person {
    
public:
    
    //constructors
    Person(std::string last_in);
    Person(std::string first_in, std::string last_in, std::string phone_in);
    
    bool operator==(const Person& p);
    void print(std::ostream& os) const;
    std::string get_last() const { return last_name; }
    
private:
    
    std::string first_name;
    std::string last_name;
    std::string phone_number;
};

using Person_list_t = std::vector<Person>;

void check_person_found(Person_list_t& person_list, Person_list_t::iterator& it);
void check_person_end(Person_list_t& person_list, Person_list_t::iterator& it);
void check_load_person(Person_list_t& person_list, Person_list_t::iterator& it);

bool is_person_list_full(Person_list_t& person_list);
void print_person_list(std::ostream& os, Person_list_t& person_list);
void clear_person_list(Person_list_t& person_list);


#endif /* PERSON_H */
