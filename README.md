# GestNote
A note-manager written in C++. Actually not stable ! 


## How to build
This programm use the following library :
- SQLite (for the storage)
- WxWidgets (for the windows)
- Pthread (for the multithreading)

g++ >= 4.9.x required (that mean : it don't work with Dev-Cpp of EFREI.)


###installation on linux (redhat) : 
first install dependencys : 
`sudo yum install wxGTK-devel wxBase sqlite-devel libxcb-devel devel`


### installation on windows (MinGW - Dev-Cpp)  : 
first, IF YOU ARE WORKING WITH EFREI COMPILERS, PLEASE REINSTALL LAST VERSION OF MinGW, elsewise your programm will not work
then copy  all in "windows - a copier dans mingw" zip file
finally, add the "bin" folder to your PATH



`g++ main.cpp -O2 -Wall -mwindows -lwxmsw31u -lwxtiff -lwxjpeg -lwxpng -lwxzlib -lwxregexu -lwxexpat -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwxregexu -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32   -mthreads -DHAVE_W32API_H -D__WXMSW__ -D__WXDEBUG__ -D_UNICODE -DWXUSINGDLL -Wno-ctor-dtor-privacy -pipe -fmessage-length=0 -lpdcurses -lpthreadGC2 -lSQLite3`


