# Compilateur
CC=g++
# Options du compilateur 
CFLAGS=-O2 -Wall -D_GNU_SOURCE=1 -Dmain=SDL_main -mwindows
# Option du linker
LIBS=-lwxmsw31u -lwxtiff -lwxjpeg -lwxpng -lwxzlib -lwxregexu -lwxexpat -lwxregexu -lwinspool -lwinmm 


REP_COURRANT=$(shell cd)

GestNote:wx.o
	$(CC) $(CFLAGS) "main.cpp" wx.o -o "$@" -I "C:\Program Files\Cyg-npp\plugins\Dev-Cpp\include"  $(LIBS)
	cmd /c start "" "$(REP_COURRANT)\GestNote.exe"
	
wx.o:
	windres -I "C:\include" "wx.rc" wx.o
	# en cas de recompilation de wx.rc : 
	# vous devez absolument copier le répertoire "include" dans un dossier SANS ESPACES !
	# ceci est un bug connu de windres.exe : https://sourceware.org/bugzilla/show_bug.cgi?id=4356
	# malheureusement, on peux pas faire grand chose contre cela (a pars attendre que windres soit mis a jour...)