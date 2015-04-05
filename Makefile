PROGRAMME=GestNotes
CC=g++
ARGS_COMPILATION=-Wall 
INCLUDE=-I "./include"


ifeq ($(OS),Windows_NT)
LIBS =-lwxmsw31u -lsqlite3 -mwindows
CFLAGS=$(ARGS_COMPILATION)
REP_COURRANT=$(shell cd)
TMP=$(shell echo %tmp%)

LANCER_PROG=cmd /C start "$(PROGRAMME)" "$(REP_COURRANT)\bin\$(PROGRAMME).exe"
COMMANDE_WINDRES=windres "./src/ressources.rc" "$(TMP)/ressources.o"
RESSOURCES="$(TMP)/ressources.o"
RM_RES=rm "$(TMP)ressources.o"

else 
LIBS=`wx-config --libs` -lsqlite3
CFLAGS=`wx-config --cxxflags` $(ARGS_COMPILATION)
REP_COURRANT=$(shell pwd)
$(shell mkdir -p obj)

TMP=./obj
LANCER_PROG=$(REP_COURRANT)/bin/GestNotes

COMMANDE_WINDRES=
RESSOURCES=
RM_RES=
endif

# note : bug connu de windres.exe : https://sourceware.org/bugzilla/show_bug.cgi?id=4356
# malheureusement, on peux pas faire grand chose contre cela (a part attendre que windres soit mis à jour...)
	
$(PROGRAMME):$(TMP)/ressources.o"
	$(CC) "./src/main.cpp"       $(CFLAGS) $(INCLUDE) -c -o $(TMP)/main.o
	$(CC) "./src/bdd.cpp"        $(CFLAGS) $(INCLUDE) -c -o $(TMP)/bdd.o
	$(CC) "./src/login.cpp"      $(CFLAGS) $(INCLUDE) -c -o $(TMP)/login.o
	$(CC) "./src/admin.cpp"      $(CFLAGS) $(INCLUDE) -c -o $(TMP)/admin.o
	$(CC) "./src/professeur.cpp" $(CFLAGS) $(INCLUDE) -c -o $(TMP)/professeur.o
	$(CC) "./src/eleve.cpp"      $(CFLAGS) $(INCLUDE) -c -o $(TMP)/eleve.o
	
	$(CC) $(TMP)/main.o $(TMP)/bdd.o $(TMP)/login.o $(TMP)/admin.o $(TMP)/professeur.o $(TMP)/eleve.o $(RESSOURCES) -o "./bin/$@"  $(LIBS)
	$(LANCER_PROG)

$(TMP)/ressources.o":
	$(COMMANDE_WINDRES)
	
clean:
	$(RM_RES)
	rm "./bin/$(PROGRAMME).exe"