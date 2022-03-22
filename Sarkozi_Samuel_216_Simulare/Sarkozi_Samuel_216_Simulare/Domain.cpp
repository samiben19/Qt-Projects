#include "Domain.h"
#include <exception>

using std::exception;

void Abonament::validare()
{
	string eroare = "";
	if (numeAbonat == "")
		eroare += "Nume invalid !\n";
	if (tip == "")
		eroare += "Tip invalid !\n";
	if (pretAbonament <= 0)
		eroare += "Pret invalid !\n";
	if (nrIntrari <= 0)
		eroare += "Numar de intrari invalid !\n";
	if (eroare.size() != 0)
		throw exception(eroare.c_str());
}
