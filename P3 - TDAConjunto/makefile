
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -std=c++11 -I$(INC) -c -O3 -g

# ************ compilación *******

all: $(BIN)/principal

$(BIN)/principal: $(OBJ)/principal.o $(OBJ)/conjunto.o $(OBJ)/enfermedad.o $(OBJ)/mutacion.o
	$(CXX) $^ -o $@ 
	
		
$(OBJ)/principal.o:  $(SRC)/principal.cpp $(INC)/mutacion.h $(INC)/enfermedad.h $(INC)/conjunto.h 
	$(CXX) $(CPPFLAGS) $< -o $@
	
$(OBJ)/conjunto.o: $(SRC)/conjunto.cpp $(INC)/conjunto.h $(INC)/mutacion.h $(INC)/enfermedad.h 
	$(CXX) $(CPPFLAGS) $< -o $@
	
$(OBJ)/enfermedad.o: $(SRC)/enfermedad.cpp $(INC)/enfermedad.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/mutacion.o: $(SRC)/mutacion.cpp $(INC)/mutacion.h $(INC)/enfermedad.h
	$(CXX) $(CPPFLAGS) $< -o $@
	
# ************ documentación *******

documentacion:
	# doxygen doxy/doxPractica.txt **** No sabemos como indicar a doxygen dónde estan los ficheros de los que tiene que generar la documentación. Lo hemos realizado manualmente 

# ************ Limpieza ************

clean:
	echo "Limpiando..."
	rm $(OBJ)/*.o 

mrproper: clean
	rm $(BIN)/*
