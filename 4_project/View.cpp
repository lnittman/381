#include "View.h"
#include "Geometry.h"
#include "Utility.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

const int default_size_c = 25;
const int default_width_c = 4;
const double default_scale_c = 2.0;
const double default_origin_coord_c = -10.0;

const int label_step_c = 3;
const int max_size_c = 30;
const int min_size_c = 7;

using namespace std;

View::View() : size(default_size_c), scale(default_scale_c), origin(Point(default_origin_coord_c, default_origin_coord_c)) {
    
    cout << "View constructed\n";
}

View::~View() {
    
    cout << "View destroyed\n";
}

// Save the supplied name and location for future use in a draw() call
// If the name is already present,the new location replaces the previous one.
void View::update_location(const std::string& name, Point location) {
    
    object_locations[name] = location;
}

// Remove the name and its location; no error if the name is not present.
void View::update_remove(const std::string& name) {
    
    object_locations.erase(name);
}

// prints out the current map
void View::draw() const {
    
    vector<vector<string>> coordinate_map(size, vector<string>(size));
    vector<string> out_of_range_objects;
    
    // Populate the coordinates in the map.
    // If an object is out of range given preset member variables, add it to the list of out-of-range objects
    int x, y;
    for (auto object : object_locations) {
        
        if (get_subscripts(x, y, object.second)) {
        
            if (coordinate_map[x][y] == "")
                coordinate_map[x][y] = object.first;
            else
                coordinate_map[x][y] = "* ";
        } else
            out_of_range_objects.push_back(object.first);
    }
    
    // Print initial output lines: member variable information, and the out-of-range objects, if any exist
    cout << "Display size: " << size << ", scale: " << scale << ", origin: " << origin << "\n";
    if (!out_of_range_objects.empty()) {
        
        copy(out_of_range_objects.begin(), out_of_range_objects.end() - 1, ostream_iterator<string>(cout, ", "));
        cout << out_of_range_objects.back() << " outside the map\n";
    }
    
    // Preserve old cout flags, then compute maximum x and y axis values
    ios::fmtflags old_settings = cout.flags();
    cout.precision(0);
    
    for (int i = (size-1); i > -1; --i) {
        
        if (!(i % label_step_c))      // if on 3rd row, output y-axis label
            cout << setw(default_width_c) << origin.y + (scale * i) << " ";
        else
            cout << "     ";
        
        for (int j = 0; j < size; ++j) {
            
            string coord_str = coordinate_map[j][i];
            if (coord_str != "")
                cout << coord_str[0] << coord_str[1];
            else
                cout << ". ";
        }
        
        cout << "\n";
    }
    
    // Output the x-axis labels on the last line of output
    int num_steps = ((size - 1) / label_step_c) + 1;
    for (int j = 0; j < num_steps; ++j)
        cout << "  " << setw(default_width_c) << origin.x + (j * scale * label_step_c);
    cout << "\n";
    
    // Restore stdout stream flags
    cout.flags(old_settings);
    cout.precision(2);
}

// modify the display parameters
// if the size is out of bounds will throw Error("New map size is too big!")
// or Error("New map size is too small!")
void View::set_size(int size_) {
    
    if (size_ > max_size_c)
        throw Error("New map size is too big!");
    else if (size_ < min_size_c)
        throw Error("New map size is too small!");
    
    size = size_;
}

// If scale is not postive, will throw Error("New map scale must be positive!");
void View::set_scale(double scale_) {
    
    if (scale_ <= 0)
        throw Error("New map scale must be positive!");
    
    scale = scale_;
}

// any values are legal for the origin
void View::set_origin(Point origin_) {
    
    origin = origin_;
}

// set the parameters to the default values
void View::set_defaults() {
    
    size = default_size_c;
    scale = default_scale_c;
    origin = Point(default_origin_coord_c, default_origin_coord_c);
}

/* *** Use this function to calculate the subscripts for the cell. */
// Calculate the cell subscripts corresponding to the supplied location parameter,
// using the current size, scale, and origin of the display.
// This function assumes that origin is a member variable of type Point,
// scale is a double value, and size is an integer for the number of rows/columns
// currently being used for the grid.
// Return true if the location is within the grid, false if not
bool View::get_subscripts(int &ix, int &iy, Point location) const {
    
    // adjust with origin and scale
    Cartesian_vector subscripts = (location - origin) / scale;
    
    // truncate coordinates to integer after taking the floor
    // floor function will return the largest integer smaller than the supplied value
    // even for negative values, so -0.05 => -1., which will be outside the array.
    ix = int(floor(subscripts.delta_x));
    iy = int(floor(subscripts.delta_y));
    
    // if out of range, return false
    if ((ix < 0) || (ix >= size) || (iy < 0) || (iy >= size)) {
        
        return false;
    }
    
    return true;
}
