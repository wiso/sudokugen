#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <ostream>
#include "costanti.h"

void inittestsudoku();
void dobench(std::ostream &os, const int RIP);
bool doone(std::ostream &os);
bool doone_logica(std::ostream &os);
void value_this(std::ostream &os, const char *stringa);
void value_file(std::ostream &os, const char *file);
void prova(std::ostream &os);

#endif
