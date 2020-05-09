#!/bin/sh

fine=""

#x=""
#echo $1

for x in "$(find . -type f)"
do
file="$x"
file=${file%%./}


echo $file

case "$file" in
	*.c | *.s | *.txt | *.sh)
				continue;;
	*)
		chmod u+x "$file";;
esac

done

exit 0

	
