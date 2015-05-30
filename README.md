# GestNotes
GestNotes est un logiciel de gestion de notes écrit en C++ !

[![Build Status](https://travis-ci.org/gusfl/GestNotes.svg)](https://travis-ci.org/gusfl/GestNotes) [![Licence](https://img.shields.io/hexpm/l/plug.svg)](https://fr.wikipedia.org/wiki/Licence_Apache)

## Comment utiliser le programme : 

Téléchargez [la dernière relase](https://github.com/gusfl/GestNotes/releases/latest) de GestNotes dans un dossier de votre ordinateur, puis lancez GestNotes.exe.

Le programme fonctionne actuellement en local sur un ordinateur. 

compte Administrateur : 
```console
matricule : 1
mot de passe : test
```

compte Professeur : 
```console
matricule : 2
mot de passe : test
```

compte Etudiant : 
```console
matricule : 3
mot de passe : test
```

## Comment compiler le programme a partir de ses sources : 
**Note :**  g++ >= 4.x.x  est requis (cela siginifie : ca ne marche pas avec Dev-Cpp de l'EFREI. Si vous travaillez avec Windows, vous devez utiliser une autre version de MinGW. Celle de codeblocks par défaut depuis 2012 fait très bien l'affaire, par exemple).


GestNotes utilise les dépendances suivantes, que vous devez installer : 
- SQLite >= 3 (pour le stockage)
- WxWidgets >= 3.x.x (pour les fenêtres)

Pour compiler GestNotes, vous devez d'abord compiler ces dépendances depuis leurs sources. 

**Pour linux (Debian)**, quelques lignes de commandes permettent de tout installer : 
 ```console 
sudo apt-key adv --fetch-keys http://repos.codelite.org/CodeLite.asc
sudo apt-add-repository 'deb http://repos.codelite.org/wx3.0.2/ubuntu/ precise universe'
sudo apt-get install -y liblzma5 libjbig0 libpango1.0-0 libwxbase3.0-0-unofficial libwxbase3.0-dev libwxgtk3.0-0-unofficial libwxgtk3.0-dev wx3.0-headers wx-common wx3.0-i18n libcppunit-dev libsqlite3-dev
sudo mv /usr/include/wx-3.0-unofficial/wx /usr/include/wx
sudo mkdir /usr/include/SQLite && sudo mv /usr/include/sqlite3.h /usr/include/SQLite/sqlite3.h 
```

**Pour windows** : 
vous pouvez télécharger toutes les dépendances compilées par votre serviteur (moi) [ici](https://mega.co.nz/#!F5EXzJpY!6W0L0zBizfhRYERPQND_8xvTLXvH4b509XSRd61qLqU). Vous avez juste à fusionner le fichier ZIP avec le dossier de MinGW qui se trouve sur votre ordinateur. 

Une fois ceci fait, vous pouvez compiler GestNotes, à l'aide du projet codeblocks (.cbp),ou du Makefile.

Note : si vous ne maitrisez ni les Makefile ni CodeBlocks : un fichier .vcxproj (pour Visual Studio) sera bientot ajouté au projet.

pour windows : Si vous avez une erreur `'wx/msw/hand.cur': No such file or directory` lors de la compilation : 
- si vous compilez à l'aide du makefile, la procédure pour déjouer ce problème est expliquéee dedans
- si vous compilez à l'aide de codeblocks, la procédure est expliquée dans le fichier ressources.rc

## Bugs connus  : 
* Eleves :L'affichage/impression du bulletin ne fonctionne pas correctement (Cause : le HTML est mal interprété par wxHtmlWindow)
* Admins : Lors de l'ajout d'un élève, la liste des appréciations générales ne se met pas à jour (le nouvel élève n'est pas ajouté. Cause : le wxDataViewList buge)
* Profs/Admins : Le tri (clic sur l'en-tête d'une colonne) ne fonctionne pas pour les administrateurs (appréciations générales) ni pour les professeurs(l'interface des notes. Cause : le wxDataViewList buge)

## Fonctionnalités futures : 
* Ajout de la notion de professeur "principal" (affectation à une classe, accès à toutes les notes de toutes les matières pour cette classe, etc)
* Ajouter un chiffrement des mots de passes à l'aide de la librairie crypto d'OpenSSL
* Améliorer les performances de la Frame de gestion des Groupes

## Fonctionnalités futures (lointaines) : 
* Proposer au professeurs d'ajouter un nombre illimité de notes (d'ajouter une colonne), si le wxDataViewList le permet
* Effectuer les sauvegardes des buletins au format PDF et non HTML, à l'aide de la librairie externe wxPdfDocument
* Utiliser une base de donnée distante(MySQL?) plutot qu'une base locale, à l'aide d'une icone d'aide sur l'interface de login.
