//
//  Amount_view.cpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Amount_view.h"
#include <iostream>

using std::cout;
using std::string;

void Amount_view::update_amount(const string& name, double amount) {
    
    update_list(name, amount);
}

void Amount_view::draw() const {
    
    cout << "Current Amounts:\n";
    List_view::draw();
}
