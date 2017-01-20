//
//  Structure.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Structure.h"
#include "Model.h"
#include "Geometry.h"
#include <iostream>

using std::cout;

Structure::Structure(std::string name_, Point location_) : Sim_object(name_), location(location_) {
    
    cout << "Structure " << get_name() << " constructed\n";
}

Structure::~Structure() {
    
    cout << "Structure " << get_name() << " destructed\n";
}

// output information about the current state
void Structure::describe() const {
    
    cout << get_name() << " at " << location << "\n";
}

// ask model to notify views of current state
void Structure::broadcast_current_state() const {
    
    g_Model_ptr->notify_location(get_name(), get_location());
}
