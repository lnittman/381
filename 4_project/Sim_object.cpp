//
//  Sim_object.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Sim_object.h"
#include <iostream>

using std::cout;

Sim_object::Sim_object(const std::string& name_) : name(name_) {
    
    cout << "Sim_object " << name << " constructed\n";
}

Sim_object::~Sim_object() {
    
    cout << "Sim_object " << name << " destructed\n";
}
