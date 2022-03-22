#pragma once
#include <vector>
#include "repository.h"
#include "domain.h"

using std::vector;

class Cos
{
private:
	Repo& repo;
	vector<Produs>elems_cos;
	double pret_total;
public:
	Cos(Repo& r) noexcept : repo{ r }, pret_total{ 0 }{}
	void adauga(const string& nume);
	void goleste() noexcept;
	void genereaza(const int n);
	void export_csv(const string& nume);

	const vector<Produs>& get_all() noexcept;
	const double& get_total() noexcept;
};

