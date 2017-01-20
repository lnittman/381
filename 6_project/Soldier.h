//
//  Soldier.h
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef SOLDIER_H
#define SOLDIER_H

#include "Warrior.h"
#include <memory>
#include <string>

struct Point;

class Soldier : public Warrior {
    
public:
    
    Soldier(const std::string& name_, Point location_);
    
    // Overrides Agent's take_hit to counterattack when attacked.
    void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;
    
    // output information about the current state
    void describe() const override;
};

#endif /* Soldier_hpp */
