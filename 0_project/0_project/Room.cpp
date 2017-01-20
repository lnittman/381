//
//  Room.cpp
//  0_project
//
//  Created by Luke Nittmann on 9/9/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Room.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>

using std::cin; using std::cout;

//constructor
Room::Room(int room_in) : room_number(room_in) {}

//equality operator
bool Room::operator==(const Room& m) const {
    
    return (m.room_number == room_number) ? true : false;
}

bool Room::empty() const {
    
    return (meeting_list.size() == 0);
}

//is time slot taken?
bool Room::is_time_open(int time) {
    
    if (find(begin(), end(), Meeting(time)) == end()) {
        
        return true;
    }
    
    return false;
}

//change time of new Meeting copy and add to meeting list
void Room::reschedule_in_meeting(Meeting meeting_in, int new_time) {
    
    meeting_in.set_time(new_time);
    meeting_list.push_back(meeting_in);
}

//add meeting to meeting list
void Room::add_meeting(int time, std::string topic) {
    
    meeting_list.push_back(Meeting(time, topic));
}

//remove meeting from meeting list
void Room::remove_meeting(int time) {
    
    auto it = find(begin(), end(), Meeting(time));
    
    if (it != meeting_list.end()) {
        
        meeting_list.erase(it);
    }
}

//add participant to meeting participant list
void Room::add_participant(int time, Person& p) {
    
    auto meeting_it = find(begin(), end(), Meeting(time));
    meeting_it->add_person(p);
}

//remove participant from meeting participant list
void Room::remove_participant(int time, Person& p) {
    
    auto meeting_it = find(begin(), end(), Meeting(time));
    meeting_it->delete_person(p);
}

//iterator members
std::vector<Meeting>::iterator Room::begin() {
    
    return meeting_list.begin();
}

std::vector<Meeting>::iterator Room::end() {
    
    return meeting_list.end();
}

//check if read room number is in proper range
void room_range_check(int room_in) {
    
    if (room_in < 1)
        throw Error(bad_room_c);
}

//clear every room's meeting list
void clear_all_meetings(Room_list_t& room_list) {
    
    for (auto& room_idx : room_list) {
        
        room_idx.clear_meetings();
    }
    
    cout << delete_all_meetings_c;
}

void clear_room_list(Room_list_t& room_list) {
    
    room_list.clear();
    cout << delete_all_rooms_meetings_c;
}

//find meeting in room by time, and print it
void print_lookup_meeting(Room_list_t::iterator& it, int time) {
    
    auto meeting_it = find(it->begin(), it->end(), Meeting(time));
    print_individual_meeting(*meeting_it);
}

void print_individual_meeting(Meeting& meeting_in) {
    
    cout << "Meeting time: " << meeting_in.get_time() << ", Topic: " << meeting_in.get_topic() << "\nParticipants:";
    
    if (meeting_in.num_participants()) {
        
        cout << "\n";
        sort(meeting_in.begin(), meeting_in.end(), person_sort_comp);
        
        for (auto& participants_idx : meeting_in) { //print person info for each participant
            
            participants_idx.print(cout);
        }
    } else {    //No participants for the meeting
        
        cout << " None\n";
    }
}

void print_individual_room(Room_list_t& room_list, int room_number) {
    
    auto room_it = find(room_list.begin(), room_list.end(), Room(room_number));
    check_room_found(room_list, room_it);
    
    cout << "--- Room " << room_number << " ---\n";
    
    if (is_meeting_list_full(room_it)) {
        
        sort(room_it->begin(), room_it->end(), meeting_sort_comp);
        
        for (auto& meeting_it : *room_it) {
            
            print_individual_meeting(meeting_it);
        }
    }
}

bool is_meeting_list_full(Room_list_t::iterator& room_it) {
    
    if (room_it->empty()) {
        
        cout << meeting_list_empty_c;
        return false;
    }
    
    return true;
}

bool is_room_list_full(Room_list_t& room_list) {
    
    if (room_list.empty()) {
        
        cout << room_list_empty_c;
        return false;
    }
    
    return true;
}

//returns the total number of scheduled meetings
int num_meetings(Room_list_t& room_list) {
    
    int num = 0;
    
    for (auto& room_it : room_list) {
        
        num += room_it.num_meetings();
    }
    
    return num;
}

//checks if an individual is a participant in any meeting
void is_meeting_participant(Room_list_t& room_list, const string& last_name) {
    
    for (auto& room_it : room_list) {    //foreach room
        
        for (auto& meeting_it : room_it) {   //foreach meeting
            
            if (find(meeting_it.begin(), meeting_it.end(), Person(last_name)) != meeting_it.end()) {
                //is person in participant list?
                
                throw Error(meeting_participant_c);
            }
        }
    }
}

//does meeting exist at specified time in this room?
void check_meeting_found(Room_list_t::iterator& it, int time) {
    
    if (it->is_time_open(time))
        throw Error(meeting_not_found_c);
}

//is there a meeting conflict at specified time in this room?
void check_meeting_conflict(Room_list_t::iterator& it, int time) {
    
    if (!it->is_time_open(time))
        throw Error(meeting_time_conflict_c);
}

//is room in room list?
void check_room_found(Room_list_t& room_list, Room_list_t::iterator& room_it) {
    
    if (room_it == room_list.end())
        throw Error(room_not_found_c);
}

//does room already exist?
void check_room_end(Room_list_t& room_list, Room_list_t::iterator& room_it) {
    
    if (room_it != room_list.end())
        throw Error(room_exists_c);
}


