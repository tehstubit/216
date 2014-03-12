OBJECTS = DungeonLevel.o
HEADERS = DungeonLevel.h

all: dlmain 

%.o: %.cpp $(HEADERS)
	g++ -std=c++0x -c $< -o $@ 

dlmain: $(OBJECTS) dlmain.o
	g++ -o dlmain $^ -lncurses

clean:
	rm -f dlmain *.o
