#!/bin/bash
if [ "$2" != "" ];
	then nom=$(pwd)/$2
fi

if [ "$3" != "" ];
	then nom2=$(pwd)/$3
fi

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
./csuper-cli $1 "$nom" "$nom2"
