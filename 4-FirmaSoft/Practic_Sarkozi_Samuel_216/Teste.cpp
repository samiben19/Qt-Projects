#include "Teste.h"

void Teste::clearFile()
{
	ofstream t("teste.txt");
	t << "2;C#;Sami;Raul;Inprogress\n";
	t.close();
}

void Teste::testService()
{
	clearFile();
	Repository repo{ "teste.txt" };
	Service srv{ repo };

	// Domain
	int id = 1;
	string descriere = "C++";
	vector<string>programatori{ "Sami" };
	string stare = "Open";
	Task t1{ id,descriere,programatori,stare };

	assert(t1.get_id() == 1);
	assert(t1.get_descriere() == "C++");
	assert(t1.get_programatori().size() == 1);
	assert(t1.get_programatori()[0] == "Sami");
	assert(t1.get_stare() == "Open");

	// Adaugarea
	assert(srv.GetAll().size() == 1);

	srv.Adauga(id,descriere,programatori,stare);

	assert(srv.GetAll().size() == 2);

	try {
		srv.Adauga(id, descriere, programatori, stare); assert(false);
	}
	catch (exception& ex) { assert(strcmp(ex.what(), "ID deja existent !\n") == 0); }

	try {
		srv.Adauga(-1, "", vector<string>{}, ""); assert(false);
	}
	catch (exception& ex) { assert(strcmp(ex.what(), "ID invalid !\nDescriere invalida !\nNumar invalid de programatori !\nStare invalida ! (Atentie, prima litera trebuie sa fie majuscula)\n") == 0); }

	try {
		srv.Adauga(-1, "", vector<string>{""}, ""); assert(false);
	}
	catch (exception& ex) { assert(strcmp(ex.what(), "ID invalid !\nDescriere invalida !\nNumele unui programator este invalid !\nStare invalida ! (Atentie, prima litera trebuie sa fie majuscula)\n") == 0); }

	// Modifica
	assert(srv.GetAll()[1].get_stare() == "Open");
	srv.Modifica_stare(1, "Close");
	assert(srv.GetAll()[1].get_stare() == "Close");

	try {
		srv.Modifica_stare(1, "Closeee");
	}
	catch (exception& ex) {
		assert(strcmp(ex.what(), "Stare invalida ! (Atentie, prima litera trebuie sa fie majuscula)\n") == 0);
	}

	try {
		srv.Modifica_stare(0, "Close");
	}
	catch (exception& ex) {
		assert(strcmp(ex.what(), "ID invalid !\n") == 0);
	}

	// Cauta
	auto gasit = srv.Cauta(1);
	assert(gasit.get_id() == 1);
	assert(gasit.get_descriere() == "C++");
	assert(gasit.get_programatori().size() == 1);
	assert(gasit.get_programatori()[0] == "Sami");
	assert(gasit.get_stare() == "Close");

	// Search
	auto filtrati1 = srv.Search("programatori", "Sami");
	assert(filtrati1.size() == 2);

	auto filtrati2 = srv.Search("stare", "Open");
	assert(filtrati2.size() == 0);

	auto filtrati3 = srv.Search("stare", "Close");
	assert(filtrati3.size() == 1);

	auto filtrati4 = srv.Search("stare", "Inprogress");
	assert(filtrati4.size() == 1);

	auto filtrati5 = srv.Search("programatori", "nimeni");
	assert(filtrati5.size() == 0);
}

void Teste::first_time() {
	remove("teste.txt");
	Repository repo{ "teste.txt" };
}

void Teste::testAll()
{
	testService();
	first_time();
	remove("teste.txt");
}
