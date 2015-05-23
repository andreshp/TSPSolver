# Fichero: makefile del proyecto TSP

	# VARIABLES #
# Compilador y Flags:
CXX=g++
CC=$(CXX)
CPPFLAGS=-c -g -O2
CXXFLAGS=-I$(INCLUDE)
LDFLAGS=-L$(LIB)
LOADLIBS=-lutilities -lalgorithms
ARFLAGS=rvs

# Directorios:
BIN=./bin
INCLUDE =./include
LIB=./lib
OBJ=./obj
SRC=./src
DOC=./doc

# Módulos, Códigos Fuentes y Ejecutable
EXECUTABLE=tsp

OBJECTS=$(OBJ)/main.o $(ALGORITHMS_OBJECTS) $(UTILITIES_OBJECTS)

ALGORITHMS_OBJECTS=$(OBJ)/TSPMejorInsercion.o $(OBJ)/TSPVecinoMasCercano.o $(OBJ)/TSPLocalSearch.o $(OBJ)/TSPILS.o $(OBJ)/TSPGRASP.o $(OBJ)/TSPSA.o $(OBJ)/TSPRandom.o $(OBJ)/TSPGenetico.o $(OBJ)/TSPACO.o $(OBJ)/TSPBranchAndBound.o $(OBJ)/TSPBacktracking.o
ALGORITHMS_INCLUDES=$(INCLUDE)/TSPMejorInsercion.h $(INCLUDE)/TSPVecinoMasCercano.h $(INCLUDE)/TSPLocalSearch.h $(INCLUDE)/TSPILS.h $(INCLUDE)/TSPGRASP.h $(INCLUDE)/TSPSA.h $(INCLUDE)/TSPRandom.h $(INCLUDE)/TSPGenetico.h $(INCLUDE)/TSPACO.h $(INCLUDE)/TSPBranchAndBound.h $(INCLUDE)/TSPBacktracking.h

UTILITIES_OBJECTS=$(OBJ)/TSPPunto.o $(OBJ)/TSPProblema.o $(OBJ)/TSPSolucion.o $(OBJ)/TSPColeccionSoluciones.o $(OBJ)/Cronometro.o   $(OBJ)/TSPPlot.o $(OBJ)/Menu.o $(OBJ)/ioTSP.o
UTILITIES_INCLUDES=$(INCLUDE)/TSPPunto.h $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPColeccionSoluciones.h $(INCLUDE)/Cronometro.h $(INCLUDE)/TSPPlot.h $(INCLUDE)/Menu.h $(INCLUDE)/ioTSP.h


	# REGLAS #
 
all: directories $(BIN)/$(EXECUTABLE)

# Build the directories needed
directories:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)
	mkdir -p $(LIB)
	mkdir -p $(DOC)


# Creación del archivo ejecutable
$(BIN)/$(EXECUTABLE): $(OBJ)/main.o $(LIB)/libalgorithms.a $(LIB)/libutilities.a
	@echo "Creando el ejecutable $@..."
	$(CC) -g -o $(BIN)/$(EXECUTABLE) $< $(LDFLAGS) $(LOADLIBS)

# Creación del objeto main.o
$(OBJ)/main.o: $(SRC)/main.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/Menu.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/main.cpp

# Creación del objeto TSPPunto.o
$(OBJ)/TSPPunto.o: $(SRC)/TSPPunto.cpp $(INCLUDE)/TSPPunto.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPPunto.cpp

# Creación del objeto TSPProblema.o
$(OBJ)/TSPProblema.o: $(SRC)/TSPProblema.cpp $(INCLUDE)/TSPPunto.h $(INCLUDE)/TSPProblema.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPProblema.cpp

# Creación del objeto TSPSolucion.o
$(OBJ)/TSPSolucion.o: $(SRC)/TSPSolucion.cpp $(INCLUDE)/TSPProblema.h  $(INCLUDE)/TSPSolucion.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPSolucion.cpp

# Creación del objeto TSPColeccionSoluciones.o 
$(OBJ)/TSPColeccionSoluciones.o: $(SRC)/TSPColeccionSoluciones.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPGRASP.h $(INCLUDE)/TSPColeccionSoluciones.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPColeccionSoluciones.cpp

# Creación del objeto Cronometro.o 
$(OBJ)/Cronometro.o: $(SRC)/Cronometro.cpp $(INCLUDE)/Cronometro.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/Cronometro.cpp

# Creación del objeto TSPPlot.o
$(OBJ)/TSPPlot.o: $(SRC)/TSPPlot.cpp $(INCLUDE)/TSPPunto.h $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPPlot.h 
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPPlot.cpp

# Creación del objeto ioTSP.o
$(OBJ)/ioTSP.o: $(SRC)/ioTSP.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPColeccionSoluciones.h $(INCLUDE)/ioTSP.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/ioTSP.cpp

# Creación del objeto Menu.o 
$(OBJ)/Menu.o: $(SRC)/Menu.cpp $(UTILITIES_INCLUDES) $(ALGORITHMS_INCLUDES)
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/Menu.cpp

# Creación de la biblioteca libutilities.a
$(LIB)/libutilities.a: $(UTILITIES_OBJECTS)
	@echo "Creando la biblioteca $@..."
	$(AR) $(ARFLAGS) $@ $^

# Creación del objeto TSPMejorInsercion.o                
$(OBJ)/TSPMejorInsercion.o: $(SRC)/TSPMejorInsercion.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPMejorInsercion.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPMejorInsercion.cpp

# Creación del objeto TSPLocalSearch.o 
$(OBJ)/TSPLocalSearch.o: $(SRC)/TSPLocalSearch.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPLocalSearch.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPLocalSearch.cpp

# Creación del objeto TSPVecinoMasCercano.o 
$(OBJ)/TSPVecinoMasCercano.o: $(SRC)/TSPVecinoMasCercano.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPVecinoMasCercano.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPVecinoMasCercano.cpp

# Creación del objeto TSPILS.o 
$(OBJ)/TSPILS.o: $(SRC)/TSPILS.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPLocalSearch.h $(INCLUDE)/TSPILS.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPILS.cpp

# Creación del objeto TSPGRASP.o 
$(OBJ)/TSPGRASP.o: $(SRC)/TSPGRASP.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPLocalSearch.h $(INCLUDE)/TSPGRASP.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPGRASP.cpp

# Creación del objeto TSPSA.o 
$(OBJ)/TSPSA.o: $(SRC)/TSPSA.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPSA.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPSA.cpp

# Creación del objeto TSPRandom.o 
$(OBJ)/TSPRandom.o: $(SRC)/TSPRandom.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPRandom.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPRandom.cpp

# Creación del objeto TSPGenetico.o 
$(OBJ)/TSPGenetico.o: $(SRC)/TSPGenetico.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPLocalSearch.h $(INCLUDE)/TSPGRASP.h $(INCLUDE)/TSPGenetico.h 
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPGenetico.cpp

# Creación del objeto TSPBranchAndBound.o
$(OBJ)/TSPBranchAndBound.o: $(SRC)/TSPBranchAndBound.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPLocalSearch.h $(INCLUDE)/TSPGRASP.h $(INCLUDE)/TSPBranchAndBound.h 
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPBranchAndBound.cpp

# Creación del objeto TSPBranchAndBound.o
$(OBJ)/TSPBacktracking.o: $(SRC)/TSPBacktracking.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPLocalSearch.h $(INCLUDE)/TSPGRASP.h $(INCLUDE)/TSPBacktracking.h 
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPBacktracking.cpp

#Creación del objeto TSPACO.o
$(OBJ)/TSPACO.o: $(SRC)/TSPACO.cpp $(INCLUDE)/TSPProblema.h $(INCLUDE)/TSPSolucion.h $(INCLUDE)/TSPLocalSearch.h $(INCLUDE)/TSPACO.h
	@echo "Creando el modulo objeto $@..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(SRC)/TSPACO.cpp

# Creación de la biblioteca libalgorithms.a
$(LIB)/libalgorithms.a: $(ALGORITHMS_OBJECTS) 
	@echo "Creando la biblioteca $@..."
	$(AR) $(ARFLAGS) $@ $^



# Regla para borrar los ficheros objeto.
clean:
	@echo "Borrando los ficheros .o del directorio $(OBJ)..."
	rm $(OBJ)/*.o

# Regla que genera la documentación con doxygen:
documentacion:
	doxygen $(DOC)/doxys/Doxyfile