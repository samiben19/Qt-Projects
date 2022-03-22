#pragma once
#include "Repository.h"
#include "Observer.h"
#include <algorithm>

class Service : public Observable
{
private:
	Repository& repo;
public:
	Service(Repository& repo) :repo{ repo } {}
	Service() = default;
	Service(const Service& ot) = delete;

	//	Functia primesete datele necesare crearii unui task, il creaza si incearca sa-l adauge in vector si in fisier, daca nu mai exista un task cu acelasi id
	//	Date de intrare:	id - numar intreg
	//						descriere - string
	//						programatori - vector de stringuri
	//						stare - string
	// 
	// 	Preconditii:	id >= 1
	//					descriere - diferit de sirul vid
	//					programatori - sa existe cel putin 1 si maxim 4 programatori cu nume diferite de sirul vid
	//					stare - sa fie unul dintre cuvintele: Open, Close sau Inprogress
	//	Date de iesire:	nimic daca s-a adaugat cu succes
	//					se ridica exceptie daca datele de intrare nu sunt valide
	//					se ridica exceptie din repository daca mai exista un task cu acelasi id
	void Adauga(int id, string descriere, vector<string>programatori, string stare);

	//	Functia primesete datele necesare crearii unui task, il creaza si incearca sa modifice starea unui task in vector si in fisier, daca exista un task cu acelasi id
	//	Date de intrare:	id - numar intreg
	//						stare_noua - string
	// 	Preconditii:	id >= 1
	//					stare_noua - sa fie unul dintre cuvintele: Open, Close sau Inprogress
	//	Date de iesire:	nimic daca s-a modificat cu succes
	//					se ridica exceptie din repository daca datele de intrare nu sunt valide
	void Modifica_stare(int id, string stare_noua);

	// Functia returneaza taskul cu un anumit id
		//	Date de intrare: id - un numar natural strict pozitiv reprezentand id-ul unui task ce urmeaza sa fie modificat
		//	Date de iesire:	un task de tip Task, daca s-a gasit task cu id-ul id
		//					se ridica exceptie daca id <= 0
		//					se ridica exceptie din repository daca nu exista un task cu acel id
	const Task& Cauta(const int id);

	// Functia returneaza un vector filtrat cu anumite taskuri
		//	Date de intrare: mod - string
		//				     sub - string
		//	Preconditii: mod sa fie "programatori" sau "stare"
		//	Date de iesire: daca mod = "programatori" se returneaza un vector care contine toate taskurile in care apar programatorii ai caror nume contin
		//						substringul sub
		//					daca mod = "stare" se returneaza un vector care contine toate taskurile care au starea sub
	vector<Task> Search(const string& mod, const string& sub);

	// Functia returneaza vectorul de taskuri
		//	Date de intrare: -
		//	Date de iesire: un vector reprezentand vectorul tuturor taskurilor din fisier
	vector<Task> GetAll();
};

