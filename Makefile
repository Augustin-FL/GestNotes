PROGRAMME=GestNotes
CC=g++
ARGS_COMPILATION=-Wall
INCLUDE=-I "./include" -I"C:\include"

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

LANCER_PROG=cmd /C start "$(PROGRAMME)" "$(REP_COURRANT)\bin\$(PROGRAMME).exe"
COMMANDE_WINDRES=windres "./include/ressources.rc" "./obj/ressources.res" -J rc -O coff $(INCLUDE)
RESSOURCES="./obj/ressources.res"
RM_RES=rm "./obj/ressources.res"

else  
# sous linux/osX : on utilise wx-config, et on ne lance pas le programme.
LIBS=`wx-config --libs` -lsqlite3 
CFLAGS=`wx-config --cxxflags` $(ARGS_COMPILATION)
REP_COURRANT=$(shell pwd)

LANCER_PROG=

COMMANDE_WINDRES=
RESSOURCES=
RM_RES=
endif
	
$(PROGRAMME):./obj/ressources.res ./obj/login.o ./obj/main.o ./obj/bdd.o ./obj/admin.o ./obj/professeur.o ./obj/eleve.o ./obj/afficher_liste_membres.o  ./obj/ajout_modification_membre.o ./obj/validateurs.o ./obj/imprimer_bulletin.o | ./bin
	$(CC) "./obj/main.o" "./obj/bdd.o" "./obj/login.o" "./obj/admin.o" "./obj/professeur.o" "./obj/eleve.o" "./obj/afficher_liste_membres.o" "./obj/validateurs.o" "./obj/ajout_modification_membre.o" "./obj/imprimer_bulletin.o" $(RESSOURCES) -o "./bin/$@"  $(LIBS)
	$(LANCER_PROG)


./obj/ressources.res: | ./obj
	$(COMMANDE_WINDRES)
./obj: 
	mkdir obj
./bin:
	mkdir bin

./obj/login.o: ./src/login.cpp
	$(CC) "./src/login.cpp"  	$(CFLAGS) $(INCLUDE) -c -o "$@"
./obj/main.o: ./src/main.cpp
	$(CC) "./src/main.cpp"   	 $(CFLAGS) $(INCLUDE) -c -o "$@"
./obj/bdd.o: ./src/bdd.cpp
	$(CC) "./src/bdd.cpp"   	 $(CFLAGS) $(INCLUDE) -c -o "$@"
./obj/admin.o: ./src/admin.cpp
	$(CC) "./src/admin.cpp" 	 $(CFLAGS) $(INCLUDE) -c -o "$@"
./obj/professeur.o: ./src/professeur.cpp
	$(CC) "./src/professeur.cpp" $(CFLAGS) $(INCLUDE) -c -o "$@"
./obj/eleve.o: ./src/eleve.cpp
	$(CC) "./src/eleve.cpp"  	 $(CFLAGS) $(INCLUDE) -c -o "$@"
./obj/afficher_liste_membres.o: ./src/afficher_liste_membres.cpp
	$(CC) "./src/afficher_liste_membres.cpp"  	 $(CFLAGS) $(INCLUDE) -c -o "$@"
./obj/validateurs.o: ./src/validateurs.cpp
	$(CC) "./src/validateurs.cpp"  	 $(CFLAGS) $(INCLUDE) -c -o "$@"	
./obj/ajout_modification_membre.o : ./src/ajout_modification_membre.cpp
	$(CC) "./src/ajout_modification_membre.cpp"  	 $(CFLAGS) $(INCLUDE) -c -o "$@"	
./obj/imprimer_bulletin.o : ./src/imprimer_bulletin.cpp
	$(CC) "./src/imprimer_bulletin.cpp"  	 $(CFLAGS) $(INCLUDE) -c -o "$@"	
	
clean:
	$(RM_RES)
	rm "./bin/$(PROGRAMME).exe"