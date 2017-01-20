//
//  Structure_factory.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Structure_factory.h"
#include "Farm.h"
#include "Town_Hall.h"
#include "Geometry.h"
#include "Utility.h"
#include <string>

using std::string;

// Create and return the pointer to the specified Structure type. If the type
// is unrecognized, throws Error("Trying to create structure of unknown type!")
// The Structure is allocated with new, so some other component is resposible for deleting it.
Structure * create_structure(const string& name, const string& type, Point location) {
    
    if (type == "Farm")
        return new Farm(name, location);
    else if (type == "Town_Hall")
        return new Town_Hall(name, location);
    else
        throw Error("Trying to create structure of unknown type!");
}
