#pragma once
#include "service.h"
#include "tools.h"
#include <algorithm>

using std::back_inserter;
using std::copy_if;
using std::sort;
using std::string;
using std::function;
using std::make_unique;

void Service::Adauga(const string& nume, const string& tip, const double& pret, const string& producator)
{
	Produs p{ nume,tip,pret,producator };
	p.validare();
	undoActions.push_back(make_unique<UndoAdauga>(repo, nume));
	repo.add(p);
	notify();
}

void Service::Modifica(const int& id, const string& nume, const string& tip, const double& pret, const string& producator)
{
	Produs p{ nume,tip,pret,producator };
	p.validare();
	const int n = (int)repo.get_all().size();
	if (id < 1 || id >= n + 1)
		throw ServiceError("ID invalid !\n");
	try 
	{ 
		repo.cauta(p.get_nume()); 
		throw ServiceError("Numele de produs deja existent !\n");
	}
	catch(RepoError)
	{
		const string& nume_id = repo.get_all().at(id - 1).get_nume();
		undoActions.push_back(make_unique<UndoModifica>(repo, nume, repo.get_all().at(id - 1)));
		repo.modif(nume_id, p);
		notify();
	}
}

void Service::Sterge(const int& id)
{
	const int n = (int)repo.get_all().size();
	if (id < 0 || id >= n + 1)
		throw ServiceError("ID invalid !\n");
	const string& nume_id = repo.get_all().at(id - 1).get_nume();
	undoActions.push_back(make_unique<UndoSterge>(repo, repo.get_all().at(id - 1)));
	repo.del(nume_id);
	notify();
}

const Produs& Service::Cauta_nume(const string& nume)
{
	return repo.cauta(nume);
}

vector<Produs> Service::generalFiltr(function<bool(const Produs&)> fct)
{
	const vector<Produs>& toate = repo.get_all();
	vector<Produs> rez;
	copy_if(toate.begin(), toate.end(), back_inserter(rez), fct);
	//for (const auto& el : repo.get_all())
	//	if (fct(el))
	//		rez.push_back(el);
	if (rez.size() == 0)
		throw ServiceError("Nu exista produse care sa satisfaca acest filtru !\n");
	return rez;
}

vector<Produs> Service::Filtrare_pret(double pretMin, double pretMax) 
{
	return generalFiltr([pretMin, pretMax](const Produs& p) noexcept {return p.get_pret() >= pretMin && p.get_pret() <= pretMax;});
}

vector<Produs> Service::Filtrare_nume(const string& sub)
{
	auto sub_low = sub;
	string_toLower(sub_low);
	return generalFiltr([sub_low](const Produs& p) {
		string nume = p.get_nume();
		string_toLower(nume);
		return nume.find(sub_low) != string::npos; });
}

vector<Produs> Service::Filtrare_producator(const string& sub)
{
	auto sub_low = sub;
	string_toLower(sub_low);
	return generalFiltr([sub_low](const Produs& p) {
		string producator = p.get_producator();
		string_toLower(producator);
		return producator.find(sub_low) != string::npos; });
}


//vector<Produs> Service::generalSort(bool(*maiMicF)(const Produs&, const Produs&, bool crescator), bool crescator)
//{
//	if (maiMicF == nullptr) throw ServiceError("Comparare invalida !\n");
//	vector<Produs> v = repo.get_all(); //fac o copie	
//	for (unsigned i = 0; i < v.size(); i++) {
//		for (unsigned j = i + 1; j < v.size(); j++) {
//			if (!maiMicF(v.at(i), v.at(j), crescator)) {
//				//interschimbam
//				std::swap(v.at(i), v.at(j));
//				/*Produs aux = v.at(i);
//				v.at(i) = v.at(j);
//				v.at(j) = aux;*/
//			}
//		}
//	}
//	return v;
//}

vector<Produs> Service::Sorteaza(int crt, bool crescator)
{
	vector<Produs> v = repo.get_all();
	if (crt == 1)
		sort(v.begin(),v.end(), [crescator](const Produs& p1, const Produs& p2)
			{
				if (crescator)
					return p1.get_nume() < p2.get_nume();
				return p1.get_nume() > p2.get_nume();
			});
	else if (crt == 2)
		sort(v.begin(), v.end(), [crescator](const Produs& p1, const Produs& p2) noexcept
			{
				if (crescator)
					return p1.get_pret() < p2.get_pret();
				return p1.get_pret() > p2.get_pret();
			});
	else
		sort(v.begin(), v.end(), [crescator](const Produs& p1, const Produs& p2)
			{
				if (crescator)
					if (p1.get_tip() == p2.get_tip())
						return p1.get_nume() < p2.get_nume();
					else
						return p1.get_tip() < p2.get_tip();
				else
					if (p1.get_tip() == p2.get_tip())
						return p1.get_nume() > p2.get_nume();
					else
						return p1.get_tip() > p2.get_tip();
			});
	return v;
}

map<string, DTO> Service::Raport()
{
	map<string, DTO> dictionar;
	const auto& elems = repo.get_all();
	for (const auto& el : elems)
	{
		if (dictionar.find(el.get_tip()) != dictionar.end())
			dictionar[el.get_tip()].inc_nr();
		else
			dictionar[el.get_tip()] = DTO(el.get_tip());
	}
	return dictionar;
}

/*vector<Produs> Service::Sorteaza(int crt, bool crescator)
{
	if (crt == 1)
		return generalSort([](const Produs& p1, const Produs& p2, bool crescator)
			{
				if (crescator)
					return p1.get_nume() < p2.get_nume();
				return p1.get_nume() > p2.get_nume();
			}, crescator);
	else if (crt == 2)
		return generalSort([](const Produs& p1, const Produs& p2, bool crescator) noexcept
			{
				if (crescator)
					return p1.get_pret() < p2.get_pret();
				return p1.get_pret() > p2.get_pret();
			}, crescator);
	else
		return generalSort([](const Produs& p1, const Produs& p2, bool crescator)
			{
				if (crescator)
					if (p1.get_tip() == p2.get_tip())
						return p1.get_nume() < p2.get_nume();
					else
						return p1.get_tip() < p2.get_tip();
				else
					if (p1.get_tip() == p2.get_tip())
						return p1.get_nume() > p2.get_nume();
					else
						return p1.get_tip() > p2.get_tip();
			}, crescator);
}*/

vector<Produs> Service::GetAll()
{
	return repo.get_all();
}

void Service::Undo()
{
	if (undoActions.empty())
		throw ServiceError("Nu mai se poate face undo !\n");
	undoActions.back()->doUndo();
	undoActions.pop_back();
	notify();
}

void Service::AdaugaCos(const string& nume)
{
	cos.adauga(nume);
	notify();
}

void Service::GolesteCos() noexcept
{
	cos.goleste();
	notify();
}

void Service::GenereazaCos(const int n)
{
	cos.genereaza(n);
	notify();
}

void Service::ExportCos(const string& nume)
{
	if (nume.size() == 0)
		throw ServiceError("Fisier invalid !\n");
	if (cos.get_total() == 0)
		throw ServiceError("Export invalid ! Cosul este gol !\n");
	cos.export_csv(nume);
}

const vector<Produs>& Service::GetAllCos() noexcept
{
	return cos.get_all();
}

const double& Service::GetTotalCos() noexcept
{
	return cos.get_total();
}
