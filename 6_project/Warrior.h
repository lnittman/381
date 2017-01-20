//
//  Warrior.h
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef WARRIOR_H
#define WARRIOR_H

#include "Agent.h"
#include <memory>
#include <string>

struct Point;

class Warrior : public Agent {
    
public:
    
    void update() override;
    
    // Overrides Agent's stop to print a message
    void stop() override;
    
    // Make this Soldier start attacking the target Agent.
    // Throws an exception if the target is the same as this Agent,
    // is out of range, or is not alive.
    void start_attacking(std::shared_ptr<Agent> target_ptr) override;
    
    void describe() const override;
    
protected:
    
    Warrior(const std::string& name_, Point location_, double range_, int strength_, const char* const attack_msg_);
    
    void attack_init(std::shared_ptr<Agent> target_ptr);

    void set_target(std::shared_ptr<Agent> target_ptr)
    {target = target_ptr;}
    
    void stop_attacking();
    
    void flee_to_structure();
    
    std::shared_ptr<Agent> find_closest_target();
  
    bool is_attacking() const
    {return Attacking_e == ATTACKING;}

    const std::shared_ptr<Agent> get_target_shared() const
    {return target.lock();}
    
private:
    
    enum {ATTACKING, NOT_ATTACKING} Attacking_e;
    
    double range;
    int strength;
    std::string attack_msg;
    std::weak_ptr<Agent> target;
};

#endif /* WARRIOR_H */
