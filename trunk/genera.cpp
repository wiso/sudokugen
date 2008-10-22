#include <ctime>
#include <cstdlib>
#include <iostream>

#include "genera.h"
#include "solver.h"
#include "costanti.h"

bool seed_init = false;

void genera_init()
{
    srand((unsigned)time(NULL));
    seed_init = true;
}


inline int genera_n(int max) //tra 0 e max-1
{
    if (!seed_init) genera_init();
    return (int)((double)max * rand()/(RAND_MAX +1.));
}

void togliuno(char stringa[X*Y])
{
    int n = 0;
    for (int i=0;i<X*Y;++i)
	if (stringa[i]!='0') ++n;
    int q = genera_n(n);
    n = -1;
    for (int i=0;i<X*Y;++i)
    {
	if (stringa[i]!='0') ++n;
	if (n==q)
	    {
		stringa[i] = '0';
		return;
	    }
    }
}

void togliuno(Solver &solver)
{
    int n = 0;
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	    if (solver.valore(x,y)!=0) ++n;
    int q = genera_n(n);
    n = -1;
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	{
	    if (solver.valore(x,y)!=0) ++n;
	    if (n==q)
	    {
		solver.valore(x,y,0);
		return;
	    }
	}
}

char* genera_finito()
{   
    char* temp;
    bool corretto = false;
    do
    {
	Solver *s = new Solver();
	for (int x=1;x<=X;++x)
	    for (int y=1;y<=Y;++y)
	    {		
		if (!s->celle(x,y)->settato())
		{
		    int quali[MAX];
		    int quanti = s->celle(x,y)->quali(quali);
		    s->celle(x,y)->value(quali[genera_n(quanti)]);
		}
		if (s->risolvilogica()) goto esci;
	    }
    esci:
	corretto = s->corretto();
	if (corretto) temp = s->stringa();
	delete s;
    }while(corretto == false);
    return temp;
}

char* genera_mostdifficult()
{
    char* temp = new char[X*Y];
    char* temp_new;
    temp_new = genera_finito();
    Solver s(temp_new);
    while (s.risolvilogica())
    {
	for (int i=0;i<X*Y;++i)
	    temp[i] = temp_new[i];   
	togliuno(temp_new);
	s.ricarica(temp_new);
    }
    delete[] temp_new;
    return temp;
}

char* genera_difficult(int min, int max)
{
    char* temp = new char[X*Y];
    char* temp_new;
    int d = 0;
    temp_new = genera_finito();
    Solver s(temp_new);
    while (d<min or d>max)
    {
	togliuno(temp_new);
	for (int i=0;i<X*Y;++i)
	    temp[i] = temp_new[i];
	s.ricarica(temp_new);
	d = s.difficolta();
	if (d == -1) temp_new = genera_finito();
	if (d>max) temp_new = genera_finito();
    }
    delete[] temp_new;
    return temp;
}

bool ok_strategia(const Strategie &s, const Strategie &s_const) //FIX
{
    return true;
}

char* genera_strategia(const Strategie &stra)
{
    char* temp = new char[X*Y];
    char *temp_new;
    Strategie stra_this;
    temp_new = genera_finito();
    Solver s(temp_new);
    while(!ok_strategia(stra_this,stra))
    {
	togliuno(temp_new);
	for (int i=0;i<X*Y;++i)
	    temp[i] = temp_new[i];
	s.ricarica(temp_new);
	if (s.difficolta()==-1) temp_new = genera_finito();	
    }
    delete[] temp_new;
    return temp;
}
