//
//  Component.cpp
//  six_project
//
//  Created by Luke Nittmann on 12/5/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Component.h"
#include "Utility.h"

Component::Component(const std::string& name_) : Sim_object(name_) {}

//
void Component::add_component(std::shared_ptr<Component> component_ptr) {
    
    throw Error("Only groups can add components!");
}

//
void Component::remove_component(std::shared_ptr<Component> component_ptr) {
    
    throw Error("Only groups can remove components!");
}
