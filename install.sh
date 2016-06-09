#!/bin/bash

APP=filecrypter
INSDST=/usr/local/bin

if [ -e $APP ]
then
  if [ ! -x $APP ]
  then
   chmod u+x $APP
  fi
  cp $APP $INSDST
  make clean
else
  if [ ! -f Makefile ]
  then
    qmake
  fi
  if [ -f Makefile ]; then
    make
    exec install.sh
  else
    echo "You'll need to install QT and then run qmake,"
    echo "followed by make before you run this script!"
  fi
fi
