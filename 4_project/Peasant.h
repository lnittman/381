/*
 A Peasant is an Agent that can move food between Structures. It can be commanded to
 start_working, whereupon it moves to the source, picks up food, returns to destination,
 deposits the food, returns to source.  If picks up zero food at the source, it waits there
 and tries again on the next update.
 If commanded to move_to somewhere, it stops working, and goes there.
 */

#ifndef PEASANT_H
#define PEASANT_H

#define MAX_AMOUNT 35;

#include "Agent.h"
#include "Geometry.h"
#include <string>

class Structure;

class Peasant : public Agent {

public:
    
    Peasant(const std::string& name_, Point location_);
    
    ~Peasant();
    
    // implement Peasant behavior
    void update() override;
    
    // overridden to suspend working behavior
    void move_to(Point dest) override;
    
    // stop moving and working
    void stop() override;
    
    // starts the working process
    // Throws an exception if the source is the same as the destination.
    void start_working(Structure * source_, Structure * destination_) override;
    
    // output information about the current state
    void describe() const override;
    
private:
    
    enum class Working_e {Not_working, Inbound, Collecting, Outbound, Depositing};
    
    double amount;
    Working_e state;
    Structure* src;
    Structure* dst;
};

#endif
