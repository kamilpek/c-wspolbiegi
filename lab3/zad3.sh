#!/bin/bash

declare -i x

dir=$(pwd)
valid='home'

if [ -d "$1" ]; then
  if [[ $1 =~ $valid ]]; then
    sciezka="$dir/$1"
    cd $sciezka
  else
    sciezka="$1"
    cd $sciezka
  fi
  for i in $( ls ); do
    if [ "$i" == "$2" ] ; then
      let "x += 1"
      # echo $i $2
    else
      # echo $i $2
      for j in $( ls -d */ 2>/dev/null ); do
          # echo $j $2
          $0 "$j" "$2" 1 &
      done
    fi
  done
else
  echo "podaj prawidlowy parametr"
fi

for job in `jobs -p`
do
  wait $job
  let "x+=$?"
done

if [ -z $3 ] ; then
# if [[ ! -z $3 ]] ; then
  if [ ! $x -ge 1 ] ; then
    echo "nie znalazlem :("
  else
    echo "znalazlem :)"
  fi
fi

exit $x
