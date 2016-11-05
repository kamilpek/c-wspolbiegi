#!/bin/bash

declare -i x

echo "0 - odczyt komunikatu"
echo "1 - zapis komunikati"
echo "2 - koniec pracy"

read x

case "$x" in
	"0") cat  "$1" ;;
	"1") echo "helo" >> "$1" ;;
	"2") exit 0 ;;
esac
exit
