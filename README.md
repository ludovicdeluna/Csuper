Csuper
======

Csuper (Compteur de Score Permettant l'Exemption de Réflexion)

Informations
-----------

Ce logiciel permet de compter des points facilement sur son ordinateur via la console.
On peut aussi sauvegarder ces fichiers dans des fichiers au format .csu (voir documentation).

Si vous avez des remarques ou des questions sur l'utilisation ou le code, n'hésiter pas à me le faire remarquer. De même si vous voulez contribuer au logiciel d'une facon ou d'une autre.

Ce logiciel a été fait en guise d'exercice personnel pendant des études donc soyez indulgent au niveau des remarques sur le code, merci.

Documentation
-------------
La documentation se fait à l'aide de Doxygen.
Une version PDF se trouve dans le dossier Documentation et une version html se trouve [ici](http://dalan.netne.net/Doc_csuper)
Un fichier explique aussi comment sont ordonnées les données dans les fichiers .csu

Installation
-----------
Les éxécutables sont disponibles sur [mon site](http://dalan.netne.net/wordpress).

Si vous voulez compiler vous même le logiciel, vous pouvez utiliser la commande `make` ou les projets codeblocks.
Puis si vous voulez l'utiliser en version portable faites `source ./add_library.sh` pour ajouter temporairement le dossier courant dans la liste de chemin de librairie.
Et si vous voulez l'installer faites `sudo make install`. Il faudra alors faire `sudo make uninstall` pour le désinstaller.

Penser à commenter ou décommenter la constante PORTABLE du fichier emplacement_fichier.h suivant la version que vous voulez.

Normalement la compilation devrait marcher sous Linux, Mac et Windows.

Informations complémentaires
----------------------------
Je suis actuellement en train de travailler sur l'amélioration des fichiers de configurations de jeu ainsi que sur la traduction anglaise.

Une interface graphique en GTK+ en prévu, mais cela risque de prendre du temps.