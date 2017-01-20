//
//  Person.cpp
//  0_project
//
//  Created by Luke Nittmann on 9/9/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Person.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>

using namespace std;

Person::Person(string last_in) : last_name(last_in) {}

Person::Person(string first_in, string last_in, string phone_in) :
    first_name(first_in), last_name(last_in), phone_number(phone_in) {}

bool Person::operator==(const Person& p) { return p.get_last() == last_name ? true : false; }

void Person::print(ostream& os) const {
    
    os << first_name << " " << last_name << " " << phone_number << "\n";
}

//check if person exists
void check_person_found(Person_list_t& person_list, Person_list_t::iterator& person_it) {
    
    if (person_it == person_list.end())
        throw Error(name_not_found_c);
}

//check for a name conflict with an existing person
void check_person_end(Person_list_t& person_list, Person_list_t::iterator& person_it) {
    
    if (person_it != person_list.end())
        throw Error(person_exists_c);
}

//check if individual with last_name loaded from file is in the person_list loaded from the same file
void check_load_person(Person_list_t& person_list, Person_list_t::iterator& person_it) {
    
    if (person_it == person_list.end())
        throw Load_error();
}

bool is_person_list_full(Person_list_t& person_list) {
    
    if (person_list.empty()) {
        
        cout << people_list_empty_c;
        return false;
    }
    
    return true;
}

void print_person_list(ostream& os, Person_list_t& person_list) {
    
    sort(person_list.begin(), person_list.end(), person_sort_comp);
    
    for (auto& person_it : person_list) {
        
        person_it.print(os);
    }
}

void clear_person_list(Person_list_t& person_list) {
    
    person_list.clear();
    cout << delete_all_persons_c;
}
