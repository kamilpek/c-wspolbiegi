#!/bin/bash

factorial()
{
	if [ $1 -le 1 ]
	then
		return 1
	else
		factorial $[$1-1]
		return $[$1*$?]
	fi 
}

factorial $1

exit $?