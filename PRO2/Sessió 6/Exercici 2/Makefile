OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o Estudiant.o
	g++ -o program.exe program.o Estudiant.o
	rm *.o

Estudiant.o: Estudiant.cc Estudiant.hh
	g++ -c Estudiant.cc $(OPCIONS)
	
program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe
