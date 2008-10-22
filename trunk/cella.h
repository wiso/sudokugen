#ifndef CELLA_H
#define CELLA_H

#include "candidati.h"
#include "pos.h"
/**
 * Classe Cella
 * Contiene tutte le informazioni relative a una cella
 */
class Cella : public Candidati, public Pos
{
 private:
    int m_value;
    bool m_settato; //se e' stato determinato
 public:
    /**
     * Costruttore di default, setta il valore a 0 e a non settato, esegue TCandidati
     */
    Cella();
    /**
     * Setta il valore iniziale, esegue TCandidati, e' settato
     */
    Cella(int valore);
    /**
     * Copy constructor
     */
    Cella(const Cella &old);
    /**
     * Ritorna il valore, 0 se non e' settato
     */
    int value() const {return m_value;}
    /**
     * Setta il valore, imposta come settato, esegue TFuturo
     */
    void value(int valore);
    /**
     * Ritorna se e' settato
     */
    inline bool settato() const {return m_settato;};
    /**
     * Esegue TCandidati::determinato, se esiste un solo valore possibile, allora setta m_value al valore e lo mette settato
     */   
    bool controlla();
    /**
     * Azzera la cella
     */
    void azzera();
    bool operator==(const Cella&) const;
    bool operator!=(const Cella&) const;
    Cella& operator=(const Cella& altro);
};

#endif
