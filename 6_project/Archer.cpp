//
//  Archer.cpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Archer.h"
#include "Model.h"
#include "Structure.h"
#include <iostream>

const int Archer_strength_c = 1;
const double Archer_range_c = 6.;
const char* const Archer_attack_msg_c = "Twang!";

using std::cout;
using std::shared_ptr;
using std::string;

Archer::Archer(const string& name_, Point location_) : Warrior(name_, location_, Archer_range_c, Archer_strength_c, Archer_attack_msg_c) {}

void Archer::take_hit(int attack_strength, shared_ptr<Agent> attacker_ptr) {
    
    Agent::take_hit(attack_strength, attacker_ptr);
    if (attack_strength > 0 && is_alive() && attacker_ptr->is_alive())
        flee_to_structure();
}

void Archer::describe() const {
    
    cout << "Archer ";
    Warrior::describe();
}

void Archer::update() {
    
    Warrior::update();
    shared_ptr<Agent> closest_ptr = find_closest_target();
    
    if (closest_ptr && is_attacking())
        cout << get_name() << ": I'm attacking!\n";
}
