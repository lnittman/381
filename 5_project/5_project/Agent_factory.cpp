//
//  Agent_factory.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Agent_factory.h"
#include "Peasant.h"
#include "Archer.h"
#include "Shaman.h"
#include "Soldier.h"
#include "Utility.h"

using std::shared_ptr; using std::make_shared;
using std::string;

// Create and return the pointer to the specified Agent type. If the type
// is unrecognized, throws Error("Trying to create agent of unknown type!")
// The Agent is allocated with new, so some other component is resposible for deleting it.
shared_ptr<Agent> create_agent(const string& name, const string& type, Point location) {
    
    if (type == "Peasant")
        return make_shared<Peasant>(name, location);
    else if (type == "Archer")
        return make_shared<Archer>(name, location);
    else if (type == "Shaman")
        return make_shared<Shaman>(name, location);
    else if (type == "Soldier")
        return make_shared<Soldier>(name, location);
    else
        throw Error("Trying to create agent of unknown type!");
}
