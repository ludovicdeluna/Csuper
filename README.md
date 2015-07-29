Csuper
======
![Csuper logo](Images/Logo_200.png)


Csuper (Universal points counter allowing a dispense with reflection)

Informations
------------

This software allow you to count points easily with a computer.
We can also save these games in a .csu file. (see documentation).

If you have any remarks or question on the use of csuper or on the code, don't hesitate to report to me.

This software is a personnel exercise of a student. Thank you to be indulgent. Furthermore, a re-writing of Csuper is on progress (see 4.3 branch).

Please note that the Github repository is a mirror of the real repository which can be found [here](https://git.framasoft.org/Dalan94/Csuper).

You can find a lot of informations on [my website](http://www.dalan.rd-h.fr/wordpress).

Documentation
-------------

The documentation is made by Doxygen.

A PDF version lay in the Documentation folder and a HTML version [here for csuper-cli](http://www.dalan.rd-h.fr/documentation/doc_csuper), [here for libcsuper](http://www.dalan.rd-h.fr/documentation/doc_libcsuper) and [here for csuper-gui](http://www.dalan.rd-h.fr/documentation/doc_csuper-gui)
A file explain the .csu files.

Installation
------------

### Executables

Executables are available on [my website](http://www.dalan.rd-h.fr/wordpress).

### Compilation

To compile csuper you need the following libraries:

 * GTK3 ≥ 3.6 (for the GUI version)
 * libxml2
 * libhpdf/libharu
 * gettext
 * cmake

Then use:
```
git clone --recursive https://git.framasoft.org/Dalan94/Csuper.git
cd csuper
cmake . -G"Unix Makefiles" -DCLI=TRUE -DGUI=TRUE
make
```

You can obviously chose to not compile the CLI or GUI version. If you are under Windows, you should specify the `CMAKE_INCLUDE_PATH` and `CMAKE_LIBRARY_PATH` variables.

There are codeblocks project to managed the sources if you want.

If you are under Linux you can run the softwares with the scripts `run-csuper-cli.sh` and `run-csuper-gui.sh`.

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

Additional Information
----------------------

If you any remark for improvement, do not hesitate to send it to me.