CPPFLAGS = -I/usr/include/irrlicht
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++11 -Wno-unused-parameter

irrlicht-exemple1: main.o
	g++ $^ -o $@ -lIrrlicht

clean:
	@rm -f irrlicht-exemple1 *.o
