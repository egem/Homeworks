all: obj clean

obj: main.o smartPhone.o ElectronicProduct.o laptopComp.o gameConsole.o tv.o  
	g++ -o main main.o ElectronicProduct.o smartPhone.o laptopComp.o gameConsole.o tv.o

main.o : main.cpp
	g++ -std=c++0x -c main.cpp

smartPhone.o : smartPhone.cpp smartPhone.h
	g++ -std=c++0x -c smartPhone.cpp

laptopComp.o : laptopComp.cpp laptopComp.h
	g++ -std=c++0x -c laptopComp.cpp 

gameConsole.o : gameConsole.cpp gameConsole.h
	g++ -std=c++0x -c gameConsole.cpp

tv.o : tv.cpp tv.h
	g++ -std=c++0x -c tv.cpp

ElectronicProduct.o : ElectronicProduct.h ElectronicProduct.cpp
	g++ -std=c++0x -c ElectronicProduct.cpp

clean : 
	rm *.o
