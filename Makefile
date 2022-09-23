all: main

main:
	g++ main.cpp -o sortingVisualizer -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o output
