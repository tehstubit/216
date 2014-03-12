OBJECTS = DungeonLevel.o
HEADERS = DungeonLevel.h

all: dlmain dltest

%.o: %.cpp $(HEADERS)
	g++ -std=c++0x -c $< -o $@ 

dlmain: $(OBJECTS) dlmain.o
	g++ -o dlmain $^

dltest: $(OBJECTS) dltest.o
	g++ -o dltest $^

clean:
	rm -f dlmain dltest *.o
