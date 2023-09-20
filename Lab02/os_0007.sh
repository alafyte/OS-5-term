#!/bin/bash

regex='^[0-9]+$'


if [ "$1" = "" ];
then
	echo "parameters not found"
	exit
elif ! [[ $1 =~ $regex ]]
then
	echo "pid=$1 process not found"
	exit
fi

if ps -p $1 > /dev/null
then
	echo -n "Name: "
	ps -p $1 -o comm=
	echo "PID: $1"
	echo -n "PPID: "
	ps -o ppid= -p $1
else
	echo "pid=$1 process not found"
	exit
fi
if [ "$2" = "fd" ];
then
	for n in $`sudo ls -1 /proc/$1/fd`;
	do 
		echo "fd = $n"
	done
fi

#:set ff=unix
