//
//  Utility.cpp
//  six_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Utility.h"
#include "Sim_object.h"
#include "Geometry.h"
#include <iostream>

using std::cin;

bool Sim_comp::operator() (std::shared_ptr<Sim_object> s1, std::shared_ptr<Sim_object> s2) const {
    
    return s1->get_name() < s2->get_name();
}

bool Sim_comp::operator() (const std::string& s1, std::shared_ptr<Sim_object> s2) const {
    
    return s1 < s2->get_name();
}

bool Sim_comp::operator() (std::shared_ptr<Sim_object> s1, const std::string& s2) const {
    
    return s1->get_name() < s2;
}
