#ifndef SUDOKUDATA_H
#define SUDOKUDATA_H

#include "costanti.h"
#include "scacchiera.h"
#include "strategiadata.h"
#include <ostream>
#include <string>
#include <fstream>

using namespace std;
using namespace geometria;

struct SudokuData
{
    char sudoku[X*Y];
    int difficolta;
    StrategiaData strategia;
};

std::ostream& operator<<(std::ostream& os, SudokuData& sudokudata);

class SudokuFile
{
 private:
    string f_name;
    fstream f;
 public:
    SudokuFile (char* name);
    ~SudokuFile();
    int n();
    //write
    void appendsudoku(Scacchiera scacchiera);
    void appendsudoku(SudokuData sudokudata);
    void appendsudoku(Scacchiera scacchiera, int difficolta);
    void appendsudoku(char data[X*Y]);
    void appendsudoku(char data[X*Y], int difficolta);
    //read
    char* read(int n);
    char* pop();
    //find
    char* finddifficult(int n);
    char* findstrategy(int strategy);
    char* findstrategy(int strategy, int n);
    //check
    void deletepairs();
    //order
    void orderdifficult(const bool decrease=true);
};

#endif //SUDOKUDATA_H
