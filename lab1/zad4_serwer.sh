#!/bin/bash

while true; do
	DANE=$(cat zad4_dane.txt 2> /dev/null)
	if [ ! -z $DANE ]; then
		echo "" > zad4_dane.txt
		if ! [[ $DANE =~ ^[0-9]+$ ]]; then
			WYNIK="Nie podano liczby!"
		else
			WYNIK=$(((DANE * DANE)*2))
		fi
		echo $WYNIK > zad4_wyniki.txt
	fi
done
