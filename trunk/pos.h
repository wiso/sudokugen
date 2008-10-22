#ifndef POS_H
#define POS_H

#include <utility>

class Pos : public std::pair<int,int>
{
 public:
    int& nx;
    int& ny;
    Pos(): std::pair<int,int>(0,0), nx(first), ny(second) {}
    Pos(int nx, int ny): std::pair<int,int>(nx,ny), nx(first), ny(second) {}
};

#endif //POS
