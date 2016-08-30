all: clean oop export_cc

CC: g++
CFLAGS := -O2 -Wall -Werror -g
LDFLAGS := -lstdc++

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

oop: vehicle.o main.o material.o cub.o
	$(CC) -o oop $^ $(LDFLAGS)
	chmod +x oop

clean:
	rm -vf oop
	rm -vf *.o
	rm -vf CMakeCache.txt
	rm -vRf CMakeFiles
	rm -vf cmake_install.cmake
	rm -vf GPATH
	rm -vf GRTAGS
	rm -vf GTAGS
export_cc:
	cmake . -DCMAKE_EXPORT_COMPILE_COMMANDS=1
	gtags
