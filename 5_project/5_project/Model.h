/*
 Model is part of a simplified Model-View-Controller pattern.
 Model keeps track of the Sim_objects in our little world. It is the only
 component that knows how many Structures and Agents there are, but it does not
 know about any of their derived classes, nor which Agents are of what kind of Agent.
 It has facilities for looking up objects by name, and removing Agents.  When
 created, it creates an initial group of Structures and Agents using the Structure_factory
 and Agent_factory.
 Finally, it keeps the system's time.
 
 Controller tells Model what to do; Model in turn tells the objects what do, and
 when asked to do so by an object, tells all the Views whenever anything changes that might be relevant.
 Model also provides facilities for looking up objects given their name.
 
 Notice how only the Standard Library headers need to be included - reduced coupling!
 
 */

#ifndef MODEL_H
#define MODEL_H

#include "Utility.h"
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class View;
class Sim_object;
class Component;
class Group;
class Agent;
class Structure;
struct Point;

class Model {
public:
   
    static Model& get_instance();
    
    // return the current time
    int get_time() const
    {return time;}
    
    /* Sim_object services */
    
    // is name already in use for either agent or structure?
    // return true if the name matches the name of an existing agent or structure
    bool is_name_in_use(std::string& name) const;
    // tell all objects to describe themselves to the console
    void describe() const;
    // increment the time, and tell all objects to update themselves
    void update();

    /* Structure services */
    
    // is there a structure with this name?
    bool is_structure_present(const std::string& name) const;
    // will throw Error("Structure not found!") if no structure of that name
    std::shared_ptr<Structure> get_structure_ptr(const std::string& name) const;
    // find the name of the closest structure
    std::shared_ptr<Structure> find_closest_structure(std::shared_ptr<Sim_object> sim_obj) const;
    // add a new structure; assumes none with the same name
    void add_structure(std::shared_ptr<Structure>);
    
    /* Component services */
    
    // is there a component (group or agent) with this name?
    bool is_component_present(const std::string& name) const;
    // will throw Error("Component not found") if no component (agent/group) of that name
    std::shared_ptr<Component> get_component_ptr(const std::string& name) const;
    // find the name of the closest agent
    std::shared_ptr<Agent> find_closest_agent(std::shared_ptr<Sim_object> sim_obj) const;
    // add a new group; assumes none with the same name
    void add_component(std::shared_ptr<Component> agent_ptr);
    // remove an existing group from the group list
    void remove_component(std::shared_ptr<Component> agent_ptr);
    
    /* View services */
    
    // Attaching a View adds it to the container and causes it to be updated
    // with all current objects'location (or other state information.
    void attach(std::shared_ptr<View> view_);
    // Detach the View by discarding the supplied pointer from the container of Views
    // - no updates sent to it thereafter.
    void detach(std::shared_ptr<View> view_);
    // notify the views about an object's location
    void notify_location(const std::string& name, Point location) const;
    // notify the views that an object is now gone
    void notify_gone(const std::string& name) const;
    // notify the views about an object's health
    void notify_health(const std::string& name, int health) const;
    // notify the views about an object's amount
    void notify_amount(const std::string& name, double amount) const;
    
private:
    
    using Sim_list_t = std::set<std::shared_ptr<Sim_object>, Sim_comp>;
    using Structure_list_t = std::map<std::string, std::shared_ptr<Structure>>;
    using Component_list_t = std::map<std::string, std::shared_ptr<Component>>;
    using View_list_t = std::vector<std::shared_ptr<View>>;
    
    int time;
    
    Sim_list_t sim_object_list;
    Structure_list_t structure_list;
    Component_list_t component_list;
    View_list_t view_list;
    
    // create the initial objects
    Model();
    ~Model() {}
    
    template <typename T>
    struct Find_closest {
        
        using Object_list_t = std::map<std::string, std::shared_ptr<T>>;
        
        Find_closest(std::shared_ptr<Sim_object> sim_ptr_) : sim_ptr(sim_ptr_) {}
        void operator()(typename Object_list_t::value_type sim_it);
        
        double min_distance = std::numeric_limits<double>::infinity();
        std::shared_ptr<Sim_object> sim_ptr;
        std::shared_ptr<T> closest_sim;
    };
    
    // disallow copy/move construction or assignment
    Model(const Model&) = delete;
    Model& operator= (const Model&)  = delete;
    Model(Model&&) = delete;
    Model& operator= (Model&&) = delete;
};

#endif
