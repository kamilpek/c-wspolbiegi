#!/bin/bash

declare -i n k i wynik nk
echo -n "Podaj pierwsza liczbe calkowita: "
read n
echo -n "Podaj druga liczbe calkowita: "
read k

./silnia.sh $n &
./silnia.sh $k &
./silnia.sh $((n-k)) &

let i=0

for job in `jobs -p`
do
    	wait $job
	silnie[i]=$?
	i=$((i+1))
done

let "wynik = ${silnie[1]}*${silnie[2]}"
let "wynik = ${silnie[0]}/$wynik"
echo "Wynik wspolczynnika dwumianowego to: $wynik"
