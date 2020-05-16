all: build run clean

build: main.c
        gcc main.c List.c List.h Checker.c Checker.h Source.c Source.h -o main -lm -std=c11

run:
        ./main

clean:
         del -rf main *.o *.exe *.out