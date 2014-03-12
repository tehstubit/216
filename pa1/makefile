OBJECTS = Entity.o Item.o Consumable.o Equipment.o Armor.o Weapon.o Character.o Creature.o Player.o XMLSerializable.o Tile.o Dungeon.o GenericFactory.o parser.o Tools.o
HEADERS = Entity.h Item.h Consumable.h Equipment.h Armor.h Weapon.h Character.h Creature.h Player.h XMLSerializable.h Tile.h Dungeon.h EntityVector.h GenericFactory.h parser.h

prog1: $(OBJECTS) prog1.o
	g++ $^ -o prog1

%.o: %.cpp $(HEADERS)
	g++ --std=c++0x -c $< -o $@

prog2: $(OBJECTS) prog2.o
	g++ $^ -o prog2

test: $(OBJECTS) test.o
	g++ $^ -o test

la5: $(OBJECTS) la5.o
	g++ $^ -o la5

prog3: $(OBJECTS) prog3.o
	g++ $^ -o prog3 -lncurses

debug: $(OBJECTS) prog3.o
	g++ $^ -g -o prog3debug

clean:
	rm -f *.o prog1 la5 prog2 test prog3
