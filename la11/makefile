OBJECTS = Armor.o Consumable.o Creature.o Entity.o Item.o parser.o Weapon.o Equipment.o Character.o XMLSerializable.o GenericFactory.o Tools.o
HEADERS = Armor.h Consumable.h Creature.h Entity.h Item.h parser.h Weapon.h Equipment.h Character.h XMLSerializable.h GenericFactory.h EntityVector.h parser.h Tools.h

all: lab11

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@ --std=c++0x

lab11: $(OBJECTS) main_la11.o
	g++ -o lab11 $^

clean:
	rm -f *.o lab11


