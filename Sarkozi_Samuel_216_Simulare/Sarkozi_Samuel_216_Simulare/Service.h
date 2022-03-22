#pragma once
#include "Repository.h"

class Service
{
private:
	Repository& repo;

public:
	Service(Repository& r): repo{r}{}
	Service(const Service& ot) = delete;
	Service() = default;

	void Adauga(const string& nume, const string& tip, const double& pret, const int& intrari);
	void Export(double pret);
	vector<Abonament> Filtrare(bool sapt, bool lunar, bool anual);
	double GetMax();
	vector<Abonament> GetAll();
};

