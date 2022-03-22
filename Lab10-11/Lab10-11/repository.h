#pragma once
#include "domain.h"
#include <vector>
#include <exception>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class RepoError
{
	string msg;
public:
	RepoError(const string& msg) : msg{ msg } {}
	string get_message() {return msg;}
};

class Repo
{
public:
	// Constructori & Destructori
	Repo() = default;
	Repo(const Repo& ot) = delete;
	virtual ~Repo() = default;
	// --------------------------

	// Adauga
	virtual void add(const Produs & p) = 0;

	// Modifica
	virtual void modif(const string & nume, const Produs & p) = 0;

	// Sterge
	virtual void del(const string & nume) = 0;

	// Cauta
	virtual const Produs& cauta(const string & nume) = 0;

	// Returneaza elemente
	virtual vector<Produs> get_all() = 0;
};

class RepositoryMemory : public Repo
{
protected:
	vector<Produs> elems;
public:
	// Constructori & Destructori
	RepositoryMemory() = default;
	RepositoryMemory(const RepositoryMemory& ot) = delete;
	~RepositoryMemory() = default;
	// --------------------------

	// Adauga
	virtual void add(const Produs& p) override;

	// Modifica
	//virtual void modif_id(const int& id, const Produs& p);
	virtual void modif(const string& nume, const Produs& p) override;

	// Sterge
	//virtual void del_id(const int& id);
	virtual void del(const string& nume) override;

	// Cauta
	virtual const Produs& cauta(const string& nume) override;

	// Returneaza elemente
	virtual vector<Produs> get_all() override;
};

class RepositoryFile : public RepositoryMemory
{
private:
	string file_name;
	void LoadFromFile();
	void WriteToFile();
public:
	RepositoryFile(string fName) : RepositoryMemory(), file_name{ fName }{
		LoadFromFile();
	}

	void add(const Produs& p) override {
		LoadFromFile();
		RepositoryMemory::add(p);
		WriteToFile();
	}

	void modif(const string& nume, const Produs& p) override {
		LoadFromFile();
		RepositoryMemory::modif(nume, p);
		WriteToFile();
	}

	void del(const string& nume) override {
		LoadFromFile();
		RepositoryMemory::del(nume);
		WriteToFile();
	}

	const Produs& cauta(const string& nume) override {
		LoadFromFile();
		return RepositoryMemory::cauta(nume);
	}

	vector<Produs> get_all() override {
		LoadFromFile();
		return RepositoryMemory::get_all();
	}
};

class RepoLab : public Repo
{
private:
	unordered_map<string, Produs> elems;
	double prob;
public:
	// Constructori & Destructori
	RepoLab(const double pr) : prob{ pr } {}
	RepoLab(const RepoLab& ot) = delete;
	virtual ~RepoLab() = default;
	// --------------------------

	// Adauga
	void add(const Produs& p) override;

	// Modifica
	void modif(const string& nume, const Produs& p) override;

	// Sterge
	void del(const string& nume) override;;

	// Cauta
	const Produs& cauta(const string& nume) override;

	// Returneaza elemente
	vector<Produs> get_all() override;
};