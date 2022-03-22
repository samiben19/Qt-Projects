#pragma once
#include <string>
#include <vector>
#include <exception>

using std::string;
using std::vector;
using std::exception;

// Clasa Task are toate datele necesare pentru a retine un task
//		Parametrii: id - numar intreg
//					descriere - string
//					programatori - vector de stringuri
//					stare - string
//		functia validare, verifica ca datele sa fie corecte, adica
//			id >= 1
//			descriere diferit de sirul vid
//			in vectorul de programatori sa existe cel putin 1 si maxim 4 programatori cu nume diferite de sirul vid
//			stare sa fie unul dintre cuvintele: Open, Close sau Inprogress
class Task
{
private:
	int id;
	string descriere;
	vector<string>programatori;
	string stare;
public:
	Task(int id, string descriere, vector<string>programatori, string stare) :id{ id }, descriere{ descriere }, programatori{ programatori }, stare{ stare }{}
	// Returneaza id-ul taskului
	int get_id() const { return id; }
	// Returneaza descrierea taskului
	const string& get_descriere() const { return descriere; }
	// Returneaza vectorul de programatori al taskului
 	const vector<string>& get_programatori() const { return programatori; }
	// Returneaza starea taskului
	const string& get_stare() const { return stare; }

	// Seteaza starea taskului cu stare_noua
	void set_stare(string stare_noua) { stare = stare_noua; }

	// Verifica daca un task este valid, adica
	//			id >= 1
	//			descriere diferit de sirul vid
	//			in vectorul de programatori sa existe cel putin 1 si maxim 4 programatori cu nume diferite de sirul vid
	//			stare sa fie unul dintre cuvintele: Open, Close sau Inprogress
	void validare() const {
		string eroare = "";
		if (id <= 0)
			eroare += "ID invalid !\n";
		if (descriere == "")
			eroare += "Descriere invalida !\n";
		if (programatori.size() <= 0 || programatori.size() >= 5)
			eroare += "Numar invalid de programatori !\n";
		else
			for(auto& pr:programatori)
				if (pr == "")
				{
					eroare += "Numele unui programator este invalid !\n";
					break;
;				}
		if (stare != "Open" && stare != "Inprogress" && stare != "Close")
			eroare += "Stare invalida ! (Atentie, prima litera trebuie sa fie majuscula)\n";
		if (eroare.size() != 0)
			throw exception(eroare.c_str());
	}
};

