cmake_minimum_required(VERSION 3.6)
project(5_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Agent.cpp
    Agent.h
    Agent_factory.cpp
    Agent_factory.h
    Amount_view.cpp
    Amount_view.h
    Archer.cpp
    Archer.h
    Component.cpp
    Component.h
    Controller.cpp
    Controller.h
    Farm.cpp
    Farm.h
    Geometry.cpp
    Geometry.h
    Grid_view.cpp
    Grid_view.h
    Group.cpp
    Group.h
    Health_view.cpp
    Health_view.h
    List_view.cpp
    List_view.h
    Local_view.cpp
    Local_view.h
    Map_view.cpp
    Map_view.h
    Model.cpp
    Model.h
    Moving_object.cpp
    Moving_object.h
    p6_main.cpp
    Peasant.cpp
    Peasant.h
    Shaman.cpp
    Shaman.h
    Sim_object.cpp
    Sim_object.h
    Soldier.cpp
    Soldier.h
    Structure.cpp
    Structure.h
    Structure_factory.cpp
    Structure_factory.h
    Town_Hall.cpp
    Town_Hall.h
    Utility.cpp
    Utility.h
    View.cpp
    View.h
    Warrior.cpp
    Warrior.h)

include_directories(.)

add_executable(5_project ${SOURCE_FILES})