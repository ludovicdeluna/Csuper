#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
./csuper-cli $1 $2 $3 $4 $5
