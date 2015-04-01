# Compilateur
CC=g++
# Options du compilateur 
CFLAGS=-O2 -Wall 
# Option du linker
LIBS=-lwxmsw31u -lsqlite3 -mwindows # -lwxmswu_31core

PROGRAMME=GestNotes

REP_COURRANT=$(shell cd)

ifeq ($(OS),Windows_NT)
TMP=$(shell echo %tmp%)
else 
TMP=.src
endif


# en cas de recompilation de wx.rc : 
# vous devez absolument copier le répertoire "include" dans un dossier SANS ESPACES !
# ceci est un bug connu de windres.exe : https://sourceware.org/bugzilla/show_bug.cgi?id=4356
# malheureusement, on peux pas faire grand chose contre cela (a part attendre que windres soit mis a jour...)

# -I "C:\Program Files\Cyg-npp\plugins\Dev-Cpp\include"

$(PROGRAMME):$(TMP)/ressources.o"
	$(CC) $(CFLAGS) "./src/bdd.cpp" "./src/login.cpp" "./src/main.cpp" "$(TMP)/ressources.o" -o "./bin/$@" -I "./include"  $(LIBS)
	
	cmd /C start "$(PROGRAMME)" "$(REP_COURRANT)\bin\$(PROGRAMME).exe"
	
$(TMP)/ressources.o":
	windres -I "C:\include" "./src/ressources.rc" "$(TMP)/ressources.o"
	
clean:
	rm "$(TMP)ressources.o"
	rm "./bin/$(PROGRAMME).exe"