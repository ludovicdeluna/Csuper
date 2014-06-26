#!/bin/bash
nom=$(pwd)/$1
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
./csuper-gui "$nom"
