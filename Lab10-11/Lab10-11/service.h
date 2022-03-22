#pragma once
#include <string>
#include <functional>
#include <map>
#include <memory>
#include "domain.h"
#include "repository.h"
#include "cos.h"
#include "undo.h"
#include "Observ.h"

using std::map;
using std::string;
using std::function;
using std::unique_ptr;

class ServiceError
{
	string msg;
public:
	ServiceError(const string& msg) : msg{ msg } {}
	string get_message() { return msg; }
};

class Service: public Observable
{
private:
	Repo& repo;
	vector<unique_ptr<ActiuneUndo>>undoActions;

	Cos cos;
	vector<Produs> generalFiltr(function<bool(const Produs&)> fct);
	//vector<Produs> generalSort(bool(*maiMicF)(const Produs&, const Produs&, bool crescator), bool crescator);
public:
	// Constructori & destructori
	Service(Repo& repo) noexcept : repo{ repo }, cos{ repo }{}
	Service(const Service& ot) = delete;
	Service() = default;


	//=-=-=-=-=-= Adauga =-=-=-=-=-= 
	// Creaza un produs de tip Produs, il valideaza si apoi il adauga daca este valid
	// Date de intrare: nume - referinta unui string
	//					tip - referinta unui string
	//					pret - referinta unui double
	//					producator - referinta unui string
	// Preconditii: stringurile sa nu fie vide
	//				pret sa nu fie <= 0
	// Date de iesire: -
	// Exceptii: RepoError daca produs mai exista in lista (numele nu se poate repeta)
	//			 ValidError daca produsul este invalid
	void Adauga(const string& nume, const string& tip, const double& pret, const string& producator);

	//=-=-=-=-=-= Modifica =-=-=-=-=-=
	// Se creaza un produs de tip Produs, se valideaza si se modifica produsul de pe pozitia id cu produsul nou creat 
	// 	   daca id este un indice valid
	// Date de intrare: id - referinta unui int
	//					nume - referinta unui string
	//					tip - referinta unui string
	//					pret - referinta unui double
	//					producator - referinta unui string
	// Preconditii:	stringurile sa nu fie vide
	//				pret > 0
	// 				id >= 1
	// Date de iesire: -
	// Exceptii: RepoError daca id <= 0
	//			 ValidError daca produsul este invalid
	void Modifica(const int& id, const string& nume, const string& tip, const double& pret, const string& producator);

	//=-=-=-=-=-= Sterge =-=-=-=-=-=
	// Se sterge produsul de pe pozitia id 
	// 	   daca id este un indice valid
	// Date de intrare: id - referinta unui int
	// Preconditii:	id >= 1
	// Date de iesire: -
	// Exceptii: RepoError daca id <= 0
	void Sterge(const int& id);

	//=-=-=-=-=-= Cauta =-=-=-=-=-=
	// Returneaza un produs de tip Produs care are ca nume un string dat
	// Date de intrare:	nume - referinta unui string
	// Preconditii:	-
	// Date de iesire: o referinta la un produs de tip Produs
	// Exceptii: RepoError daca nu exista produsul
	const Produs& Cauta_nume(const string& nume);

	//=-=-=-=-=-= Filtrari =-=-=-=-=-=
	// Returneaza un vector de Produse
	// Date de intrare: pretMin, pretMax - double
	//					sub - referinta unui string
	// Preconditii:	-
	// Date de iesire: un vector de Produse cu produsele care satisfac filtrarea
	// Exceptii: ServiceError daca nu exista niciun produs care sa satisfaca filtrarea
	vector<Produs> Filtrare_pret(double pretMin, double pretMax);

	vector<Produs> Filtrare_nume(const string& sub);

	vector<Produs> Filtrare_producator(const string& sub);

	//=-=-=-=-=-= Sortari =-=-=-=-=-=
	// Returneaza un vector de Produse
	// Date de intrare: crt - int
	//					crescator - bool
	// Preconditii:	crt = [1,3]
	//				crt = 1 => sortare dupa nume
	//				crt = 2 => sortare dupa pret
	//				crt = 3 => sortare dupa tip si nume
	//				crescator = true => crescator
	//				crescator = false => descrescator
	// Date de iesire: un vector de Produse cu produsele sortate
	// Exceptii: -
	vector<Produs> Sorteaza(int crt, bool crescator);

	map<string, DTO> Raport();

	//=-=-=-=-=-= GetAll =-=-=-=-=-=
	// Returneaza referinta vectorului de Produse
	// Date de intrare: -
	// Preconditii: -
	// Date de iesire: o referinta la vectorul de Produse
	// Exceptii: -
	vector<Produs> GetAll();

	void Undo();

	void AdaugaCos(const string& nume);

	void GolesteCos() noexcept;

	void GenereazaCos(const int n);

	void ExportCos(const string& nume);

	const vector<Produs>& GetAllCos() noexcept;

	const double& GetTotalCos() noexcept;
};

