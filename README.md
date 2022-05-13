This repository solves sudoku puzzles.


Clone the repo using the following command

```
git clone --recursive https://github.com/gurukamath/sudoku.git
```

Build the project

```
cd sudoku
cmake -S . -B build
cmake --build build
```

Type in the sudoku that you want to solve in the `example.txt` file. Separate the different rows on different lines.
Although you do not need to seperate the digits using commas, using commas makes it easier to read.

To solve the sudoku
```
./build/sudoku --file=example.txt
```

Although the algorithm solves most of the sudokus out there, a solution is not gaurenteed. In some extremely rare cases, the algorithm might halt at a certain stage since it does not know how to proceed.

There are some pre-built examples of varying levels of difficulty in more_examples.