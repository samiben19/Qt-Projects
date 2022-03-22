#include "Service.h"

void Service::Adauga(const string& nume, const string& tip, const double& pret, const int& intrari)
{
	Abonament p{ nume,tip,pret,intrari };
	p.validare();
	repo.add(p);
}

void Service::Export(double pret)
{
	repo.exporta(pret);
}

vector<Abonament> Service::Filtrare(bool sapt, bool lunar, bool anual)
{
	vector<Abonament> filtrat;
	for (auto el : repo.getall()) {
		if (sapt && el.get_intrari() <= 5)
			filtrat.push_back(el);
		if (lunar && el.get_intrari() > 5 && el.get_intrari() <= 20)
			filtrat.push_back(el);
		if (anual && el.get_intrari() > 20)
			filtrat.push_back(el);
	}
	return filtrat;
}

double Service::GetMax()
{
	return repo.get_max();
}

vector<Abonament> Service::GetAll()
{
	return repo.getall();
}
