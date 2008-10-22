#include <fstream>
#include <string>
#include <sstream>

#include "utilities.h"
#include "scacchiera.h"

using namespace std;

template <class T>
string NumToString(T num)
{
    ostringstream myStream;
    myStream << num << flush;
    return(myStream.str());    
}

string IntToString(int num)
{
    ostringstream myStream;
    myStream << num << flush;
    return(myStream.str());
}

string DoubleToString(double num)
{
    ostringstream myStream;
    myStream << num << flush;
    return(myStream.str());
}

bool checkfile(const char* file)
{
    bool temp;
    ifstream f;
    f.open(file);
    temp = f.good();
    f.close();
    return temp;
}

bool controllafile(const char* file)
{
    char h;
    int g = 0;
    ifstream f;
    f.open(file);
    while(!f.eof())
    {
	f >> noskipws >> h;
	if (h!='0' and h!='1' and h!='2' and h!='3' and h!='4' and h!='5' and h!='6' and h!='7' and h!='8' and h!='9' and h!=' ' and h!='.' and h!='\n')
	{f.close(); return false;}
	if (g++>X*Y) {f.close(); return false;}
	if (h=='\n') 
	{
	    if (g!=X*Y+1 and g!=1) {f.close(); return false;}
	    g = 0;	
	}
    }
    f.close();
    return true;
}

char* sudoku_n(const char* file, int n)
{
    ifstream f;
    f.open(file);
    int length = X*Y;
    char *buffer = new char[length];
    char invio;
    for (int i=0;i<=n;++i)
    {
	f.read(buffer,length);
	f.read(&invio,1);
    }
    f.close();
    return buffer;
}

int contasudoku(const char* file)
{
    ifstream f;
    char h;
    int temp = 0;
    f.open(file);
    while (!f.eof())
    {
	f >> noskipws >> h;
	if (h == '\n') temp++;	
    }
    if (h=='\n') temp-=2;
    f.close();
    return temp+1;
}

bool controllasudoku(char sudo[])
{
    Scacchiera s(sudo);
    return s.corretto();
}
