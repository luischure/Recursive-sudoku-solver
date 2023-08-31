/**
 * @file SudokuSolver.cpp
 * @author Luis Chure Ortiz 
 * @brief 
 * @version 0.1
 * @date 2023-04-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SudokuSolver.hpp"
#define M 9
#define N 9

//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::

 
//Add your public members here
 /**
  * @brief  the default constructor initializes an emtpy board, that is, a board filled with zeros (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable.
  * 
  */
 SudokuSolver::SudokuSolver(){
        // Initialize an empty board
        puzzleNumbers_ = new int*[9];
        for (int i = 0; i < 9; i++) {
            puzzleNumbers_[i] = new int[9];
            for (int j = 0; j < 9; j++) {
                puzzleNumbers_[i][j] = 0;
            }
        }
        is_solvable = false; // the board is unsolvable by default
 }

 /**
  * @brief  the parameterized constructor reads the input file to initialize the board. The input files consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board.
  *  Empty squares contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not
  * 
  */
 SudokuSolver::SudokuSolver(std::string input_file){
    std::ifstream inputF;
    inputF.open(input_file);
    
    puzzleNumbers_ = new int *[9];
    int index = 0;
    while(inputF.good()){
        std::string rows;
        while(getline(inputF, rows)){
            std::string columns;
            std::stringstream ss(rows);
            
            puzzleNumbers_[index] = new int [9];
            for(int j = 0; j < 8; j++){
                std::getline(ss, columns, ',');
                puzzleNumbers_[index][j] = stoi(columns);
            }
            std::getline(ss, columns);
            puzzleNumbers_[index][8] = stoi(columns);
            index++;
        }
    }
    
    if(solve()){
        setSolvable();
    }
    else{
        is_solvable = false; 
    }
     
 }

 bool SudokuSolver::solve(){
    /**
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (puzzleNumbers_[i][j] != 0) {
                if (!checkLegalValue(puzzleNumbers_[i][j], )) {
                    return false;
                }
            }
        }
    }
    */

    Sudoku::Location loc = returnNextEmpty();
    if (loc.row == -1 && loc.col == -1) {
        //setSolvable(); 
        return true;
        // Puzzle is solved 
}

         
    for (int i = 1; i <= 9; i++) {
        // Check if the number is legal in this position
        if (checkLegalValue(i, loc)) {
            // If it's legal, set the number and continue recursively
            puzzleNumbers_[loc.row][loc.col] = i;
            if (solve()) {
                //setSolvable();
                return true; // Puzzle is solved
               
            }
            // If the recursion didn't solve the puzzle, backtrack and try the next number
            //puzzleNumbers_[loc.row][loc.col] = 0;        
        }
    //    else{
        // puzzleNumbers_[loc.row][loc.col] = 0;
        // }
    }
    // If no number worked, the puzzle is unsolvable
   // is_solvable = false; 
    puzzleNumbers_[loc.row][loc.col] = 0;   
    return false;
 }


  /**
   * @brief returns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when solving the problem at construction, rather than solving the puzzle again each time this function is called.
   * 
   */
bool SudokuSolver::isPuzzleSolvable() {
    return is_solvable;
}

  /**
   * @brief records the puzzle as being solvable.
   * 
   * @return true 
   * @return false 
   */
void SudokuSolver::setSolvable(){
    is_solvable = true; 
}

  /**
   * @brief returns the  2D pointer array representing the puzzle
   * 
   */
int** SudokuSolver::getPuzzleNumbers() {
    return puzzleNumbers_;
}

  /**
   * @brief sets the  2D pointer array representing the puzzle to the value of the parameter
   * 
   * @param puzzle 
   */
void SudokuSolver::setPuzzleNumbers(int** puzzle){
    puzzleNumbers_ = puzzle;
}


  /**
   * @brief returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is
   * an empty square in the sudoku board. To find the first empty square you must read the 2D array from top-left (0,0) to
   *  bottom right (8,8), one row at a time. Set the row and col of the Location to the indices at which the first 0 is found in the 2D array. 
   * If there are no empty squares the Location object should have row and col values of -1.
   * @return Location 
   */
Sudoku::Location SudokuSolver::returnNextEmpty() const{
    Sudoku::Location loc; 
    loc.row = -1;
    loc.col = -1;
    for(int i = 0; i < M; i++){
        for ( int j = 0; j < N; j++){
            if (puzzleNumbers_[i][j] == 0 ){
                loc.row = i;
                loc.col = j;
                return loc; 
            }
        }
    }
    return loc;
}


/**
 * @brief returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location in the 2D array 
 * without breaking the rules of sudoku. It returns false if placing value at location is not a legal move. Remember, in order to be a 
 * valid move, the value must be unique with a row, column, and sub-grid.
 * @param value 
 * @param location 
 */
bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location){
    for( int i = 0; i < M; i++){//checks every row if the the parameter value is already in one of the rows at location.row
        if(puzzleNumbers_[location.row][i] == value) {
            return false;
        }
    }
    for( int j = 0; j < N; j++){//checks every column to see if the parameter value exist in any of the columns at the location.col
        if(puzzleNumbers_[j][location.col] == value){
            return false; 
        }
    }
    int startRow = floor(location.row / 3) * 3;// checks if the value in the parameter exist anywhere within the 3x3 box
    int startCol = floor(location.col / 3) * 3; 
    for( int i = startRow; i < startRow + 3; i++){
        for ( int j = startCol; j < startCol + 3; j++ ){
            if( puzzleNumbers_[i][j] == value){
                return false; 
            }
        }
    }
    return true;
}


/**
 * @brief will display the board 
 * 
 */
void SudokuSolver::display(){
    for( int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            if( j == 3 || j == 6){
                std::cout << " | "; 
                show_x(puzzleNumbers_[i][j]);
                std::cout << " ";
            }
            else if(j == 8){
                if( i == 2 || i == 5){
                    show_x(puzzleNumbers_[i][j]);
                    std::cout<<std::endl << "- - - - - - - - - - - -";
                }
                else{
                    show_x(puzzleNumbers_[i][j]);
                }
            }
            else{
                show_x(puzzleNumbers_[i][j]);
                std::cout << " ";
            }
        }
        std::cout << std::endl; 
    }
}

void SudokuSolver::show_x(int num){
    if(num == 0){
        std::cout << "X";
    }
    else{
        std::cout << num; 
    }
}




