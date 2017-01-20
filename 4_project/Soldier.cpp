//
//  Soldier.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Soldier.h"
#include "Utility.h"
#include <iostream>

using std::cout;
using std::string;

Soldier::Soldier(const string& name_, Point location_) : Agent(name_, location_), range(2), strength(2), target(nullptr), is_attacking(false) {
    
    cout << "Soldier " << get_name() << " constructed\n";
}

Soldier::~Soldier() {
    
    cout << "Soldier " << get_name() << " destructed\n";
}

// update implements Soldier behavior
void Soldier::update() {
    
    Agent::update();
    
    if (is_alive() && is_attacking) {
        
        if (!target->is_alive()) {
            
            cout << get_name() << ": Target is dead\n";
            stop_attacking();
        } else if (cartesian_distance(get_location(), target->get_location()) > range) {
            
            cout << get_name() << ": Target is now out of range\n";
            stop_attacking();
        } else {
            
            cout << get_name() << ": Clang!\n";
            target->take_hit(strength, this);
            
            if (!target->is_alive()) {
                
                cout << get_name() << ": I triumph!\n";
                stop_attacking();
            }
        }
    }
}

// Make this Soldier start attacking the target Agent.
// Throws an exception if the target is the same as this Agent,
// is out of range, or is not alive.
void Soldier::start_attacking(Agent* target_ptr) {
    
    if (this == target_ptr)
        throw Error(get_name() + ": I cannot attack myself!");
    
    if (!target_ptr->is_alive())
        throw Error(get_name() + ": Target is not alive!");
    
    if (cartesian_distance(get_location(), target_ptr->get_location()) > range)
        throw Error(get_name() + ": Target is out of range!");
    
    target = target_ptr;
    is_attacking = true;
    cout << get_name() << ": I'm attacking!\n";
}

// Overrides Agent's take_hit to counterattack when attacked.
void Soldier::take_hit(int attack_strength, Agent* attacker_ptr) {
    
    Agent::lose_health(attack_strength);
    
    if (is_attacking && !is_alive())
        stop_attacking();
    else if (!is_attacking && is_alive() && attacker_ptr->is_alive()) {
        
        target = attacker_ptr;
        is_attacking = true;
        cout << get_name() << ": I'm attacking!\n";
    }
}

// Overrides Agent's stop to print a message
void Soldier::stop() {
    
    cout << get_name() << ": Don't bother me\n";
}

// output information about the current state
void Soldier::describe() const {
    
    cout << "Soldier ";
    Agent::describe();
    
    if (is_attacking)
        cout << "   Attacking " << target->get_name() << "\n";
    else
        cout << "   Not attacking\n";
}

// set the soldier's state to not attacking and forget the target ptr
void Soldier::stop_attacking() {
    
    is_attacking = false;
    target = nullptr;
}
