#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include <ostream>
#include <istream>

#include "celle.h"
#include "costanti.h"

using namespace geometria;

const int Z = 9;

/**
 * Classe Scacchiera
 * Contiene tutte le informazioni relative alla scacchiera
 */
class Scacchiera : public Celle
{
 private:
    void print(std::ostream &os) const;
    void printverbose(std::ostream &os) const;
   
 protected:
    void quadratoxy2xy(int zx,int zy, int &x1, int &x2, int &y1, int &y2);
    void quadratoz2xy(int z, int &x1, int &x2, int &y1, int &y2);

    bool corretta_linea(int y);
    bool corretta_colonna(int x);
    bool corretto_quadrato(int z);
    bool corretto_quadrato(int zx, int zy);
    bool corretto_rettangolo(int x1, int x2, int y1, int y2);

    bool same_units(int x1, int y1, int x2, int y2);
    bool same_linea(int x1, int y1, int x2, int y2);
    bool same_colonna(int x1, int y1, int x2, int y2);
    bool same_quadrato(int x1, int y1, int x2, int y2);

    friend std::ostream& operator<<(std::ostream& os, const Scacchiera& s);
    friend std::istream& operator>>(std::istream& is, Scacchiera& s);

    int xy2z(int x,int y);

 public:

    /**
     * Costruttore.
     * Azzera tutte le celle, quindi le setta tutte come non determinate
     * e pone tutti i candidati per ogni cella possili
     */
    Scacchiera();
    /**
     * Costruttore copia
     */
    Scacchiera(const Scacchiera &old);
    /**
     * Costruttore.
     * Inizializza la scacchiera ad una situazione definita dall'array init
     */
    Scacchiera(int init[X][Y]);
    /**
     * Costruttore.
     * Inizializza la schacchiera ad una situazione definita dalla stringa init
     * Gli spazi vuoti possono essere rappresentati con 0, . o spazio
     */
    Scacchiera(const char init[]);
    /**
     * Restituisce il numero di celle orizzontali
     */
    int width();
    /**
     * Restituisce il numero di celle verticali
     */
    int heigth();
    /**
     * Restituisce il puntatore alla cella di coordinate x,y
     */
    Cella* celle(int x, int y);
    const Cella* celle(int x, int y) const;

    /**
     * Ricarica la situazione a quella definita dall'array init
     */
    void ricarica(int init[X][Y]);
    /**
     * Ricarica la situazione a quella definita dalla stringa init
     */
    void ricarica(const char init[]);
    /**
     * Restituisce il valore della cella x,y, zero se non e' determinata
     */
    int valore(int x,int y) const;
    /**
     * Setta il valore n alla cella x,y
     */
    void valore(int x,int y, int n);
    /**
     * Restituisce quante celle sono state inserite
     */
    int inseriti();
    /**
     * Restituisce quante celle sono vuote
     */
    int mancanti();
    /**
     * Restituisce se sono state riempite tutte le celle
     */
    bool completato();
    /**
     * Resistituisce se il sudoku e' corretto (anche se non risolto)
     */
    bool corretto();
    /**
     * Resistuisce se il sudoku e' finito correttamente
     */
    bool finito();
    /**
     * Restituisce la stringa che descrive il sudoku, gli spazi vuoti sono
     * rappresentati con 0
     */
    char *stringa();
    /**
     * Traspone la schacchiera come una matrice
     */     
    void trasponi();
    /**
     * Riflette destra e sinistra
     */
    void riflettix();
    /**
     * Riflette sopra e sotto
     */
    void riflettiy();    
    /**
     * Azzera tutte le celle
     */
    void azzera();
    void LaTeX(char* file);
    const char* LaTeX();

    int quadratoxy2z(int x, int y);

    bool operator==(const Scacchiera&) const;
    bool operator!=(const Scacchiera&) const;
    /**
     * Operatore <.
     * A < B quando:
     *  - B ha piu' celle determinate
     *  - le celle determinate di A sono uguali a quelle di B
     */
    bool operator<(const Scacchiera&) const;
    bool operator<=(const Scacchiera&) const;  
};

std::ostream& operator<<(std::ostream& os, const Scacchiera& s);
std::istream& operator>>(std::istream& is, Scacchiera& s);


#endif
