#!/bin/bash
nom=$(pwd)/$2
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
./csuper-cli $1 "$nom"
