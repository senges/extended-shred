#!/bin/bash

echo "[+] Clearing tests"
rm -rf toto*;

echo "[+] Generating tests"

for i in {1..5}; do

	echo "Creating directory ./toto$i";
	mkdir "toto$i";

	for j in {1..10}; do
		echo "Adding file ./toto$i/tata$j";
		touch "toto$i/tata$j";
	done;

	echo "";
done;

echo "[+] All tests successfully generated"
echo "[+] Directory verbose"

if ! [ -x "$(command -v tree)" ]; then
	echo "[-] `tree' command not installed, using `ls' instead"
	ls -R;
else
	tree;
fi

echo ""
echo "[+] Executing compilation routine"

make clean;
make;

echo ""
echo "[+] Tests ready to execute"

read -p "Ready to run (y/n) ?" choice
case "$choice" in 
  y|Y )	echo "[+] Ok, go"		;;
  n|N )	echo "[-] Exiting"; exit	;;
  * )	echo "[-] Invalid"; exit	;;
esac

echo ""
echo "[+] Shreding all directories"
./main -r -zuvf toto*

echo ""
echo "[+] Done, plese check manually"
