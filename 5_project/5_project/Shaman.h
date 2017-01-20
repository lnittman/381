//
//  Shaman.h
//  6_project
//
//  Created by Luke Nittmann on 12/5/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef SHAMAN_H
#define SHAMAN_H

#include "Warrior.h"
#include "Structure.h"
#include <memory>

class Agent;
struct Point;

class Shaman : public Warrior {
    
public:
    
    Shaman(const std::string& name_, Point location_);

    // Overrides Agent's take_hit to:
    // a) flee to nearest structure if attacker is == target
    // b) self-heal when attacked and health falls to a certain threshold.
    void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;
    
    // Overrides Warrior's describe to:
    // output healing information, as opposed to attack related information
    void describe() const override;
    
    // implement Shaman behavior
    void update() override;

    // calls Agent::start_attacking to throw Error("I can't attack!")
    void start_attacking(std::shared_ptr<Agent> target_ptr) override;

private:
        
    void self_heal();
};

#endif /* SHAMAN_H */
