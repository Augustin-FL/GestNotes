# Compilateur
CC=g++
# Options du compilateur 
CFLAGS=-O2 -Wall -mwindows 
# Option du linker
LIBS=-lwxmsw31u -lsqlite3 # -lwxmswu_31core

PROGRAMME=GestNote

REP_COURRANT=$(shell cd)

$(PROGRAMME):wx.o
	$(CC) $(CFLAGS) "main.cpp" wx.o -o "$@" -I "C:\Program Files\Cyg-npp\plugins\Dev-Cpp\include"  $(LIBS)
	$(REP_COURRANT)\$(PROGRAMME).exe
	
wx.o:
	windres -I "C:\include" "wx.rc" wx.o
	
	# en cas de recompilation de wx.rc : 
	# vous devez absolument copier le répertoire "include" dans un dossier SANS ESPACES !
	# ceci est un bug connu de windres.exe : https://sourceware.org/bugzilla/show_bug.cgi?id=4356
	# malheureusement, on peux pas faire grand chose contre cela (a pars attendre que windres soit mis a jour...)