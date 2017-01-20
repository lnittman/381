//
//  main.cpp
//  0_project
//
//  Created by Luke Nittmann on 9/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Room.h"
#include "Meeting.h"
#include "Person.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

//information message constants
const char * const cmd_prompt_c = "\nEnter command: ";
const char * const quit_message_c = "Done\n";

//error constants
const char * const unrecognized_cmd_c = "Unrecognized command!\n";
const char * const meeting_list_nonempty_c = "Cannot clear people list unless there are no meetings!\n";
const char * const bad_file_c = "Could not open file!\n";
const char * const bad_data_c = "Invalid data found in file!\n";

//load/save command message constants
const char * const data_save_c = "Data saved\n";
const char * const data_load_c = "Data loaded\n";

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

//action constants
const char print_c = 'p';
const char add_c = 'a';
const char reschedule_c = 'r';
const char delete_c = 'd';
const char save_c = 's';
const char load_c = 'l';

//object constants
const char person_c = 'i';
const char room_c = 'r';
const char meeting_c = 'm';
const char participant_c = 'p';
const char schedule_c = 's';
const char group_c = 'g';
const char allocation_c = 'a';
const char data_c = 'd';
const char quit_c = 'q';

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

//print function prototypes
void print_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list);
void print_person(Person_list_t& person_list);
void print_room(Room_list_t& room_list);
void print_meeting(Room_list_t& room_list);
void print_schedule(Room_list_t& room_list);
void print_group(Person_list_t& person_list);
void print_allocation(Room_list_t& room_list, Person_list_t& person_list);

//add function prototypes
void add_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list);
void add_person(Person_list_t& person_list);
void add_room(Room_list_t& room_list);
void add_meeting(Room_list_t& room_list);
void add_participant(Room_list_t& room_list, Person_list_t& person_list);

//reschedule function prototypes
void reschedule_handle(const char& object, Room_list_t& room_list);
void reschedule_meeting(Room_list_t& room_list);

//delete function prototypes
void delete_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list);
void delete_person(Room_list_t& room_list, Person_list_t& person_list);
void delete_room(Room_list_t& room_list);
void delete_meeting(Room_list_t& room_list);
void delete_participant(Room_list_t& room_list, Person_list_t& person_list);
void delete_schedule(Room_list_t& room_list);
void delete_group(Room_list_t& room_list, Person_list_t& person_list);
void delete_all(Room_list_t& room_list, Person_list_t& person_list);

//save function prototypes
void save_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list);
void save_file(Room_list_t& room_list, Person_list_t& person_list);

//load function prototypes
void load_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list);
void load_file(Room_list_t& room_list, Person_list_t& person_list);
void get_load_int(ifstream& in_file, int& load_in);
void clear_lists(Room_list_t& room_list, Person_list_t& person_list);
bool load_range_check(int load_in);

//quit function prototypes
void quit_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list);

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    
    char action, object;
    
    Room_list_t room_list;
    Person_list_t person_list;
    
    for (;;) {
        
        cout << cmd_prompt_c;
        
        try {
         
            cin >> action >> object;
                
            switch (action) {
                    
                case print_c:
                    
                    print_handle(object, room_list, person_list);
                    break;
                    
                case add_c:
                    
                    add_handle(object, room_list, person_list);
                    break;
                    
                case reschedule_c:
                    
                    reschedule_handle(object, room_list);
                    break;
                    
                case delete_c:
                    
                    delete_handle(object, room_list, person_list);
                    break;
                    
                case save_c:
                    
                    save_handle(object, room_list, person_list);
                    break;
                    
                case load_c:
                    
                    load_handle(object, room_list, person_list);
                    break;
                    
                case quit_c:
                    
                    quit_handle(object, room_list, person_list);
                    return 0;
                    
                default:
                    
                    throw Error(unrecognized_cmd_c);
                    break;
            }
        } catch (Error& e) {
            
            clear_cin();
            e.print();
        }
    }
}

/////////////////////////PRINT FAMILY//////////////////////////////
///////////////////////////////////////////////////////////////////

//switches to proper print fn depending on object character
void print_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list) {
    
    switch (object) {
            
        case person_c:
            
            print_person(person_list);
            break;
            
        case room_c:
            
            print_room(room_list);
            break;
            
        case meeting_c:
            
            print_meeting(room_list);
            break;
            
        case schedule_c:
            
            print_schedule(room_list);
            break;
            
        case group_c:
            
            print_group(person_list);
            break;
            
        case allocation_c:
            
            print_allocation(room_list, person_list);
            break;
            
        default:

            throw Error(unrecognized_cmd_c);
    }
}

//prints a specified individual's information
void print_person(Person_list_t& person_list) {
    
    string last_name;
    cin >> last_name;
    
    auto person_it = std::find(person_list.begin(), person_list.end(), Person(last_name));
    check_person_found(person_list, person_it);
    person_it->print(cout);
}

//prints a specified room's information
void print_room(Room_list_t& room_list) {
    
    int room_number;
    get_room(room_number);
    print_individual_room(room_list, room_number);
}

//prints a specified meeting's information
void print_meeting(Room_list_t& room_list) {
    
    int room_number;
    get_room(room_number);
    auto room_it = std::find(room_list.begin(), room_list.end(), Room(room_number));
    check_room_found(room_list, room_it);
    
    int time;
    get_time(time);
    check_meeting_found(room_it, time);
    print_lookup_meeting(room_it, time);
}

//prints room information for all rooms in the room list
void print_schedule(Room_list_t& room_list) {
    
    if (is_room_list_full(room_list)) {
    
        cout << "Information for " << room_list.size() << " rooms:\n";
        sort(room_list.begin(), room_list.end(), room_sort_comp);
        
        for (auto& room_it : room_list) {
            
            print_individual_room(room_list, room_it.get_room());
        }
    }
}

//prints individual information for all people in the people list
void print_group(Person_list_t& person_list) {
    
    if (is_person_list_full(person_list)) {
    
        cout << "Information for " << person_list.size() << " people:\n";
        print_person_list(cout, person_list);
    }
}

//prints the amount of people, meetings, and rooms currently in existence
void print_allocation(Room_list_t& room_list, Person_list_t& person_list) {
    
    cout << "Memory allocations:\nPersons: " << person_list.size() << "\nMeetings: " << num_meetings(room_list) << "\nRooms: " << room_list.size() << "\n";
}

/////////////////////////ADD FAMILY////////////////////////////////
///////////////////////////////////////////////////////////////////

//switches to proper add fn depending on object character
void add_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list) {
    
    switch (object) {
            
        case person_c:
            
            add_person(person_list);
            break;
            
        case room_c:
            
            add_room(room_list);
            break;
            
        case meeting_c:
            
            add_meeting(room_list);;
            break;
            
        case participant_c:
            
            add_participant(room_list, person_list);
            break;
            
        default:
            
            throw Error(unrecognized_cmd_c);
    }
}

//add an individual to person list
void add_person(Person_list_t& person_list) {
    
    string first_name, last_name, phone;
    cin >> first_name >> last_name >> phone;
    
    auto person_it = std::find(person_list.begin(), person_list.end(), Person(last_name));    //search for person w/ last name
    check_person_end(person_list, person_it);    //does person w/ same last name already exist?
    
    person_list.push_back(Person(first_name, last_name, phone));
    cout << "Person " << last_name << " added\n";
}

//add a room to room list
void add_room(Room_list_t& room_list) {
    
    int room_number;
    get_room(room_number);
    auto room_it = std::find(room_list.begin(), room_list.end(), Room(room_number));
    check_room_end(room_list, room_it); //does room number already exist?
    
    room_list.push_back(Room(room_number));
    cout << "Room " << room_number << " added\n";
}

//add a meeting to a specified room's meeting list
void add_meeting(Room_list_t& room_list) {
    
    int room_number;
    get_room(room_number);
    auto room_it = std::find(room_list.begin(), room_list.end(), Room(room_number));
    check_room_found(room_list, room_it);    //does room exist?
    
    int time;
    get_time(time);
    check_meeting_conflict(room_it, time);   //is time slot already occupied?
    
    string topic;
    cin >> topic;

    room_it->add_meeting(time, topic);  //time slot is not occupied, add meeting
    cout << "Meeting added at " << time << "\n";
}

//add a participant
void add_participant(Room_list_t& room_list, Person_list_t& person_list) {
 
    int room_number;
    get_room(room_number);
    auto room_it = std::find(room_list.begin(), room_list.end(), Room(room_number));
    check_room_found(room_list, room_it);    //does room exist?
    
    int time;
    get_time(time);
    check_meeting_found(room_it, time);     //does meeting exist?
    
    string last_name;
    cin >> last_name;
    
    auto person_it = std::find(person_list.begin(), person_list.end(), Person(last_name));
    check_person_found(person_list, person_it);  //does person exist?
    room_it->add_participant(time, *person_it);
    cout << "Participant " << last_name << " added\n";
}

/////////////////////RESCHEDULE FAMILY/////////////////////////////
///////////////////////////////////////////////////////////////////

//switches to reschedule meeting fn if object character is correct
void reschedule_handle(const char& object, Room_list_t& room_list) {

    switch (object) {
            
        case meeting_c:
            
            reschedule_meeting(room_list);
            break;
            
        default:
            
            throw Error(unrecognized_cmd_c);
    }
}

//reschedules a specified meeting from one room/time pair to another.
void reschedule_meeting(Room_list_t& room_list) {
    
    int old_room;
    get_room(old_room);
    auto old_room_it = std::find(room_list.begin(), room_list.end(), Room(old_room));
    check_room_found(room_list, old_room_it);    //does old room exist?
    
    int old_time;
    get_time(old_time);
    check_meeting_found(old_room_it, old_time);        //is there a meeting in old room @ old time?
    
    int new_room;
    get_room(new_room);
    auto new_room_it = std::find(room_list.begin(), room_list.end(), Room(new_room));
    check_room_found(room_list, new_room_it);    //does new room exist?
    
    int new_time;
    get_time(new_time);
    check_meeting_conflict(new_room_it, new_time);   //is meeting time clear in new room?
    
    auto old_meeting_it = std::find(old_room_it->begin(), old_room_it->end(), Meeting(old_time));
    new_room_it->reschedule_in_meeting(*old_meeting_it, new_time);
    old_room_it->remove_meeting(old_time);
    cout << "Meeting rescheduled to room " << new_room << " at " << new_time << "\n";
}

/////////////////////////DELETE FAMILY/////////////////////////////
///////////////////////////////////////////////////////////////////

//switches to proper delete1 fn depending on object character
void delete_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list) {
    
    switch (object) {
            
        case person_c:
            
            delete_person(room_list, person_list);
            break;
            
        case room_c:
            
            delete_room(room_list);
            break;
            
        case meeting_c:
            
            delete_meeting(room_list);
            break;
            
        case participant_c:
            
            delete_participant(room_list, person_list);
            break;
            
        case schedule_c:
            
            delete_schedule(room_list);
            break;
            
        case group_c:
            
            delete_group(room_list, person_list);
            break;
            
        case allocation_c:
            
            delete_all(room_list, person_list);
            break;
            
        default:
            
            throw Error(unrecognized_cmd_c);
    }
}

//delete individual from person list
void delete_person(Room_list_t& room_list, Person_list_t& person_list) {

    string last_name;
    cin >> last_name;
    
    auto person_it = find(person_list.begin(), person_list.end(), Person(last_name));
    check_person_found(person_list, person_it);  //does person exist?
    is_meeting_participant(room_list, last_name);   //is person a meeting participant?
    
    person_list.erase(person_it);
    cout << "Person " << last_name << " deleted\n";
}

//delete room from room list
void delete_room(Room_list_t& room_list) {
    
    int room_number;
    get_room(room_number);
    auto room_it = find(room_list.begin(), room_list.end(), Room(room_number));
    check_room_found(room_list, room_it);    //does room exist?

    room_list.erase(room_it);
    cout << "Room " << room_number << " deleted\n";
}

//delete meeting from specified room's meeting list
void delete_meeting(Room_list_t& room_list) {

    int room_number;
    get_room(room_number);
    auto room_it = find(room_list.begin(), room_list.end(), Room(room_number));
    check_room_found(room_list, room_it);    //does room exist?
    
    int time;
    get_time(time);
    check_meeting_found(room_it, time);        //is there a meeting in the room at this time?

    room_it->remove_meeting(time);
    cout << "Meeting at " << time << " deleted\n";
}

//delete participant from specified meeting's participant list
void delete_participant(Room_list_t& room_list, Person_list_t& person_list) {

    int room_number;
    get_room(room_number);
    auto room_it = find(room_list.begin(), room_list.end(), Room(room_number));
    check_room_found(room_list, room_it);    //does room exist?
    
    int time;
    get_time(time);
    check_meeting_found(room_it, time);    //is there a meeting in the room at this time?
    
    string last_name;
    cin >> last_name;
    
    auto person_it = find(person_list.begin(), person_list.end(), Person(last_name));
    check_person_found(person_list, person_it);  //does person exist?
    room_it->remove_participant(time, *person_it);
    cout << "Participant " << last_name << " deleted\n";
}

//delete all meetings from every room
void delete_schedule(Room_list_t& room_list) {
    
    clear_all_meetings(room_list);
}

//delete all people from the person list
void delete_group(Room_list_t& room_list, Person_list_t& person_list) {
    
    if (num_meetings(room_list))    //are there any scheduled meetings?
        throw Error(meeting_list_nonempty_c);
    
    clear_person_list(person_list);
}

//delete all rooms/meetings from room list and all people from person list
void delete_all(Room_list_t& room_list, Person_list_t& person_list) {
    
    clear_room_list(room_list);
    clear_person_list(person_list);
}

//save function definitions

////////////////////////SAVE FAMILY////////////////////////////////
///////////////////////////////////////////////////////////////////

void save_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list) {
    
    switch (object) {
            
        case 'd':
            
            save_file(room_list, person_list);
            break;
            
        default:
            
            throw Error(unrecognized_cmd_c);
    }
}

//save current data to specified file
void save_file(Room_list_t& room_list, Person_list_t& person_list) {
    
    string filename;
    cin >> filename;
    
    ofstream out_file;
    out_file.open(filename);
    
    if (out_file.is_open()) {
        
        out_file << person_list.size() << "\n";
        print_person_list(out_file, person_list);
        out_file << room_list.size() << "\n";
        
        for (auto& room_it : room_list) {
            
            out_file << room_it.get_room() << " " << room_it.num_meetings() << "\n";
            
            for (auto& meeting_it : room_it) {
                
                out_file << meeting_it.get_time() << " " << meeting_it.get_topic() << " " << meeting_it.num_participants() << "\n";
                
                for (auto& participant_it : meeting_it) {
                    
                    out_file << participant_it.get_last() << "\n";
                }
            }
        }
        
        cout << data_save_c;
    } else {
        
        throw Error(bad_file_c);
    }
}

//////////////////////////LOAD FAMILY//////////////////////////////
///////////////////////////////////////////////////////////////////

void load_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list) {
    
    switch (object) {
            
        case 'd':
            
            load_file(room_list, person_list);
            break;
            
        default:
            
            throw Error(unrecognized_cmd_c);
    }
}

//load current data from specified file
void load_file(Room_list_t& room_list, Person_list_t& person_list) {
    
    string filename;
    cin >> filename;
    
    ifstream in_file;
    in_file.open(filename);
    
    if (in_file.is_open()) {
        
        clear_lists(room_list, person_list);
        
        try {
            
            int person_list_size;
            get_load_int(in_file, person_list_size);
            
            string first, last, phone;
            
            for (int i = 0; i < person_list_size; ++i) {    //add people to new person_list
                
                if (in_file >> first >> last >> phone) {
                    
                    person_list.push_back(Person(first, last, phone));
                } else {
                    
                    throw Load_error();
                }
            }
            
            int room_list_size;
            get_load_int(in_file, room_list_size);
            
            for (int i = 0; i < room_list_size; ++i) {
                //foreach room, add meetings
                
                int room_number;
                get_load_int(in_file, room_number);
                room_list.push_back(Room(room_number));
 
                int num_meetings;
                get_load_int(in_file, num_meetings);
                
                for (int j = 0; j < num_meetings; ++j) {
                    //foreach meeting, add information
                    
                    int meeting_time;
                    get_load_int(in_file, meeting_time);
                    
                    string topic;
                    
                    if (in_file >> topic) {
                        
                        room_list[i].add_meeting(meeting_time, topic);
                    } else {
                        
                        throw Load_error();
                    }
                    
                    int num_participants;
                    get_load_int(in_file, num_participants);
                    
                    string last_name;
                    
                    for (int k = 0; k < num_participants; ++k) {
                        //foreach participant, add to meeting
                        
                        if (in_file >> last_name) {
                            
                            auto person_it = find(person_list.begin(), person_list.end(), Person(last_name));
                            check_load_person(person_list, person_it);
                            room_list[i].add_participant(meeting_time, *person_it);
                        } else {
                            
                            throw Load_error();
                        }
                    }
                }
            }
            
            cout << data_load_c;
        } catch (Load_error& l_err) {
            
            clear_lists(room_list, person_list);
            throw Error(bad_data_c);
        }
    } else {
        
        throw Error(bad_file_c);
    }
}

//read and check an integer from the file stream
void get_load_int(ifstream& in_file, int& load_int) {
    
    in_file >> load_int;
    
    if (!in_file || load_range_check(load_int))
        throw Load_error();
}

//verify that integer loaded from file is in range
bool load_range_check(int load_in) {
    
    return (load_in < 0);
}

//clear room and person lists
void clear_lists(Room_list_t& room_list, Person_list_t& person_list) {
    
    room_list.clear();
    person_list.clear();
}

//////////////////////QUIT FAMILY//////////////////////////////////
///////////////////////////////////////////////////////////////////

//quit program if object character is properly specified
void quit_handle(const char& object, Room_list_t& room_list, Person_list_t& person_list) {
    
    switch (object) {
            
        case quit_c:
            
            delete_all(room_list, person_list);
            cout << quit_message_c;
            break;
            
        default:
            throw Error(unrecognized_cmd_c);
    }
}
