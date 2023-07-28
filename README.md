# Crossing Cars Organizer
A Qt program using semaphores coordinates cars crossing a single-lane road in opposite directions. The solution supports any number of cars/threads, randomly assigned to each side of the crossing. Each car waits for a random time before attempting to cross.


## Prerequisites
- Qt 6 library 
  
## How to Run

1. Clone this repository:
```
git clone <repo-link>
```
2. Run the project:
```
qmake6 carsCrossing.pro
make
./carsCrossing <numOfThreads>
```
