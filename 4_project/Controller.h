/* Controller
 This class is responsible for controlling the Model and View according to interactions
 with the user.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>

class Model;
class View;
class Agent;

class Controller {
public:
    // Output a message after doing all initialization and clean-up work
    Controller();
    ~Controller();
    
    // create View object, run the program by acccepting user commands, then destroy View object
    void run();
    
private:
    
    using Cmd_func_t = void(Controller::*)(Agent*, View*);
    using Cmd_map_t = std::map<std::string, Cmd_func_t>;
    
    Cmd_map_t cmd_map;
    View* view_ptr;
    bool is_view_open;
    
    // View commands
    void cmd_open(Agent*, View*);
    void cmd_close(Agent*, View*);
    void cmd_default(Agent*, View* view);
    void cmd_size(Agent*, View* view);
    void cmd_zoom(Agent*, View* view);
    void cmd_pan(Agent*, View* view);
    
    // Whole-program commands
    void cmd_quit(Agent*, View*);
    void cmd_status(Agent*, View*);
    void cmd_show(Agent*, View* view);
    void cmd_go(Agent*, View*);
    void cmd_build(Agent*, View*);
    void cmd_train(Agent*, View*);
    
    // Agent commands
    void cmd_move(Agent* agent, View*);
    void cmd_work(Agent* agent, View*);
    void cmd_attack(Agent* agent, View*);
    void cmd_stop(Agent* agent, View*);
};

#endif
