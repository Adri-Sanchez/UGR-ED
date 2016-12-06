
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -std=c++11 -I$(INC) -c

# ************ compilación *******

all: $(BIN)/principal

$(BIN)/principal: $(OBJ)/principal.o
	$(CXX) $< -o $@ 
	
		
$(OBJ)/principal.o:  $(SRC)/principal.cpp $(INC)/mutacion.h $(INC)/enfermedad.h $(INC)/mutacion.hxx $(INC)/enfermedad.hxx
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
