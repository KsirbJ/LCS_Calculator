
FLAGS = -Wall -std=c++11

all:	p1 p2 p3

p1:	program1.o
	g++ $(FLAGS) program1.o -o program1

program1.o:	program1.cpp
	g++ -c $(FLAGS) program1.cpp -o program1.o

p2:	program2.o	
	g++ $(FLAGS) program2.o -o program2

program2.o:	program2.cpp
	g++ -c $(FLAGS) program2.cpp -o program2.o

p3:	program3.o	
	g++ $(FLAGS) program3.o -o program3

program3.o:	program3.cpp
	g++ -c $(FLAGS) program3.cpp -o program3.o

clean:
	rm -f *.o program1 program2 program3

# compile and tun all 3 programs. args should be provided through command line
# as args='<filex> <filey>'
run: p1 p2 p3
	./program1 ${args} output1.txt
	./program2 ${args} output2.txt
	./program3 ${args} output3.txt

submit:	clean
	mkdir brisk_jacob
	cp *.cpp brisk_jacob
	cp Makefile brisk_jacob
	cp readme* brisk_jacob
	zip -r brisk_jacob.zip brisk_jacob
	rm -r brisk_jacob
