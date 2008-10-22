#include "benchmark.h"
#include "scacchiera.h"
#include "genera.h"
#include "utilities.h"
#include "solver.h"
#include "sudokufile.h"
#include "pos.h"
#include "latex.h"
#include "strategiadata.h"

#include <ostream>
#include <ctime>



int sudoku_a[X][Y], sudoku_b[X][Y], sudoku_c[X][Y], sudoku_d[X][Y], sudoku_f[X][Y];


char sudoku_e[] = "000200000030000040650980012000000203005179800409000000280096035010000070000003000";
char sudoku_g[] = "970304065020506080000000000005802900002040300008705100000000000060208030840109027"; //easiest
char sudoku_h[] = "098500200100000004050000030002643100000908000007152600070000080200000007006001520"; //gentle
char sudoku_j[] = "302070504000000000006254000090000600008965100005000020000197800000000000507080206"; //moderate
char sudoku_k[] = "005401600000060000094007020370020040000010000010040056050800260000090000002306900"; //tought
char sudoku_i[] = "001003800040000060700906501600500002000000000800007009306108004090000080008700200"; //diabolical
char sudoku_l[] = "043980250600425000200001094900004070300608000410209003820500000000040005534890710";// xwing
char sudoku_m[] = "070009004000060081000500000080000340632080975045000020000003000810070000900200060";
//char sudoku_n[] = "...9.4...79.....248..2....1.8.451.3...........7.369.4.2....7..341.....62...5.6..."; //box reduction
char sudoku_o[] = "004500190065100204000000600090041030500007400402695700000058021800206900001700806";//xwing mio

char sudoku_finito[] = "675148329832795614941623857428516973319874562756239148297351486564987231183462795";

void inittestsudoku()
{
    for (int y=0;y<Y;++y)
	for (int x=0;x<X;++x)
	{
	    sudoku_a[x][y] = 0;
	    sudoku_b[x][y] = 0;
	    sudoku_c[x][y] = 0;
	    sudoku_d[x][y] = 0;
	    sudoku_f[x][y] = 0; //tough
	}

    sudoku_a[1][0] = 3;
    sudoku_a[7][0] = 4;
    sudoku_a[0][1] = 2;
    sudoku_a[1][1] = 9;
    sudoku_a[2][1] = 5;
    sudoku_a[4][1] = 1;
    sudoku_a[6][1] = 3;
    sudoku_a[7][1] = 7;
    sudoku_a[8][1] = 8;
    sudoku_a[0][2] = 6;
    sudoku_a[5][2] = 7;
    sudoku_a[8][2] = 9;
    sudoku_a[2][3] = 9;
    sudoku_a[3][3] = 3;
    sudoku_a[0][6] = 8;
    sudoku_a[0][7] = 9;
    sudoku_a[1][7] = 4;
    sudoku_a[2][7] = 2;
    sudoku_a[1][8] = 1;
    sudoku_a[4][4] = 5;
    sudoku_a[5][5] = 4;
    sudoku_a[6][5] = 6;
    sudoku_a[7][4] = 8;
    sudoku_a[3][6] = 2;
    sudoku_a[4][7] = 6;
    sudoku_a[8][6] = 1;
    sudoku_a[6][7] = 7;
    sudoku_a[7][7] = 3;
    sudoku_a[8][7] = 5;
    sudoku_a[7][8] = 9;
    sudoku_a[1][4] = 7;

    sudoku_b[1][0] = 3;
    sudoku_b[3][0] = 2;
    sudoku_b[7][0] = 1;
    sudoku_b[0][1] = 7;
    sudoku_b[4][1] = 8;
    sudoku_b[8][1] = 2;
    sudoku_b[1][2] = 5;
    sudoku_b[2][2] = 6;
    sudoku_b[6][2] = 4;
    sudoku_b[7][2] = 7;
    sudoku_b[5][3] = 1;
    sudoku_b[8][3] = 3;
    sudoku_b[1][4] = 8;
    sudoku_b[4][4] = 4;
    sudoku_b[7][4] = 6;
    sudoku_b[0][5] = 9;
    sudoku_b[3][5] = 5;
    sudoku_b[1][6] = 4;
    sudoku_b[2][6] = 3;
    sudoku_b[6][6] = 2;
    sudoku_b[7][6] = 8;
    sudoku_b[0][7] = 1;
    sudoku_b[4][7] = 6;
    sudoku_b[8][7] = 9;
    sudoku_b[1][8] = 9;
    sudoku_b[5][8] = 7;
    sudoku_b[7][8] = 3;
//    sudoku_b[3][4] = 7;

    sudoku_c[1][0] = 2;
    sudoku_c[2][0] = 8;
    sudoku_c[3][0] = 1;
    sudoku_c[5][0] = 5;
    sudoku_c[6][0] = 3;
    sudoku_c[7][0] = 9;
    sudoku_c[0][1] = 3;
    sudoku_c[1][1] = 9;
    sudoku_c[2][1] = 1;
    sudoku_c[4][1] = 4;
    sudoku_c[6][1] = 6;
    sudoku_c[7][1] = 8;
    sudoku_c[8][1] = 5;
    sudoku_c[4][2] = 9;
    sudoku_c[0][3] = 2;
    sudoku_c[2][3] = 4;
    sudoku_c[6][3] = 9;
    sudoku_c[8][3] = 7;
    sudoku_c[0][4] = 8;
    sudoku_c[1][4] = 5;
    sudoku_c[3][4] = 9;
    sudoku_c[5][4] = 6;
    sudoku_c[7][4] = 4;
    sudoku_c[8][4] = 3;
    sudoku_c[0][5] = 9;
    sudoku_c[2][5] = 6;
    sudoku_c[6][5] = 5;
    sudoku_c[8][5] = 8;
    sudoku_c[4][6] = 8;
    sudoku_c[0][7] = 5;
    sudoku_c[1][7] = 4;
    sudoku_c[2][7] = 2;
    sudoku_c[4][7] = 1;
    sudoku_c[6][7] = 8;
    sudoku_c[7][7] = 3;
    sudoku_c[8][7] = 9;
    sudoku_c[1][8] = 8;
    sudoku_c[2][8] = 9;
    sudoku_c[3][8] = 3;
    sudoku_c[5][8] = 4;
    sudoku_c[6][8] = 7;
    sudoku_c[7][8] = 1;

    sudoku_d[1][0] = 6;
    sudoku_d[7][0] = 3;
    sudoku_d[8][0] = 8;
    sudoku_d[0][1] = 5;
    sudoku_d[2][1] = 1;
    sudoku_d[1][2] = 4;
    sudoku_d[2][2] = 7;
    sudoku_d[3][2] = 1;
    sudoku_d[4][2] = 8;
    sudoku_d[8][2] = 5;
    sudoku_d[5][3] = 7;
    sudoku_d[7][3] = 4;
    sudoku_d[1][4] = 1;
    sudoku_d[3][4] = 3;
    sudoku_d[5][4] = 9;
    sudoku_d[7][4] = 5;
    sudoku_d[1][5] = 7;
    sudoku_d[3][5] = 6;
    sudoku_d[0][6] = 1;
    sudoku_d[4][6] = 3;
    sudoku_d[5][6] = 4;
    sudoku_d[6][6] = 9;
    sudoku_d[7][6] = 6;
    sudoku_d[6][7] = 5;
    sudoku_d[8][7] = 4;
    sudoku_d[0][8] = 4;
    sudoku_d[1][8] = 9;
    sudoku_d[7][8] = 7;

    sudoku_f[2][0] = 5;
    sudoku_f[3][0] = 4;
    sudoku_f[5][0] = 1;
    sudoku_f[6][0] = 6;
    sudoku_f[4][1] = 6;
    sudoku_f[1][2] = 9;
    sudoku_f[2][2] = 4;
    sudoku_f[5][2] = 7;
    sudoku_f[7][2] = 2;
    sudoku_f[0][3] = 3;
    sudoku_f[1][3] = 7;
    sudoku_f[4][3] = 2;
    sudoku_f[7][3] = 4;
    sudoku_f[4][4] = 1;
    sudoku_f[1][5] = 1;
    sudoku_f[4][5] = 4;
    sudoku_f[7][5] = 5;
    sudoku_f[8][5] = 6;
    sudoku_f[1][6] = 5;
    sudoku_f[3][6] = 8;
    sudoku_f[6][6] = 2;
    sudoku_f[7][6] = 6;
    sudoku_f[4][7] = 9;
    sudoku_f[2][8] = 2;
    sudoku_f[3][8] = 3;
    sudoku_f[5][8] = 6;
    sudoku_f[6][8] = 9;
}

void dobench(std::ostream &os, const int RIP)
{
    os << "***BENCHMARK***\n";
    os << "Numero ripetizioni:................";
    os << '[' << RIP << "]\n";
    os << "Creo i puntatori...................";
    Solver* s[RIP];
    os << "[Done]\n";
    os << "Alloco............................." << std::flush;
    int start = time(NULL);
    int startc = clock();
    for (int rip=0;rip<RIP;++rip)
	s[rip] = new Solver(sudoku_e);
    int stop = time(NULL);
    int stopc = clock();
    os << '[' << stop-start << ' ' << stopc-startc << ']' << std::endl;
    os << *s[0];
    os << "Inizio a risolvere................." << std::flush;;
    start = time(NULL);
    startc = clock();
    for (int rip=0;rip<RIP;++rip)    
	s[rip]->risolvi();
    stopc = clock();
    stop = time(NULL);
    os << '[' << stop-start << ' ' << stopc-startc << ']' << std::endl;
    os << *s[0];
}


bool doone(std::ostream &os)
{
    Solver s("000009000004130000000700510100000360070060040065000007031006700000078100000200000");
    os << s;
    s.risolvi();
    os << s;
    if (s.corretto()) os << "corretto\n";
    else os << "######NON CORRETTO#######\n";
    if (s.finito()) os << "finito\n";
    else os << "non finito\n";
    return s.corretto();
}

bool doone_logica(std::ostream &os)
{
    os << "Risolvo solo con la logica\n";
    Solver s(sudoku_o);
    os << s;
    s.risolvilogicadebug();
    os << s;
    if (s.corretto()) os << "corretto\n";
    else os << "######NON CORRETTO#######\n";
    if (s.finito()) os << "finito\n";
    else os << "non finito\n";
    return s.corretto();
}

void value_this(std::ostream &os, const char *stringa)
{
    Solver s(stringa);
    os << "Punteggio: " << s.difficolta() << '\n';
}

void value_file(std::ostream &os, const char* file)
{
    if (!checkfile(file))
    {
        os << "Il file " << file << " non esiste.\n";
	return;
    }
    if (!controllafile(file))
    {
        os << "Il file e' corrotto";
        return;
    }
    int n_sudoku = contasudoku(file);
    os << "Trovati " << n_sudoku << " sudoku\n";
    os << "Inizio a valutare\n";
    char *c;
    int max = 0;
    int q = 0;
    for (int i=0;i<n_sudoku;++i)
    {
	c = sudoku_n(file,i);
	os << "Sudoku numero " << i << ":\n" << std::flush;
	Solver s(c);
	os << s;	
        if (!controllasudoku(c))        
	    os << "Il sudoku numero " << i << " e' incorretto\n";
	else
	{
	    int temp = s.difficolta();
	    os << "Difficolta' " << temp << '\n';
	    if (temp>max) { max = temp; q = i; }	    
	}
	delete[] c;
    }
    os << "Sudoku piu' difficile: " << q << " (" << max << ")\n";
    c = sudoku_n(file,q);
    Solver s(c);
    os << s;
}

void prova(std::ostream &os)
{
    Solver s("000084096600920700040670300871002000065100007004700005500006003400800600000009008");
    Solver a(s);
    os << (a == s) << endl;
    os << s.celle(4,1)->nx << endl;
}
