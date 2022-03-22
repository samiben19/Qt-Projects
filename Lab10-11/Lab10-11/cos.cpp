#include "cos.h"
#include <random>
#include <fstream>
#include <ostream>

using std::ofstream;

void Cos::adauga(const string& nume)
{
	const Produs& deAdaugat = repo.cauta(nume);
	elems_cos.push_back(deAdaugat);
	pret_total += deAdaugat.get_pret();
}

void Cos::goleste() noexcept
{
	elems_cos.clear();
	pret_total = 0;
}

void Cos::genereaza(const int n)
{
	const vector<Produs>& elems_repo = repo.get_all();
	for (int i = 0; i < n; i++)
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> const dist(0, repo.get_all().size() - 1);
		const int rndNr = dist(mt);
		const Produs& deAdaugat = elems_repo.at(rndNr);
		elems_cos.push_back(deAdaugat);
		pret_total += deAdaugat.get_pret();
	}
}

void Cos::export_csv(const string& nume)
{
	unsigned k{ 1 };
	ofstream out(nume + ".csv");
	if (!out.good()) throw RepoError("Fisierul nu a putut fi deschis !\n");
	out << "ID,Nume,Tip,Pret,Producator\n";
	for (const auto& el : elems_cos)
		out << k++ << "," << el.get_nume() << "," << el.get_tip() << "," << el.get_pret() << "," << el.get_producator()<<"\n";
	out << "\nTotal,,," << pret_total;
	out.close();
}

const vector<Produs>& Cos::get_all() noexcept
{
	return elems_cos;
}

const double& Cos::get_total() noexcept
{
	return pret_total;
}
