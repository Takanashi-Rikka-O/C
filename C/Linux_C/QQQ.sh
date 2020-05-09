#!/bin/sh

echo Show the .c files

for x in $1 $2
do
	case "$x" in
		*.c)
			echo file is $x ;;
		.*)
			echo unknow this file..$x ;;
	esac
done

echo is over...

exit 0
