# Conway's Game of Life

The game of Life, invented by Professor John Conway.

## Description

The game consists of a board of varying size, where each cell can be either alive or dead at any generation.
Then the next generation is calculated according to the three following rules:
  1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
  2. Any live cell with two or three live neighbours lives on to the next generation.
  3. Any live cell with more than three live neighbours dies, as if by overcrowding.
  4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

where a neighbour is any cell that is horizontally, vertically or diagonally adjacent.

The live cells are represented by digits from '0' to '9' indicating the number of generations that the cell has survived since it was created, an age greater than '9' is indicated by an 'X'. Cells are assigned an age of '0' upon creation.

The program takes four arguments on the command line. The file name, width, height and generations. The maximum width is 78 and maximum height is 50. The first line of the file provides the initial live cells, then the row and column positions of each live cell is provided on a separate line.

## Getting Started

### Dependencies

* Linux OS

### Compiling

* Open the terminal.
* Go to the folder containing the program.
* Run the following command to compile the program.
```
gcc -ansi -Wall gameOfLife.c -o gameOfLife
```

### Executing the Program

* Use the example files to test the program.
* Run the following command to run the program.
```
./gameOfLife <file-name> <width> <height> <generations>
```

### Example Files

* beehive
```
./gameOfLife beehive 6 6 6
```
* block
```
./gameOfLife block 6 6 6
```
* glider
```
./gameOfLife glider 6 6 6
```
* methusalah
```
./gameOfLife methusalah 35 35 6
```
* traffic
```
./gameOfLife traffic 6 6 6
```

## Author

Suraj Rohira

Contact: suraj.rohira0@gmail.com
