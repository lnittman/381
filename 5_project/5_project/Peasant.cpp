//
//  Peasant.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Peasant.h"
#include "Model.h"
#include "Sim_object.h"
#include "Structure.h"
#include "Geometry.h"
#include "Utility.h"
#include <iostream>

const double max_carry_capacity_c = 35.;

using std::cout;
using std::string;
using std::shared_ptr;

Peasant::Peasant(const string& name_, Point location_) : Agent(name_, location_), Working_e(NOT_WORKING) {}

// implement Peasant behavior
void Peasant::update() {
    
    Agent::update();
    if (is_alive() && Working_e != NOT_WORKING) {
        
        switch (Working_e) {
                
            case INBOUND:

                if (!is_moving() && src->get_location() == get_location())
                    Working_e = COLLECTING;
    
                break;
            case COLLECTING:
            {
                double amount_received = src->withdraw(max_carry_capacity_c - amount);
                amount += amount_received;
                Model::get_instance().notify_amount(get_name(), amount);
                
                if (amount_received > 0) {
                    
                    cout << get_name() << ": Collected " << amount_received << "\n";
                    Working_e = OUTBOUND;
                    Agent::move_to(dst->get_location());
                } else
                    cout << get_name() << ": Waiting \n";
                
                break;
            }
            case OUTBOUND:
                
                if (!is_moving() && dst->get_location() == get_location())
                    Working_e = DEPOSITING;
                
                break;
            case DEPOSITING:
                
                dst->deposit(amount);
                cout << get_name() << ": Deposited " << amount << "\n";
                amount = 0;
                Model::get_instance().notify_amount(get_name(), amount);
                Agent::move_to(src->get_location());
                Working_e = INBOUND;
                break;
            default:
                
                break;
        }
    }
} 

// overridden to suspend working behavior
void Peasant::move_to(Point dest) {
    
    if (Working_e != NOT_WORKING) {
        
        cout << get_name() << ": I'm stopping work\n";
        stop_working();
    }
    
    Agent::move_to(dest);
} 

// stop moving and working
void Peasant::stop() {
    
    Agent::stop();
    if (Working_e != NOT_WORKING) {
        
        cout << get_name() << ": I'm stopping work\n";
        stop_working();
    }
} 

// starts the working process
// Throws an exception if the source is the same as the destination.
void Peasant::start_working(shared_ptr<Structure> source_, shared_ptr<Structure> destination_) {
    
    Agent::stop();
    stop_working();
    
    if (source_ == destination_)
        throw Error(get_name() + ": I can't move food to and from the same place!");

    src = source_;
    dst = destination_;
    
    if (amount == 0.0) {
        
        if (source_->get_location() == get_location())
            Working_e = COLLECTING;
        else {
            
            Agent::move_to(source_->get_location());
            Working_e = INBOUND;
        }
    } else {
        
        if (destination_->get_location() == get_location())
            Working_e = DEPOSITING;
        else {
            
            Agent::move_to(destination_->get_location());
            Working_e = OUTBOUND;
        }
    }
} 

// output information about the current state
void Peasant::describe() const {
    
    cout << "Peasant ";
    Agent::describe();
    cout << "   Carrying " << amount << "\n";

    switch (Working_e) {
            
        case OUTBOUND:
            
            cout << "   Outbound to destination " << dst->get_name() << "\n";
            break;
        case INBOUND:
            
            cout << "   Inbound to source " << src->get_name() << "\n";
            break;
        case COLLECTING:
            
            cout << "   Collecting at source " << src->get_name() << "\n";
            break;
        case DEPOSITING:
            
            cout << "   Depositing at destination " << dst->get_name() << "\n";
            break;
            
        default:
            
            break;
    }
}

void Peasant::broadcast_current_state() const {
    
    Agent::broadcast_current_state();
    Model::get_instance().notify_amount(get_name(), get_amount());
} 

// set the peasant's state to not working, forget src and dst pointers
void Peasant::stop_working() {
    
    Working_e = NOT_WORKING;
    src.reset();
    dst.reset();
} 
