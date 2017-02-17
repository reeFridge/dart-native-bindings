#!/usr/bin/env bash

cd ./lib/src/native/

g++ -fPIC -I$1 -DDART_SHARED_LIB -c mpg123native.cc
gcc -shared -Wl,-soname,libmpg123native.so -o libmpg123native.so mpg123native.o -lmpg123