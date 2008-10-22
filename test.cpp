#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "utilities.h"
#include "test.h"
#include "costanti.h"
#include "solver.h"


using namespace std;

void presentazione()
{
    cout << "********************\nQuesto programma e' ancora in fase di sviluppo. Per fare questo c'e' bisogno di molti test di funzionamento per trovare i bug.\n\n";
    cout << "Per inserire un nuovo sudoku edita il file test.txt. Aggiungi il nuovo sudoku sotto quelli gia' inseriti. Il formato e' molto semplice: i sudoku vanno scritti in linea, un numero dopo l'altro, partendo da in alto a sinistra, riga per riga. Negli spazi vuoti inserire uno 0, in alternativa uno spazio o un punto.\n\n";
    cout << "MOLTO IMPORTANTE: ogni sudoku va separato dai precedenti con un invio. Dopo l'ultimo sudoku non va inserito nessun invio.\n\n";
    cout << "Il programma provera' a risolvere il sudoku senza usare strategie iterative, non e' detto che ci riesca.\n\n";
    cout << "Premi ENTER per iniziare" << flush;
    cin.get();
}

void creafile()
{
    ofstream f;
    f.open(NOME_FILE);
    f << SUDOKU_DEFAULT;
    f.close();
}

bool risolviquesto(char sudo[], int &n_finiti)
{
    Solver s(sudo);
    cout << s;
    s.risolvilogica();
    cout << s;    
    if (s.finito()) { cout << "finito\n"; ++n_finiti; }
    else cout << "non finito\n";
    if (s.corretto()) cout << "corretto\n";
    else 
	{
	    ofstream fbug;
	    fbug.open(NOME_FILEBUG, ofstream::out | ofstream::app);
	    fbug.write(sudo,X*Y);
	    fbug << '\n';
	    fbug.close();
	    cout << "***********NON CORRETTO***********\n";
	    cout << "*                                *\n";
	    cout << "*     per favore manda il file   *\n";
	    cout << "*   sudokubug.txt all'indirizzo  *\n";
	    cout << "*       <giurrero@gmail.com>     *\n";
	    cout << "*                                *\n";
	    cout << "**********************************\n";
	    return false;
	}
    return true;
}

void dotest(const char* filename)
{    
    if (!checkfile(filename))
    {
	cout << "File non trovato\n";
	return;
    }
    if (!controllafile(filename))
    {
	cout << "File non correttamente formattato\n";
	return;
    }
    int n_sudoku = contasudoku(filename);
    int n_errori = 0;
    int n_finiti = 0;
    cout << "Trovati " << n_sudoku << " sudoku\n";

    string messaggio;    
    if (n_sudoku>=10 and n_sudoku<20)
	messaggio += "* I sudoku aggiunti sono un po', spediscili a <giurrero@gmail.com>\n";
    if (n_sudoku>=20)
    {
	messaggio += "**********************************\n";
	messaggio += "*                                *\n";
	messaggio += "*     i sudoku inseriti sono     *\n";
	messaggio += "*      tantissimi, manda il      *\n";
	messaggio += "*  file test.txt all'indirizzo   *\n";
	messaggio += "*       <giurrero@gmail.com>     *\n";
	messaggio += "*                                *\n";
	messaggio += "**********************************\n";
    }
    cout << "Inizio a risolvere\n";
    char *c;
    bool errore = false;
    bool erroreutente = false;
    for (int i=0;i<n_sudoku;++i)
    {
	c = sudoku_n(filename,i);
	cout << "Sudoku numero " << i << ":\n" << flush;
	if (!controllasudoku(c))
	{
	    cout << "Il sudoku numero " << i << " e' incorretto\n";
	    messaggio += "* Il sudoku numero " + IntToString(i) + " e' incorretto, non e' stato risolto, controllare il file " + (string)(filename) +'\n';
	    erroreutente = true;
	}
	else
	    if (!risolviquesto(c,n_finiti)) { errore = true; ++n_errori; }
	delete[] c;
    }
    if (errore)
    {
	messaggio += "**************ERRORE**************\n";
	messaggio += "*                                *\n";
	messaggio += "*     per favore manda il file   *\n";
	messaggio += "*   sudokubug.txt all'indirizzo  *\n";
	messaggio += "*       <giurrero@gmail.com>     *\n";
	messaggio += "*                                *\n";
	messaggio += "**********************************\n";
    }
    else 
    {
	messaggio += "* Nessun errore rilevato\n";
	messaggio += "* Completati " + IntToString(n_finiti) +
	    " su " + IntToString(n_sudoku) + " (" +
	    DoubleToString( (double)n_finiti / (double)n_sudoku*100 ) + " %)\n";
    }
    cout << "\n**********   MESSAGGI   **********\n";
    cout << messaggio << endl;
}

void dotest()
{
    string messaggio;
    presentazione();
    
    if (!checkfile(NOME_FILE))
    {
	cout << "Il file " << NOME_FILE << " non esiste. Lo creo\n";
	messaggio += "* Il file " + (string)NOME_FILE + " non esisteva, l'ho creato\n";
	creafile();
    }
    dotest(NOME_FILE);
    cout << messaggio;
}


