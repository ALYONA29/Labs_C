all: build run clean

build: main.c
        gcc main.c -o main -lm -std=c11

run:
        ./main

clean:
         del -rf main *.o *.exe *.out