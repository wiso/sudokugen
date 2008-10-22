/***************************************************************************
 *   Copyright (C) 2006 by ruggero                                         *
 *   giurrero@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/**
 * \author Rugggero Turra
 */

#include <iostream>
#include <cstdlib>

#include "scacchiera.h"
#include "benchmark.h"
#include "test.h"
#include "genera.h"
#include "interactive.h"
#include "sudokufile.h"

using namespace::std;

/*versione ver1.ver2.ver*/
const int ver1 = 0;
const int ver2 = 0;
const int ver3 = 18;

void usage();

/**
 * Programma principale
 */
int main(int argc, char **argv)
{
    inittestsudoku();
    
    if (argc>1)
    {
	string *argvstring = new string[argc];
//	string argvstring[argc];
	for (int i=0;i<argc;i++) {argvstring[i] = argv[i];}
	if (argvstring[1]=="-r")
	{
	    if (argc==2) dotest();
	    if (argc==3) dotest(argv[2]);	
	    if (argc>3)  { usage(); return 1; }
	}
	if (argvstring[1]=="-c")
	{
	    if (argc==2) 		
		for (int i=0;i<5;i++)
		{
		    char *stringa;
		    stringa = genera_difficult(5,300);
		    cout << stringa << '\n';
		    delete[] stringa;
		}
	    if (argc==5)
		for (int i=0;i<atoi(argvstring[2].c_str());i++)
		{
		    char *stringa;
		    stringa = genera_difficult(atoi(argvstring[3].c_str()),atoi(argvstring[4].c_str()));
		    cout << stringa << '\n';
		    delete[] stringa;
		}
	    if (argc==3 or argc==4 or argc>5) {usage(); return 1;}
	}
	if (argvstring[1]=="-e")
	{
	    if (argc==2)
		value_file(cout,"data/default");
	    if (argc==3)
		value_file(cout,(argv[2]));
	}
	if (argvstring[1]=="-v")
	    cout << "Sudoku " << ver1 << '.' << ver2 << '.' << ver3 << std::endl;
	if (argvstring[1]=="-h")
	    usage();	if (argvstring[1]=="-i")
	    runinteractive();
	if (argvstring[1]=="-s")
	{
	    int a;
	    risolviquesto(argv[2],a);
	}
	if (argvstring[1]=="-xxx")
	{

/* benchmark */
//    dobench(cout,1);
    
/* run */

//    doone_logica(cout); //ne risolve uno solo con la logica
//    doone(cout);        //ne risolve uno 

/*prova*/
	    prova(cout);
    
/*    char *stringa;  //genera sudoku piu' difficili di 10
    stringa = genera_difficult(10);
    cout << stringa << '\n';
    value_this(cout, stringa);*/
	}
	delete[] argvstring;
    }
    else cout << "Try sudoku -h" << endl;
    return 0;    
}

/* b
- 3 - | 2 7 - | - 1 - |
7 1 - | - 8 - | 3 - 2 |
2 5 6 | - - - | 4 7 8 |
_______________________
- - - | - - 1 | - - 3 |
3 8 - | - 4 - | - 6 - | <== 7 a sx del 4
9 - - | 5 3 - | - 2 4 |
_______________________
6 4 3 | - - - | 2 8 7 |
1 - - | - 6 - | 5 4 9 |
- 9 - | 4 - 7 | - 3 - |
_______________________
perche' in posizione (4,5) e (5,6) possono starci solo il 2 e il 9
21:11:02
  si

  Alina
  quindi in tutte le altre celle del 5 riquadro non possono esserci quei due numeri

quindi in tutte le altre celle del 5 riquadro non possono esserci quei due numeri
21:11:55
  Alina
  in posizione (5,4) potevano starci solo il 9 e il 7
21:12:00
  Alina
  ==> solo il 7!
*/

void usage()
{
    cout << "\nUsage: sudoku [options]";
    cout << "\nOptions: ";
    cout << "\n          -c           Create sudokus";
    cout << "\n          -c n a b     Create n sudokus with difficult from a (>0) and b";
    cout << "\n          -e           Evalue difficult of default file";
    cout << "\n          -e file      Evalue difficult of file";
    cout << "\n          -h           Display this help";
    cout << "\n          -i           Interactive mode";
    cout << "\n          -r           Solve the default sudokus";
    cout << "\n          -r file      Solve the sudokus in file";
    cout << "\n          -s sudoku    Solve the sudoku";
    cout << "\n                       sudoku must be in string format";
    cout << "\n                       0 for blank cells";
    cout << "\n          -v           Display version number";
    cout << "\nExamples:";
    cout << "\n          sudoku -c 3 10 300";
    cout << "\n          sudoku -r data/xwing";
    cout << endl;
    return;
}
