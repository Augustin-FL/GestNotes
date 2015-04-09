PROGRAMME=GestNotes
CC=g++
ARGS_COMPILATION=-Wall -g
INCLUDE=-I "./include"

# note : si vous avez comme erreur 'wx/msw/hand.cur': No such file or directory
# c'est un bug connu de windres.exe : https://sourceware.org/bugzilla/show_bug.cgi?id=4356
# pour le résoudre, vous devez rajouter a INCLUDE ceci : "-I le_Chemin_Vers_Votre_MINGW"
# Tout en veillant a ce que le chemin ne contienne pas d'espace (utilisez "progra~1" au lieu de "program files" par exemple)



ifeq ($(OS),Windows_NT)
# sous windows : on compile avec wxMSW, et -mwindows.
# de plus on utilise les ressources rc et on lance le programme a la fin du makefile
# enfin, les fichiers .o sont mis dans le dossier %TMP%
LIBS =-lwxmsw31u -lsqlite3 -mwindows
CFLAGS=$(ARGS_COMPILATION)
REP_COURRANT=$(shell cd)
TMP=$(shell echo %tmp%)

LANCER_PROG=cmd /C start "$(PROGRAMME)" "$(REP_COURRANT)\bin\$(PROGRAMME).exe"
COMMANDE_WINDRES=windres "./include/ressources.rc" "$(TMP)/ressources.o" $(INCLUDE)
RESSOURCES="$(TMP)/ressources.o"
RM_RES=rm "$(TMP)ressources.o"

else  
# sous linux/osX : on utilise wx-config, et on ne lance pas le programme.
# et les fichiers .o sont mis dans le dossier ./obj
LIBS=`wx-config --libs` -lsqlite3
CFLAGS=`wx-config --cxxflags` $(ARGS_COMPILATION)
REP_COURRANT=$(shell pwd)
$(shell mkdir -p obj)

TMP=./obj
LANCER_PROG=

COMMANDE_WINDRES=
RESSOURCES=
RM_RES=
endif
	
$(PROGRAMME):$(TMP)/ressources.o $(TMP)/login.o $(TMP)/main.o $(TMP)/bdd.o $(TMP)/admin.o $(TMP)/professeur.o $(TMP)/eleve.o
	
	$(CC) "$(TMP)/main.o" "$(TMP)/bdd.o" "$(TMP)/login.o" "$(TMP)/admin.o" "$(TMP)/professeur.o" "$(TMP)/eleve.o" $(RESSOURCES) -o "./bin/$@"  $(LIBS)
	$(LANCER_PROG)


$(TMP)/ressources.o:
	$(COMMANDE_WINDRES)

$(TMP)/login.o: ./src/login.cpp
	$(CC) "./src/login.cpp"  	$(CFLAGS) $(INCLUDE) -c -o "$@"
$(TMP)/main.o: ./src/main.cpp
	$(CC) "./src/main.cpp"   	 $(CFLAGS) $(INCLUDE) -c -o "$@"
$(TMP)/bdd.o: ./src/bdd.cpp
	$(CC) "./src/bdd.cpp"   	 $(CFLAGS) $(INCLUDE) -c -o "$@"
$(TMP)/admin.o: ./src/admin.cpp
	$(CC) "./src/admin.cpp" 	 $(CFLAGS) $(INCLUDE) -c -o "$@"
$(TMP)/professeur.o: ./src/professeur.cpp
	$(CC) "./src/professeur.cpp" $(CFLAGS) $(INCLUDE) -c -o "$@"
$(TMP)/eleve.o: ./src/eleve.cpp
	$(CC) "./src/eleve.cpp"  	 $(CFLAGS) $(INCLUDE) -c -o "$@"
	
clean:
	$(RM_RES)
	rm "./bin/$(PROGRAMME).exe"