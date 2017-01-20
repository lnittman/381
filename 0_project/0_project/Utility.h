//
//  Utility.h
//  0_project
//
//  Created by Luke Nittmann on 9/9/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef UTILITY_H
#define UTILITY_H


#include <fstream>
#include <string>
#include <vector>

const char * const bad_time_c = "Time is not in range!\n";
const char * const bad_number_c = "Could not read an integer value!\n";

class Room;
class Meeting;
class Person;

class Error {
    const char * const error_str;
public:
    Error(const char * const in_str);
    void print() const;
};

class Load_error {};

//error prototypes
void clear_cin();

//input prototypes
void get_room(int& room_in);
void get_time(int& time_in);
void get_int(int& int_in);

//time utility prototypes
void time_range_check(int time_in);
bool is_am(int time_in);
bool is_pm(int time_in);

//comparison fn prototypes
bool meeting_sort_comp(const Meeting& m1, const Meeting& m2);
bool room_sort_comp(const Room& r1, const Room& r2);
bool person_sort_comp(const Person& p1, const Person& p2);

#endif /* UTILITY_H */
