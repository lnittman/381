//
//  Local_view.hpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef LOCAL_VIEW_H
#define LOCAL_VIEW_H

#include "Grid_view.h"
#include <string>

struct Point;

class Local_view : public Grid_view {
    
public:
    
    Local_view(const std::string& subject_, Point location_);
    
    // Save the supplied name and location for future use in a draw() call
    // If the name is already present,the new location replaces the previous one.
    void update_location(const std::string& name, Point location) override;
    
    void draw() const override;
    
private:
    
    std::string subject;

    Point calculate_origin(double x, double y);
};

#endif /* LOCAL_VIEW_H */
