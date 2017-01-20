//
//  Farm.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Farm.h"
#include "Geometry.h"
#include <iostream>

using std::cout;

Farm::Farm(const std::string& name_, Point location_): Structure(name_, location_), rate(2), amount(50) {
    
    cout << "Farm " << get_name() << " constructed\n";
}

Farm::~Farm() {
    
    cout << "Farm " << get_name() << " destructed\n";
}

// returns the specified amount, or the remaining amount, whichever is less,
// and deducts that amount from the amount on hand
double Farm::withdraw(double amount_to_get) {
    
    int ret_amount = 0;
    if (amount_to_get > amount) {
        
        ret_amount = amount;
        amount = 0;
    } else {
        
        ret_amount = amount_to_get;
        amount -= amount_to_get;
    }
    
    return ret_amount;
}

//	update adds the production amount to the stored amount
void Farm::update() {
    
    amount += rate;
    cout << "Farm " << get_name() << " now has " << amount << "\n";
}

// output information about the current state
void Farm::describe() const {
    
    cout << "Farm ";
    Structure::describe();
    cout << "   Food available: " << amount << "\n";
}
