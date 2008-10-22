#include "cella.h"
#include "candidati.h"

Cella::Cella()
    :Candidati(),  m_value(0), m_settato(false) {}

Cella::Cella(int valore)
    :Candidati(valore), m_value(valore), m_settato(true) 
{
    possibile_n(valore);
}

Cella::Cella(const Cella &old)
    :Candidati(old), m_value(old.m_value), m_settato(old.m_settato)
{}

void Cella::value(int valore)
{
    m_value = valore;
    m_settato = true;
    possibile_n(valore);
}

bool Cella::controlla()
{
    if (!m_settato)
    {
	int n;
	if (determinato(n)) 
	{
	    value(n);
	    m_settato = true;
	    return true;
	}
    }
    return false;
}

void Cella::azzera()
{
    m_value = 0;
    m_settato = 0;
    tutti_possibili();
}

bool Cella::operator==(const Cella& altro) const
{
    return (m_settato == altro.m_settato and m_value == altro.m_value and Candidati::operator==(altro));
}

bool Cella::operator!=(const Cella& altro) const
{
    return !(*this == altro);
}

Cella& Cella::operator=(const Cella& altro)
{
    if (this==&altro) return *this;
    Candidati::operator=(altro);
    m_settato = altro.m_settato;
    m_value = altro.m_value;
    return *this;
}
