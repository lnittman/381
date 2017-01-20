//
//  Meeting.cpp
//  0_project
//
//  Created by Luke Nittmann on 9/9/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Meeting.h"
#include "Person.h"
#include "Utility.h"
#include <algorithm>

using std::string;

Meeting::Meeting(int time_in) : time(time_in) {}

Meeting::Meeting(int time_in, std::string topic_in) : time(time_in), topic(topic_in) {}

bool Meeting::operator==(const Meeting& m) {
    
    return (m.time == time);
}

//add person to participant list
void Meeting::add_person(Person& p) {
    
    auto part_it = find(begin(), end(), p);
    
    if (part_it != end())
        throw Error(existing_participant_c);
     
    participant_list.push_back(p);
}

//remove person from participant list
void Meeting::delete_person(Person& p) {
    
    auto part_it = find(begin(), end(), p);
    
    if (part_it == end())
        throw Error(not_a_participant_c);
    
    participant_list.erase(part_it);
}

//iterator members
std::vector<Person>::iterator Meeting::begin() {
    
    return participant_list.begin();
}

std::vector<Person>::iterator Meeting::end() {
    
    return participant_list.end();
}
