#pragma once
#include "repository.h"
#include "tools.h"
#include <fstream>
#include <exception>
#include <algorithm>
#include <random>

using std::find_if;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::exception;

void RepositoryMemory::add(const Produs& p)
{
	auto it = find_if(elems.begin(), elems.end(), [p](const Produs& el) { return iequals(p.get_nume(), el.get_nume()); });
	if (it != elems.end())
		throw RepoError("Produsul " + p.get_nume() + " exista deja !\n");
	elems.push_back(p);
	/*for (const auto& el : elems)
		if (iequals(el.get_nume(), p.get_nume()))
			throw RepoError("Produsul " + p.get_nume() + " exista deja !\n");
	elems.push_back(p);*/
}

//void Repository::modif_id(const int& id, const Produs& p)
//{
//	const int n = elems.size();
//	if (id < 0 || id >= n)
//		throw RepoError("ID invalid !\n");
//	elems.at(id) = p;
//}

void RepositoryMemory::modif(const string& nume, const Produs& p)
{
	cauta(nume);
	std::replace_if(elems.begin(), elems.end(), [nume](const Produs& p) {return p.get_nume() == nume; }, p);
}

//void Repository::del_id(const int& id)
//{
//	const int n = elems.size();
//	if (id < 0 || id >= n)
//		throw RepoError("ID invalid !\n");
//	elems.erase(elems.begin() + id);
//}

void RepositoryMemory::del(const string& nume)
{
	auto it = remove_if(elems.begin(), elems.end(), [nume](const Produs& p) {return p.get_nume() == nume; });
	if (it == elems.end())
		throw RepoError("Produs inexistent !\n");
	elems.erase(it);
}

const Produs& RepositoryMemory::cauta(const string& nume)
{
	auto it = find_if(elems.begin(), elems.end(), [nume](const Produs& p) { return iequals(p.get_nume(), nume); });
	if (it == elems.end())
		throw RepoError("Produs inexistent !\n");
	return *it;
	/*for (const auto& el : elems)
		if (iequals(el.get_nume(),nume))
			return el;
	throw RepoError("Produs inexistent !\n");*/
}

vector<Produs> RepositoryMemory::get_all() { return elems; }

void RepositoryFile::LoadFromFile()
{
	elems.clear();
	ifstream in(file_name);
	if (!in.is_open())
	{
		ofstream first_run(file_name);
		if (!first_run.is_open()) throw RepoError("Fisierul nu a putut fi deschis !\n");
		first_run.close();
		in.clear();
		in.open(file_name);
	}
	// Fiecare camp pe linie noua
	while (!in.eof())
	{
		string nume;
		getline(in,nume);
		if (nume.size() == 0) 
			continue;
		string tip;
		getline(in, tip);
		if (tip.size() == 0)
			continue;
		string buffer;
		getline(in, buffer);
		if (buffer.size() == 0)
			continue;
		int pct{ 0 };
		bool ok = true;
		for (const char& c : buffer)
		{
			if (!isdigit(c))
			{
				if (ispunct(c))
				{
					pct++;
					if (pct >= 2)
					{
						ok = false;
						break;
					}
				}
				else
				{
					ok = false;
					break;
				}
			}
		}
		if (!ok)
			continue;
		double pret{ 0 };
		pret = std::stod(buffer);
		if (pret <= 0)
			continue;
		string producator;
		getline(in,producator);
		if (producator.size() == 0)
			continue;

		Produs p{ nume, tip, pret, producator };
		RepositoryMemory::add(p);
	}
	in.close();
}

void RepositoryFile::WriteToFile()
{
	ofstream out(file_name);
	if (!out.is_open()) throw RepoError("Fisierul nu a putut fi deschis !\n");
	// Fiecare camp pe linie noua
	for (auto& p : elems)
	{
		out << p.get_nume() << '\n';
		out << p.get_tip() << '\n';
		out << p.get_pret() << '\n';
		out << p.get_producator() << '\n';
	}
	out.close();
}

void RepoLab::add(const Produs& p)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, 101);
	const int rndNr = dist(mt);
	if (rndNr < prob * 100)
		throw RepoError("Ghinion !\n");
	if (elems.find(p.get_nume()) != elems.end())
		throw RepoError("Produsul " + p.get_nume() + " exista deja !\n");
	elems[p.get_nume()] = p;
}

void RepoLab::modif(const string& nume, const Produs& p)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, 101);
	const int rndNr = dist(mt);
	if (rndNr < prob * 100)
		throw RepoError("Ghinion !\n");
	if (elems.find(nume) == elems.end())
		throw RepoError("Produs inexistent !\n");
	elems.erase(nume);
	elems[p.get_nume()] = p;
}

void RepoLab::del(const string& nume)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, 101);
	const int rndNr = dist(mt);
	if (rndNr < prob * 100)
		throw RepoError("Ghinion !\n");
	if (elems.find(nume) == elems.end())
		throw RepoError("Produs inexistent !\n");
	elems.erase(nume);
}

const Produs& RepoLab::cauta(const string& nume)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, 101);
	const int rndNr = dist(mt);
	if (rndNr < prob * 100)
		throw RepoError("Ghinion !\n");
	if (elems.find(nume) == elems.end())
		throw RepoError("Produs inexistent !\n");
	return (*elems.find(nume)).second;
}

vector<Produs> RepoLab::get_all()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, 101);
	const int rndNr = dist(mt);
	if (rndNr < prob * 100)
		throw RepoError("Ghinion !\n");
	vector<Produs> elems_vect;
	for (auto& el : elems)
		elems_vect.push_back(el.second);
	return elems_vect;
}
