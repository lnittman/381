/* A Structure is a Sim_object with a location and interface to derived types */

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Sim_object.h"
#include "Geometry.h"

class Structure : public Sim_object {
    
public:
    
    Structure(std::string name, Point location);
    virtual ~Structure() = 0;

    Point get_location() const override
    {return location;}
    
    virtual void update() override {}
    
    // output information about the current state
    virtual void describe() const override;
    
    // ask model to notify views of current state
    virtual void broadcast_current_state() const override;
    
    // fat interface for derived types
    virtual double withdraw(double amount_to_get) {return 0.0;}
    virtual void deposit(double amount_to_give) {}
    
private:
    
    Point location;
};

#endif
