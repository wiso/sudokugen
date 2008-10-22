#ifndef SOLVER_H
#define SOLVER_H

#include <ostream>
#include <istream>

#include "celle.h"
#include "costanti.h"
#include "scacchiera.h"
#include "strategiadata.h"


/**
 * Classe Solver
 */
class Solver: public Scacchiera
{
 public:
    Solver(): Scacchiera() {};
    Solver(int init[X][Y]) : Scacchiera(init) {};
    Solver(const char init[]) : Scacchiera(init) {};
    inline int valore(int x, int y) {return Scacchiera::valore(x,y);};
    void valore(int x, int y, int n);
    // strategie
    bool controlla();
    //elimina
    bool lineameno(int y, int n);
    bool colonnameno(int x, int n);
    bool quadratomeno(int z, int n);	
    bool quadratomeno(int zx, int zy, int n);
    bool eliminalinea(int y);
    bool eliminacolonna(int x);
    bool eliminaquadrato(int zx, int zy);
    bool eliminaquadrato(int z);
    bool elimina();
    //singles
    bool singles();
    bool colonnaunico(int x,int n);
    bool lineaunico(int y, int n);
    bool quadratounico(int z, int n);
    bool singlescolonna(int x);
    bool singleslinea(int y);
    bool singlesquadrato(int z);
    // naked pair
    bool nackedpairlinea(int y);
    bool nackedpaircolonna(int x);
    bool nackedpairquadrato(int z);
    bool nackedpair();
    // hiddern pair
    bool hiddenpairlinea(int y);
    bool hiddenpaircolonna(int x);
    bool hiddenpairquadrato(int z);
    bool hiddenpair();
    //pointing pair
    bool pointingpairquadrato(int z);
    bool pointingpair();    
    //boxreduction
    bool boxreductionlinea(int y);
    bool boxreductioncolonna(int x);
    bool boxreduction();
    //xwing
    bool xwing();
    //simplecolouring
    bool nextcatenapairone(int x, int y, int x0, int y0, int n, int step, Scacchiera& used);
    bool simplecolouring();    

    bool risolvilogica();
    bool risolvilogicadebug();
    bool risolvi();
    int risolvidifficolta();
    Strategie risolvistrategie();
    Strategie strategie();
    int difficolta(); 
};


#endif //SOLVER_H
