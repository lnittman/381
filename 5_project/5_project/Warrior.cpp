//
//  Warrior.cpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Warrior.h"
#include "Model.h"
#include "Sim_object.h"
#include "Structure.h"
#include "Geometry.h"
#include "Utility.h"
#include <iostream>

using namespace std;

void Warrior::update() {
    
    Agent::update();
    if (is_alive() && is_attacking()) {
        
        shared_ptr<Agent> target_ptr = target.lock();
        if (!target_ptr || !target_ptr->is_alive()) {
            
            cout << get_name() << ": Target is dead\n";
            stop_attacking();
        } else if (cartesian_distance(get_location(), target_ptr->get_location()) > range) {
            
            cout << get_name() << ": Target is now out of range\n";
            stop_attacking();
        } else {
            
            cout << get_name() << ": " << attack_msg << "\n";
            target_ptr->take_hit(strength, static_pointer_cast<Agent>(shared_from_this()));
            
            if (!target_ptr->is_alive()) {
                
                cout << get_name() << ": I triumph!\n";
                stop_attacking();
            }
        }
    }
}

void Warrior::stop() {
    
    cout << get_name() << ": Don't bother me\n";
}

// Make this Soldier start attacking the target Agent.
// Throws an exception if the target is the same as this Agent,
// is out of range, or is not alive.
void Warrior::start_attacking(shared_ptr<Agent> target_ptr) {
    
    if (shared_from_this() == target_ptr)
        cout << get_name() << ": I cannot attack myself!\n";
    else if (!target_ptr->is_alive())
        cout << get_name() << ": Target is not alive!\n";
    else if (cartesian_distance(get_location(), target_ptr->get_location()) > range)
        cout << get_name() << ": Target is out of range!\n";
    else {
        
        cout << get_name() << ": I'm attacking!\n";
        attack_init(target_ptr);
    }
}

void Warrior::describe() const {
    
    Agent::describe();
    if (is_attacking()) {
        
        shared_ptr<Agent> target_ptr = target.lock();
        if (target_ptr)
            cout << "   Attacking " << target_ptr->get_name() << "\n";
        else
            cout << "   Attacking dead target\n";
    } else
        cout << "   Not attacking\n";
}

Warrior::Warrior(const std::string& name_, Point location_, double range_, int strength_, const char* const attack_msg_) : Agent(name_, location_), Attacking_e(NOT_ATTACKING), range(range_), strength(strength_), attack_msg(attack_msg_) {}

void Warrior::attack_init(std::shared_ptr<Agent> target_ptr) {
    
    target = target_ptr;
    Attacking_e = ATTACKING;
}

// set the soldier's state to not attacking and forget the target ptr
void Warrior::stop_attacking() {
    
    Attacking_e = NOT_ATTACKING;
    target.reset();
}

void Warrior::flee_to_structure() {
    
    shared_ptr<Structure> flee_destination = Model::get_instance().find_closest_structure(shared_from_this());
    if (flee_destination) {
        
        cout << get_name() << ": I'm going to run away to " << flee_destination->get_name() << "\n";
        move_to(flee_destination->get_location());
    }
}

// searches for the closest agent in the grid
// if the target is found and within range, the warrior will start attacking it
std::shared_ptr<Agent> Warrior::find_closest_target() {
    
    if (!is_attacking()) {
    
        if (shared_ptr<Agent> new_target = Model::get_instance().find_closest_agent(shared_from_this())) {
            
            if (cartesian_distance(new_target->get_location(), get_location()) <= range)
                attack_init(new_target);
        
            return new_target;
        }
    }
    
    return nullptr;
}
