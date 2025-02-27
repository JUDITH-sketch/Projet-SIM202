
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g  


SRC_CPP = exemple1.cpp
EXEC = exemple1

# Fichier intermédiaire généré par exemple1.cpp qui est ensuite lu par le programme .py
INTERMEDIATE_FILE = graph_data.txt 
# Routine pyton qui sert à afficher le graphe en format obstacle et le chemin optimal 
PYTHON_SCRIPT = trace_parcours_optimal.py

# clean des fichiers qui polluent le git 
all: clean $(EXEC) run

# Compilation du fichier executable
$(EXEC): $(SRC_CPP)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC_CPP)

# Exécution du programme C++ et du script Python
run: $(EXEC)
#ici à chaque fois avec echo j'affiche où est le probleme car quand il y en avait au début cela m'a permit de debuger 
	@echo "Exécution de $(EXEC)..."  
	ulimit -m unlimited 2>/dev/null || true  # Essai de lever les restrictions mémoire
	ulimit -v unlimited 2>/dev/null || true
	./$(EXEC) || { echo "Erreur lors de l'exécution de $(EXEC), vérifiez votre code."; exit 1; } 

	@echo "Exécution de $(PYTHON_SCRIPT)..."
	python3 $(PYTHON_SCRIPT) || { echo "Erreur lors de l'exécution de $(PYTHON_SCRIPT)."; exit 1; }

# Nettoyage des fichiers inutiles
clean:
	rm -f $(EXEC) *.o a.out $(INTERMEDIATE_FILE)

# regarde si il y a  des erreurs liées à l'allocation de mémoire et dit où c'est 
check:
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

.PHONY: all run clean check

