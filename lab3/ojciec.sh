declare -i x y z
echo -n "Podaj liczbe calkowita: "
read x
./syn.sh $x &
y=x*x
wait $!
y=y+$?
echo -n "Wynik: "
echo $y