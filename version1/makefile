INC=include/
SRC=src/
OBJ=obj/
BIN=bin/
AR = ar
CXX = g++
CXXFLAGS= -Wall -g -I./$(INC) -c


all: $(BIN)conectaN.out


# ******************* Compilación de módulos ***********

$(OBJ)Matriz.o : $(INC)Matriz.h $(SRC)Matriz.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)Matriz.o $(SRC)Matriz.cpp

$(OBJ)Tablero.o : $(INC)Matriz.h $(INC)Tablero.h $(INC)Jugador.h $(SRC)Tablero.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)Tablero.o $(SRC)Tablero.cpp

$(OBJ)Jugador.o : $(INC)Jugador.h $(INC)Matriz.h $(SRC)Jugador.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)Jugador.o $(SRC)Jugador.cpp

$(OBJ)conectaN.o : $(INC)Tablero.h $(SRC)conectaN.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)conectaN.o $(SRC)conectaN.cpp

$(BIN)conectaN.out : $(OBJ)conectaN.o $(OBJ)Tablero.o $(OBJ)Jugador.o $(OBJ)Matriz.o
	$(CXX) $^ -o $(BIN)conectaN.out 

# ********************** Limpieza ************************

clean:
	echo "Borrando archivos..."
	rm $(OBJ)/*.o

mrproper: clean
	rm $(BIN)/*.out

