//
//  Archer.hpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef ARCHER_H
#define ARCHER_H

#include "Warrior.h"
#include <string>
#include <memory>

struct Point;

class Archer : public Warrior {
    
public:
    
    Archer(const std::string& name_, Point location_);
    
    void update() override;
    
    // Overrides Agent's take_hit to flee to the nearest structure when attacked.
    void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;
    
    void describe() const override;
};

#endif /* ARCHER_H */
