all: obj clean

obj: main.o  eecapsule.o eeaircraft.o sorteddynamicqueue.o enode.o userinterface.o
	g++ -o main main.o  eecapsule.o eeaircraft.o sorteddynamicqueue.o enode.o userinterface.o

main.o : main.cpp
	g++ -c main.cpp


eecapsule.o : eecapsule.cpp eecapsule.h
	g++ -c eecapsule.cpp

eeaircraft.o : eeaircraft.cpp eeaircraft.h
	g++ -c eeaircraft.cpp

sorteddynamicqueue.o : sorteddynamicqueue.cpp sorteddynamicqueue.h
	g++ -c sorteddynamicqueue.cpp

enode.o : enode.cpp enode.h
	g++ -c enode.cpp

userinterface.o : userinterface.cpp userinterface.h
	g++ -c userinterface.cpp

clean : 
	rm *.o
