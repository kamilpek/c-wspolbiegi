#!/bin/bash

declare -i x

echo "podaj cyfre"

read x

echo $x > zad4_dane.txt

serwer_pid=`pidof zad4_serwer.sh`

wait $serwer_pid

wynik=$(cat zad4_wyniki.txt)

echo $wynik

echo > zad4_dane.txt

exit
