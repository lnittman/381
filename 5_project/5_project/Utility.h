#ifndef UTILITY_H
#define UTILITY_H

#include <exception>
#include <iostream>
#include <memory>
#include <string>

class Sim_object;
struct Point;

/* Utility declarations, functions, and classes used by other modules */

// a simple class for error exceptions that inherits from std::exception
class Error : public std::exception {
public:
    Error(const std::string& in_msg = "") :
    msg(in_msg)
    {}
    const char* what() const noexcept override {return msg.c_str();}
private:
    const std::string msg;
};

class Cout_format_saver {
    
public:
    
    Cout_format_saver() : old_flags(std::cout.flags()), old_precision(std::cout.precision()) {}
    
    ~Cout_format_saver() {
        
        std::cout.flags(old_flags);
        std::cout.precision(old_precision);
    }
    
private:
    
    std::ios::fmtflags old_flags;
    long old_precision;
};

struct Sim_comp {
    
    using is_transparent = std::true_type;
    
    bool operator() (std::shared_ptr<Sim_object> s1, std::shared_ptr<Sim_object> s2) const;
    bool operator() (const std::string& s1, std::shared_ptr<Sim_object> s2) const;
    bool operator() (std::shared_ptr<Sim_object> s1, const std::string& s2) const;
};

#endif
