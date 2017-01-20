//
//  Group.cpp
//  six_project
//
//  Created by Luke Nittmann on 12/5/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Group.h"
#include "Agent.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include <typeinfo>

using namespace std;

Group::Group(const string& group_name_) : Component(group_name_) {}

bool Group::check_group_members(std::shared_ptr<Component> component_ptr) {
    
    for (auto child_it : children)
        if (component_ptr == child_it.second)
            return true;
    
    return false;
}

Point Group::get_location() const {

    throw Error("Group does not have a location!");
}

void Group::describe() const {
    
    cout << "Group " << get_name() << "\n   Members:\n";
    if (children.empty())
        cout << "    None\n";
    else {
        
        for (auto component_ptr : children) {
            
            string type = typeid(*(component_ptr.second)).name();
            cout << "    - " << type.substr(1, type.size()) << " " << component_ptr.first << "\n";
        }
    }
}

void Group::move_to(Point destination) {
    
    Cmd_set_t cmd_set;
    fill_cmd_set(cmd_set);
    for_each(cmd_set.begin(), cmd_set.end(), [&destination](Cmd_set_t::value_type component_ptr){component_ptr->move_to(destination);});
}

void Group::stop() {
    
    Cmd_set_t cmd_set;
    fill_cmd_set(cmd_set);
    for_each(cmd_set.begin(), cmd_set.end(), [](Cmd_set_t::value_type component_ptr){component_ptr->stop();});
}

void Group::start_working(shared_ptr<Structure> src, shared_ptr<Structure> dst) {
    
    Cmd_set_t cmd_set;
    fill_cmd_set(cmd_set);
    for_each(cmd_set.begin(), cmd_set.end(), [src, dst](Cmd_set_t::value_type component_ptr){component_ptr->start_working(src, dst);});
}

void Group::start_attacking(shared_ptr<Agent> target) {

    Cmd_set_t cmd_set;
    fill_cmd_set(cmd_set);
    for_each(cmd_set.begin(), cmd_set.end(), [target](Cmd_set_t::value_type component_ptr){component_ptr->start_attacking(target);});
}

void Group::add_component(shared_ptr<Component> component_ptr) {
    
    string component_name = component_ptr->get_name();
    if (component_name == get_name())
        throw Error("A group can't add itself!");
    else if (check_group_members(component_ptr))
        throw Error("Component already present in the group!");

    // if already a child of this group, can't add it as a member
    if (shared_ptr<Group> group_ptr = dynamic_pointer_cast<Group>(component_ptr))
        if (group_ptr->check_group_members(shared_from_this()))
            throw Error("Two groups can't contain each other!");

    children.insert(make_pair(component_name, component_ptr));
}

void Group::remove_component(shared_ptr<Component> component_ptr) {
    
    if (!check_group_members(component_ptr))
        throw Error("Component not found in group!");
    
    children.erase(component_ptr->get_name());
}

void Group::fill_cmd_set(Cmd_set_t& fill_set) {
    
    for (auto child_it : children) {
        
        if (shared_ptr<Group> group_ptr = dynamic_pointer_cast<Group>(child_it.second))
            group_ptr->fill_cmd_set(fill_set);
        else
            fill_set.insert(child_it.second);
    }
}
