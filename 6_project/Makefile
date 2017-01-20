CC = g++
LD = g++
CFLAGS = -c -g -std=c++14 -pedantic-errors -Wall
LFLAGS = -g

OBJS = p6_main.o Model.o View.o Grid_view.o Map_view.o Local_view.o List_view.o Amount_view.o Health_view.o Controller.o 
OBJS += Component.o Group.o
OBJS += Sim_object.o Structure.o Moving_object.o Agent.o
OBJS += Farm.o Town_Hall.o
OBJS += Peasant.o Warrior.o Archer.o Shaman.o Soldier.o
OBJS += Agent_factory.o Structure_factory.o
OBJS += Geometry.o Utility.o
PROG = p6exe

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

p6_main.o: p6_main.cpp Controller.h
	$(CC) $(CFLAGS) p6_main.cpp

Model.o: Model.cpp Model.h View.h Component.h Group.h Structure.h Agent.h Agent_factory.h Structure_factory.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Model.cpp

View.o: View.cpp View.h Geometry.h
	$(CC) $(CFLAGS) View.cpp

Grid_view.o: Grid_view.cpp Grid_view.h View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Grid_view.cpp

Map_view.o: Map_view.cpp Map_view.h Grid_view.h
	$(CC) $(CFLAGS) Map_view.cpp

Local_view.o: Local_view.cpp Local_view.h Grid_view.h
	$(CC) $(CFLAGS) Local_view.cpp

List_view.o: List_view.cpp List_view.h View.h Geometry.h
	$(CC) $(CFLAGS) List_view.cpp

Amount_view.o: Amount_view.cpp Amount_view.h List_view.h 
	$(CC) $(CFLAGS) Amount_view.cpp

Health_view.o: Health_view.cpp Health_view.h List_view.h
	$(CC) $(CFLAGS) Health_view.cpp

Controller.o: Controller.cpp Controller.h Model.h View.h Sim_object.h Structure.h Agent.h Agent_factory.h Structure_factory.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Controller.cpp

Component.o: Component.cpp Component.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Component.cpp

Group.o: Group.cpp Group.h Component.h Utility.h
	$(CC) $(CFLAGS) Group.cpp

Sim_object.o: Sim_object.cpp Sim_object.h Geometry.h
	$(CC) $(CFLAGS) Sim_object.cpp

Structure.o: Structure.cpp Structure.h Sim_object.h Geometry.h
	$(CC) $(CFLAGS) Structure.cpp

Farm.o: Farm.cpp Farm.h Structure.h Sim_object.h Model.h Geometry.h
	$(CC) $(CFLAGS) Farm.cpp

Town_Hall.o: Town_Hall.cpp Town_Hall.h Structure.h Model.h Sim_object.h Geometry.h
	$(CC) $(CFLAGS) Town_Hall.cpp

Agent.o: Agent.cpp Agent.h Component.h Moving_object.h Model.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Agent.cpp

Peasant.o: Peasant.cpp Peasant.h Agent.h Model.h Sim_object.h Structure.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Peasant.cpp

Warrior.o: Warrior.cpp Warrior.h Agent.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Warrior.cpp

Archer.o: Archer.cpp Archer.h Warrior.h Model.h Structure.h
	$(CC) $(CFLAGS) Archer.cpp

Shaman.o: Shaman.cpp Shaman.h Warrior.h Model.h Structure.h
	$(CC) $(CFLAGS) Shaman.cpp

Soldier.o: Soldier.cpp Soldier.h Warrior.h
	$(CC) $(CFLAGS) Soldier.cpp

Moving_object.o: Moving_object.cpp Moving_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Moving_object.cpp

Agent_factory.o: Agent_factory.cpp Agent_factory.h Agent.h Peasant.h Archer.h Shaman.h Soldier.h Utility.h
	$(CC) $(CFLAGS) Agent_factory.cpp

Structure_factory.o: Structure_factory.cpp Structure_factory.h Structure.h Farm.h Town_Hall.h Utility.h
	$(CC) $(CFLAGS) Structure_factory.cpp

Geometry.o: Geometry.cpp Geometry.h
	$(CC) $(CFLAGS) Geometry.cpp

Utility.o: Utility.cpp Utility.h Sim_object.h Geometry.h
	$(CC) $(CFLAGS) Utility.cpp

clean:
	rm -f *.o
real_clean:
	rm -f $(PROG)
	rm -f *.o
