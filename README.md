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

This software is a personnel exercise of a student. Thank you to be indulgent. Furthermore, a re-writing of Csuper is on prgress (see 4.3 branch).

Please note that the Github repository is a mirror of the real repository which can be found [here](https://git.framasoft.org/Dalan94/Csuper).

### Documentation

The documentation is made by Doxygen.

A PDF version lay in the Documentation folder and a HTML version [here for csuper-cli](http://www.dalan.rd-h.fr/documentation/doc_csuper), [here for libcsuper](http://www.dalan.rd-h.fr/documentation/doc_libcsuper) and [here for csuper-gui](http://www.dalan.rd-h.fr/documentation/doc_csuper-gui)
A file explain the .csu files.

### Installation

#### Executables

Executables are available on [my website](http://www.dalan.rd-h.fr/wordpress).

#### Compilation

To compile csuper you need the following libraries:

 * GTK3 ≥ 3.6 (for the GUI version)
 * libxml2
 * libhpdf/libharu
 * gettext
 * cmake

Then use:
```
git clone --recursive https://git.framasoft.org/Dalan94/Csuper.git
cmake . -G"Unix Makefiles" -DCLI=TRUE -DGUI=TRUE
make
```

You can obviously chose to not compile the CLI or GUI version. If you are under Windows, you should specify the `CMAKE_INCLUDE_PATH` and `CMAKE_LIBRARY_PATH` variables.

There are codeblocks project to managed the sources if you want.

If you are under Linux you can run the softwares with the scripts `run-csuper` and `run-csuper-gui`.

The update and compilation of the translation is done via the following commands:

```
./update_translations
./compile_translations`
```

If you want to install or unistall csuper, use 

```
./install_csuper-cli
./install_csuper-gui
./uninstall_csuper-cli
./uninstall_csuper-gui
```

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

Ce logiciel a été fait en guise d'exercice personnel pendant des études donc soyez indulgent au niveau des remarques sur le code, merci. De plus une ré-écriture du logiciel en cours (voir branche 4.3).

Veuillez prendre en compte que le dépot Github est un miroir du vrai dépot qui se trouve [ici](https://git.framasoft.org/Dalan94/Csuper).

### Documentation

La documentation se fait à l'aide de Doxygen.
Une version PDF se trouve dans le dossier Documentation et une version HTML se trouve [ici pour csuper-cli](http://www.dalan.rd-h.fr/documentation/doc_csuper), [ici pour libcsuper](http://www.dalan.rd-h.fr/documentation/doc_libcsuper) et [ici pour csuper-gui](http://www.dalan.rd-h.fr/documentation/doc_csuper-gui).
Un fichier explique aussi comment sont ordonnées les données dans les fichiers .csu

### Installation


#### Exécutables

Les exécutables sont disponibles sur [mon site](http://www.dalan.rd-h.fr/wordpress).

#### Compilation

Les librairies nécessaires à la compilation sont :

 * GTK3 ≥ 3.6 (pour la version GUI)
 * libxml2
 * libhpdf/libharu
 * gettext
 * cmake

Pour récupérer le code source, utiliser

`git clone --recursive https://git.framasoft.org/Dalan94/Csuper.git`.

Vous pouvez compiler en utilisant cmake. Sous Linux aller à la racine du projet avec votre terminal puis utilsier les commandes suivantes :

```
cmake . -G"Unix Makefiles" -DCLI=TRUE -DGUI=TRUE
make
```

Vous pouvez évident choisir de ne pas compiler la version CLI ou GUI en supprimant la partie concernant dans cmake ainsi que ajouter les chemin vers les librairies à l'aide des variables `CMAKE_INCLUDE_PATH` et `CMAKE_LIBRARY_PATH`.

Vous pouvez ensuite utiliser les projets codeblocks si vous le souhaitez.

La mise à jour et la compilation de la traduction se fait via les commandes suivantes :

```
./update_translations
./compile_translations
```

Puis si vous êtes sous Linux vous pouvez lancer les logiciels avec les scripts `run-csuper-cli` et `run-csuper-gui`.

Si vous voulez installer ou désinstaller csuper, il faut utiliser les commandes suivantes : 

```
./install_csuper-cli
./install_csuper-gui
./uninstall_csuper-cli
./uninstall_csuper-gui
```

Penser à commenter ou décommenter la constante PORTABLE du fichier main.h pour csuper-cli et csuper-gui.h pour csuper-gui suivant la version que vous voulez.

Normalement la compilation devrait marcher sous Linux, Mac et Windows.

### Informations complémentaires

Si vous voyez des choses à améliorer, n'hésitez à me le faire parvenir.