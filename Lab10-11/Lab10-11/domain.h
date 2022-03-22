#pragma once
#include <string>
#include <iostream>

using std::string;

class ValidError
{
	string msg;
public:
	ValidError(const string& msg) : msg{ msg } {}
	string get_message() { return msg; }
};

class Produs
{
private:
	string nume;
	string tip;
	double pret;
	string producator;
public:
	// Constructori
	Produs(const string& nume, const string& tip, const double& pret, const string& producator) : nume{ nume }, tip{ tip }, pret{ pret }, producator{ producator }{
	}
	Produs() = default;
	Produs(const Produs& ot) :nume{ ot.nume }, tip{ ot.tip }, pret{ ot.pret }, producator{ ot.producator }{/*std::cout << "COPIE !!\n";*/ };
	//Produs& operator=(const Produs& ot);


	void validare() const;

	string get_nume() const {
		return nume;
	}
	string get_tip() const {
		return tip;
	}
	double get_pret() const noexcept {
		return pret;
	}
	string get_producator() const {
		return producator;
	}


	void set_nume(const string& nume_nou) {
		nume = nume_nou;
	}
	void set_tip(const string& tip_nou) {
		tip = tip_nou;
	}
	void set_pret(const double& pret_nou) noexcept{
		pret = pret_nou;
	}
	void set_producator(const string& producator_nou) {
		producator = producator_nou;
	}
};

class DTO
{
private:
	string tip;
	int nr;
public:
	DTO() : tip{ "" }, nr{ 0 }{}
	DTO(const string& tip) : tip{ tip }, nr{ 1 }{}
	void inc_nr();
	int get_nr() const;
};
