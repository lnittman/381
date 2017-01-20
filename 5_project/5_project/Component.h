//
//  Component.h
//  six_project
//
//  Created by Luke Nittmann on 12/5/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "Sim_object.h"
#include <memory>

class Structure;
class Agent;

class Component : public Sim_object, public std::enable_shared_from_this<Component> {
    
public:
    
    virtual ~Component() {}
    
    /* abstract interface for Agent and Group */
    
    //
    virtual void move_to(Point destination) = 0;
    //
    virtual void stop() = 0;
    //
    virtual void start_working(std::shared_ptr<Structure> src, std::shared_ptr<Structure> dst) = 0;
    //
    virtual void start_attacking(std::shared_ptr<Agent> target) = 0;
    
    /* Fat interface for derived classes */
    
    //
    virtual void add_component(std::shared_ptr<Component> component_ptr);
    //
    virtual void remove_component(std::shared_ptr<Component> component_ptr);
    
protected:
    
    Component(const std::string& name_);
};

#endif /* COMPONENT_H */
