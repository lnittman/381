//
//  Amount_view.h
//  5_project
//
//  Created by Luke Nittmann on 12/4/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#ifndef AMOUNT_VIEW_H
#define AMOUNT_VIEW_H

#include "List_view.h"
#include <string>

class Amount_view : public List_view {
public:
    
    // notify the views about an object's amount on hand
    void update_amount(const std::string& name, double amount) override;
    
    //
    void draw() const override;
};

#endif /* AMOUNT_VIEW_H */
