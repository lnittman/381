#include "Model.h"
#include "View.h"
#include "Structure.h"
#include "Agent.h"
#include "Structure_factory.h"
#include "Agent_factory.h"
#include "Geometry.h"
#include "Utility.h"
#include <algorithm>
#include <functional>
#include <iostream>

class Sim_object;

using namespace std;
using namespace std::placeholders;

Model* g_Model_ptr = nullptr;

Model::Model() {
    
    Structure* rivendale = create_structure("Rivendale", "Farm", Point(10., 10.));
    sim_object_list.push_back(rivendale);
    structure_list.push_back(rivendale);
    
    Structure* sunnybrook = create_structure("Sunnybrook", "Farm", Point(0., 30.));
    sim_object_list.push_back(sunnybrook);
    structure_list.push_back(sunnybrook);
    
    Structure* shire = create_structure("Shire", "Town_Hall", Point(20., 20.));
    sim_object_list.push_back(shire);
    structure_list.push_back(shire);
    
    Structure* paduca = create_structure("Paduca", "Town_Hall", Point(30., 30.));
    sim_object_list.push_back(paduca);
    structure_list.push_back(paduca);
    
    Agent* pippin = create_agent("Pippin", "Peasant", Point(5., 10.));
    sim_object_list.push_back(pippin);
    agent_list.push_back(pippin);
    
    Agent* merry = create_agent("Merry", "Peasant", Point(0., 25.));
    sim_object_list.push_back(merry);
    agent_list.push_back(merry);
    
    Agent* zug = create_agent("Zug", "Soldier", Point(20., 30.));
    sim_object_list.push_back(zug);
    agent_list.push_back(zug);
    
    Agent* bug = create_agent("Bug", "Soldier", Point(15., 20.));
    sim_object_list.push_back(bug);
    agent_list.push_back(bug);
    
    sort(sim_object_list.begin(), sim_object_list.end(), Sim_ptr_comp());
    sort(structure_list.begin(), structure_list.end(), Sim_ptr_comp());
    sort(agent_list.begin(), agent_list.end(), Sim_ptr_comp());
    cout << "Model constructed\n";
}

Model::~Model() {
    
    for_each(sim_object_list.begin(), sim_object_list.end(), Delete());
    cout << "Model destructed\n";
}

// is name already in use for either agent or structure?
// return true if the name matches the name of an existing agent or structure
bool Model::is_name_in_use(const std::string& name) const {
    
    return any_of(sim_object_list.begin(), sim_object_list.end(), Name_search{name});
}

// is there a structure with this name?
bool Model::is_structure_present(const std::string& name) const {
    
    return any_of(structure_list.begin(), structure_list.end(), Name_search{name});
}

// add a new structure; assumes none with the same name
void Model::add_structure(Structure* structure) {
    
    auto sim_it = lower_bound(sim_object_list.begin(), sim_object_list.end(), structure, Sim_ptr_comp());
    sim_object_list.insert(sim_it, structure);
    
    auto structure_it = lower_bound(structure_list.begin(), structure_list.end(), structure, Sim_ptr_comp());
    structure_list.insert(structure_it, structure);
    
    structure->broadcast_current_state();
}

// will throw Error("Structure not found!") if no structure of that name
Structure* Model::get_structure_ptr(const std::string& name) const {
    
    auto structure_it = lower_bound(structure_list.begin(), structure_list.end(), name, Sim_ptr_comp());
    if ((*structure_it)->get_name() != name)
        throw Error("Structure not found!");
    
    return *structure_it;
}

// is there an agent with this name?
bool Model::is_agent_present(const std::string& name) const {
    
    return any_of(agent_list.begin(), agent_list.end(), Name_search{name});
}

// add a new agent; assumes none with the same name
void Model::add_agent(Agent* agent) {
    
    auto sim_it = lower_bound(sim_object_list.begin(), sim_object_list.end(), agent, Sim_ptr_comp());
    sim_object_list.insert(sim_it, agent);
    
    auto agent_it = lower_bound(agent_list.begin(), agent_list.end(), agent, Sim_ptr_comp());
    agent_list.insert(agent_it, agent);
    agent->broadcast_current_state();
}

// will throw Error("Agent not found!") if no agent of that name
Agent* Model::get_agent_ptr(const std::string& name) const {
    
    auto agent_it = lower_bound(agent_list.begin(), agent_list.end(), name, Sim_ptr_comp());
    if ((*agent_it)->get_name() != name)
        throw Error("Agent not found!");
    
    return *agent_it;
}

// tell all objects to describe themselves to the console
void Model::describe() const {
    
    for_each(sim_object_list.begin(), sim_object_list.end(), bind(&Sim_object::describe, _1));
}

// increment the time, and tell all objects to update themselves
void Model::update() {
    
    ++time;
    for_each(sim_object_list.begin(), sim_object_list.end(), bind(&Sim_object::update, _1));
    
    vector<Agent*> disappearing_agents;
    for (auto agent : agent_list) {
        
        if (agent->is_disappearing()) {
            
            disappearing_agents.push_back(agent);
            auto sim_it = lower_bound(sim_object_list.begin(), sim_object_list.end(), agent, Sim_ptr_comp());
            sim_object_list.erase(sim_it);
            
            auto agent_it = lower_bound(agent_list.begin(), agent_list.end(), agent, Sim_ptr_comp());
            agent_list.erase(agent_it);
        }
    }
    
    for_each(disappearing_agents.begin(), disappearing_agents.end(), Delete());
}

/* View services */
// Attaching a View adds it to the container and causes it to be updated
// with all current objects'location (or other state information.
void Model::attach(View* view_) {
    
    view_list.push_back(view_);
    for_each(sim_object_list.begin(), sim_object_list.end(), bind(&Sim_object::broadcast_current_state, _1));
}

// Detach the View by discarding the supplied pointer from the container of Views
// - no updates sent to it thereafter.
void Model::detach(View* view) {
    
    auto view_it = find(view_list.begin(), view_list.end(), view);
    view_list.erase(view_it);
}

// notify the views about an object's location
void Model::notify_location(const std::string& name, Point location) const {
    
    for_each(view_list.begin(), view_list.end(), bind(&View::update_location, _1, name, location));
}

// notify the views that an object is now gone
void Model::notify_gone(const std::string& name) const {
    
    for_each(view_list.begin(), view_list.end(), bind(&View::update_remove, _1, name));
}

bool Model::Name_search::operator()(Sim_object *sim_obj) {
    
    return name == sim_obj->get_name();
}

bool Model::Sim_ptr_comp::operator()(const Sim_object* s1, const Sim_object* s2) {
    
    return s1->get_name() < s2->get_name();
}

bool Model::Sim_ptr_comp::operator()(const Sim_object* s, const std::string& name) {
    
    return s->get_name() < name;
}
