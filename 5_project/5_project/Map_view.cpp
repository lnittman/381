//
//  Map_view.cpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Map_view.h"

Map_view::Map_view() : Grid_view(default_size_c, default_scale_c, Point(default_origin_coord_c, default_origin_coord_c)) {}

// modify the display parameters
// if the size is out of bounds will throw Error("New map size is too big!")
// or Error("New map size is too small!")
void Map_view::set_size(int size_) {
    
    Grid_view::set_size(size_);
}

// If scale is not postive, will throw Error("New map scale must be positive!");
void Map_view::set_scale(double scale_) {
    
    Grid_view::set_scale(scale_);
}

// any values are legal for the origin
void Map_view::set_origin(Point origin_) {
    
    Grid_view::set_origin(origin_);
}

// set the parameters to the default values
void Map_view::set_defaults() {
    
    Grid_view::set_defaults();
}

void Map_view::draw() const {
    
    Grid_view::print_map_info();
    Grid_view::draw();
}
