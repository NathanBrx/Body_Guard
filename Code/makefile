sfml-app : main.o definitions.o generation.o perso.o projectile.o background.o projectile_ennemi.o
	g++ main.o definitions.o generation.o perso.o projectile.o background.o projectile_ennemi.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

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
projectile_ennemi : projectile_ennemi.cpp projectile_ennemi.hpp
	g++ -Wall -c projectile_ennemi.cpp

clean : 
	rm *.o sfml-app
