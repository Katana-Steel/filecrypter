#!/bin/bash

if [ -n "$1" ]
then
p=$1
else
p="."
fi

rm -f *.o
if [ ! -e "$p/lib" ]
then
 mkdir "$p/lib"
fi

if [ ! -e "$p/include" ]
then
 mkdir "$p/include"
fi

cp *.a "$p/lib/"
cp *.h "$p/include/"