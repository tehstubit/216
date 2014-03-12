OBJECTS = Armor.o Consumable.o Creature.o Entity.o Item.o parser.o Weapon.o Equipment.o Character.o XMLSerializable.o CreatureFactory.o
HEADERS = Armor.h Consumable.h Creature.h Entity.h Item.h parser.h Weapon.h Equipment.h Character.h XMLSerializable.h CreatureFactory.h

all: prog1 lab9

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@ --std=c++0x

prog1: $(OBJECTS) main_pa1.o
	g++ -o prog1 $^

lab9: $(OBJECTS) main_la9.o
	g++ -o lab9 $^

clean:
	rm -f *.o prog1 lab9


