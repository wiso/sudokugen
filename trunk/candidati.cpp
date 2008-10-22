#include <iostream>
#include "candidati.h"

Candidati::Candidati()
    :max(geometria::MAX)
{
    m_data = new bool[max];
    tutti_possibili();
}

Candidati::Candidati(int n)
    :max(geometria::MAX)
{
    m_data = new bool[max];
    possibile_n(n);
}

Candidati::Candidati(const Candidati &old)
    :max(old.max)
{
    m_data = new bool[max];
    for (int i=0;i<max;++i)
	m_data[i] = old.m_data[i];
}

Candidati::~Candidati()
{
    delete[] m_data;
}

bool Candidati::determinato(int &n) const
{
    int veri = 0;
    for (int i=0;i<max;++i)
    {
	if (m_data[i])
	{
	    ++veri;
	    if (veri>1) {n = 0; return false;}
	    n = i+1;
	}
    }
    if (veri==1) return true;
    else 
    {
	n = -1;
	return false;
    }
}

bool Candidati::determinato() const
{
    int veri = 0;
    for (int i=0;i<max;++i)
    {
	if (m_data[i]) ++veri;
//	if (veri>1) return false;
    }
    if (veri==1) return true;
    return false;
//    return true;
}

int Candidati::quanti() const
{
    int veri = 0;
    for (int i=0;i<max;++i)
	if (m_data[i]) veri++;
    return veri;
}

void Candidati::possibile(int n,bool in)
{
    m_data[n-1] = in;
}

bool Candidati::togli(int n)
{
    if (possibile(n))
    {
	possibile(n,false);
	return true;
    }
    else return false;
}

void Candidati::possibile_n(int n)
{
    for (int i=1;i<=max;possibile(i++,false));
    possibile(n,true);
}

void Candidati::tutti_possibili()
{
    for (int i=1;i<=max;++i)
	possibile(i,true);
}

bool Candidati::coppia(int &a, int &b) const
{
    int *temp = new int[max];
    int veri = 0;
    for (int i=0;i<max;++i)
	if (m_data[i]) 	
	    temp[veri++] = i+1;	    
    a = temp[0];
    b = temp[1];
    delete[] temp;
    if (veri==2) return true;
    else return false;    
}

int Candidati::quali(int vet[]) const
{
    int veri = 0;
    for (int i=0;i<max;++i)
	if (m_data[i]) 	
	    vet[veri++] = i+1;	    
    for (int i=veri;i<max;++i)
	vet[i] = 0;
    return veri;
}


bool Candidati::operator==(const Candidati& altro) const
{
    bool temp = true;
    for (int i=0;i<max;++i)
	if (m_data[i] != altro.m_data[i]) temp = false;
    return temp;	
}

Candidati& Candidati::operator=(const Candidati& altro)
{
    if (this == &altro) return *this;
    for (int i=0;i<max;++i)
	m_data[i] = altro.m_data[i];
    return *this;
}
