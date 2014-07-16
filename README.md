Csuper
======
![Csuper logo](Images/Logo_200.png)

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

A PDF version lay in the Documentation folder and a HTML version [here for csuper](http://www.dalan.rd-h.fr/documentation/doc_csuper), [here for libcsuper](http://www.dalan.rd-h.fr/documentation/doc_libcsuper) and [here for csuper-gui](http://www.dalan.rd-h.fr/documentation/doc_csuper-gui)
A file explain the .csu files.

###Installation

Executables are available on [my website](http://www.dalan.rd-h.fr/wordpress).

If you want to compile yourself, you can use the codeblocks project.
To compile libcsuper and csuper you have to have gettext installed.
To compile csuper-gui you have to have GTK3 installed.

If you are under Linux you can run the softwares with the scripts `run-csuper` and `run-csuper-gui`.

The update of the translation is done via the command `./update_translations` and the compilation is done via the command `./compile_translations`

If you want to install csuper, do `./install_csuper` or `./install_csuper-gui`. To uninstall `./uninstall_csuper` or `./uninstall_csuper-gui`

Think to comment or decomment PORTABLE in the file main.h for csuper or the file csuper-gui.h for csuper-gui depending on the version you want.

The compilation should work under Linux, Mac et Windows.

###Additional Information

If you any remark for improvement, do not hesitate to send it to me.

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
Une version PDF se trouve dans le dossier Documentation et une version HTML se trouve [ici pour csuper](http://www.dalan.rd-h.fr/documentation/doc_csuper), [ici pour libcsuper](http://www.dalan.rd-h.fr/documentation/doc_libcsuper) et [ici pour csuper-gui](http://www.dalan.rd-h.fr/documentation/doc_csuper-gui).
Un fichier explique aussi comment sont ordonnées les données dans les fichiers .csu

###Installation

Les exécutables sont disponibles sur [mon site](http://www.dalan.rd-h.fr/wordpress).

Si vous voulez compiler vous même le logiciel, vous pouvez utiliser les projets codeblocks.
Pour pouvoir compiler libcsuper et csuper il faut que vous ayez d'installé gettext.
Et pour csuper-gui il faut avoir GTK3 d'installé.

La mise à jour de la traduction se fait via la commande `./update_translations` et la compilation de la traduction par la commande `./compile_translations`

Puis si vous êtes sous Linux vous pouvez lancer les logiciels avec les scripts `run-csuper` et `run-csuper-gui`.

Et si vous voulez installer csuper faites `./install_csuper` ou `./install_csuper-gui`. Pour le désinstaller `./uninstall_csuper` ou `./uninstall_csuper-gui`

Penser à commenter ou décommenter la constante PORTABLE du fichier main.h pour csuper et csuper-gui.h pour csuper-gui suivant la version que vous voulez.

Normalement la compilation devrait marcher sous Linux, Mac et Windows.

###Informations complémentaires

Si vous voyez des choses à améliorer, n'hésitez à me le faire parvenir.