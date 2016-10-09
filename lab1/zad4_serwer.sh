#!/bin/bash

plik="/home/majster/Dokumenty/wspolbiegi/lab1/zad4_dane.txt"

liczba=$(cat "$plik")

let wynik=(liczba*liczba)/2

echo $wynik > /home/majster/Dokumenty/wspolbiegi/lab1/zad4_wyniki.txt

$0
