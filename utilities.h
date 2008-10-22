#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

template <typename T>
std::string NumToString(T num);
std::string IntToString(int num);
std::string DoubleToString(double num);
bool checkfile(const char* file);
bool controllafile(const char* file);
char* sudoku_n(const char* file, int n);
int contasudoku(const char* file);
bool controllasudoku(char sudo[]);

#endif
