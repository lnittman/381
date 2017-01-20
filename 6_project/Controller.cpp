//
//  Controller.cpp
//  four_project
//
//  Created by Luke Nittmann on 11/2/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "Controller.h"
#include "Model.h"
#include "View.h"
#include "Map_view.h"
#include "Local_view.h"
#include "Health_view.h"
#include "Amount_view.h"
#include "Component.h"
#include "Group.h"
#include "Agent.h"
#include "Structure.h"
#include "Structure_factory.h"
#include "Agent_factory.h"
#include "Geometry.h"
#include "Utility.h"
#include <algorithm>
#include <cassert>
#include <iostream>

const int Min_name_length_c = 2;

using namespace std;
using namespace std::placeholders;

static int read_int();
static double read_double();
static Point read_coordinates();

Controller::Controller() {
 
    shared_ptr<int> intShared(new int);
    intShared.reset();



    // View commands
    program_cmd_map.insert(make_pair("open", &Controller::cmd_open));
    program_cmd_map.insert(make_pair("close", &Controller::cmd_close));
    program_cmd_map.insert(make_pair("default", &Controller::cmd_default));
    program_cmd_map.insert(make_pair("size", &Controller::cmd_size));
    program_cmd_map.insert(make_pair("zoom", &Controller::cmd_zoom));
    program_cmd_map.insert(make_pair("pan", &Controller::cmd_pan));

    // Whole-program commands
    program_cmd_map.insert(make_pair("status", &Controller::cmd_status));
    program_cmd_map.insert(make_pair("show", &Controller::cmd_show));
    program_cmd_map.insert(make_pair("go", &Controller::cmd_go));
    program_cmd_map.insert(make_pair("build", &Controller::cmd_build));
    program_cmd_map.insert(make_pair("train", &Controller::cmd_train));
    program_cmd_map.insert(make_pair("group", &Controller::cmd_group));
    program_cmd_map.insert(make_pair("disband", &Controller::cmd_disband));

    // Component (group or agent) commands
    component_cmd_map.insert(make_pair("move", &Controller::cmd_move));
    component_cmd_map.insert(make_pair("work", &Controller::cmd_work));
    component_cmd_map.insert(make_pair("attack", &Controller::cmd_attack));
    component_cmd_map.insert(make_pair("stop", &Controller::cmd_stop));
    component_cmd_map.insert(make_pair("add", &Controller::cmd_add));
    component_cmd_map.insert(make_pair("remove", &Controller::cmd_remove));
}

// run the program by acccepting user commands
void Controller::run() {
    
    Model::get_instance();  //instantiate the Model singleton
    
    while (true) {
        
        cout << "\nTime " << Model::get_instance().get_time() << ": Enter command: ";

        string command;
        cin >> command;
        
        try {
        
            if (command == "quit") {
                
                cout << "Done\n";
                return;
            } else if (Model::get_instance().is_component_present(command)) {
                
                string component_cmd;
                cin >> component_cmd;
                
                shared_ptr<Component> component_ptr = Model::get_instance().get_component_ptr(command);
                Component_cmd_func_t cmd_fp = find_cmd(component_cmd, component_cmd_map);
                (this->*(cmd_fp))(component_ptr);
            } else {
                
                Cmd_func_t cmd_fp = find_cmd(command, program_cmd_map);
                (this->*(cmd_fp))();
            }
        } catch (Error& e) {
            
            cout << e.what() << "\n";
            cin.clear();
            while (getchar() != '\n');  //clear remaining input line
        } catch(...) {
            
            cerr << "Unkown exception caught!\n";
            return;
        }
    }
}

/*
 

 Command lookup
 
 
*/

template <typename T>
T Controller::find_cmd(const std::string& cmd_name, map<string, T>& cmd_map) const {
    
    auto cmd_it = cmd_map.find(cmd_name);
    if (cmd_it == cmd_map.end())
        throw Error("Unrecognized command!");
    
    return cmd_it->second;
}

/*
 
 
 View commands 
 
 
*/

// open the view, throws error if view is already open
void Controller::cmd_open() {
    
    string view_name;
    cin >> view_name;
    
    if (open_views.find(view_name) != open_views.end())
        throw Error("View of that name already open!");
    
    open_views.emplace(view_name, create_view(view_name));
    Model::get_instance().attach(open_views[view_name]);
    view_names.push_back(view_name);
}

// close the view, throws error if view is closed
void Controller::cmd_close() {
    
    string view_name;
    cin >> view_name;
    
    if (open_views.find(view_name) == open_views.end())
        throw Error("No view of that name is open!");

    Model::get_instance().detach(open_views[view_name]);
    view_names.erase(remove(view_names.begin(), view_names.end(), view_name));
    open_views.erase(view_name);
}

// sets view parameters to their defaults, throws error if view is closed
void Controller::cmd_default() {
    
    check_open_map();
    
    shared_ptr<Map_view> map_ptr = static_pointer_cast<Map_view>(open_views["map"]);
    map_ptr->set_defaults();
} 

// sets view size, throws an error if view is closed
void Controller::cmd_size() {
    
    check_open_map();
    
    int size = read_int();
    shared_ptr<Map_view> map_ptr = static_pointer_cast<Map_view>(open_views["map"]);
    map_ptr->set_size(size);
} 

// sets view scale, throws an error if view is closed
void Controller::cmd_zoom() {
    
    check_open_map();
    
    double scale = read_double();
    shared_ptr<Map_view> map_ptr = static_pointer_cast<Map_view>(open_views["map"]);
    map_ptr->set_scale(scale);
} 

// sets view origin, throws an error if view is closed
void Controller::cmd_pan() {
    
    check_open_map();
    
    Point pan_origin = read_coordinates();
    shared_ptr<Map_view> map_ptr = static_pointer_cast<Map_view>(open_views["map"]);
    map_ptr->set_origin(pan_origin);
} 

void Controller::check_open_map() const {
    
    if (open_views.find("map") == open_views.end())
        throw Error("No map view is open!");
}  

/* 
 

 Whole-program commands
 
 
*/

// prints a list of sim_objects and their information
void Controller::cmd_status() {
    
    Model::get_instance().describe();
} 

// prints the view information
void Controller::cmd_show() {
    
    for_each(view_names.begin(), view_names.end(), [this](const string& name){open_views[name]->draw();});
} 

// calls update on the Model, i.e. on every sim_object
void Controller::cmd_go() {
    
    Model::get_instance().update();
} 

// builds a new structure with the supplied name at the supplied location
// throws error if either name or location are invalid
void Controller::cmd_build() {
    
    string name;
    cin >> name;
    check_object_name(name);
    
    string type;
    cin >> type;
    
    Point build_coordinates = read_coordinates();
    Model::get_instance().add_structure(create_structure(name, type, build_coordinates));
}

// trains a new agent with the supplied name at the supplied location
// throws error if either name or location are invalid
void Controller::cmd_train() {
    
    string name;
    cin >> name;
    check_object_name(name);
    
    string type;
    cin >> type;
    
    Point train_coordinates = read_coordinates();
    Model::get_instance().add_component(create_agent(name, type, train_coordinates));
}

// forms a new group with the supplied name and no members
// throws an error if name is invalid
void Controller::cmd_group() {
    
    string group_name;
    cin >> group_name;
    check_object_name(group_name);
    
    Model::get_instance().add_component(make_shared<Group>(group_name));
}

// disbands the group with the supplied name
// throws an error if the user tries to 'disband' an individual agent
void Controller::cmd_disband() {
    
    string group_name;
    cin >> group_name;
    
    shared_ptr<Component> component_ptr = Model::get_instance().get_component_ptr(group_name);
    if (dynamic_pointer_cast<Agent>(component_ptr))
        throw Error("Can't disband an agent!");
        
    Model::get_instance().remove_component(component_ptr);
}

/*
 
 
 Component (group or agent) commands
 
 
 */

// initiate a component's movement to supplied coordinates
void Controller::cmd_move(shared_ptr<Component> component_ptr) const {
    
    Point destination = read_coordinates();
    component_ptr->move_to(destination);
}  

// initiate a component's work between a destination and source structure
void Controller::cmd_work(shared_ptr<Component> component_ptr) const {
    
    string src_name, dst_name;
    cin >> src_name >> dst_name;
    
    shared_ptr<Structure> src_ptr = Model::get_instance().get_structure_ptr(src_name);
    shared_ptr<Structure> dst_ptr = Model::get_instance().get_structure_ptr(dst_name);
    component_ptr->start_working(src_ptr, dst_ptr);
} 

// initiate a component's attack on another agent
void Controller::cmd_attack(shared_ptr<Component> component_ptr) const {
    
    string target_name;
    cin >> target_name;
    
    shared_ptr<Component> target_ptr = Model::get_instance().get_component_ptr(target_name);
    if (dynamic_pointer_cast<Group>(target_ptr))
        throw Error("Can't attack a group!");
    
    component_ptr->start_attacking(static_pointer_cast<Agent>(target_ptr));
}

// tells a component to stop moving
void Controller::cmd_stop(shared_ptr<Component> component_ptr) const {
    
    component_ptr->stop();
}

// Add the component with the supplied name to the group if it exists
void Controller::cmd_add(std::shared_ptr<Component> component_ptr) const {
    
    string component_name;
    cin >> component_name;
        
    shared_ptr<Component> add_component_ptr = Model::get_instance().get_component_ptr(component_name);
    component_ptr->add_component(add_component_ptr);
}

// Remove the component with the supplied name from the group if it exists
void Controller::cmd_remove(std::shared_ptr<Component> component_ptr) const {
    
    string component_name;
    cin >> component_name;
    
    shared_ptr<Component> remove_component_ptr = Model::get_instance().get_component_ptr(component_name);
    component_ptr->remove_component(remove_component_ptr);
}

/*

 
 Controller utils
 
 
*/

// Checks an input string for validity as a Sim_object name value
void Controller::check_object_name(string& name) const {
    
    if ((name.length() < Min_name_length_c) || any_of(name.begin(), name.end(), [](char& c){return !isalnum(c);}) || check_command_name_conflict(name) || Model::get_instance().is_name_in_use(name))
        throw Error("Invalid name for new object!");
}

// Checks an input string for naming conflicts with a program command string
bool Controller::check_command_name_conflict(const string& name) const {
    
    return (program_cmd_map.find(name) != program_cmd_map.end()) || (component_cmd_map.find(name) != component_cmd_map.end()) || (name == "quit");
}

// Create and return the pointer to the specified View type.
// If the specified type is a group name, throws Error("Can't open a local view for a group!")
// If the type is unrecognized, throws Error("No object of that name!")
shared_ptr<View> Controller::create_view(const string& type) const {
    
    if (type == "map")
        return make_shared<Map_view>();
    else if (type == "health")
        return make_shared<Health_view>();
    else if (type == "amounts")
        return make_shared<Amount_view>();
    else if (Model::get_instance().is_structure_present(type))
        return make_shared<Local_view>(type, Model::get_instance().get_structure_ptr(type)->get_location());
    else if (Model::get_instance().is_component_present(type)) {
        
        shared_ptr<Component> component_ptr = Model::get_instance().get_component_ptr(type);
        return make_shared<Local_view>(type, component_ptr->get_location());
    }
    
    throw Error("No object of that name!");
}

static int read_int() {
    
    int read_;
    if (!(cin >> read_))
        throw Error("Expected an integer!");
    
    return read_;
}

static double read_double() {
    
    double read_;
    if (!(cin >> read_))
        throw Error("Expected a double!");
    
    return read_;
}

static Point read_coordinates() {
    
    double x_coord = read_double();
    double y_coord = read_double();
    return Point(x_coord, y_coord);
}
