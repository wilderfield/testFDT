
all: main.exe run

clean:
	rm -rf ./main.exe ./main.o

main.o:
	g++ -c main.cpp

main.exe: main.o
	g++ -lfdt main.o

run:
	./main.exe
