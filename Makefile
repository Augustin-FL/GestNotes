# Compilateur
CC=g++
# Options du compilateur 
CFLAGS= -Wall 
# Make

PROGRAMME=GestNotes
LIBS=-lwxmsw31u -lsqlite3 # -lwxmswu_31core





ifeq ($(OS),Windows_NT)
REP_COURRANT=$(shell cd)
TMP=$(shell echo %tmp%)

LANCER_PROG=cmd /C start "$(PROGRAMME)" "$(REP_COURRANT)\bin\$(PROGRAMME).exe"
COMMANDE_WINDRES=windres "./src/ressources.rc" "$(TMP)/ressources.o"
RESSOURCES="$(TMP)/ressources.o"
RM_RES=rm "$(TMP)ressources.o"
MWINDOWS=-mwindows
else 
REP_COURRANT=$(shell pwd)
$(shell mkdir -p obj)
TMP=./obj
LANCER_PROG=$(REP_COURRANT)/bin/GestNotes
COMMANDE_WINDRES=
RESSOURCES=
RM_RES=
MWINDOWS=
endif

# note : bug connu de windres.exe : https://sourceware.org/bugzilla/show_bug.cgi?id=4356
# malheureusement, on peux pas faire grand chose contre cela (a part attendre que windres soit mis à jour...)
	
$(PROGRAMME):$(TMP)/ressources.o"
	$(CC) $(CFLAGS) "./src/main.cpp" "./src/bdd.cpp" "./src/login.cpp" "./src/admin.cpp" "./src/professeur.cpp" "./src/eleve.cpp" $(RESSOURCES) -o "./bin/$@" -I "./include" $(LIBS) $(MWINDOWS)
	$(LANCER_PROG)
	
$(TMP)/ressources.o":
	$(COMMANDE_WINDRES)
	
clean:
	$(RM_RES)
	rm "./bin/$(PROGRAMME).exe"