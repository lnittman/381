//
//  Structure.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Structure.h"
#include <iostream>

using std::cout;
using std::string;

// output information about the current state
void Structure::describe() const {
    
    cout << get_name() << " at " << location << "\n";
}

Structure::Structure(const string& name_, Point location_) : Sim_object(name_), location(location_) {}
