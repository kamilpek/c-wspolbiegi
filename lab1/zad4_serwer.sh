#!/bin/bash

plik="zad4_dane.txt"

liczba=$(cat "$plik")

let wynik=(liczba*liczba)/2

echo $wynik > zad4_wyniki.txt

$0
