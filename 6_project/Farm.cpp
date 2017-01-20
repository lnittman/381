//
//  Farm.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Farm.h"
#include "Model.h"
#include <iostream>

const int Farm_production_rate_c = 2;
const int Farm_initial_amount_c = 50;

using std::cout;
using std::string;

Farm::Farm(const string& name_, Point location_) : Structure(name_, location_), amount(Farm_initial_amount_c), rate(Farm_production_rate_c) {}

// returns the specified amount, or the remaining amount, whichever is less,
// and deducts that amount from the amount on hand
double Farm::withdraw(double amount_to_get) {

    double ret_amount = 0;
    if (amount_to_get > amount)
        ret_amount = amount;
    else
        ret_amount = amount_to_get;
    
    amount -= ret_amount;
    Model::get_instance().notify_amount(get_name(), amount);
    return ret_amount;
} 

//	update adds the production amount to the stored amount
void Farm::update() {
    
    amount += rate;
    Model::get_instance().notify_amount(get_name(), amount);
    cout << "Farm " << get_name() << " now has " << amount << "\n";
} 

// output information about the current state
void Farm::describe() const {
    
    cout << "Farm ";
    Structure::describe();
    cout << "   Food available: " << amount << "\n";
} 

void Farm::broadcast_current_state() const {
    
    Model::get_instance().notify_location(get_name(), get_location());
    Model::get_instance().notify_amount(get_name(), amount);
} 
