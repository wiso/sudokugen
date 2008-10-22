#ifndef TEST_H
#define TEST_H

const char NOME_FILE[] = "data/test";
const char NOME_FILEBUG[] = "sudokubug.txt";
const char SUDOKU_DEFAULT[] = "970304065020506080000000000005802900002040300008705100000000000060208030840109027";

void presentazione();
void creafile();
bool risolviquesto(char sudo[],int &n_finiti);
void dotest(const char*);
void dotest();

#endif
