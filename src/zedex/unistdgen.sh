#!/bin/bash

function gencfile
{
	echo "#include <stdio.h>"
	echo "#include <unistd.h>"
	echo "#include <sys/syscall.h>"
	echo "int main()"
	echo "{"
	while IFS= read -r line
	do
		name=$(echo $line | cut -d' ' -f1)
		echo "    #ifdef $name"
		echo "    printf(\"|$name| %i\n\", $name);"
		echo "    #endif"
	done < .template
	echo "    return 0;"
	echo "}"
}

if [ "$CC" = "" ]
then
	CC=gcc
fi

if ! which dialog
then
	echo 'Please install `dialog`.'
	exit
fi

dialog --yesno "Are these files to be configured for the machine running this application?" 10 50
case $? in
	0)
		gencfile > .tmp.c
		$CC $CFLAGS $LDFLAGS .tmp.c -o .tmpx
		./.tmpx > .tmpu
	;;
	1)
		if [ -f "$1" ]
		then
			cp "$1" .tmpu
		else
			gencfile > syslog.c
			dialog --msgbox  "Please compile and run the generated \`syslog.c\` file on the desired target system, store the output of it to a file, then call this script again passing the generated log as a command-line argument." 10 50
			clear
			exit
		fi
	;;
	255)
		clear
		exit
	;;
esac

cat .tmpu | awk '{ print -length($1), $0 }' "$@" | sort -n -s | cut -d" " -f2->.tmps

echo "//Automatically generated for $(uname -m)" > include/unistd.h
while IFS= read -r line
do
	name=$(echo $line | cut -d' ' -f1)
	id=$(cat .tmps | grep "|$name|" | cut -d' ' -f2)
	arg=$(echo "$line" | cut -d' ' -f2-)
	if [ "$id" != "" ] && [ "$name" != "" ]
	then
		echo "#define $name $id" >> include/unistd.h
	fi
done < .template
rm -f .tmp*
clear

echo "Done."
