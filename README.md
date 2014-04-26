Csuper
======

English
-------

Csuper (Universal points counter allowing reflexion exemption)

###Informations

This software allow you to count points easily with a computer.
We can also save these games in a .csu file. (see documentation).

If you have any remarks or question on the use of csuper or on the code, don't hesitate to report to me. Similarly if you want to contribute on the code.

This software is a personnel exercise of a student. Thank you to be indulgent.

###Documentation

The documentation is made by Doxygen.

A PDF version lay in the Documentation folder and a HTML version [here for csuper](http://dalan.netne.net/Doc_csuper) and [here for libcsuper](http://dalan.netne.net/Doc_libcsuper)
A file explain the .csu files.

###Installation

Executables are available on [my website](http://dalan.netne.net/wordpress).

If you want to compile yourself, you can use the codeblocks project.
To compile you have to have gettext installed.

If you are under Linux and you want to use a portable version do `./add_library.sh` to add temporarily the current folder library file path.

The update of the translation is done via the command `./update_translations` and the compilation is done via the command `./compile_translations`

If you want to install it, do `./install_csuper`. To uninstall `./uninstall_csuper`

Think to comment or decomment PORTABLE in the file main.h depending on the version you want.

The compilation should work under Linux, Mac et Windows.

###Additional Information

A graphical interface in GTK+ is planned, this will surely take time.

Français
--------

Csuper (Compteur de Score Permettant l'Exemption de Réflexion)

###Informations

Ce logiciel permet de compter des points facilement sur son ordinateur via la console.
On peut aussi sauvegarder les parties dans des fichiers au format .csu (voir documentation).

Si vous avez des remarques ou des questions sur l'utilisation du logiciel ou le code en lui-même, n'hésiter pas à me le faire remarquer. De même si vous voulez contribuer au logiciel d'une façon ou d'une autre.

Ce logiciel a été fait en guise d'exercice personnel pendant des études donc soyez indulgent au niveau des remarques sur le code, merci.

###Documentation

La documentation se fait à l'aide de Doxygen.
Une version PDF se trouve dans le dossier Documentation et une version HTML se trouve [ici pour csuper](http://dalan.netne.net/Doc_csuper) et [ici pour libcsuper](http://dalan.netne.net/Doc_libcsuper)
Un fichier explique aussi comment sont ordonnées les données dans les fichiers .csu

###Installation

Les exécutables sont disponibles sur [mon site](http://dalan.netne.net/wordpress).

Si vous voulez compiler vous même le logiciel, vous pouvez utiliser les projets codeblocks.
Pour pouvoir compiler il faut que vous ayez d'installé gettext.

La mise à jour de la traduction se fait via la commande `./update_translations` et la compilation de la traduction par la commande `./compile_translations`

Puis si vous êtes sous Linux et que vous voulez l'utiliser en version portable faites `./add_library.sh` pour ajouter temporairement le dossier courant dans la liste de chemin de librairie.

Et si vous voulez l'installer faites `./install_csuper`. Pour le désinstaller `./uninstall_csuper`

Penser à commenter ou décommenter la constante PORTABLE du fichier main.h suivant la version que vous voulez.

Normalement la compilation devrait marcher sous Linux, Mac et Windows.

###Informations complémentaires

Une interface graphique en GTK+ en prévu, mais cela risque de prendre du temps.