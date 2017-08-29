#!/bin/sh

echo "| Number of Messages | Insert Time      | Memory Use       |"
echo "|--------------------|------------------|----------------- |"


echo -n "| 10                 | " 
./createMessages 72000 10 > input
./measure ./LogTest < input | tail -n 0
echo -n "| 100                | " 
./createMessages 72000 100 > input
./measure ./LogTest < input | tail -n 0
echo -n "| 1000               | " 
./createMessages 72000 1000 > input
./measure ./LogTest < input | tail -n 0
echo -n "| 10000              | " 
./createMessages 72000 10000 > input
./measure ./LogTest < input | tail -n 0
echo -n "| 100000             | " 
./createMessages 72000 100000 > input
./measure ./LogTest < input | tail -n 0
echo -n "| 1000000            | " 
./createMessages 72000 1000000 > input
./measure ./LogTest < input | tail -n 0

rm input
