#!/bin/sh

echo "| Number of Messages | Search Time      | Memory Use       |"
echo "|--------------------|------------------|------------------|"


echo -n "| 10                 | " 
./createMessages 72000 10 > input
./LogTest search < input | tail -n 1 
echo -n "| 100                | " 
./createMessages 72000 100 > input
./LogTest search < input | tail -n 1
echo -n "| 1000               | " 
./createMessages 72000 1000 > input
./LogTest search < input | tail -n 1 
echo -n "| 10000              | " 
./createMessages 72000 10000 > input
./LogTest search < input | tail -n 1 
echo -n "| 100000             | " 
./createMessages 72000 100000 > input
./LogTest search < input | tail -n 1 
echo -n "| 1000000            | " 
./createMessages 72000 1000000 > input
./LogTest search < input | tail -n 1 
rm input
