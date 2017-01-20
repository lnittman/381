#include "Model.h"
#include "View.h"
#include "Component.h"
#include "Group.h"
#include "Sim_object.h"
#include "Agent.h"
#include "Structure.h"
#include "Structure_factory.h"
#include "Agent_factory.h"
#include "Geometry.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

// returns the static singleton instantiation of Model
Model& Model::get_instance() {
    
    static Model m;
    return m;
}

/*
 
 
 Sim_object services
 
 
*/

// is name already in use for either agent, group, or structure?
// return true if the name matches the name of an existing agent, group, or structure
bool Model::is_name_in_use(const string& name) const {
    
    return (sim_object_list.find(name) != sim_object_list.end()) || (component_list.find(name) != component_list.end());
}

// tell all objects to describe themselves to the console
void Model::describe() const {
    
    for_each(sim_object_list.begin(), sim_object_list.end(), [](Sim_list_t::value_type sim_obj){sim_obj->describe();});
}

// increment the time, and tell all objects to update themselves
void Model::update() {
    
    ++time;
    for_each(sim_object_list.begin(), sim_object_list.end(), [](Sim_list_t::value_type sim_obj){sim_obj->update();});
}

/*
 
 
 Structure services
 
 
 */

// is there a structure with this name?
bool Model::is_structure_present(const string& name) const {
    
    return structure_list.find(name) != structure_list.end();
}

// will throw Error("Structure not found!") if no structure of that name
shared_ptr<Structure> Model::get_structure_ptr(const string& name) const {

    auto structure_it = structure_list.find(name);
    if (structure_it == structure_list.end())
        throw Error("Structure not found!");

    return structure_it->second;
}

// add a new structure; assumes none with the same name
void Model::add_structure(shared_ptr<Structure> structure) {
    
    structure_list.emplace(structure->get_name(), structure);
    sim_object_list.insert(structure);
    structure->broadcast_current_state();
}

// return a shared_ptr to the closest structure
shared_ptr<Structure> Model::find_closest_structure(shared_ptr<Sim_object> sim_obj) const {
 
    return for_each(structure_list.begin(), structure_list.end(), Find_closest<Structure>(sim_obj)).closest_sim;
}

/*
 
 
 Component services
 
 
 */

//
bool Model::is_component_present(const string& name) const {
    
    return component_list.find(name) != component_list.end();
}

// will throw Error("Component not found") if no component (agent/group) of that name
std::shared_ptr<Component> Model::get_component_ptr(const std::string& name) const {
    
    auto component_it = component_list.find(name);
    if (component_it == component_list.end())
        throw Error("Component not found!");
    
    return component_it->second;
}

// add a new component; assumes none with the same name
void Model::add_component(std::shared_ptr<Component> component_ptr) {

    sim_object_list.insert(component_ptr);
    component_list.emplace(component_ptr->get_name(), component_ptr);
    component_ptr->broadcast_current_state();
}

// remove an existing component from the containers
void Model::remove_component(std::shared_ptr<Component> component_ptr) {
    
    sim_object_list.erase(component_ptr);
    component_list.erase(component_ptr->get_name());
    
    // remove the component from each group that it was a member of
    for (auto component : component_list)
        if (shared_ptr<Group> group_ptr = dynamic_pointer_cast<Group>(component.second))
            if (group_ptr->check_group_members(component_ptr))
                group_ptr->remove_component(component_ptr);
}


// find the name of the closest agent
shared_ptr<Agent> Model::find_closest_agent(shared_ptr<Sim_object> sim_obj) const {
    
    shared_ptr<Component> component_ptr = for_each(component_list.begin(), component_list.end(), Find_closest<Component>(sim_obj)).closest_sim;
    return static_pointer_cast<Agent>(component_ptr);
}

/* 
 
 
 View services 
 
 
*/

// Attaching a View adds it to the container and causes it to be updated
// with all current objects'location (or other state information).
void Model::attach(shared_ptr<View> view_) {

    view_list.push_back(view_);
    for_each(sim_object_list.begin(), sim_object_list.end(), [](Sim_list_t::value_type sim_obj){sim_obj->broadcast_current_state();});
}

// Detach the View by discarding the supplied pointer from the container of Views
// - no updates sent to it thereafter.
void Model::detach(shared_ptr<View> view_) {

    auto view_it = find(view_list.begin(), view_list.end(), view_);
    view_list.erase(view_it);
}

// notify the views about an object's location
void Model::notify_location(const string& name, Point location) const {

    for_each(view_list.begin(), view_list.end(), bind(&View::update_location, _1, name, location));
}

// notify the views that an object is now gone
void Model::notify_gone(const string& name) const {

    for_each(view_list.begin(), view_list.end(), bind(&View::update_remove, _1, name));
}

// notify the views about an object's health
void Model::notify_health(const string& name, int health) const {
    
    for_each(view_list.begin(), view_list.end(), bind(&View::update_health, _1, name, health));
}

// notify the views about an object's amount
void Model::notify_amount(const string& name, double amount) const {
    
    for_each(view_list.begin(), view_list.end(), bind(&View::update_amount, _1, name, amount));
}

/*
 
 
 Find_closest operator() definition
 
 
 */

template <typename T>
void Model::Find_closest<T>::operator()(typename Object_list_t::value_type sim_it) {

    shared_ptr<T> sim_obj = sim_it.second;
    if (dynamic_pointer_cast<Group>(sim_it.second) || sim_ptr == sim_obj)
        return;
    
    double distance = cartesian_distance(sim_ptr->get_location(), sim_obj->get_location());
    if (distance < min_distance) {
        
        min_distance = distance;
        closest_sim = sim_obj;
    }
}

/*
 
 
 Model constructor
 
 
 */

Model::Model() {
    
    shared_ptr<Structure> rivendale = create_structure("Rivendale", "Farm", Point(10., 10.));
    sim_object_list.insert(rivendale);
    structure_list.emplace("Rivendale", rivendale);
    
    shared_ptr<Structure> sunnybrook = create_structure("Sunnybrook", "Farm", Point(0., 30.));
    sim_object_list.insert(sunnybrook);
    structure_list.emplace("Sunnybrook", sunnybrook);
    
    shared_ptr<Structure> shire = create_structure("Shire", "Town_Hall", Point(20., 20.));
    sim_object_list.insert(shire);
    structure_list.emplace("Shire", shire);
    
    shared_ptr<Structure> paduca = create_structure("Paduca", "Town_Hall", Point(30., 30.));
    sim_object_list.insert(paduca);
    structure_list.emplace("Paduca", paduca);
    
    shared_ptr<Agent> pippin = create_agent("Pippin", "Peasant", Point(5., 10.));
    sim_object_list.insert(pippin);
    component_list.emplace("Pippin", pippin);
    
    shared_ptr<Agent> merry = create_agent("Merry", "Peasant", Point(0., 25.));
    sim_object_list.insert(merry);
    component_list.emplace("Merry", merry);
    
    shared_ptr<Agent> zug = create_agent("Zug", "Soldier", Point(20., 30.));
    sim_object_list.insert(zug);
    component_list.emplace("Zug", zug);
    
    shared_ptr<Agent> bug = create_agent("Bug", "Soldier", Point(15., 20.));
    sim_object_list.insert(bug);
    component_list.emplace("Bug", bug);
    
    shared_ptr<Agent> iriel = create_agent("Iriel", "Archer", Point(20., 38.));
    sim_object_list.insert(iriel);
    component_list.emplace("Iriel", iriel);
}
