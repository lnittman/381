#ifndef VIEW_H
#define VIEW_H

#include "Geometry.h"
#include <string>

class View {
public:
    
    virtual ~View() = 0;

    // prints out the current map
    virtual void draw() const = 0;
    
    /* Fat interface for derived views */
    
    // notify the views about an object's location
    virtual void update_location(const std::string& name, Point location) {}
    // Remove the name and its location; no error if the name is not present.
    virtual void update_remove(const std::string& name) {}
    // notify the views about an object's amount on hand
    virtual void update_amount(const std::string& name, double amount) {}
    // notify the views about an object's health
    virtual void update_health(const std::string& name, double health) {}
};

#endif
