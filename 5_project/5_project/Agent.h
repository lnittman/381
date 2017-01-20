/*
 Agents are a kind of Sim_object, and privately inherit from Moving_object.
 Agents can be commanded to move to a destination. Agents have a health, which
 is decreased when they take a hit. If the Agent's health > 0, it is alive.
 If its heath <= 0, it starts dying, then on subsequent updates,
 it becomes dead, and finally disappearing.
 */

#ifndef AGENT_H
#define AGENT_H

#include "Sim_object.h"
#include "Component.h"
#include "Moving_object.h"
#include <memory>
#include <string>

class Structure;
struct Point;

class Agent : public Component {
  
public:
    
    // return true if this agent is Alive or Disappearing
    bool is_alive() const
    {return Life_e == ALIVE;}
    
    int get_health() const
    {return health;}
    
    // return true if this Agent is in motion
    bool is_moving() const
    {return movement.is_currently_moving();}
    
    // Tell this Agent to accept a hit from an attack of a specified strength
    // The attacking Agent identifies itself with its this pointer.
    // A derived class can override this function.
    // The function lose_health is called to handle the effect of the attack.
    virtual void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr);

    /* Sim_object declarations */
    
    // return this Agent's location
    Point get_location() const override
    {return movement.get_current_location();}
    
    // output information about the current state
    void describe() const override;
    
    // update the moving state and Agent state of this object.
    void update() override;
    
    // ask Model to broadcast our current state to all Views
    void broadcast_current_state() const override;
    
    /* Component declarations */
    
    // tell this Agent to start moving to location destination
    void move_to(Point destination_) override;
    
    // tell this Agent to stop its activity
    void stop() override;
    
        /* Fat Interface for derived classes */
    
    // Throws exception that an Agent cannot attack.
    void start_attacking(std::shared_ptr<Agent>) override;
    
    // Throws exception that an Agent cannot work.
    void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) override;
    
protected:

    Agent(const std::string& name_, Point location_);
    
    // if health decreases to zero or negative, Agent state becomes Dying, and any movement is stopped.
    void lose_health(int attack_strength);
    
    // calculate gain in health by negating the supplied health_strength, and add it to the current health.
    void gain_health(int heal_strength);
    
private:
    
    enum {ALIVE, DEAD} Life_e;

    int health;
    Moving_object movement;
};

#endif
