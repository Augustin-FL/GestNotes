# GestNotes
GestNotes est un logiciel de gestion de notes écrit en C++ !

[![Build Status](https://travis-ci.org/zestedesavoir/zds-site.svg?branch=dev)]()

## Comment utiliser le programme : 

Copiez tout les fichiers présents dans le dossier "bin" sur un dossier de votre ordinateur, puis lancez GestNotes.exe.

Le programme fonctionne actuellement en local sur un ordinateur. 

compte Administrateur : 
```console
matricule : 1
mot de passe : test
```

compte Professeur(fenètres pas encore crées) : 
```console
matricule : 2
mot de passe : test
```

compte Etudiant (fenètres pas encore créés) : 
```console
matricule : 3
mot de passe : test
```

## Comment compiler le programme a partir de ses sources : 
**Note :**  g++ >= 4.x.x  est requis (cela siginifie : ca ne marche pas avec Dev-Cpp de l'EFREI. Si vous travaillez avec Windows, vous devez utiliser une autre version de MinGW. Celle de codeblocks par défaut depuis 2012 fait très bien l'affaire, par exemple).


GestNotes utilise les dépendances suivantes, que vous devez installer : 
- SQLite >= 3 (pour le stockage)
- WxWidgets >= 3.x.x (pour les fenêtres)

Pour compiler GestNotes, vous devez d'abbord compiler ces dépendances depuis leurs sources sources. 

**Pour linux (Red Hat)**, c'est simple : 
 ```console 
sudo yum install wxGTK-devel wxBase
```
**Pour windows** en revanche, c'est plus complexe : 
- Pour wxWidgets, vous trouverez un tutoriel sur [le site officiel de codeblocks](http://wiki.codeblocks.org/index.php?title=Compiling_wxWidgets_3.0.0_to_develop_Code::Blocks_(MSW)) 
- Pour SQLite, le tutoriel se trouve sur leur [site officiel](https://www.sqlite.org/howtocompile.html)

Pour windows : Si vous ne voulez pas vous embêter avec les dépendances (et que vous recherchez la solution de facilité), vous pouvez télécharger celles ci toutes compilées par votre serviteur(moi) [ici](https://mega.co.nz/#!F5EXzJpY!6W0L0zBizfhRYERPQND_8xvTLXvH4b509XSRd61qLqU). Vous avez juste à fusionner le fichier ZIP avec le dossier de MinGW qui se trouve sur votre ordinateur.

Vous devrez également ajouter une variable d'environement (qui est néssésaire au fonctionnement de wxWidgets) : `WXCFG=gcc_dll\mswud`
 

Une fois ceci fait, vous pouvez compiler GestNotes.

Note : si vous ne maitrisez pas la ligne de commande ni les Makefile :  un fichier .cbp (pour codeblocks) et un fichier .vcxproj (pour visual studio) seront bientot ajoutés au projet.


## ToDo list : 

futur proche :
* Terminer l'interface de gestion des administrateurs
* -> Supporter la suppression d'un étudiant/élève/prof
* -> Supporter la modification d'un étudiant/élève/prof
* Créer l'interface de gestion pour les professeurs
* -> Saisie des notes
* -> Saisie des groupes
* Créer l'interface de gestion pour les élèves
* Ajouter une fonctionnalité : l'impression des buletins
* Ajouter les menus graphiques

futur éloigné : 
* Ajouter un chiffrement de la base de donnée à l'aide de la librairie crypto d'OpenSSL
* Utiliser une base de donnée distante(MySQL?) plutot qu'une base locale 
* Creer un installateur à l'aide de NSIS
