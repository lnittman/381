//
//  Peasant.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Peasant.h"
#include "Structure.h"
#include "Utility.h"
#include <iostream>

using std::cout;

Peasant::Peasant(const std::string& name_, Point location_) : Agent(name_, location_), state(Working_e::Not_working),  amount(0), src(nullptr), dst(nullptr) {
    
    cout << "Peasant " << get_name() << " constructed\n";
}

Peasant::~Peasant() {
    
    cout << "Peasant " << get_name() << " destructed\n";
}

// implement Peasant behavior
void Peasant::update() {
    
    Agent::update();
    
    if (is_alive() && state != Working_e::Not_working) {
        
        switch (state) {
                
            case Working_e::Inbound:
                
                if (!is_moving() && src->get_location() == get_location())
                    state = Working_e::Collecting;
                
                break;
            case Working_e::Collecting:
            {
                int amount_received = src->withdraw(35 - amount);
                amount += amount_received;
                
                if (amount_received) {
                    
                    cout << get_name() << ": Collected " << amount_received << "\n";
                    state = Working_e::Outbound;
                    Agent::move_to(dst->get_location());
                } else
                    cout << get_name() << ": Waiting\n";
                
                break;
            }
            case Working_e::Outbound:
                
                if (!is_moving() && dst->get_location() == get_location())
                    state = Working_e::Depositing;
                
                break;
            case Working_e::Depositing:
                
                dst->deposit(amount);
                cout << get_name() << ": Deposited " << amount << "\n";
                amount = 0;
                Agent::move_to(src->get_location());
                state = Working_e::Inbound;
                break;
            default:
                
                //error
                break;
        }
    }
}

// overridden to suspend working behavior
void Peasant::move_to(Point dest) {
    
    if (state != Working_e::Not_working) {
        
        cout << get_name() << ": I'm stopping work\n";
        
        state = Working_e::Not_working;
        src = nullptr;
        dst = nullptr;
    }
    
    Agent::move_to(dest);
}

// stop moving and working
void Peasant::stop() {
    
    Agent::stop();
    
    if (state != Working_e::Not_working) {
        
        cout << get_name() << ": I'm stopping work\n";
        
        state = Working_e::Not_working;
        src = nullptr;
        dst = nullptr;
    }
}

// starts the working process
// Throws an exception if the source is the same as the destination.
void Peasant::start_working(Structure * source_, Structure * destination_) {
    
    Agent::stop();
    
    state = Working_e::Not_working;
    src = nullptr;
    dst = nullptr;
    
    if (source_ == destination_)
        throw Error(get_name() + ": I can't move food to and from the same place!");
    
    if (amount == 0.0) {
        
        if (source_->get_location() == get_location())
            state = Working_e::Collecting;
        else {
            
            Agent::move_to(source_->get_location());
            state = Working_e::Inbound;
            src = source_;
        }
    } else {
        
        if (destination_->get_location() == get_location())
            state = Working_e::Depositing;
        else {
            
            Agent::move_to(destination_->get_location());
            state = Working_e::Outbound;
            dst = destination_;
        }
    }
}

// output information about the current state
void Peasant::describe() const {
    
    cout << "Peasant ";
    Agent::describe();
    cout << "   Carrying " << amount << "\n";
    
    switch (state) {
            
        case Working_e::Outbound:
            
            cout << "   Outbound to destination " << dst->get_name() << "\n";
            break;
        case Working_e::Inbound:
            
            cout << "   Inbound to source " << src->get_name() << "\n";
            break;
        case Working_e::Collecting:
            
            cout << "   Collecting at source " << src->get_name() << "\n";
            break;
        case Working_e::Depositing:
            
            cout << "   Depositing at destination " << dst->get_name() << "\n";
            break;
            
        default:
            
            //error or not working
            break;
    }
}
