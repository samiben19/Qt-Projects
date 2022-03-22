#pragma once
#include <string>

using std::string;

class Abonament
{
private:
	string numeAbonat;
	string tip;
	double pretAbonament;
	int nrIntrari;
public:
	Abonament(const string& n, const string& t, const double& p, const int& nr): numeAbonat{n},tip{t},pretAbonament{p},nrIntrari{nr}{}
	Abonament() = default;

	string get_nume() const {
		return numeAbonat;
	}

	string get_tip() const {
		return tip;
	}

	double get_pret() const {
		return pretAbonament;
	}

	int get_intrari() const {
		return nrIntrari;
	}

	void validare();
};

