#ifndef CELLE_H
#define CELLE_H

#include "cella.h"
#include "costanti.h"

using namespace geometria;

/**
 * Classe Celle
 * Non fa nulla
 */
struct Celle
{
    Cella item[X][Y];
    Celle()
	{ for (int y=0;y<Y;++y) for (int x=0;x<X;++x)
		{ item[x][y].nx = x+1; item[x][y].ny = y+1; } };
};


#endif
