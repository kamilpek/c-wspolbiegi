#!/bin/bash

usr=$(echo $HOME)
# usr="majster"

klient="$usr/Dokumenty/wspolbiegi/laborki/lab4/klientfifo"
serwer="/home/$2/Dokumenty/wspolbiegi/laborki/lab4/serwerfifo"


if [[ ! -p $serwer ]]; then
  echo "nie mozna sie polaczyc z laczem serwera"
  exit 1
fi


if [[ "$1" ]]; then
  echo $usr $1 >$serwer
  # echo "$1" >$serwer
  if [[ -p $klient ]]; then
    while true
    do
      if read line <$klient; then
          echo $line
          if [[ "$line" =~ $digit ]]; then
            exit 0
          else
            exit 0
          fi
      fi
    done
      else
        echo "nima"
        echo "$klient"
  fi
else
  echo "podaj prawidlowy argument polecenia"
fi
