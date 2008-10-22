#include "interactive.h"
#include "solver.h"
#include "genera.h"
#include <iostream>

using namespace std;

const int DIFFICOLTA = 10;
int difficolta = DIFFICOLTA;

char menu()
{
    cout << "\n**   Menu   **";
    cout << "\n1. Inizia partita";
    cout << "\n2. Setta difficolta";
    cout << "\n0. Esci";
    cout << endl;
    char c;
    cin >> c;
    return c;
}

char askdifficolta()
{
    int c;
    cout << "\nDifficolta (1-300): ";
    cin >> c;
    return c;
}

void pulisci (const int n=30)
{
    for (int i=0;i<n;++i) cout << '\n';
}

void run()
{
    int min = static_cast<int> (difficolta * 0.8);
    int max = static_cast<int> (difficolta * 1.2);
    if ((max-min)<24) {min = difficolta-12; max = difficolta+12;}
    if (min<3) min=3;
    cout << "\nCreo sudoku (" << min << ',' << max << ")...." << endl;
    char *sudoku_char = genera_difficult(min,max);
    Solver s(sudoku_char);
    Solver sudoku_finito(sudoku_char);
    sudoku_finito.risolvi();
    
    int n=-1;
    while (n!=0)
    {
	cout << s << flush;
	cout << "\nPosizione (x y): " << flush;
	int x,y;
	cin >> x >> y;
	cout << "Numero: " << flush;	
	cin >> n;
	if (n==0) break;
	if (sudoku_finito.valore(x,y)==n)
	    s.valore(x,y,n);
	if (s.finito()) { cout << "Completato"; break; }
	pulisci();
    }
}

void runinteractive()
{
    char a = 'a';
    do
    {
	a = menu();
	switch (a)
	{
	    case '1': run();
		break;
	    case '2': difficolta = askdifficolta();
		break;
	    default:;
	};
    }while (a!='0');
}
