//
//  List_view.h
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef LIST_VIEW_H
#define LIST_VIEW_H

#include "View.h"
#include <string>
#include <map>

struct Point;

class List_view : public View {
    
public:
    
    // remove an object from the list
    void update_remove(const std::string& name) override;
    
    // prints out the current list
    void draw() const override;
    
protected:
    
    // updates an object's datum in the list
    void update_list(const std::string& name, double list_datum);
    
private:
    
    using List_t = std::map<std::string, double>;
    
    List_t list_objects;
};

#endif /* LIST_VIEW_H */
