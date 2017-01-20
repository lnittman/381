//
//  string_exception_test_harness.cpp
//  2_project
//
//  Created by Luke Nittmann on 10/5/16.
//  Copyright © 2016 Luke Nittmann. All rights reserved.
//

#include "String.h"
#include <stdio.h>

// another  exception class
class User_screwed_up {
};

using std::cin; using std::cout; using std::endl;
/*
int main(int argc, const char * argv[]) {
    
    while(true) {
        try {
            
            String str, code;
            int i, j;
            
            str = "0123456789";
            cout << "Enter quit, or a test name and two integers, i and j:";
            cin >> code;
            if(code == "quit")
                break;
            cin >> i >> j;
            if (!cin) {
                throw User_screwed_up();
            }
            
            if(code == "[]") {
                cout << "Before: " << str << endl;
                str[i] = str[j];
                cout << "After:  " << str << endl;
            }
            else
                throw User_screwed_up();
            
        } // end of try block
        catch(User_screwed_up& x) {
            cout << "Excuse me, but you entered something wrong. Please try again." << endl;
            cout << "In the meantime, I will clean up the place a bit." << endl;
            cin.clear();
            while(cin.get() != '\n');
        }
        catch(String_exception& x) {
            cout << x.msg << endl;
        }
        
        // go around again
    }
    cout << "And thank you, for trying out String's exception throwing!" << endl;
}

*/
