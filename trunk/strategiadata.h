#ifndef STRATEGIADATA_H
#define STRATEGIADATA_H

#include <map>
#include <string>

class StrategiaData
{
    char *name;
    int n;
};


typedef std::map<const int, const std::string> map_t;
const map_t::value_type valori_nomi[] = 
   { 
          map_t::value_type(0,"controlla"), 
          map_t::value_type(1,"elimina"), 
          map_t::value_type(2,"singles"),
	  map_t::value_type(3,"nackedpair"),
	  map_t::value_type(4,"hiddenpair"),
	  map_t::value_type(5,"pointingpair"),
	  map_t::value_type(6,"boxreduction"),
	  map_t::value_type(7,"xwing")
   };
   
extern map_t nomestrategia;
   
typedef std::map<int, int> Strategie;

#endif //STRATEGIADATA_H
