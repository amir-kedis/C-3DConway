.PHONY: build all clean

all: build run

FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

build:
	gcc 3dconway.c -o 3dconway.out $(FLAGS)
	
clean:
	rm -f *.out

run:
	./3dconway.out

