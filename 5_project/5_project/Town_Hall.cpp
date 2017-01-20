//
//  Town_Hall.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Town_Hall.h"
#include "Model.h"
#include "Sim_object.h"
#include "Geometry.h"
#include <iostream>

const double Taxed_amount_c = 0.9;
const int Withdrawal_minimum_c = 1;

using std::cout;
using std::string;

Town_Hall::Town_Hall(const string& name_, Point location_) : Structure(name_, location_) {}

// deposit adds in the supplied amount
void Town_Hall::deposit(double deposit_amount) {
    
    amount += deposit_amount;
    Model::get_instance().notify_amount(get_name(), amount);
} 

// Return whichever is less, the request or (the amount on hand - 10%) (a "tax"),
// but amounts less than 1.0 are not supplied - the amount returned is zero.
// update the amount on hand by subtracting the amount returned.
double Town_Hall::withdraw(double amount_to_obtain) {
    
    double taxed_amount = Taxed_amount_c * amount;
    if (taxed_amount < Withdrawal_minimum_c)
        taxed_amount = 0;
    
    double ret_amount;
    if (amount_to_obtain > taxed_amount)
        ret_amount = taxed_amount;
    else
        ret_amount = amount_to_obtain;
    
    amount -= ret_amount;
    Model::get_instance().notify_amount(get_name(), amount);
    return ret_amount;
} 

// output information about the current state
void Town_Hall::describe() const {
    
    cout << "Town_Hall ";
    Structure::describe();
    cout << "   Contains " << amount << "\n";
} 

void Town_Hall::broadcast_current_state() const {
    
    Model::get_instance().notify_location(get_name(), get_location());
    Model::get_instance().notify_amount(get_name(), amount);
} 
