//
//  Agent_factory.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Agent_factory.h"
#include "Peasant.h"
#include "Soldier.h"
#include "Geometry.h"
#include "Utility.h"

// Create and return the pointer to the specified Agent type. If the type
// is unrecognized, throws Error("Trying to create agent of unknown type!")
// The Agent is allocated with new, so some other component is resposible for deleting it.
Agent * create_agent(const std::string& name, const std::string& type, Point location) {
    
    if (type == "Peasant")
        return new Peasant(name, location);
    else if (type == "Soldier")
        return new Soldier(name, location);
    else
        throw Error("Trying to create agent of unknown type!");
}
