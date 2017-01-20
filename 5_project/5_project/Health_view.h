//
//  Health_view.h
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef HEALTH_VIEW_H
#define HEALTH_VIEW_H

#include "List_view.h"
#include <string>

class Health_view : public List_view {
    
public:
    
    // notify the views about an object's health
    void update_health(const std::string& name, double health) override;
    
    //
    void draw() const override;
};

#endif /* HEALTH_VIEW_H */
