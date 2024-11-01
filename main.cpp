#include "src/sudoku.h"

int main(){

    sudoku s;
    s.inputBoard();
    s.printBoard();
    std::cout << std::endl;  
    if(s.solveWithBT(0,0))s.printBoard();
}