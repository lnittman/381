//
//  Soldier.cpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Soldier.h"
#include <iostream>

const int Soldier_strength_c = 2;
const double Soldier_range_c = 2.;
const char* const Soldier_attack_msg_c = "Clang!";

using std::cout;
using std::shared_ptr;
using std::string;

Soldier::Soldier(const string& name_, Point location_) : Warrior(name_, location_, Soldier_range_c, Soldier_strength_c, Soldier_attack_msg_c) {}

// Overrides Agent's take_hit to counterattack when attacked.
void Soldier::take_hit(int attack_strength, shared_ptr<Agent> attacker_ptr) {
    
    Agent::take_hit(attack_strength, attacker_ptr);
    if (attack_strength > 0 && !is_attacking() && is_alive() && attacker_ptr->is_alive()) {
        
        cout << get_name() << ": I'm attacking!\n";
        attack_init(attacker_ptr);
    }
}

// output information about the current state
void Soldier::describe() const {
    
    cout << "Soldier ";
    Warrior::describe();
}
