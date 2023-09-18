#!/bin/bash

output=$(ls lib/) 
gcc_command="gcc -o main.out main.c"
winegcc_command="i686-w64-mingw32-gcc -o main.exe main.c"

for item in $output; do
	if [[ $item == *.c ]]; then
		gcc_command="$gcc_command lib/$item"
		winegcc_command="$winegcc_command lib/$item"

	fi
done

$gcc_command
$winegcc_command
echo
./main.out

