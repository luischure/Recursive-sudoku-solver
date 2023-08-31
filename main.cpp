#include "SudokuSolver.hpp"


int main(){
    //SudokuSolver default_solver;

    //default_solver.display();
    SudokuSolver param_solver("puzzle1.csv");
   // param_solver.display();
/**
    Sudoku::Location loc;
    loc.row = 4;
    loc.col = 3;


    if (param_solver.checkLegalValue(4, loc) == true){
        std::cout << "true"; 
    }
    else{
        std::cout << "false"; 
    }
*/

    //param_solver.solve(); 
    if(param_solver.isPuzzleSolvable() == true){
        std::cout << "is solvable"<<std::endl;
    }
    else{
        std::cout << "not solvable"<<std::endl;
    }

    param_solver.display();

    std::cout<< "\n";

    SudokuSolver paramn_solver2("puzzle2.csv");

    if(paramn_solver2.isPuzzleSolvable()== true){
       std::cout << "is solvable"<<std::endl;
    }
    else{
        std::cout << "not solvable"<<std::endl;
    }

    paramn_solver2.display();

    

}
