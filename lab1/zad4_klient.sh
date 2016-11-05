#!/bin/bash


	echo "Podaj liczbe:"
	read LICZBA
	echo $LICZBA > zad4_dane.txt

	while true; do
		WYNIK=$(cat zad4_wyniki.txt 2> /dev/null)
		if [ ! -z "$WYNIK" ]; then
			echo "" > zad4_wyniki.txt
			echo "Wynik: $WYNIK"
			break
		fi
	done

