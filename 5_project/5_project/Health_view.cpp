//
//  Health_view.cpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Health_view.h"
#include <iostream>

using std::cout;
using std::string;

void Health_view::update_health(const string& name, double health) {
    
    update_list(name, health);
}

void Health_view::draw() const {
    
    cout << "Current Health:\n";
    List_view::draw();
}
