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
#include "Agent.h"
#include "Structure_factory.h"
#include "Agent_factory.h"
#include "Geometry.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>

using namespace std;

Controller::Controller() : is_view_open(false) {
    
    // View commands
    cmd_map.insert(make_pair("open", &Controller::cmd_open));
    cmd_map.insert(make_pair("close", &Controller::cmd_close));
    cmd_map.insert(make_pair("default", &Controller::cmd_default));
    cmd_map.insert(make_pair("size", &Controller::cmd_size));
    cmd_map.insert(make_pair("zoom", &Controller::cmd_zoom));
    cmd_map.insert(make_pair("pan", &Controller::cmd_pan));
    
    // Whole-program commands
    cmd_map.insert(make_pair("status", &Controller::cmd_status));
    cmd_map.insert(make_pair("show", &Controller::cmd_show));
    cmd_map.insert(make_pair("go", &Controller::cmd_go));
    cmd_map.insert(make_pair("build", &Controller::cmd_build));
    cmd_map.insert(make_pair("train", &Controller::cmd_train));
    
    // Agent commands
    cmd_map.insert(make_pair("move", &Controller::cmd_move));
    cmd_map.insert(make_pair("work", &Controller::cmd_work));
    cmd_map.insert(make_pair("attack", &Controller::cmd_attack));
    cmd_map.insert(make_pair("stop", &Controller::cmd_stop));
    
    cout << "Controller constructed\n";
}

Controller::~Controller() {
    
    cout << "Controller destructed\n";
}

// create View object, run the program by acccepting user commands, then destroy View object
void Controller::run() {
    
    while (true) {
        
        cout << "\nTime " << g_Model_ptr->get_time() << ": Enter command: ";
        
        string command;
        cin >> command;
        
        if (command == "quit") {
            
            if (is_view_open)
                cmd_close(nullptr, nullptr);
            
            cout << "Done\n";
            return;
        }
        
        try {
            
            if (g_Model_ptr->is_agent_present(command)) {
                
                Agent* agent_ptr = g_Model_ptr->get_agent_ptr(command);
                if (!agent_ptr->is_alive())
                    throw Error("Agent is not alive!");
                
                string agent_cmd;
                cin >> agent_cmd;
                
                Cmd_func_t cmd_fp = find_command(agent_cmd);
                (this->*(cmd_fp))(agent_ptr, nullptr);
            } else {
                
                Cmd_func_t cmd_fp = find_command(command);
                (this->*(cmd_fp))(nullptr, view_ptr);
            }
        } catch (exception& e) {
            
            cout << e.what() << "\n";
            cin.clear();
            while (getchar() != '\n');  //clear remaining input line
        } catch(...) {
            
            if (is_view_open)
                cmd_close(nullptr, nullptr);
            
            cerr << "Unkown exception caught!\n";
            return;
        }
    }
}

// perform a lookup for a command function pointer by name
Controller::Cmd_func_t Controller::find_command(string& cmd_name) {
    
    auto cmd_it = cmd_map.find(cmd_name);
    if (cmd_it == cmd_map.end())
        throw Error("Unrecognized command!");
    
    return cmd_it->second;
}

// View commands

// open the view, throws error if view is already open
void Controller::cmd_open(Agent*, View*) {
    
    if (is_view_open)
        throw Error("View is already open!");
    
    is_view_open = true;
    view_ptr = new View;
    g_Model_ptr->attach(view_ptr);
}

// close the view, throws error if view is closed
void Controller::cmd_close(Agent*, View*) {
    
    if (!is_view_open)
        throw Error("View is not open!");
    
    is_view_open = false;
    g_Model_ptr->detach(view_ptr);
    delete view_ptr;
}

// sets view parameters to their defaults, throws error if view is closed
void Controller::cmd_default(Agent*, View* view) {
    
    if (!is_view_open)
        throw Error("View is not open!");
    
    view->set_defaults();
}

// sets view size, throws an error if view is closed
void Controller::cmd_size(Agent*, View* view) {
    
    if (!is_view_open)
        throw Error("View is not open!");
    
    int size;
    if (!(cin >> size))
        throw Error("Expected an integer!");
    
    view->set_size(size);
}

// sets view scale, throws an error if view is closed
void Controller::cmd_zoom(Agent*, View* view) {
    
    if (!is_view_open)
        throw Error("View is not open!");
    
    double scale;
    if (!(cin >> scale))
        throw Error("Expected a double!");
    
    view->set_scale(scale);
}

// sets view origin, throws an error if view is closed
void Controller::cmd_pan(Agent*, View* view) {
    
    if (!is_view_open)
        throw Error("View is not open!");
    
    double x, y;
    if (!(cin >> x >> y))
        throw Error("Expected a double!");
    
    view->set_origin(Point(x, y));
}

// Whole-program commands

// prints a list of sim_objects and their information
void Controller::cmd_status(Agent*, View*) {
    
    g_Model_ptr->describe();
}

// prints the view information
void Controller::cmd_show(Agent*, View* view) {
    
    if (!is_view_open)
        throw Error("View is not open!");
    
    view->draw();
}

// calls update on the Model, i.e. on every sim_object
void Controller::cmd_go(Agent*, View*) {
    
    g_Model_ptr->update();
}

// builds a new structure with the supplied name at the supplied location
// throws error if either name or location are invalid
void Controller::cmd_build(Agent*, View*) {
    
    string name;
    cin >> name;
    
    if ((name.length() < 2) || any_of(name.begin(), name.end(), [](char& c){return !isalnum(c);}) ||
        (cmd_map.find(name) != cmd_map.end()) || g_Model_ptr->is_name_in_use(name))
        throw Error("Invalid name for new object!");
    
    string type;
    cin >> type;
    
    double x, y;
    if (!(cin >> x >> y))
        throw Error("Expected a double!");
    
    g_Model_ptr->add_structure(create_structure(name, type, Point(x, y)));
}

// trains a new agent with the supplied name at the supplied location
// throws error if either name or location are invalid
void Controller::cmd_train(Agent*, View*) {
    
    string name;
    cin >> name;
    
    if ((name.length() < 2) || any_of(name.begin(), name.end(), [](char& c){return !isalnum(c);}) ||
        (cmd_map.find(name) != cmd_map.end()) || g_Model_ptr->is_name_in_use(name))
        throw Error("Invalid name for new object!");
    
    string type;
    cin >> type;
    
    double x, y;
    if (!(cin >> x >> y))
        throw Error("Expected a double!");
    
    g_Model_ptr->add_agent(create_agent(name, type, Point(x, y)));
}

// Agent commands

// initiate an agent's movement to supplied coordinates
void Controller::cmd_move(Agent* agent, View*) {
    
    double x, y;
    if (!(cin >> x >> y))
        throw Error("Expected a double!");
    
    agent->move_to(Point(x, y));
}

// initiate a peasant's work between a destination and source structure
void Controller::cmd_work(Agent* agent, View*) {
    
    string src_structure, dst_structure;
    cin >> src_structure >> dst_structure;
    agent->start_working(g_Model_ptr->get_structure_ptr(src_structure), g_Model_ptr->get_structure_ptr(dst_structure));
}

// initiate a soldier's attack on another agent
void Controller::cmd_attack(Agent* agent, View*) {
    
    string target_name;
    cin >> target_name;
    agent->start_attacking(g_Model_ptr->get_agent_ptr(target_name));
}

// tells an agent to stop moving
void Controller::cmd_stop(Agent* agent, View*) {
    
    agent->stop();
}
