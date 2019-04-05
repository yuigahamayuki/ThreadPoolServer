#!/bin/bash
# This script test average process time of three servers:
# 1. thread pool server using deque;
# 2. thread pool server using array;
# 3. stop and wait server.
# Everytime there are 2500 connections, and loop for 100 times

./threadPoolSimpleServer &

declare -i totalTime
declare -i processTime
totalTime=0
for (( i=1; i<=100; i=i+1 ))
do
	processTime=$(./client 192.168.1.3 8888 5 500)
	totalTime=totalTime+processTime
done
# first job number == [1]+ Running  ./threadPoolSimpleServer &
# then remove the unnecessary strings, job number becomes 1
jobNo=$(jobs | grep Simple)
jobNo=${jobNo%%]*}
jobNo=${jobNo#[}
# kill %1, kill the background server
kill %$jobNo

echo "average time of thread pool server using deque:"
totalTime=totalTime/100
echo $totalTime

./threadPoolArrayServer &
totalTime=0
for (( i=1; i<=100; i=i+1 ))
do
	processTime=$(./client 192.168.1.3 8888 5 500)
	totalTime=totalTime+processTime
done

jobNo=$(jobs | grep Array)
jobNo=${jobNo%%]*}
jobNo=${jobNo#[}

kill %$jobNo

echo "average time of thread pool server using array:"
totalTime=totalTime/100
echo $totalTime

./stopWaitServer &
totalTime=0
for (( i=1; i<=100; i=i+1 ))
do
	processTime=$(./client 192.168.1.3 8888 5 500)
	totalTime=totalTime+processTime
done

jobNo=$(jobs | grep Wait)
jobNo=${jobNo%%]*}
jobNo=${jobNo#[}

kill %$jobNo

echo "average time of stop and wait server:"
totalTime=totalTime/100
echo $totalTime
