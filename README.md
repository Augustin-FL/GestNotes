# GestNote
GestNote est un logiciel de gestion de notes écrit en C++ . Actuellement non stable !

[![Build Status](https://travis-ci.org/zestedesavoir/zds-site.svg?branch=dev)]()

## Comment utiliser le programme : 

Copiez tout les fichiers présents dans le dossier "bin" sur un dossier de votre ordinateur, puis lancez GestNote.exe.

Le programme fonctionne actuellement en local sur un ordinateur.

## Comment compiler le programme a partir de ses sources : 


**Attention** : le Makefile actuel du projet n'est pas universel ! Ceci est en cours d'amélioration.


Celui ci utilise les dépendances suivantes, que vous devez installer : 
- SQLite >= 3 (pour le stockage)
- WxWidgets >= 3.x.x (pour les fenêtres)
- g++ >= 4.x.x  est requis (cela siginifie : ca ne marche pas avec Dev-Cpp de l'EFREI. Si vous travaillez avec Windows, vous devez utiliser une autre version de MinGW. Celle de codeblocks par défaut depuis 2012 fait très bien l'affaire, par exemple).

Vous devez pour cela compiler ces dépendances depuis les sources. 
- Pour wxWidgets, vous trouverez un tutoriel sur le site officiel de codeblocks : http://wiki.codeblocks.org/index.php?title=Compiling_wxWidgets_3.0.0_to_develop_Code::Blocks_(MSW) 
- Pour SQLite, le tutoriel se trouve sur leur site officiel : https://www.sqlite.org/howtocompile.html

Pour windows -> Si vous ne voulez pas vous embêter avec les dépendances (solution de facilité), vous pouvez télécharger celles ci toutes compilées par votre serviteur ici : https://mega.co.nz/#!F5EXzJpY!6W0L0zBizfhRYERPQND_8xvTLXvH4b509XSRd61qLqU
Vous avez juste à fusionner le fichier ZIP avec le dossier de MinGW qui se trouve sur votre ordinateur. Vous devrez également ajouter une variable d'environement : `WXCFG=gcc_dll\mswud`


Une fois ceci fait, vous pouvez compiler GestNote, en effectuant les commandes suivantes : 
```console
windres "./src/wx.rc" ".tmp/wx.o"
g++ -O2 -Wall -lwxmsw31u -lsqlite3 -mwindows "./src/bdd.cpp" "./src/main.cpp" "./tmp/wx.o" -I "./include" -o "./bin/GestNote.exe"
```

## ToDo list : 
futur proche : 
 *terminer l'interface de gestion des administrateurs
 *creer l'interface de gestion pour les élèves et professeurs
 *Ajouter une fonctionnalité : l'impression des buletins
 
futur éloigné : 
 *ajouter une encryption de la base de donnée à l'aide de GNU-TLS
 *utiliser une base de donnée distante plutot qu'une base locale
 
