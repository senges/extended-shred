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
echo "[+] Removing toto1"

./main -r -zuvf toto1

test -e toto1
TEST_1=$?

test -e toto2
TEST_2=$?

./main -zuvf toto2/tata1

test -e toto2/tata1
TEST_3=$?

test -e toto2/tata2
TEST_4=$?

./main -r -zuvf toto*

test -e toto3
TEST_5=$?

if [ $TEST_1 -eq 1 ] && [ $TEST_2 -eq 0 ] && [ $TEST_3 -eq 1 ] && [ $TEST_4 -eq 0 ] && [ $TEST_5 -eq 1 ]
then
	echo "[+] Test coverage : 100%"
else
	echo "[-] Test coverage incomplete"
fi
