# SleepSort.c

Sort an array of unsigned integers using an atomic counter and sleep to insert elements into an array.
The amount of time you sleep for is the value of the element multiplied by some constant. The higher the constant the more stable the sort it, at the cost of speed in real time.

## How to compile
`gcc -g -pthread -Wall sleepsort.c -o sleepsort`

## How to run
`./sleepsort`

Currently values are hardcoded


