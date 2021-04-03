#!/bin/bash

if [[ $1 == "re" ]]; then
	echo "Re-Building project" && cd build/ &&  make re
	if [[ $2 == "run" ]]; then
		echo "Running arcade" && cd ../ && ./arcade
	fi
else
	echo "Building project" && cd build/ &&  make
	if [[ $1 == "run" ]]; then
		echo "Running arcade" && cd ../ && ./arcade
	fi
fi