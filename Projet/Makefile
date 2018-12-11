CPPFLAGS = -I/usr/include/irrlicht
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++11 -Wno-unused-parameter

jeu: main.o events.o adds.o
	g++ $^ -o $@ -lIrrlicht

main.o events.o adds.o: events.h gui_ids.h adds.h
clean:
	@rm -f jeu *.o
