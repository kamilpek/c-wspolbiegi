#!/bin/bash

declare -i x

dir=$(pwd)

if [ -d "$1" ]; then
  sciezka="$dir/$1"
  cd $sciezka
  for i in $( ls ); do
    if [ "$i" == "$2" ] ; then
      let "x += 1"
    else
      for j in $( ls -d ); do
        $0 $i $2 1 &
      done
    fi
  done
else
  echo "podaj prawidlowy parametr"
fi

if [ -z $3] ; then
  if [ -z $x ] ; then
    echo "nie znalazlem :("
  else
    echo "znalazlem :)"
  fi
fi
