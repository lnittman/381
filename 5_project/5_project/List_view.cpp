//
//  List_view.cpp
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "List_view.h"
#include <algorithm>
#include <iostream>

using std::cout;
using std::string;

void List_view::update_remove(const string& name)  {
    
    list_objects.erase(name);
}

void List_view::update_list(const string &name, double list_datum) {
    
    list_objects[name] = list_datum;
}

void List_view::draw() const {
    
    cout << "--------------\n";
    for_each(list_objects.begin(), list_objects.end(), [](List_t::value_type obj){cout << obj.first << ": " << obj.second << "\n";});
    cout << "--------------\n";
}
