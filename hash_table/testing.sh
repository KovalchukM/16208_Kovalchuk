#!/bin/bash
if [ $# = 0 ]
then
echo " dummy give file pls "
exit 0
fi

if [ ! -f $1 ]
then
echo " dummy give file pls "
exit 0
fi
rm tests.out
g++ -g $1 -o tests.out -std=c++11 -lgtest -lpthread -fprofile-arcs -ftest-coverage
valgrind --leak-check=full --show-leak-kinds=all ./tests.out
gcovr --html -r . -o coverage.html -d
exit 0
