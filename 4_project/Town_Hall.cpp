//
//  Town_Hall.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Town_Hall.h"
#include "Geometry.h"
#include <iostream>
#include <string>

using std::cout;
using std::string;

Town_Hall::Town_Hall(const std::string& name_, Point location_) : Structure(name_, location_), amount(0) {
    
    cout << "Town_Hall " << name_ << " constructed\n";
}

Town_Hall::~Town_Hall() {
    
    cout << "Town_Hall " << get_name() << " destructed\n";
}

// Return whichever is less, the request or (the amount on hand - 10%) (a "tax"),
// but amounts less than 1.0 are not supplied - the amount returned is zero.
// update the amount on hand by subtracting the amount returned.
double Town_Hall::withdraw(double amount_to_obtain) {
    
    double taxed_amount = 0.9 * amount;
    
    if (taxed_amount < 1.0)
        taxed_amount = 0;
    
    int ret_amount = 0;
    if (amount_to_obtain > taxed_amount) {
        
        ret_amount = taxed_amount;
        amount -= taxed_amount;
    } else {
        
        ret_amount = amount_to_obtain;
        amount -= amount_to_obtain;
    }
    
    return ret_amount;
}

// output information about the current state
void Town_Hall::describe() const {
    
    cout << "Town_Hall ";
    Structure::describe();
    cout << "   Contains " << amount << "\n";
}
