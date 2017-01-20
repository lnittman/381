//
//  Meeting_room.h
//  0_project
//
//  Created by Luke Nittmann on 9/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef ROOM_H
#define ROOM_H

#include "Meeting.h"
#include "Utility.h"
#include <string>
#include <vector>

const char * const meeting_list_empty_c = "No meetings are scheduled\n";
const char * const room_list_empty_c = "List of rooms is empty\n";
const char * const meeting_time_conflict_c = "There is already a meeting at that time!\n";
const char * const meeting_participant_c = "This person is a participant in a meeting!\n";
const char * const bad_room_c = "Room number is not in range!\n";
const char * const room_exists_c = "There is already a room with this number!\n";
const char * const room_not_found_c = "No room with that number!\n";
const char * const meeting_not_found_c = "No meeting at that time!\n";
const char * const delete_all_meetings_c = "All meetings deleted\n";
const char * const delete_all_rooms_meetings_c = "All rooms and meetings deleted\n";

class Person;

class Room {

public:
    
    //constructor
    Room(int room_in);
    
    bool operator==(const Room& m) const;
    bool empty() const;
    
    //member access
    int get_room() const { return room_number; }
    size_t num_meetings() const { return meeting_list.size(); }
    void clear_meetings() { meeting_list.clear(); }
    
    //is time slot open?
    bool is_time_open(int time);
    
    //add and remove meetings
    void reschedule_in_meeting(Meeting meeting_in, int new_time);
    void add_meeting(int time, std::string topic);
    void remove_meeting(int time);
    void remove_individual_meeting(int time);
    
    //add and remove meeting participants
    void add_participant(int time, Person& p);
    void remove_participant(int time, Person& p);
    
    //iterator members
    std::vector<Meeting>::iterator begin();
    std::vector<Meeting>::iterator end();
    
private:
    
    int room_number;
    std::vector<Meeting> meeting_list;
};

using Room_list_t = std::vector<Room>;

void room_range_check(int room_in);
void clear_all_meetings(Room_list_t& room_list);
void clear_room_list(Room_list_t& room_list);
void print_lookup_meeting(Room_list_t::iterator& it, int time);
void print_individual_meeting(Meeting& meeting_it);
void print_individual_room(Room_list_t& room_list, int room_number);

bool is_meeting_list_full(Room_list_t::iterator& it);
bool is_room_list_full(Room_list_t& room_list);

int num_meetings(Room_list_t& room_list);
void is_meeting_participant(Room_list_t& room_list, const std::string& last_name);

//iterator check prototypes
void check_meeting_found(Room_list_t::iterator& it, int time);
void check_meeting_conflict(Room_list_t::iterator& it, int time);
void check_room_found(Room_list_t& room_list, Room_list_t::iterator& room_it);
void check_room_end(Room_list_t& room_list, Room_list_t::iterator& room_it);


#endif /* ROOM_H */
