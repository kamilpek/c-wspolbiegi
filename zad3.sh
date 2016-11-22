#!/bin/bash

declare -i x
valid='home'

dir=$(pwd)

if [ -d "$1" ]; then
  if [[ ! $1 =~ $vaild ]]; then
    sciezka="$dir/$1"
    cd $sciezka
  else
    sciezka="$1"
    cd $sciezka 2>/dev/null
  fi
  sciezka="$dir/$1"
  cd $sciezka 2>/dev/null
  for i in $( ls ); do
    if [ "$i" == "$2" ] ; then
      let "x += 1"
    else
      for j in $( ls -d "$sciezka"/*/ 2>/dev/null ); do
        $0 $j $2 x
      done
    fi
  done
else
  echo "podaj prawidlowy parametr $0 $1 $2 $3"
fi

if [[ ! -z $3 ]] ; then
  if [ -z $x ] ; then
    echo "nie znalazlem :("
  else
    echo "znalazlem w katalogu: $1"
  fi
fi
