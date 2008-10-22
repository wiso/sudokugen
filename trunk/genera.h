#ifndef GENERA_H
#define GENERA_H

#include "strategiadata.h"

/**
 * Genera un sudoku completato
 */
char* genera_finito();
/**
 * Partendo da un sudoku completato toglie i numeri fino a quando riesce a risolverlo
 */
char* genera_mostdifficult();
/**
 * Genera un sudoku con difficolta' compresa tra min e max
 */
char* genera_difficult(int min, int max);
/**
 * Genera un sudoku tale che il numero di volte che devono essere usate le strategie e' maggiore di quanto richiesto
 */
char* genera_strategia(const Strategie&);

#endif
