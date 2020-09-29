#!/bin/bash
rm out.txt

for i in $(seq 1 $1);
do
	echo "Seed $i: " >> out.txt
	./Game Mati Dummy Dummy Dummy -s "$i" -i default.cnf -o default.res &> temp.txt
	grep "got" temp.txt >> out.txt
	echo " " >> out.txt
done
rm temp.txt
cat out.txt
echo Mati ha ganado
cat out.txt | grep -o "Mati got top score" | wc -l
