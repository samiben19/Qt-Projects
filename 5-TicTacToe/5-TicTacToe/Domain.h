#pragma once
#include <string>
#include <exception>

using std::string;
using std::exception;

class Joc
{
private:
	int id;
	int dim;
	string tabla;
	string urmator;
	string stare;
public:
	Joc(int id, int dim, string tabla, string urmator, string stare) :id{ id }, dim{ dim }, tabla{ tabla }, urmator{ urmator }, stare{ stare }{}

	int get_id() const { return id; }
	int get_dim() const { return dim; }
	const string& get_tabla() const { return tabla; }
	const string& get_urmator() const { return urmator; }
	const string& get_stare() const { return stare; }

	void set_dim(int dim_nou) { dim = dim_nou; }
	void set_tabla(string tabla_noua) { tabla = tabla_noua; }
	void set_urmator(string urmator_nou) { urmator = urmator_nou; }
	void set_stare(string stare_noua) { stare = stare_noua; }

	void validare() {
		string eroare = "";
		if (id <= 0)
			eroare += "ID invalid !\n";
		if (dim <= 2 || dim >= 6)
			eroare += "Dimensiune invalida !\n";
		if (tabla.size() != dim * dim)
			eroare += "Tabla invalida !\n";
		else
			for (auto& el : tabla)
				if (el != 'X' && el != 'O' && el != '-')
				{
					eroare += "Tabla contine caractere invalide ! (Atentie, doar majuscule !)\n";
					break;
				}
		if (urmator != "X" && urmator != "O")
			eroare += "Jucatorul care urmeaza sa mute invalid ! (Atentie, doar majuscule !)\n";
		
		if(stare != "Neinceput" && stare != "In derulare" && stare != "Terminat")
			eroare += "Stare invalida (Atentie, prima litera trebuie sa fie majuscula !\n";
		
		if (eroare.size() != 0)
			throw exception(eroare.c_str());
	}
};

