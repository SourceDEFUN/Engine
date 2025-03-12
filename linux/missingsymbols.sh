#!/bin/bash

inputModule=$1
dependencies=$2
objectFilesDir=$3

if [ "$inputModule" == "" -o "$dependencies" == "" -o "$objectFilesDir" == "" ]; then
	echo "Usage: missingsymbols.sh [module to search] [dependencies] [object files dir]"
	echo "ex: missingsymbols server_tf_i486.so \"tier0_i486.so vstdlib_i486.so\" ~/linux/src/engine/obj"
	exit
fi

missingSymbols=`nm -o $inputModule | grep -i " U " | grep -o '[^[:space:]]*$' | grep -v '@@'`

for missingSymbol in $missingSymbols; do
	modulesContaining=`nm -o $dependencies | grep $missingSymbol`
	if [ "$modulesContaining" == "" ]; then
		echo `c++filt "$missingSymbol"` "($missingSymbol)"
	fi
done

