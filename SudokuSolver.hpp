#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack> 
#include <cmath> 


//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{ 
  struct Location
  {
    int row = 0;
    int col = 0;
  };
}

class SudokuSolver
{
public:
 
//Add your public members here
 /**
  * @brief  the default constructor initializes an emtpy board, that is, a board filled with zeros (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable.
  * 
  */
 SudokuSolver();

 /**
  * @brief  the parameterized constructor reads the input file to initialize the board. The input files consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board.
  *  Empty squares contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not
  * 
  */
 SudokuSolver(std::string input_file);

  /**
   * @brief Creturns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when solving the problem at construction, rather than solving the puzzle again each time this function is called.
   * 
   */
bool isPuzzleSolvable() ;

  /**
   * @brief records the puzzle as being solvable.
   * 
   * @return true 
   * @return false 
   */
void setSolvable();

  /**
   * @brief returns the  2D pointer array representing the puzzle
   * 
   */
int** getPuzzleNumbers() ;

  /**
   * @brief sets the  2D pointer array representing the puzzle to the value of the parameter
   * 
   * @param puzzle 
   */
void setPuzzleNumbers(int** puzzle);


  /**
   * @brief returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is
   * an empty square in the sudoku board. To find the first empty square you must read the 2D array from top-left (0,0) to
   *  bottom right (8,8), one row at a time. Set the row and col of the Location to the indices at which the first 0 is found in the 2D array. 
   * If there are no empty squares the Location object should have row and col values of -1.
   * @return Location 
   */
Sudoku::Location returnNextEmpty() const ;


/**
 * @brief eturns true if the value parameter (which can take on values 1-9) can legally be placed at the given location in the 2D array 
 * without breaking the rules of sudoku. It returns false if placing value at location is not a legal move. Remember, in order to be a 
 * valid move, the value must be unique with a row, column, and sub-grid.
 * @param value 
 * @param location 
 */
bool checkLegalValue(int value, Sudoku::Location location);


/**
 * @brief will display the board 
 * 
 */
void display();

//helper function that solves the puzzle if there is a solution.
bool solve();   


private:
//puzzle numbers private variable 
int** puzzleNumbers_;
//boolean variable that stores whether the puzzle is solvable or not
bool is_solvable;
//helper function that solves the puzzle if there is a solution.  
//bool solve();

void show_x(int num); // this will convert all the zeros from the grid into X







};

#endif
