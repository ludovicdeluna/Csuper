Csuper
======
![Csuper logo](Images/Logo_200.png)

English
-------

Csuper (Universal points counter allowing a dispense with reflection)

### Informations

This software allow you to count points easily with a computer.
We can also save these games in a .csu file. (see documentation).

If you have any remarks or question on the use of csuper or on the code, don't hesitate to report to me.

This software is a personnel exercise of a student. Thank you to be indulgent.

Please note that the Github repository is a mirror of the real repository which can be found [here](https://git.framasoft.org/Dalan94/Csuper).

### Documentation

The documentation is made by Doxygen.

A PDF version lay in the Documentation folder and a HTML version [here for csuper-cli](http://www.dalan.rd-h.fr/documentation/doc_csuper), [here for libcsuper](http://www.dalan.rd-h.fr/documentation/doc_libcsuper) and [here for csuper-gui](http://www.dalan.rd-h.fr/documentation/doc_csuper-gui)
A file explain the .csu files.

### Installation

Executables are available on [my website](http://www.dalan.rd-h.fr/wordpress).

To retrieve the source code use `git clone --recursive https://git.framasoft.org/Dalan94/Csuper.git` and then `git submodule update --init`.
If you want to compile yourself, you can use the codeblocks project.
You can also use cmake. On Linux type `cmake . -G"Unix Makefiles" -DCLI=TRUE -DGUI=TRUE` then `make`.
To compile libcsuper and csuper-cli you have to have gettext, libxml2 and liphpdf/libharu installed.
To compile csuper-gui you have to have GTK3 installed.

If you are under Linux you can run the softwares with the scripts `run-csuper` and `run-csuper-gui`.

The update of the translation is done via the command `./update_translations` and the compilation is done via the command `./compile_translations`

If you want to install csuper, do `./install_csuper-cli` or `./install_csuper-gui`. To uninstall `./uninstall_csuper-cli` or `./uninstall_csuper-gui`

Think to comment or decomment PORTABLE in the file main.h for csuper-cli or the file csuper-gui.h for csuper-gui depending on the version you want.

The compilation should work under Linux, Mac et Windows.

### Additional Information

If you any remark for improvement, do not hesitate to send it to me.

Français
--------

Csuper (Compteur de Score Permettant l'Exemption de Réflexion)

### Informations

Ce logiciel permet de compter des points facilement sur son ordinateur via la console.
On peut aussi sauvegarder les parties dans des fichiers au format .csu (voir documentation).

Si vous avez des remarques ou des questions sur l'utilisation du logiciel ou le code en lui-même, n'hésiter pas à me le faire remarquer.

Ce logiciel a été fait en guise d'exercice personnel pendant des études donc soyez indulgent au niveau des remarques sur le code, merci.

Veuillez prendre en compte que le dépot Github est un miroir du vrai dépot qui se trouve [ici](https://git.framasoft.org/Dalan94/Csuper).

### Documentation

La documentation se fait à l'aide de Doxygen.
Une version PDF se trouve dans le dossier Documentation et une version HTML se trouve [ici pour csuper-cli](http://www.dalan.rd-h.fr/documentation/doc_csuper), [ici pour libcsuper](http://www.dalan.rd-h.fr/documentation/doc_libcsuper) et [ici pour csuper-gui](http://www.dalan.rd-h.fr/documentation/doc_csuper-gui).
Un fichier explique aussi comment sont ordonnées les données dans les fichiers .csu

### Installation

Les exécutables sont disponibles sur [mon site](http://www.dalan.rd-h.fr/wordpress).

Pour récupérer le code source, utiliser `git clone --recursive https://git.framasoft.org/Dalan94/Csuper.git` puis `git submodule update --init`.
Si vous voulez compiler vous même le logiciel, vous pouvez utiliser les projets codeblocks.
Vous pouvez aussi compiler en utilisant cmake. Sous Linux aller à la racine du projet avec votre terminal puis taper `cmake . -G"Unix Makefiles" -DCLI=TRUE -DGUI=TRUE` et enfin `make`.
Pour pouvoir compiler libcsuper et csuper-cli il faut que vous ayez d'installé gettext, libxml2 et libhpdf/libharu.
Et pour csuper-gui il faut avoir GTK3 d'installé.

La mise à jour de la traduction se fait via la commande `./update_translations` et la compilation de la traduction par la commande `./compile_translations`

Puis si vous êtes sous Linux vous pouvez lancer les logiciels avec les scripts `run-csuper-cli` et `run-csuper-gui`.

Et si vous voulez installer csuper faites `./install_csuper-cli` ou `./install_csuper-gui`. Pour le désinstaller `./uninstall_csuper-cli` ou `./uninstall_csuper-gui`

Penser à commenter ou décommenter la constante PORTABLE du fichier main.h pour csuper-cli et csuper-gui.h pour csuper-gui suivant la version que vous voulez.

Normalement la compilation devrait marcher sous Linux, Mac et Windows.

### Informations complémentaires

Si vous voyez des choses à améliorer, n'hésitez à me le faire parvenir.