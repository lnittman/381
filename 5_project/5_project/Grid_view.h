//
//  Grid_view.h
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef GRID_VIEW_H
#define GRID_VIEW_H

#include "View.h"
#include "Geometry.h"
#include <map>
#include <string>

// default map_view parameters
const int default_size_c = 25;
const int default_width_c = 4;
const double default_scale_c = 2.;
const double default_origin_coord_c = -10.;

class Grid_view : public View {
    
public:
    
    // Save the supplied name and location for future use in a draw() call
    // If the name is already present,the new location replaces the previous one.
    void update_location(const std::string& name, Point location) override;
    
    void update_remove(const std::string& name) override;
    
protected:
    
    Grid_view(int size_, double scale_, Point origin_);
    
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
    
    void print_map_info() const;
    
    void draw() const override;
    
private:
    
    int size;
    double scale;
    Point origin;
    std::map<std::string, Point> object_locations;
    
    bool get_subscripts(int &ix, int &iy, Point location) const;
};

#endif /* GRID_VIEW_H */
