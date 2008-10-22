#ifndef COSTANTI_H
#define COSTANTI_H

namespace geometria{
    const int MAX = 9;
    const int N = 9; //numero di simboli
    const int base = 3;
    const int X = base*base;
    const int Y = base*base;
}

const bool MY_DEBUG = false;
const bool VERBOSE = false;


namespace punteggio {
    const int PUNTEGGIO_CONTROLLA = 1;
    const int PUNTEGGIO_ELIMINA = 2;
    const int PUNTEGGIO_SINGLES = 3;
    const int PUNTEGGIO_NACKEDPAIR = 4;
    const int PUNTEGGIO_HIDDENPAIR = 5;
    const int PUNTEGGIO_POINTINGPAIR = 6;
    const int PUNTEGGIO_BOXREDUCTION = 6;
    const int PUNTEGGIO_XWING = 10;
}

#endif
