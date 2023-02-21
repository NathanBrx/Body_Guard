sfml-app : main.o definitions.o
	g++ main.o definitions.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	g++ -Wall -c main.cpp

definitions.o : definitions.cpp mainheader.hpp
	g++ -Wall -c definitions.cpp

clean : 
	rm *.o sfml-app
