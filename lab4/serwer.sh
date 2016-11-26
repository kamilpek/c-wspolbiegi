#!/bin/bash

trap "" SIGHUP SIGTERM SIGCHLD
trap "exit 0" SIGUSR1

pipe=serwerfifo
if [[ -p $pipe ]]; then
  rm $pipe
  mkfifo $pipe
  chmod 777 $pipe
fi


digit='^[0-9]+$'
valid='home'

if [ ! -z $3 ]; then
  if [ ! -z $1 ] && [ ! -z $2 ]; then
    klient="$1/Dokumenty/wspolbiegi/laborki/lab4/klientfifo"
    if [[ -p $klient ]]; then
      var=$2
      let "var+=1"
      echo "$var" >$klient
    else
      echo "nie mozna polaczyc z klientem"
      echo $klient
    fi
  fi

  if [[ -p $pipe ]]; then
    while true
    do
      if read line <$pipe; then
        copy=$line
        line=$(sed 's/[0-9]*//g' <<< $line)
        x=$line
        copy=$(sed 's/[^0-9]//g' <<< $copy)
        y=$copy
        $0 $x $y &
      fi
  done
    else
      echo "nima"
  fi
else
  $0 $1 $2 1 &
fi
