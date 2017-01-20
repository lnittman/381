//
//  Structure_factory.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Structure_factory.h"
#include "Structure.h"
#include "Farm.h"
#include "Town_Hall.h"
#include "Utility.h"

using std::string;
using std::shared_ptr; using std::make_shared;

//struct Point;

// Create and return the pointer to the specified Structure type. If the type
// is unrecognized, throws Error("Trying to create structure of unknown type!")
// The Structure is allocated with new, so some other component is resposible for deleting it.
shared_ptr<Structure> create_structure(const string& name, const string& type, Point location) {
    
    if (type == "Farm")
        return make_shared<Farm>(name, location);
    else if (type == "Town_Hall")
        return make_shared<Town_Hall>(name, location);
    else
        throw Error("Trying to create structure of unknown type!");
}
