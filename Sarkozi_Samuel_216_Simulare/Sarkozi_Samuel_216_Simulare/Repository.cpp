#include "Repository.h"
#include <fstream>
#include <exception>

using std::ofstream;
using std::ifstream;
using std::exception;
using std::find_if;

void Repository::add(const Abonament& p)
{
	auto it = find_if(elems.begin(), elems.end(), [p](const Abonament& a) {return p.get_nume() == a.get_nume(); });
	if (it != elems.end())
		throw exception("Abonament deja existent");
	if (p.get_pret() > max)
		max = p.get_pret();
	elems.push_back(p);
}

void Repository::exporta(double pret)
{
	ofstream out{ "out.txt" };
	if (!out.good()) throw exception("Fisierul nu a putut fi creat !\n");
	out << "Nume, Tip, Pret, Numar intrari\n";
	for (const auto& el : elems)
		if(el.get_pret() <= pret)
			out << el.get_nume() << ", " << el.get_tip() << ", " << el.get_pret() << ", " << el.get_intrari() << "\n";
	out.close();
}

vector<Abonament> Repository::getall()
{
	return elems;
}

double Repository::get_max()
{
	return max;
}
