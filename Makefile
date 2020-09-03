
all: clean main.exe run

clean:
	rm -rf ./main.exe ./main.o

main.o:
	g++ -c main.cpp

main.exe: main.o
	g++ main.o -lfdt -o main.exe

run:
	./main.exe
