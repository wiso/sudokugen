#include "sudokufile.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, SudokuData& sudokudata)
{
    os << sudokudata.sudoku << sudokudata.difficolta;
    return os;
}

SudokuFile::SudokuFile(char* name)
    :f_name(name)
{
    f.open(name,fstream::in | fstream::out | fstream::app);
}

SudokuFile::~SudokuFile()
{
    f.close();
}

void SudokuFile::appendsudoku(Scacchiera scacchiera)
{
//    f.seekp(0,ios_base::end);
//    f.write(scacchiera.stringa(),X*Y);
    f << "i";
    std::cout << scacchiera.stringa();
    f << flush;
}

char* SudokuFile::pop()
{
    f.seekg(-X*Y,ios_base::end);
    char* stringa = new char[X*Y];
    f.read(stringa,X*Y);
    return stringa;
}
