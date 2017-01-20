//
//  Utility.cpp
//  0_project
//
//  Created by Luke Nittmann on 9/9/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Utility.h"
#include "Meeting.h"
#include "Room.h"
#include <iostream>

using std::cin; using std::cout;

////////////////////////ERROR HANDLING/////////////////////////////
///////////////////////////////////////////////////////////////////

Error::Error(const char * const in_str) : error_str(in_str) {}

void Error::print() const {
    
    cout << error_str;
}

void clear_cin() {
    
    cin.clear();
    while (cin.get() != '\n');
}

///////////////////////INPUT UTILITIES//////////////////////////////
////////////////////////////////////////////////////////////////////

//read and check a room number
void get_room(int& room_in) {
    
    get_int(room_in);
    room_range_check(room_in);
}

//read and check a time
void get_time(int& time_in) {
    
    get_int(time_in);
    time_range_check(time_in);
}

//read an integer from stdin, throw error if unsuccessful
void get_int(int& int_in) {
    
    std::cin >> int_in;
    
    if (!std::cin) {
       
        throw Error(bad_number_c);
    }
}

//////////////////////////TIME UTILITIES///////////////////////////
///////////////////////////////////////////////////////////////////

//does time fall within business hours? (9am-5pm inclusive)
void time_range_check(int time_in) {
    
    if (!is_am(time_in) && !is_pm(time_in))
        throw Error(bad_time_c);
}

bool is_am(int time_in) {
    
    return ((8 < time_in) && (time_in < 13));
}

bool is_pm(int time_in) {
    
    return ((0 < time_in) && (time_in < 6));
}

//////////////////////COMPARISON UTILITIES/////////////////////////
///////////////////////////////////////////////////////////////////

bool meeting_sort_comp(const Meeting& m1, const Meeting& m2) {
    
    int m1_time = m1.get_time();
    int m2_time = m2.get_time();
    
    if ((is_am(m1_time) && is_am(m2_time)) || (is_pm(m1_time) && is_pm(m2_time))){
        
        return (m1_time < m2_time);
    } else if (is_am(m1_time) && is_pm(m2_time)) {
        
        return true;
    }
    
    return false;
}

bool room_sort_comp(const Room& r1, const Room& r2) {
    
    return (r1.get_room() < r2.get_room());
}

bool person_sort_comp(const Person& p1, const Person& p2) {
    
    return (p1.get_last() < p2.get_last());
}
