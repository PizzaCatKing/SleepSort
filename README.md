# SleepSort.c

Sort an array of unsigned integers using an atomic counter and sleep to insert elements into an array. Each value is processed on it's own thread so that the sleep operations won't interfere with eachother.
The amount of time you sleep for is the value of the element multiplied by some constant. The higher the constant the more stable the sort is, at the cost of speed in real time.

## How to compile
`gcc -pthread -Wall sleepsort.c -o sleepsort`

## How to run
`./sleepsort`

Currently values are hardcoded

## This doesn't work
At larger length arrays the sort becomes unstable as the time to process the code exceeds the time between sleeps.
The resulting values will not be in the correct order.

To "fix" this you can:
- Add a larger constant
- Get a faster CPU
- Get a better sorting algorithm

## Motivation
I was told by a colleague that an interviewee provided this as the answer when asked to implement a sotring algorithm during an interview. I though it would be funny to implement. It was.
