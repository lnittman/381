//
//  Shaman.cpp
//  6_project
//
//  Created by Luke Nittmann on 12/5/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Shaman.h"
#include "Model.h"
#include "Structure.h"
#include <iostream>

const int Shaman_power_c = -1;
const int Shaman_selfheal_threshold = 3;
const double Shaman_range_c = 1.;
const char * const Shaman_attack_msg_c = "Hmmmmm!";

using namespace std;

Shaman::Shaman(const string& name_, Point location_) : Warrior(name_, location_, Shaman_range_c, Shaman_power_c, Shaman_attack_msg_c) {}

// Shaman will flee to nearest structure if its target starts to attack it
// i.e. Shaman is loyal to the target's cause, until it turns against him.
// i.e. Shaman will not leave the closest agent's side, even if it is under attack itself (from other warriors).
void Shaman::take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) {
    
    Agent::take_hit(attack_strength, attacker_ptr);
    self_heal(); // Shaman will always self-heal (if necessary) when another warrior interacts with it

    if (attack_strength > 0 && is_alive() && attacker_ptr->is_alive() && attacker_ptr == get_target_shared()) {
        
        stop_attacking();   // stop healing the hostile target
        flee_to_structure();
    }
}

void Shaman::describe() const {
    
    cout << "Shaman ";
    Agent::describe();
    
    if (is_attacking()) {
        
        shared_ptr<Agent> target_ptr = get_target_shared();
        if (target_ptr)
            cout << "   Healing " << target_ptr->get_name() << "\n";
        else
            cout << "   Healing dead target\n";
    } else
        cout << "   Not healing\n";
}

// Calls Warrior update, will do nothing more if the Shaman is on the way to a healing target
// If stationary and not attacking, Shaman will move to the nearest target's location
void Shaman::update() {
    
    Warrior::update();
    if (is_moving())
        return;
    
    shared_ptr<Agent> closest_ptr = find_closest_target();
    if (closest_ptr && !is_attacking()) {
        
        move_to(closest_ptr->get_location());
        set_target(closest_ptr);
    } else if (closest_ptr && is_attacking())
        cout << get_name() << ": I'm healing!\n";
}

void Shaman::start_attacking(std::shared_ptr<Agent> target_ptr) {
    
    Agent::start_attacking(target_ptr);
}

// Whenever Shaman is hit, or healed, it will check its own health
// If still alive, and current health is lower than the selfhealing threshold, the Shaman will cast a healing spell on itself
void Shaman::self_heal() {
    
    int health = get_health();
    if (health > 0 && health <= Shaman_selfheal_threshold) {
        
        cout << get_name() << ": Summoning self-healing spirits!\n";
        Agent::take_hit(Shaman_power_c, static_pointer_cast<Agent>(shared_from_this()));
    }
}
