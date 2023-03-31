sfml-app : main.o definitions.o generation.o perso.o projectile.o background.o
	g++ main.o definitions.o generation.o perso.o projectile.o background.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	g++ -Wall -c main.cpp

definitions.o : definitions.cpp mainheader.hpp
	g++ -Wall -c definitions.cpp

generation.o : generation.cpp generation.hpp
	g++ -Wall -c generation.cpp

perso.o : perso.cpp perso.hpp
	g++ -Wall -c perso.cpp

projectile.o : projectile.cpp projectile.hpp
	g++ -Wall -c projectile.cpp

background.o : background.cpp background.hpp
	g++ -Wall -c background.cpp

clean : 
	rm *.o sfml-app
