/* Controller
 This class is responsible for controlling the Model and View according to interactions
 with the user.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <memory>
#include <vector>
#include <string>

class Model;
class View;
class Grid_view;
class List_view;
class Component;
class Group;
class Agent;

class Controller {
public:
    
    // Output a message after doing all initialization and clean-up work
    Controller();
    
    // create View object, run the program by acccepting user commands, then destroy View object
    void run();

private:
    
    // Program command aliases
    using Cmd_func_t = void(Controller::*)();
    using Cmd_map_t = std::map<std::string, Cmd_func_t>;

    // Agent command aliases
    using Component_cmd_func_t = void(Controller::*)(std::shared_ptr<Component>) const;
    using Component_cmd_map_t = std::map<std::string, Component_cmd_func_t>;
    
    // Containers to hold/distinguish program, agent, and group commands
    Cmd_map_t program_cmd_map;
    Component_cmd_map_t component_cmd_map;

    // Containers to track open views
    std::map<std::string, std::shared_ptr<View>> open_views;
    std::vector<std::string> view_names;
    
    // Templated command lookup - for use with either of the cmd_maps
    template <typename T>
    T find_cmd(const std::string& cmd_name, std::map<std::string, T>& cmd_map) const;
    
    // View commands
    void cmd_open();
    void cmd_close();
    void cmd_default();
    void cmd_size();
    void cmd_zoom();
    void cmd_pan();
    
    // Throw an error if map view is not open
    void check_open_map() const;
    
    // Whole-program commands
    void cmd_quit();
    void cmd_status();
    void cmd_show();
    void cmd_go();
    void cmd_build();
    void cmd_train();
    void cmd_group();
    void cmd_disband();
    
    // Component commands
    void cmd_move(std::shared_ptr<Component> component_ptr) const;
    void cmd_work(std::shared_ptr<Component> component_ptr) const;
    void cmd_attack(std::shared_ptr<Component> component_ptr) const;
    void cmd_stop(std::shared_ptr<Component> component_ptr) const;
    void cmd_add(std::shared_ptr<Component> component_ptr) const;
    void cmd_remove(std::shared_ptr<Component> component_ptr) const;
    
    // needed in Controller class to ensure new object's name is not one of the command strings
    void check_object_name(std::string& name) const;
    // check that a supplied name string does not conflict with any program commands
    bool check_command_name_conflict(const std::string& name) const;
    
    // Create and return the pointer to the specified View type. If the type
    // is unrecognized, throws Error("Trying to create view of unknown type!")
    // The Structure is allocated with new, so some other component is resposible for deleting it.
    std::shared_ptr<View> create_view(const std::string& type) const;
};

#endif
