#!/bin/bash
rm -f .tmpa .tmpb .tmpc

systems=$(ls unistd | sed 's/asm\-//')
command="dialog --menu 'Pick the target architecture:' 12 45 25"
j=1
for i in $systems
do
	command="$command $j \"$i\""
	j=$((j + 1))
done

system=""
bash -c "$command" 2> .configure
c=$(cat .configure)
j=1
for i in $systems
do
	if [ "$j" = "$c" ]
	then
		system="$i"
	fi
	j=$((j + 1))
done
if [ "$system" = "" ]
then
	exit
fi

#fetch unistd.h file
cp unistd/asm-$system/unistd.h .tmpa


#remove anything that is not an __NR define
cat .tmpa | sed 's/\/.*//' | grep -i 'define __NR' | sed 's/\t/ /g' > .tmpb
rm -f .tmpa .tmpc

echo "Fetching syscall values..."
while IFS= read -r line; do
	nme=$(echo "$line" | cut -d' ' -f2)
	val=$(echo "$line" | cut -d' ' -f3-)

	if printf "%d" "$val" >/dev/null 2>/dev/null
	then
		val=$(printf "%d" "$val")
	fi

	res=$(echo "$val" | bc 2>/dev/null)
	if [ "$res" != "" ]
	then
		echo "|$nme| $val" >> .tmpa
	fi
done < .tmpb

echo "Checking for duplicate entries..."
checked="|"
while IFS= read -r line; do
	nme=$(echo "$line" | cut -d' ' -f1 | sed 's/|//g')
	chk=$(echo "$checked" | grep "|$nme|")
	if [ "$chk" == "" ]
	then
		cnt=$(cat .tmpa | grep "|$nme|" | wc -l)
		if [ "$cnt" != "1" ]
		then
			echo "$nme"
			command="dialog --menu \"$nme\" 12 45 25"
			j=1
			sel=$(cat .tmpa | grep "$nme" | cut -d' ' -f2)
			for i in $sel
			do
				h=$(printf "0x%x" "$i")
				command="$command $j \"$h\""
				j=$((j + 1))
			done
			bash -c "$command" 2> .configure
			opt=""
			cnf=$(cat .configure)
			j=1
			for i in $sel
			do
				if [ "$j" = "$cnf" ]
				then
					opt="$i"
				fi
				j=$((j + 1))
			done
			if [ "$opt" = "" ]
			then
				exit
			fi
			opt=$(printf "%d" "$opt")
			echo "|$nme| $opt" >> .tmpc
		else
			echo "$line" >> .tmpc
		fi
		checked="$checked|$nme|"
	fi
done < .tmpa

#sort to avoid substitution issues
cat .tmpc | awk '{ print -length($1), $0 }' "$@" | sort -n -s | cut -d" " -f2-> .tmpa
rm .tmpc

echo "Computing values..."
while IFS= read -r line; do
	nme=$(echo "$line" | cut -d' ' -f2)
	val=$(echo "$line" | cut -d' ' -f3-)
	if printf "%d" "$val" >/dev/null 2>/dev/null
	then
		val=$(printf "%d" "$val")
	fi
	cmp=$(echo "$val" | bc 2>&1 | grep -E "(illegal|error)" | wc -c)
	if [ "$cmp" = "0" ]
	then

		val=$(echo "$val" | bc)
		echo "|$nme| $val" >> .tmpc
	else
		while IFS= read -r sline; do
			snme=$(echo "$sline" | cut -d' ' -f1 | sed 's/|//g')
			sval=$(echo "$sline" | cut -d' ' -f2)
			val=$(echo "$val" | sed "s/$snme/$sval/g")
		done < .tmpa
		cmp=$(echo "$val" | bc 2>&1 | grep -E "(illegal|error)" | wc -c)
		if [ "$cmp" != "0" ]
		then
			echo "could not parse"
			echo "$val"
			exit
		else
			val=$(echo "$val" | bc)
			echo "|$nme| $val" >> .tmpc
		fi
	fi
done < .tmpb

echo "Generating files..."
rm -f .tmpb unistd.h
while IFS= read -r line; do
	name=$(echo $line | cut -d' ' -f1)
	cat .tmpc | grep "|$name|" | uniq > .tmpa
	if [ "$(cat .tmpa | wc -l)" != "0" ]
	then
		while IFS= read -r sline; do
			id=$(echo "$sline" | cut -d' ' -f2)
			echo $id $(echo "$line" | cut -d' ' -f2-) >> .tmpb
			echo "#define $name $id" >> unistd.h
		done < .tmpa
	fi
done < .template
mv .tmpb zedexconf
