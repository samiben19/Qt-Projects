#pragma once
#include "domain.h"
#include <string>

//Produs& Produs::operator=(const Produs& ot)
//{
//	if (this == &ot) {
//		return *this;// protect against self-assignment (a = a)
//	}
//	this->nume = ot.nume;
//	this->tip = ot.tip;
//	this->pret = ot.pret;
//	this->producator = ot.producator;
//	return *this;
//
//}

void Produs::validare() const
{
	string eroare = "";
	if (nume == "")
		eroare += "Nume invalid !\n";
	if (tip == "")
		eroare += "Tip invalid !\n";
	if (pret <= 0)
		eroare += "Pret invalid !\n";
	if (producator == "")
		eroare += "Producator invalid !\n";

	if (eroare.size() != 0)
		throw ValidError(eroare);
}

void DTO::inc_nr()
{
	nr++;
}

int DTO::get_nr() const
{
	return nr;
}
