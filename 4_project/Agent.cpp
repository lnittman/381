//
//  Agent.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Agent.h"
#include "Model.h"
#include "Utility.h"
#include <iostream>

using std::cout;
using std::string;

Agent::~Agent() {
    
    cout << "Agent " << get_name() << " destructed\n";
}

// tell this Agent to start moving to location destination_
void Agent::move_to(Point destination_) {
    
    start_moving(destination_);
    if (is_moving())
        cout << get_name() << ": I'm on the way\n";
    else
        cout << get_name() << ": I'm already there\n";
}

// tell this Agent to stop its activity
void Agent::stop() {
    
    if (is_moving()) {
        
        stop_moving();
        cout << get_name() << ": I'm stopped\n";
    }
}

// Tell this Agent to accept a hit from an attack of a specified strength
// The attacking Agent identifies itself with its this pointer.
// A derived class can override this function.
// The function lose_health is called to handle the effect of the attack.
void Agent::take_hit(int attack_strength, Agent *attacker_ptr) {
    
    lose_health(attack_strength);
}

// update the moving state and Agent state of this object.
void Agent::update() {
    
    switch (state) {
            
        case Alive_e::Alive:
            
            if (is_moving()) {
                
                if (update_location())
                    cout << get_name() << ": I'm there!\n";
                else
                    cout << get_name() << ": step...\n";
                
                g_Model_ptr->notify_location(get_name(), get_location());
            }
            
            break;
        case Alive_e::Dying:
            
            state = Alive_e::Dead;
            g_Model_ptr->notify_gone(get_name());
            break;
        case Alive_e::Dead:
            
            state = Alive_e::Disappearing;
            break;
        default:
            
            break;
    }
}

// output information about the current state
void Agent::describe() const {
    
    cout << get_name() << " at " << get_location() << "\n";
    
    switch (state) {
            
        case Alive_e::Alive:
            
            cout << "   Health is " << health << "\n";
            
            if (is_moving())
                cout << "   Moving at speed " << get_current_speed() << " to " << get_current_destination() << "\n";
            else
                cout << "   Stopped\n";
            
            break;
        case Alive_e::Dying:
            
            cout << "   Is dying\n";
            break;
        case Alive_e::Dead:
            
            cout << "   Is dead\n";
            break;
        case Alive_e::Disappearing:
            
            cout << "   Is disappearing\n";
            break;
        default:
            
            break;
    }
}

// ask Model to broadcast our current state to all Views
void Agent::broadcast_current_state() const {
    
    g_Model_ptr->notify_location(get_name(), get_location());
}

/* Fat Interface for derived classes */
// Throws exception that an Agent cannot work.
void Agent::start_working(Structure *, Structure *) {
    
    throw Error(get_name() + ": Sorry, I can't work!");
}

// Throws exception that an Agent cannot attack.
void Agent::start_attacking(Agent *) {
    
    throw Error(get_name() + ": Sorry, I can't attack!");
}

// Protected constructor for an Agent object (protected so that derived Peasant, Soldier can access)
Agent::Agent(const string& name_, Point location_) : Sim_object(name_), Moving_object(location_, 5), health(5), state(Alive_e::Alive) {
    
    cout << "Agent " << name_ << " constructed\n";
}

// calculate loss of health due to hit.
// if health decreases to zero or negative, Agent state becomes Dying, and any movement is stopped.
void Agent::lose_health(int attack_strength) {
    
    health -= attack_strength;
    
    if (health <= 0) {
        
        state = Alive_e::Dying;
        stop_moving();
        cout << get_name() << ": Arrggh!\n";
    } else
        cout << get_name() << ": Ouch!\n";
}
