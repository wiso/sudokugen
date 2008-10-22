#include "scacchiera.h"
#include "latex.h"
#include <ostream>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>


Scacchiera::Scacchiera(){}

Scacchiera::Scacchiera(int init[X][Y])
{
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)	
	    if (init[x-1][y-1]!=0) 
		celle(x,y)->value(init[x-1][y-1]);	
}

Scacchiera::Scacchiera(const char init[])
{
    ricarica(init);
}

Scacchiera::Scacchiera(const Scacchiera &old)
    : Celle::Celle(old){}

int Scacchiera::width() { return X; }
int Scacchiera::heigth() { return Y; }

void Scacchiera::ricarica(int init[X][Y])
{
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)	
	    if (init[x-1][y-1]!=0) 
		celle(x,y)->value(init[x-1][y-1]);
	    else celle(x,y)->azzera();
}

void Scacchiera::ricarica(const char init[])
{
    int i = 0;
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	{
	    if (init[i]!='0' and init[i]!=' ' and init[i]!='.')
		celle(x,y)->value((int)(init[i]) - 48);
	    else celle(x,y)->azzera();
	    ++i;	    
	}
}

Cella* Scacchiera::celle(int x, int y)
{
    return &(item[x-1][y-1]);
}

const Cella* Scacchiera::celle(int x, int y) const
{
    return &(item[x-1][y-1]);
}

int Scacchiera::inseriti()
{
    int temp = 0;
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	    if (celle(x,y)->settato()) ++temp;
    return temp;
}

int Scacchiera::mancanti()
{
    return X*Y - inseriti();
}

bool Scacchiera::completato()
{
    if (mancanti()==0) return true;
    else return false;
}

bool Scacchiera::finito()
{
    if (!completato()) return false;
    if (!corretto()) return false;
    return true;
}

int Scacchiera::valore(int x,int y) const
{
    return item[x-1][y-1].value();
}

void Scacchiera::valore(int x, int y, int n)
{
    celle(x,y)->value(n);
}

void Scacchiera::azzera()
{
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	    celle(x,y)->azzera();
}

char* Scacchiera::stringa()
{
    int i = 0;
    char *temp = new char[X*Y];
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	    temp[i++] = valore(x,y) + 48;
    return temp;
	
}

void Scacchiera::trasponi()
{
    for (int y=0;y<Y-1;++y)
	for (int x=y+1;x<X;++x)
	{
	    Cella temp;
	    temp = item[x][y];
	    item[x][y] = item[y][x];
	    item[y][x] = temp;
	}	    
}

void Scacchiera::riflettix()
{
    for (int y=0;y<Y;++y)
	for (int x=0;x<X/2;++x)
	{
	    Cella temp;
	    temp = item[x][y];
	    item[x][y] = item[X-x-1][y];
	    item[X-x-1][y] = temp;
	}
}

void Scacchiera::riflettiy()
{
    for (int x=0;x<X;++x)
	for (int y=0;y<Y/2;++y)
	{
	    Cella temp;
	    temp = item[x][y];
	    item[x][y] = item[x][Y-y-1];
	    item[x][Y-y-1] = temp;
	}
}

void Scacchiera::quadratoxy2xy(int zx,int zy, int &x1, int &x2, int &y1, int &y2)
{
    x1 = (zx-1) * base + 1;
    x2 = zx * base;
    y1 = (zy-1) * base + 1;
    y2 = zy * base;
}

void Scacchiera::quadratoz2xy(int z, int &x1, int &x2, int &y1, int &y2)
{
    x1 = ( (z-1) % base ) * base + 1;
    x2 = ( (z-1) % base + 1) * base;
    y1 = base*( (z-1) / base ) + 1;
    y2 = ( (z-1) / base + 1) * base;
}

int Scacchiera::quadratoxy2z(int x, int y)
{
    return ((y-1)/base * base) + ((x-1)/base + 1);
}

//correttezza
bool Scacchiera::corretto_rettangolo(int x1, int x2, int y1, int y2)
{    
    int ripetuto[N];
    for (int n=0;n<N;ripetuto[n++] = 0);
    for (int x=x1;x<=x2;++x)
	for (int y=y1;y<=y2;++y)
	{
	    if ( celle(x,y)->settato() and 
		 ((++(ripetuto[valore(x,y)-1])) > 1) )	
		return false;
	}
    return true;   
}

bool Scacchiera::corretta_linea(int y)
{
    return corretto_rettangolo(1,X,y,y);
}

bool Scacchiera::corretta_colonna(int x)
{
    return corretto_rettangolo(x,x,1,Y);
}

bool Scacchiera::corretto_quadrato(int z)
{
    int x1,x2,y1,y2;
    quadratoz2xy(z,x1,x2,y1,y2);
    return corretto_rettangolo(x1,x2,y1,y2);
}

bool Scacchiera::corretto_quadrato(int zx, int zy)
{
    int x1,x2,y1,y2;
    quadratoxy2xy(zx,zy,x1,x2,y1,y2);
    return corretto_rettangolo(x1,x2,y1,y2);
}

bool Scacchiera::corretto()
{
    for (int x=1;x<=X;++x)
	if (!corretta_linea(x)) return false;
    for (int y=1;y<=Y;++y)
	if(!corretta_colonna(y)) return false;
    for (int z=1;z<=base*base;++z)
	if(!corretto_quadrato(z)) return false;
    return true;
}

//appartenenza
int Scacchiera::xy2z(int x, int y)
{
    return ((y-1)/base)*base + (x-1)/base + 1;
}

bool Scacchiera::same_units(int x1, int y1, int x2, int y2)
{
    if (same_linea(x1,y1,x2,y2) or same_colonna(x1,y1,x2,y2) or same_quadrato(x1,y1,x2,y2)) return true;
    return false;
}

bool Scacchiera::same_linea(int x1, int y1, int x2, int y2)
{
    if (y1==y2)	return true;
    return false;
}

bool Scacchiera::same_colonna(int x1, int y1, int x2, int y2)
{
    if (x1==x2) return true;
    return false;
}

bool Scacchiera::same_quadrato(int x1, int y1, int x2, int y2)
{
    if (xy2z(x1,y1)==xy2z(x2,y2)) return true;
    return false;
}

//print
void Scacchiera::print(std::ostream &os) const
{
    os << "\n\n";
    for (int y=1;y<=Y;++y)
    {
	for (int x=1;x<=X;++x)
	{
	    if (valore(x,y) == 0) os << "- ";
	    else os << valore(x,y) << ' ';
	    if (x%base == 0) os << "| ";
	}
	if (y%base == 0) os << "\n_______________________\n";
	else os << '\n';
    }
}

void Scacchiera::printverbose(std::ostream &os) const
{
    os << "\n\n";
    for (int y=1;y<=Y;++y)
    {
	for (int x=1;x<=X;++x)
	{
	    if (celle(x,y)->settato())
		os << celle(x,y)->value() << "        ";
	    else 
		for (int i=1;i<=MAX;++i)
		    if (celle(x,y)->possibile(i)) os << i;
		    else os << '.';
	    os << ' ';
	    if (x%base == 0) os << "|#|";
	}
	if (y%base == 0) os << "\n__________________________________________________________________________________________________\n";
	else os << '\n';
    }		
}

const char* Scacchiera::LaTeX()
{
    std::string s;
    s+= "\n\\begin{sudoku}\n";
    for (int y=0;y<Y;++y)
    {
        for (int x=0;x<X;++x)
            s+= "|" + (s[y*X+x]=='0'?' ':s[y*X+x]);
        s+= "|.\n";
    }
    s+= "\\end{sudoku}";
    return s.c_str();
}

void Scacchiera::LaTeX(char* name)
{
    ScacchieraLaTeX(name,*this);
}

bool Scacchiera::operator==(const Scacchiera &altro) const
{
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	{
	    if (valore(x,y)!=altro.valore(x,y)) return false;
	}
    return true;
}

bool Scacchiera::operator!=(const Scacchiera &altro) const
{
    return !(*this == altro);
}

bool Scacchiera::operator<=(const Scacchiera &altro) const
{
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	{
	    if (valore(x,y)!=0)
		if (valore(x,y)!=altro.valore(x,y)) return false;
	}
    return true;
}

bool Scacchiera::operator<(const Scacchiera &altro) const
{
    for (int y=1;y<=Y;++y)
	for (int x=1;x<=X;++x)
	{
	    if (valore(x,y)!=0)
		if (valore(x,y)!=altro.valore(x,y)) return false;
	}
    if (*this==altro) return false;
    return true;
}


std::ostream& operator<<(std::ostream& os, const Scacchiera& s)
{
    if (VERBOSE)
	s.printverbose(os);
    else
	s.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Scacchiera& s)
{
    char stringa[X*Y];
    is.read(stringa,X*Y);
    s.ricarica(stringa);
    return is;
}
