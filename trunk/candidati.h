#ifndef CANDIDATI_H
#define CANDIDATI_H

#include "costanti.h"

/**
 * Classe TCandidati
 * e' un contenitore in cui sono memorizzati gli stati possibili
 * \author Ruggero Turra
 * \date 2006
 */

class Candidati
{
 private:
    const int max;
    bool *m_data;
    void possibile(int n,bool in);
 public:
    /**
     * Costruttore,
     * Setta tutti i valori come possibili
     */
    Candidati();
    /**
     * Costruttore,
     * Setta tutti i valori come impossibili tranne n
     */
    Candidati(int n);
    /**
     * Costruttore copia
     */
    Candidati(const Candidati &old);
    /**
     * Distruttore
     */
    ~Candidati();
    /** Ritorna se n e' possibile
     *  
     */
    inline bool possibile(int n) const { return m_data[n-1]; };
    /**
     *  Setta n come impossibile e ritorna se e' cambiato qualcosa
     */
    bool togli(int n);    
    /**
     * Setta tutti i valori come possibili
     */
    void tutti_possibili();
    /**
     * Setta tutti i valori come impossibili tranne n
     */
    void possibile_n(int n);
    /**
     * Dice se esiste un solo valore possibile
     */
    bool determinato() const;
    /**
     * Dice se esiste un solo valore possibile e ne scrive il valore in n
     */
    bool determinato(int &n) const;
    /**
     * Dice quanti candidati ci sono
     */
    int quanti() const;
    /**
     * Dice se c'e' solo una coppia possibile e restituisce i valori
     */
    bool coppia(int &a,int &b) const;
    /**
     * Dice quanti e quali
     */
    int quali(int vet[]) const;
    /**
     * Confronta con un altro
     */
    bool operator==(const Candidati&) const;    
    Candidati& operator=(const Candidati& altro);
};

#endif
