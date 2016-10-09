#!/bin/bash

declare -i x

echo "podaj cyfre"

read x

echo $x > /home/majster/Dokumenty/wspolbiegi/lab1/zad4_dane.txt

serwer_pid=`pidof zad4_serwer.sh`

wait $serwer_pid

wynik=$(cat /home/majster/Dokumenty/wspolbiegi/lab1/zad4_wyniki.txt)

echo $wynik

echo > /home/majster/Dokumenty/wspolbiegi/lab1/zad4_dane.txt

exit
