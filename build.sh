#!/bin/bash
gcc src/*.c -lcurl -o parser
if [ $? -ne 0 ]; then
	echo "compiling error"
fi
