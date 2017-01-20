//
//  Map_view.h
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include "Grid_view.h"

struct Point;

class Map_view : public Grid_view {
    
public:
    
    Map_view();
    
    // modify the display parameters
    // if the size is out of bounds will throw Error("New map size is too big!")
    // or Error("New map size is too small!")
    void set_size(int size_);
    
    // If scale is not postive, will throw Error("New map scale must be positive!");
    void set_scale(double scale_);
    
    // any values are legal for the origin
    void set_origin(Point origin_);
    
    // set the parameters to the default values
    void set_defaults();
    
    // 
    void draw() const override;
};


#endif /* MAP_VIEW_H */
