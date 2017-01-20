/* A Structure is a Sim_object with a location and interface to derived types */

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Sim_object.h"
#include "Geometry.h"
#include <string>

class Structure : public Sim_object {
    
public:
    
    Point get_location() const override
    {return location;}
    
    // output information about the current state
    virtual void describe() const override;
    
    // fat interface for derived types
    void update() override {}
    virtual double withdraw(double amount_to_get) {return 0.0;}
    virtual void deposit(double amount_to_give) {}
    
protected:
    
    Structure(const std::string& name, Point location);
    
private:
    
    Point location;
};

#endif
