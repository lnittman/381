//
//  Group.h
//  six_project
//
//  Created by Luke Nittmann on 12/5/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef GROUP_H
#define GROUP_H

#include "Component.h"
#include "Geometry.h"
#include "Utility.h"
#include <map>
#include <memory>
#include <set>
#include <string>

class Group : public Component {
    
public:
    
    Group(const std::string& group_name);
    
    bool check_group_members(std::shared_ptr<Component> component_ptr);
    
    /* Sim_object declarations */
    
    // throws an error that a group doesn't have a singular location
    virtual Point get_location() const override;
    // outputs the group name and a list of group members
    void describe() const override;
    // group does nothing on update
    void update() override {}
    // group has no state to broadcast to views (for now)
    void broadcast_current_state() const override {}
    
    /* Component declarations */
    
    void move_to(Point destination) override;
    
    void stop() override;
    
    void start_attacking(std::shared_ptr<Agent> target) override;
    
    void start_working(std::shared_ptr<Structure> src, std::shared_ptr<Structure> dst) override;
    
    void add_component(std::shared_ptr<Component> component_ptr) override;
    
    void remove_component(std::shared_ptr<Component> component_ptr) override;
    
private:
    
    using Children_map_t = std::map<std::string, std::shared_ptr<Component>>;
    using Cmd_set_t = std::set<std::shared_ptr<Component>, Sim_comp>;
    
    Children_map_t children;
    
    void fill_cmd_set(Cmd_set_t& fill_set);
};

#endif /* GROUP_H */
