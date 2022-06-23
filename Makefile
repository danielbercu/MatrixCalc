CC := g++
INCLUDE := -I include
FLAGS := -Wall -Wpedantic

SRC := src
OBJ := obj
EXE := build

EXEC := $(EXE)/MatrixCalc

MatrixCalc: main.o SquareMat.o Rational.o
	mkdir -p $(EXE)
	$(CC) $(OBJ)/main.o $(OBJ)/SquareMat.o $(OBJ)/Rational.o $(FLAGS) -o $(EXEC)

main.o:
	mkdir -p $(OBJ)
	$(CC) -c $(SRC)/main.cpp $(INCLUDE) $(FLAGS) -o $(OBJ)/main.o

SquareMat.o:
	$(CC) -c $(SRC)/SquareMat.cpp $(INCLUDE) $(FLAGS) -o $(OBJ)/SquareMat.o

Rational.o:
	$(CC) -c $(SRC)/Rational.cpp $(INCLUDE) $(FLAGS) -o $(OBJ)/Rational.o

clean:
	rm -rf $(OBJ) $(EXE)
