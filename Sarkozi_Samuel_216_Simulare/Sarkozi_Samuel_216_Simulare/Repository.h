#pragma once
#include "Domain.h"
#include <vector>

using std::vector;

class Repository
{
private:
	vector<Abonament> elems;
	double max;
public:
	Repository() : max{ 0 } {};
	Repository(const Repository& ot) = delete;
	~Repository() = default;


	void add(const Abonament& p);
	void exporta(double pret);
	double get_max();
	vector<Abonament> getall();
};

