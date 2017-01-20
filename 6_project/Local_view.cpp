//
//  Local_view.cpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Local_view.h"
#include <iostream>

// size and scale of local_view
const int local_size_c = 9;
const double local_scale_c = 2.;

using std::cout;
using std::string;

Local_view::Local_view(const string& subject_, Point location_) : Grid_view(local_size_c, local_scale_c, Point()), subject(subject_) {
    
    set_origin(calculate_origin(location_.x, location_.y));
}

// Save the supplied name and location for future use in a draw() call
// If the name is already present,the new location replaces the previous one.
void Local_view::update_location(const string& name, Point location) {
    
    Grid_view::update_location(name, location);
    if (name == subject)
        set_origin(calculate_origin(location.x, location.y));
}

void Local_view::draw() const {
    
    cout << "Local view for: " << subject << "\n";
    Grid_view::draw();
}

Point Local_view::calculate_origin(double x, double y) {
    
    double origin_x = x - ((local_size_c / 2.) * local_scale_c);
    double origin_y = y - ((local_size_c / 2.) * local_scale_c);
    return Point(origin_x, origin_y);
}
