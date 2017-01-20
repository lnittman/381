//
//  Meeting.h
//  0_project
//
//  Created by Luke Nittmann on 9/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef MEETING_H
#define MEETING_H

#include "Person.h"
#include <string>
#include <vector>

const char * const existing_participant_c = "This person is already a participant!\n";
const char * const not_a_participant_c = "This person is not a participant in the meeting!\n";

using std::string;

class Meeting {
    
public:
    
    //constructors
    Meeting(int time_in);
    Meeting(int time_in, std::string topic_in);
    
    bool operator==(const Meeting& m);
    
    //member access
    void set_time(int new_time) { time = new_time; }
    int get_time() const { return time; }
    std::string get_topic() const { return topic; }
    size_t num_participants() const { return participant_list.size(); }
    
    //add and delete participants from p_l
    void add_person(Person& p);
    void delete_person(Person& p);
    
    //iterator member fns
    std::vector<Person>::iterator begin();
    std::vector<Person>::iterator end();
    
private:
    
    int time;
    std::string topic;
    std::vector<Person> participant_list;
};

#endif /* MEETING_H */
