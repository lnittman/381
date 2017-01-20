//
//  Agent.cpp
//  five_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Agent.h"
#include "Model.h"
#include "Sim_object.h"
#include "Geometry.h"
#include "Utility.h"
#include <iostream>
#include <memory>

const int Agent_health_c = 5;
const int Agent_speed_c = 5;

const int Heal_power_negate_c = -1;

using std::cout;
using std::shared_ptr;
using std::string;

// Tell this Agent to accept a hit from an attack of a specified strength
// The attacking Agent identifies itself with its this pointer.
// A derived class can override this function.
// The function lose_health is called to handle the effect of the attack.
// If a negative attack strength is supplied, the agent gains the corresponding amount of health
void Agent::take_hit(int attack_strength, shared_ptr<Agent> attacker_ptr) {

    if (attack_strength > 0)
        lose_health(attack_strength);
    else
        gain_health(attack_strength);
}

// output information about the current state
void Agent::describe() const {
    
    cout << get_name() << " at " << get_location() << "\n";
    
    switch (Life_e) {
        
        case ALIVE:
            
            cout << "   Health is " << health << "\n";
            
            if (is_moving())
                cout << "   Moving at speed " << movement.get_current_speed() << " to " << movement.get_current_destination() << "\n";
            else
                cout << "   Stopped\n";
            
            break;
        case DEAD:
            
            cout << "   Is dead\n";
            break;
        default:
            
            break;
    }
} 

// update the moving state and Agent state of this object.
void Agent::update() {
    
    switch (Life_e) {
            
        case ALIVE:
            
            if (is_moving()) {
                
                if (movement.update_location())
                    cout << get_name() << ": I'm there!\n";
                else
                    cout << get_name() << ": step...\n";
                
                Model::get_instance().notify_location(get_name(), get_location());
            }
            
            break;
        default:
            
            break;
    }
}

// ask Model to broadcast our current state to all Views
void Agent::broadcast_current_state() const {
    
    Model::get_instance().notify_location(get_name(), get_location());
    Model::get_instance().notify_health(get_name(), get_health());
}

// tell this Agent to start moving to location destination_
void Agent::move_to(Point destination_) {
    
    movement.start_moving(destination_);
    if (is_moving())
        cout << get_name() << ": I'm on the way\n";
    else
        cout << get_name() << ": I'm already there\n";
}

// tell this Agent to stop its activity
void Agent::stop() {
    
    if (is_moving()) {
        
        movement.stop_moving();
        cout << get_name() << ": I'm stopped\n";
    }
}

// Throws exception that an Agent cannot attack.
void Agent::start_attacking(shared_ptr<Agent>) {
    
    cout << get_name() << ": Sorry, I can't attack!\n";
}

// Throws exception that an Agent cannot work.
void Agent::start_working(shared_ptr<Structure>, shared_ptr<Structure>) {
    
    cout << get_name() << ": Sorry, I can't work!\n";
}

// Protected constructor for an Agent object (protected so that derived Warrior can access)
Agent::Agent(const string& name_, Point location_) : Component(name_), Life_e(ALIVE), health(Agent_health_c), movement(location_, Agent_speed_c) {}

// if health decreases to zero or negative, Agent state becomes Dying, and any movement is stopped.
void Agent::lose_health(int attack_strength) {
    
    health -= attack_strength;
    if (health <= 0) {
        
        Life_e = DEAD;
        Model::get_instance().notify_gone(get_name());
        movement.stop_moving();
        cout << get_name() << ": Arrggh!\n";
        Model::get_instance().remove_component(shared_from_this());
    } else {

        cout << get_name() << ": Ouch!\n";
        Model::get_instance().notify_health(get_name(), get_health());
    }
}

// calculate gain in health by negating the supplied health_strength, and add it to the current health
void Agent::gain_health(int heal_strength) {
    
    heal_strength *= Heal_power_negate_c;    // negate the negative heal_strength to calculate gain in health
    health += heal_strength;
    
    cout << get_name() << ": +" << heal_strength << " health gained!\n";
    Model::get_instance().notify_health(get_name(), get_health());
}
