#compilateur c++ pour la partie programme en cpp
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

#premier fichier a éxécuté
SRC_CPP = exemple1.cpp
EXEC = exemple1

#routine python à faire
PYTHON_SCRIPT = trace_parcours_optimal.py

# Règle principale
all: $(EXEC) run

# Compilation du programme C++
$(EXEC): $(SRC_CPP)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC_CPP)

# Exécution du programme C++ et de la routune Python
run: $(EXEC)
	./$(EXEC)  # Exécute exemple1
	python3 $(PYTHON_SCRIPT)  # Exécute trace_parcours_optimal.py

#on se débarasse des fichiers .o qui polluent le folder
clean:
	rm -f $(EXEC) *.o

.PHONY: all run clean
