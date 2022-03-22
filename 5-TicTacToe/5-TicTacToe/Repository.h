#pragma once
#include "Domain.h"
#include <vector>
#include <fstream>
#include <exception>
#include <sstream>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::exception;
using std::stringstream;
using std::getline;
using std::stoi;

class Repository
{
private:
	vector<Joc> elems;
	string file_name;
	int ultimul;

	void read_from_file() {
		elems.clear();
		ifstream in(file_name);
		if (!in.is_open())
		{
			ofstream first_run(file_name);	// Daca nu exista fisierul la prima rulare, il cream
			if (!first_run.is_open())
				throw exception("Fisierul nu a putut fi deschis !\n");
			first_run.close();
			in.clear();
			in.open(file_name);
		}
		while (!in.eof())
		{
			string linie;
			getline(in, linie);
			if (linie.size() == 0)
				break;

			stringstream ss(linie);
			string word;
			vector<string>words;
			while (getline(ss, word, ';')) {
				words.push_back(word);
			}

			if (words.size() <= 4)
				return;
			int id = stoi(words[0]);
			int dim = stoi(words[1]);
			string tabla = words[2];
			string urmator = words[3];
			string stare = words[4];
			if (id > ultimul)
				ultimul = id;

			Joc j{ id,dim,tabla,urmator,stare };
			elems.push_back(j);
		}
		in.close();
	}
	void write_to_file() {
		ofstream out(file_name);
		if (!out.is_open()) throw exception("Fisierul nu a putut fi deschis !\n");
		for (auto& j : elems)
		{
			out << j.get_id() << ";";
			out << j.get_dim() << ";";
			out << j.get_tabla() << ";";
			out << j.get_urmator() << ";";
			out << j.get_stare() << "\n";
		}
		out.close();
	}
public:
	Repository() = default;
	Repository(string file_name) : file_name{ file_name }, ultimul{ 0 } {
		read_from_file();
	}
	Repository(const Repository& other) = delete;

	void add(const Joc& j) {
		for (auto& el : elems)
			if (el.get_id() == j.get_id())
				throw exception("ID deja existent !\n");
		elems.push_back(j);
		write_to_file();
	}

	void modif(int id, Joc& joc_nou) {
		for (auto& el : elems)
			if (el.get_id() == id)
			{
				el = joc_nou;
				write_to_file();
				return;
			}
		throw exception("ID inexistent !\n");
	}

	const Joc& cauta(const int id) {
		for (const auto& j : elems)
			if (j.get_id() == id)
				return j;
		throw exception("ID inexistent !\n");
	}

	const int ult() {
		return ultimul;
	}

	vector<Joc>& get_all() {
		return elems;
	}

};

