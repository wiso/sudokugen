#include "solver.h"
#include <ostream>
#include <fstream>
#include <istream>
#include <iostream>


void Solver::valore(int x, int y, int n)
{
    Scacchiera::valore(x,y,n);
    colonnameno(x,n);
    lineameno(y,n);
    quadratomeno(quadratoxy2z(x,y),n);   
}

//strategie
bool Solver::controlla()
{
    bool changed = false;
    int q;
    for (int x=1;x<=X;++x)
	for (int y=1;y<=Y;++y)
	    if (!celle(x,y)->settato())
		if (celle(x,y)->determinato(q))
		{
		    valore(x,y,q);
		    changed = true;
		}
    return changed;
}

bool Solver::lineameno(int y, int n)
{
    bool changed = false;
    int q;
    for (int x=1;x<=X;++x)
    {
	if (celle(x,y)->togli(n))
	{
	    changed = true;
	    if (celle(x,y)->determinato(q)) 
		valore(x,y,q);
	}
    }
    return changed;
}

bool Solver::colonnameno(int x, int n)
{
    bool changed = false;
    int q;
    for (int y=1;y<=Y;++y)
    {
	if (celle(x,y)->togli(n))
	{
	    changed = true;
	    if (celle(x,y)->determinato(q))	    
		valore(x,y,q);	    
	}
    }
    return changed;
}

bool Solver::quadratomeno(int zx, int zy, int n)
{
    bool changed = false;
    int q;
    for (int x = (zx-1)*base+1; x<=zx*base; ++x)
	for (int y = (zy-1)*base+1; y<=zy*base; ++y)
	{
	    if (celle(x,y)->togli(n))
	    {
		changed = true;
		if (celle(x,y)->determinato(q))
		    valore(x,y,q);
	    }
	}
    return changed;
}

bool Solver::quadratomeno(int z, int n)
{
    bool changed = false;
    int q;
    for (int x = ( (z-1) % base ) * base + 1; x<=( (z-1) % base + 1) * base; ++x)
	for (int y = base*( (z-1) / base ) + 1; y<=( (z-1) / base + 1) * base; ++y)
	{
	    if (celle(x,y)->togli(n))
	    {
		changed = true;
		if (celle(x,y)->determinato(q))
		    valore(x,y,q);
	    }
	}
    return changed;
}

bool Solver::eliminalinea(int y)
{
    bool changed = false;
    for (int x=1;x<=X;++x)
    {
	if (celle(x,y)->settato())
	    if (lineameno(y,celle(x,y)->value())) changed = true;
    }
    return changed;
}

bool Solver::eliminacolonna(int x)
{
    bool changed = false;
    for (int y=1;y<=Y;++y)
    {
	if (celle(x,y)->settato())
	    if (colonnameno(x,celle(x,y)->value())) changed = true;
    }
    return changed;
}

bool Solver::eliminaquadrato(int zx, int zy)
{
    bool changed = false;
    for (int x = (zx-1)*base+1; x<=zx*base; ++x)
	for (int y = (zy-1)*base+1; y<=zy*base; ++y)
	{
	    if (celle(x,y)->settato())
		if (quadratomeno(zx,zy,celle(x,y)->value())) changed = true;
	}
    return changed;
}

bool Solver::eliminaquadrato(int z)
{
    bool changed = false;
    for (int x = ( (z-1) % base ) * base + 1; x<=( (z-1) % base + 1) * base; ++x)
	for (int y = base*( (z-1) / base ) + 1; y<=( (z-1) / base + 1) * base; ++y)
	{
	    if (celle(x,y)->settato())
		if (quadratomeno(z,celle(x,y)->value())) changed = true;
	}
    return changed;
}

bool Solver::elimina()
{
    bool changed = false;
    for (int x=1;x<=X;++x)
	if (eliminacolonna(x)) changed = true;
    for (int y=1;y<=Y;++y)
	if (eliminalinea(y)) changed = true;
    for (int z=1;z<=Z;++z)
	if (eliminaquadrato(z)) changed = true;
    return changed;
}

bool Solver::singlescolonna(int x)
{
    bool changed = false;
    int j, yy=-1;
    for (int n=1;n<=N;++n)
    {
	j = 0; //occorrenze
	for (int y=1;y<=Y;++y)	
	    if (celle(x,y)->possibile(n)) 
	    {
		++j;
		if (j>1) break;  //conviene?
		yy = y;
	    }
	if (j==1)
	{
	    valore(x,yy,n); 
	    changed = true;
	}	
    }
    return changed;
}

bool Solver::singleslinea(int y)
{
    bool changed = false;
    int j, xx=-1;
    for (int n=1;n<=N;++n)
    {
	j = 0; //occorrenze
	for (int x=1;x<=X;++x)
	    if (celle(x,y)->possibile(n))
	    {
		++j;
		xx = x;
	    }
	if (j==1)
	{
	    valore(xx,y,n);
	    changed = true;
	}
    }
    return changed;
}

bool Solver::singlesquadrato(int z)
{
    bool changed = false;
    int j, xx=-1, yy=-1;
    for (int n=1;n<=N;++n)
    {
	j = 0; //occorrenze
	
	for (int x = ( (z-1) % base ) * base + 1; x<=( (z-1) % base + 1) * base; ++x)
	    for (int y = base*( (z-1) / base ) + 1; y<=( (z-1) / base + 1) * base; ++y)
		if (celle(x,y)->possibile(n))
		{
		    ++j;
		    xx = x;
		    yy = y;
		}
	if (j==1)
	{
	    valore(xx,yy,n);
	    changed = true;
	}
    }
    return changed;
}

bool Solver::singles()
{
    bool changed = false;
    for (int x=1;x<=X;++x)
	if (singlescolonna(x)) changed = true;
    for (int y=1;y<=Y;++y)
	if (singleslinea(y)) changed = true;
    for (int z=1;z<=Z;++z)
	if (singlesquadrato(z)) changed = true;
    return changed;
}

bool Solver::nackedpairlinea(int y)
{
    bool changed = false;
    int a,b;
    for (int x=1;x<X;++x) //potrebbe anche essere < (togli l'ultimo)
    {
	if (celle(x,y)->coppia(a,b))
	    for (int xx=x+1;xx<=X;++xx)
		if (*(celle(x,y))==*(celle(xx,y))) 
		{
		    for (int xxx=1;xxx<=X;++xxx)
		    {
			if (xxx!=x and xxx!=xx)
			{
			    if (celle(xxx,y)->togli(a)) changed = true;
			    if (celle(xxx,y)->togli(b)) changed = true;
			}
		    }
		    goto esci; //esiste solo una coppia di coppie
		}
    esci:;
    }
    return changed;
}

bool Solver::nackedpaircolonna(int x)
{
    bool changed = false;
    int a,b;
    for (int y=1;y<Y;++y) //potrebbe anche essere < (togli l'ultimo)
    {
	if (celle(x,y)->coppia(a,b))
	    for (int yy=y+1;yy<=Y;++yy) //<==voglio che il goto lo faccia uscire da qui
		if (*(celle(x,y))==*(celle(x,yy))) 
		{
		    for (int yyy=1;yyy<=Y;++yyy)
		    {
			if (yyy!=y and yyy!=yy)
			{
			    if (celle(x,yyy)->togli(a)) changed = true;
			    if (celle(x,yyy)->togli(b)) changed = true;
			}
		    }
		    goto esci;
		}
    esci:;
    }
    return changed;
}

bool Solver::nackedpairquadrato(int z)
{
    bool changed = false;
    int a,b;
    int x1,x2,y1,y2;
    quadratoz2xy(z,x1,x2,y1,y2);
    for (int y=y1;y<=y2;++y)
	for (int x=x1;x<=x2;++x)
	{
//	esci:
	    if (celle(x,y)->coppia(a,b))
		for (int yy=y;yy<=y2;++yy)
		    for (int xx=x+1;xx<=x2;++xx)
			if (*(celle(x,y))==*(celle(xx,yy)))
			{
			    for (int yyy=y1;yyy<=y2;++yyy)
				for (int xxx=x1;xxx<=x2;++xxx)
				    if (yyy!=y and yyy!=yy and xxx!=x and xxx!=xx)
				    {
					if (celle(xxx,yyy)->togli(a)) changed = true;
					if (celle(xxx,yyy)->togli(b)) changed = true;
				    }
//			    goto esci;
			}
	}
    return changed;
}

bool Solver::nackedpair()
{
    bool changed = false;
    for (int y=1;y<=Y;++y)
	if (nackedpairlinea(y)) changed = true;
    for (int x=1;x<=X;++x)
	if (nackedpaircolonna(x)) changed = true;
    for (int z=1;z<=Z;++z)
	if (nackedpairquadrato(z)) changed = true;
    return changed;    
}

bool Solver::hiddenpairlinea(int y)
{
    bool changed = false;
    int n1,a,b;//a,b sono le posizioni dove c'e' la coppia
    for (int i=1;i<=MAX;++i)
    {
	n1 = 0;//conta le ripetizioni di i
	for (int x=1;x<=X;++x)
	{
	    if (celle(x,y)->possibile(i)) 
	    {
		if (++n1>2) break;
		if (n1==1) a = x;
		if (n1==2) b = x;
	    }
	}
	if (n1==2)
	{
	    for (int j=1;j<=MAX;++j)//j=i+1
	    {
		if (i==j) continue;
		int n2 = 0;
		for (int x=1;x<=X;++x)
		{
		    if (celle(x,y)->possibile(j))
		    {
			if (x!=a and x!=b) {n2 = -1; break;}
			else ++n2;
		    }
		}
		if (n2==2)
		{
		    for (int n=1;n<=N;++n)
			if (n!=i and n!=j) 
			{
			    if (celle(a,y)->togli(n)) changed = true;
			    if (celle(b,y)->togli(n)) changed = true;
			}
		}
	    }
	}
	
    }
    return changed;
}

bool Solver::hiddenpaircolonna(int x)
{
    bool changed = false;
    int n1,a,b;//a,b sono le posizioni dove c'e' la coppia
    for (int i=1;i<=MAX;++i)
    {
	n1 = 0;//conta le ripetizioni di i
	for (int y=1;y<=Y;++y)
	{
	    if (celle(x,y)->possibile(i)) 
	    {
		if (++n1>2) break;
		if (n1==1) a = y;
		if (n1==2) b = y;
	    }
	}
	if (n1==2)
	{
	    for (int j=1;j<=MAX;++j)
	    {
		if (i==j) continue;
		int n2 = 0;
		for (int y=1;y<=Y;++y)
		{
		    if (celle(x,y)->possibile(j))
		    {
			if (y!=a and y!=b) {n2 = -1; break;}
			else ++n2;
		    }
		}
		if (n2==2)
		{
		    for (int n=1;n<=N;++n)
			if (n!=i and n!=j) 
			{
			    if (celle(x,a)->togli(n)) changed = true;
			    if (celle(x,b)->togli(n)) changed = true;
			}
		}
	    }
	}
	
    }
    return changed;
}


bool Solver::hiddenpairquadrato(int z)
{
    bool changed = false;
    int n1,ax,bx,ay,by;//a,b sono le posizioni dove c'e' la coppia
    int x1,x2,y1,y2;
    quadratoz2xy(z,x1,x2,y1,y2);
    for (int i=1;i<=MAX;++i)
    {
	n1 = 0;//conta le ripetizioni di i
	for (int y=y1;y<=y2;++y)
	    for (int x=x1;x<=x2;++x)
	    {
		if (celle(x,y)->possibile(i)) 
		{
		    if (++n1>2) break;
		    if (n1==1) {ay = y; ax = x;}
		    if (n1==2) {by = y; bx = x;}
		}
	    }
	if (n1==2)
	{
	    for (int j=1;j<=MAX;++j)
	    {
		if (i==j) continue;
		int n2 = 0;
		for (int y=y1;y<=y2;++y)
		    for (int x=x1;x<=x2;++x)
		    {
			if (celle(x,y)->possibile(j))
			{
			    if ((y!=ay or x!=ax) and (y!=by or x!=bx)) {n2 = -1; break;}
			    else ++n2;
			}
		    }
		if (n2==2)
		{
		    for (int n=1;n<=N;++n)
			if (n!=i and n!=j)
			{
			    if (celle(ax,ay)->togli(n)) changed = true;
			    if (celle(bx,by)->togli(n)) changed = true;
			}
		}
	    }
	}
	
    }
    return changed;
}

bool Solver::hiddenpair()
{
    bool changed = false;
    for (int y=1;y<=Y;++y)
	if (hiddenpairlinea(y)) changed = true;    
    for (int x=1;x<=X;++x)
	if (hiddenpaircolonna(x)) changed = true;
    for (int z=1;z<=Z;++z)
	if (hiddenpairquadrato(z)) changed = true;
    return changed;     
}

bool Solver::pointingpairquadrato(int z)
{
    bool changed = false;
    bool riga = false;
    bool colonna = false;
    int x1,x2,y1,y2;
    int a,b,n;
    quadratoz2xy(z,x1,x2,y1,y2);
    for (int i=1;i<=MAX;++i)
    {
	a = b = 0;
	n = 0;
	riga = colonna = false;
	for (int x=x1;x<=x2;++x)
	{
	    for (int y=y1;y<=y2;++y)
		if (celle(x,y)->possibile(i))
		{
		    if (++n>3) { riga=colonna=false; goto esci; }
		    if (n == 1)
		    {
			a = x;
			b = y;
		    }
		    if (n == 2)
		    {
			if (x == a) colonna = true;
			if (y == b) riga = true;
			if (!colonna and !riga) goto esci;
		    }
		    if (n == 3)
		    {
			if (colonna)
			    if (x == a) colonna = true;
			    else {colonna = false; goto esci;}
			if (riga)
			    if (y == b) riga = true;
			    else {riga = false; goto esci;}
		    }
		}
	}
	if (colonna)
	    for (int yy=1;yy<=Y;++yy)
	    {
		if (quadratoxy2z(a,yy)!=z)
		    if (celle(a,yy)->togli(i)) changed = true;
	    }
	if (riga)
	    for (int xx=1;xx<=X;++xx)
	    {
		if (quadratoxy2z(xx,b)!=z)
		{
		    if (celle(xx,b)->togli(i)) changed = true;
		}
	    }
    esci:{}
    }  
    return changed;
}

bool Solver::pointingpair()
{
    bool changed = false;
    for (int z=1;z<=Z;++z)
	if (pointingpairquadrato(z)) changed = true;
    return changed;
}

bool Solver::boxreductionlinea(int y)
{
    bool changed = false;
    for (int i=1;i<=MAX;++i)
    {
	int n = 0;
	int z1 = 0;
	for (int x=1;x<=X;++x)
	    if (celle(x,y)->possibile(i))
	    {
		if (++n>3) goto esci;
		if (n == 1) z1 = quadratoxy2z(x,y);
		if (n == 2)
		    if (quadratoxy2z(x,y) != z1) goto esci;
		if (n == 3)
		    if (quadratoxy2z(x,y) != z1) goto esci;
	    }
	if (n!=0)
	{
	    int x1,x2,y1,y2;
	    quadratoz2xy(z1,x1,x2,y1,y2);
	    for (int xx=x1;xx<=x2;++xx)
		for (int yy=y1;yy<=y2;++yy)
		    if (yy!=y)
			if (celle(xx,yy)->togli(i)) changed = true;
	}
    esci:{}
    }
    return changed;
}

bool Solver::boxreductioncolonna(int x)
{
    bool changed = false;
    for (int i=1;i<=MAX;++i)
    {
	int n = 0;
	int z1 = 0;
	for (int y=1;y<=Y;++y)
	    if (celle(x,y)->possibile(i))
	    {
		if (++n>3) goto esci;
		if (n == 1) z1 = quadratoxy2z(x,y);
		if (n == 2)
		    if (quadratoxy2z(x,y) != z1) goto esci;
		if (n == 3)
		    if (quadratoxy2z(x,y) != z1) goto esci;
	    }
	if (n!=0)
	{
	    int x1,x2,y1,y2;
	    quadratoz2xy(z1,x1,x2,y1,y2);
	    for (int xx=x1;xx<=x2;++xx)
		for (int yy=y1;yy<=y2;++yy)
		    if (xx!=x)
			if (celle(xx,yy)->togli(i)) changed = true;	    
	}
    esci:{}
    }
    return changed;
}

bool Solver::boxreduction()
{
    bool changed = false;
    for (int x=1;x<=X;++x)
	if (boxreductioncolonna(x)) changed = true;
    for (int y=1;y<=Y;++y)
	if (boxreductionlinea(y)) changed = true;
    return changed;
}

bool Solver::xwing()
{
    bool changed = false;

    for (int i=1;i<=MAX;++i)
    {
	for (int y=1;y<Y;++y)//colonne
	{
	    int n = 0;
	    int a,b;
	    for (int x=1;x<=X;++x)
		if (celle(x,y)->possibile(i))
		{
		    if (++n>2) break;
		    if (n==1) a = x;
		    if (n==2) b = x;
		}	
	    if (n==2)
		for (int yy=y+1;yy<=Y;++yy)
		{
		    int nn = 0;
		    for (int x=1;x<=X;++x)
			if (celle(x,yy)->possibile(i))
			{
			    if (++nn>2) break;
			    if (nn==1 and x!=a) {nn=-1; break;}
			    if (nn==2 and x!=b) {nn=-1; break;}
			}
		    if (nn==2)
		    {
			for (int x=a+1;x<b;++x)
			{
			    if (celle(x,y)->togli(i)) changed = true;
			    if (celle(x,yy)->togli(i)) changed = true;
			}
			for (int yyy=y+1;yyy<yy;++yyy)
			{
			    if (celle(a,yyy)->togli(i)) changed = true;
			    if (celle(b,yyy)->togli(i)) changed = true;
			}
		    }
		}
	}
	for (int x=1;x<X;++x)//righe
	{
	    int n = 0;
	    int a,b;
	    for (int y=1;y<=Y;++y)
		if (celle(x,y)->possibile(i))
		{
		    if (++n>2) break;
		    if (n==1) a = x;
		    if (n==2) b = x;
		}
	    if (n==2)
		for (int xx=x+1;xx<=X;++xx)    
		{
		    int nn = 0;
		    for (int y=1;y<=Y;++y)
			if (celle(xx,y)->possibile(i))
			{
			    if (++n>2) break;
			    if (nn==1 and y!=a) {nn=-1; break;}
			    if (nn==2 and y!=b) {nn=-1; break;}
			}
		    if (nn==2)
		    {
			for (int y=a+1;y<b;++y)
			{
			    if (celle(x,y)->togli(i)) changed = true;
			    if (celle(xx,y)->togli(i)) changed = true;
			}
			for (int xxx=x+1;xxx<xx;++xxx)
			{
			    if (celle(xxx,a)->togli(i)) changed = true;
			    if (celle(xxx,b)->togli(i)) changed = true;
			}
		    }
		}
	}
    }    
    return changed;
}

bool Solver::nextcatenapairone(int x, int y, int x0, int y0, int n, int step, Scacchiera& used)
{

    bool findend = false;
    for (int xx=1;xx<=X;++xx)
	if (celle(xx,y)->quanti()==2 and xx!=x and celle(xx,y)->possibile(n) and used.valore(xx,y)==0)
	{
	    used.valore(xx,y,1); //usato (1);
	    nextcatenapairone(xx,y,x0,y0,n,++step,used);
	}
	else
	{
	    
	}
}

bool Solver::simplecolouring()
{
    bool changed = false;
    Scacchiera used;
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	{
	    int a0,b0;
	    if (celle(x,y)->coppia(a0,b0))
		for (int ni=0;ni<2;++ni)
		{
		    int n0;
		    if (ni==0) n0 = a0;
		    else n0 = b0;
		    used.azzera();
		    used.valore(x,y,2); //l'inizio (2)
		    nextcatenapairone(x,y,x,y,ni,0,used);
		}
	}
    return changed;
}


//risolvi

bool Solver::risolvilogica()
{
    bool changed = true;
    while (changed)
    {
	changed = false;
	if (controlla())     { changed = true; continue; }
	if (elimina())       { changed = true; continue; }
	if (singles())       { changed = true; continue; }
	if (nackedpair())    { changed = true; continue; }
	if (completato())    {                    break; }
	if (hiddenpair())    { changed = true; continue; }
	if (pointingpair())  { changed = true; continue; }
	if (completato())    {                    break; }
	if (boxreduction())  { changed = true; continue; }
	if (xwing())         { changed = true; continue; }
    }
    return finito();
}

bool Solver::risolvilogicadebug()
{
    bool changed = true;
    while (changed)
    {
	changed = false;
	if (MY_DEBUG) std::cout << "controlla\n" << std::flush;
	if (controlla()) 
	{
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "controlla true" << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}

	if (MY_DEBUG) std::cout << "elimina\n" << std::flush;
	if (elimina()) 
	{
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "elimina true" << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "singles\n" << std::flush;
	if (singles())
	{
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "singles true" << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "nackedpair\n" << std::flush;
	if (nackedpair())
	{
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "nackedpair true" << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "hiddenpair\n" << std::flush;
	if (hiddenpair())
	{
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "hiddenpair true" << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "pointingpair\n" << std::flush;
	if (pointingpair())
	{
	    changed = true;
	    if (MY_DEBUG)
	    {
		std::cout << "pointingpair true" << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "boxreduction\n" << std::flush;
	if (boxreduction())
	{
	    changed = true;
	    if (MY_DEBUG)
	    {
		std::cout << "Box reduction true" << std::flush;
		std::cout << *this;
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "xwing\n" << std::flush;
	if (xwing())
	{
	    changed = true;
	    if (MY_DEBUG)
	    {
		std::cout << "xwing true" << std::flush;
		std::cout << *this;
	    }
	    continue;
	}
    }
    return finito();
}

int Solver::risolvidifficolta()
{
    using namespace punteggio;
    bool changed = true;
    int punteggio = 0;
    while (changed)
    {
	changed = false;
	if (MY_DEBUG) std::cout << "controlla\n" << std::flush;
	if (controlla())
	{
	    punteggio += PUNTEGGIO_CONTROLLA;
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "controlla true\n";
		std::cout << "punteggio + " << PUNTEGGIO_CONTROLLA << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "elimina\n" << std::flush;
	if (elimina()) 
	{
	    punteggio += PUNTEGGIO_ELIMINA;
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "elimina true\n";
		std::cout << "punteggio + " << PUNTEGGIO_ELIMINA << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "singles\n" << std::flush;
	if (singles())
	{
	    punteggio += PUNTEGGIO_SINGLES;
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "singles true\n";
		std::cout << "punteggio + " << PUNTEGGIO_SINGLES << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "nackedpair\n" << std::flush;
	if (nackedpair())
	{
	    punteggio += PUNTEGGIO_NACKEDPAIR;
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "nackedpair true\n";
		std::cout << "punteggio + " << PUNTEGGIO_NACKEDPAIR << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "hiddenpair\n" << std::flush;
	if (hiddenpair())
	{
	    punteggio += PUNTEGGIO_HIDDENPAIR;
	    changed = true; 
	    if (MY_DEBUG)
	    {
		std::cout << "hiddenpair true\n";
		std::cout << "punteggio + " << PUNTEGGIO_HIDDENPAIR << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "pointingpair\n" << std::flush;
	if (pointingpair())
	{
	    punteggio += PUNTEGGIO_POINTINGPAIR;
	    changed = true;
	    if (MY_DEBUG)
	    {
		std::cout << "pointingpair true\n";
		std::cout << "punteggio + " << PUNTEGGIO_POINTINGPAIR << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "boxreduction\n" << std::flush;
	if (boxreduction())
	{
	    punteggio += PUNTEGGIO_BOXREDUCTION;
	    changed = true;
	    if (MY_DEBUG)
	    {
		std::cout << "boxreduction true\n";
		std::cout << "punteggio + " << PUNTEGGIO_BOXREDUCTION << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
	if (MY_DEBUG) std::cout << "xwing\n" << std::flush;
	if (xwing())
	{
	    punteggio += PUNTEGGIO_XWING;
	    changed = true;
	    if (MY_DEBUG)
	    {
		std::cout << "xwing true\n";
		std::cout << "punteggio + " << PUNTEGGIO_XWING << std::flush;
		std::cout << *this; 
	    }
	    continue;
	}
    }
    if (!finito()) return -1;
    return punteggio;
}

int Solver::difficolta()
{
    Solver *temp = new Solver(*this);
    int dif = temp->risolvidifficolta();
    delete temp;
    return dif;
}


bool Solver::risolvi()
{
    risolvilogica();
    if (!finito())    
    {
	for (int y=1;y<=Y;++y)
	{	 
	    for (int x=1;x<=X;++x)	    	
		if (!celle(x,y)->settato())
		    for (int n=1;n<=N;++n)		    
			if (celle(x,y)->possibile(n))
			{
			    Solver *ricorsione = new Solver(*this);
			    ricorsione->celle(x,y)->value(n);
			    if (ricorsione->risolvi())
				celle(x,y)->possibile_n(n);
			    if (ricorsione->completato() and
				(!ricorsione->corretto()) )
				celle(x,y)->togli(n);
			}
	}
	risolvilogica();
	if (finito()) return true;
    }
    else return true;
    return false;
}

Strategie Solver::risolvistrategie()
{
    bool changed = true;
    Strategie s;
    while (changed)
    {
	changed = false;
	if (controlla())     { changed = true; s[0]++; continue; }
	if (elimina())       { changed = true; s[1]++; continue; }
	if (singles())       { changed = true; s[2]++; continue; }
	if (nackedpair())    { changed = true; s[3]++; continue; }
	if (completato())    {                    break; }
	if (hiddenpair())    { changed = true; s[4]++; continue; }
	if (pointingpair())  { changed = true; s[5]++; continue; }
	if (completato())    {                    break; }
	if (boxreduction())  { changed = true; s[6]++; continue; }
	if (xwing())         { changed = true; s[7]++; continue; }
    }
    return s;
}

Strategie Solver::strategie()
{
    Solver *temp = new Solver(*this);
    Strategie s = temp->risolvistrategie();
    delete temp;
    return s;
}
