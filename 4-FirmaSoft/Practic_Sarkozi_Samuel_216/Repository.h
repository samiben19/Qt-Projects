#pragma once
#include "Domain.h"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::stoi;

// Clasa repository care se ocupa de citirea si scrierea in fisier
//		Date de intrare: file_name - string, reprezentand numele fisierului
class Repository
{
private:
	vector<Task> elems;	// vectorul de Taskuri
	string file_name;	// numele fisierului
	
	// Functia care realizeaza citirea din fisier si adauga Taskurile in memorie, intr-un vector de taskuri
	void read_from_file();
	// Functia care realizeaza scrierea in fisierul cu numele file_name
	void write_to_file();
public:
	Repository(string file_name) :file_name{ file_name } {
		read_from_file();
	}

	Repository() = default;
 	Repository(const Repository& ot) = delete;
	
	// Functia incearca sa adauge un task in vector si in fisier, daca nu mai exista un task cu acelasi id
		//	Date de intrare: t, un task de tip Task
		//	Date de iesire:	nimic daca s-a adaugat cu succes
		//					se ridica exceptie daca mai exista un task cu acelasi id
	void add(const Task& t);

	// Functia incearca sa modifice starea unui task cu id-ul id, daca exista
		//	Date de intrare: id - un numar natural strict pozitiv reprezentand id-ul unui task ce urmeaza sa fie modificat
		//					stare - string, reprezentand noua stare cu care se actualizeaza taskul care are id-ul id
		//	Date de iesire:	nimic daca s-a modificat cu succes
		//					se ridica exceptie daca nu exista un task cu acel id
	void modif(int id, string stare);

	// Functia returneaza taskul cu un anumit id
		//	Date de intrare: id - un numar natural strict pozitiv reprezentand id-ul unui task ce urmeaza sa fie modificat
		//	Date de iesire:	un task de tip Task daca s-a gasit task cu id-ul id
		//					se ridica exceptie daca nu exista un task cu acel id
	const Task& cauta(const int id);

	// Functia returneaza vectorul de taskuri
		//	Date de intrare: -
		//	Date de iesire: un vector reprezentand vectorul tuturor taskurilor din fisier
	vector<Task>& get_all();
};

