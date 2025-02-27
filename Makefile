
# Compilateur de c 
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

# Routine Python
PYTHON_SCRIPT = trace_parcours_optimal.py

# Fichier intermédiaire généré entre le .cpp et le .py
INTERMEDIATE_FILE = graph_data.txt

# Demande du numéro de l'exemple
all:
	@read -p "Entre le numéro de l'exemple que tu veux essayer (ex: 1, 2, 3...) : " num; \
	$(MAKE) run EXEMPLE_NUM=$$num

# Compilation du fichier .cpp et de la routine python bcp d'erreurs de mémoire donc j'affiche avec echo où est le soucis pour pouvoir debugger
run:
	@if [ -z "$(EXEMPLE_NUM)" ]; then \
		echo "Erreur: Aucun numéro d'exemple fourni. Utilisez make EXEMPLE_NUM=<num>."; \
		exit 1; \
	fi
	@if [ ! -f exemple$(EXEMPLE_NUM).cpp ]; then \
		echo "Erreur: Le fichier exemple$(EXEMPLE_NUM).cpp n'existe pas."; \
		exit 1; \
	fi
	@echo "Compilation de exemple$(EXEMPLE_NUM).cpp..."
	$(CXX) $(CXXFLAGS) -o exemple$(EXEMPLE_NUM) exemple$(EXEMPLE_NUM).cpp

	@echo "Exécution de exemple$(EXEMPLE_NUM)..."
	./exemple$(EXEMPLE_NUM) || { echo "Erreur lors de l'exécution."; exit 1; }

	@echo "Exécution de $(PYTHON_SCRIPT)..."
	python3 $(PYTHON_SCRIPT) || { echo "Erreur lors de l'exécution de $(PYTHON_SCRIPT)"; exit 1; }

# Nettoyage des fichiers inutiles qui polluent le folder
clean:
	rm -f exemple[0-9]*  
	rm -f *.o a.out $(INTERMEDIATE_FILE)  
# Vérification que cette fois il n'y a plus aucun problème de mémoire
check:
	@if [ -z "$(EXEMPLE_NUM)" ]; then \
		echo "Erreur: Aucun numéro d'exemple fourni. Utilisez make check EXEMPLE_NUM=<num>."; \
		exit 1; \
	fi
	valgrind --leak-check=full --show-leak-kinds=all ./exemple$(EXEMPLE_NUM)


