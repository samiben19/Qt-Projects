#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "tests.h"
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "tools.h"
#include <assert.h>
#include <fstream>
#include <vector>

void Tests::testDomain()
{
	Produs p1{ "Lenovo Legion 5", "Gaming", 3999.99, "Lenovo" };
	p1.validare();

	assert(!iequals("Rac", "Car"));
	assert(p1.get_nume() == "Lenovo Legion 5");
	assert(p1.get_tip() == "Gaming");
	assert(p1.get_pret() == 3999.99);
	assert(p1.get_producator() == "Lenovo");

	p1.set_nume("");

	try { p1.validare(); }
		//assert(false);
	catch (ValidError& ve) { assert(ve.get_message() == "Nume invalid !\n"); }
	p1.set_tip("");
	p1.set_pret(0);
	p1.set_producator("");
	try { p1.validare(); }
		//assert(false);
	catch (ValidError& ve) { assert(ve.get_message() == "Nume invalid !\nTip invalid !\nPret invalid !\nProducator invalid !\n"); }
}

void Tests::testRepo()
{
	RepositoryMemory repo;
	Produs p1{ "Lenovo Legion 5", "Gaming", 3999.99, "Lenovo" };
	// Adaugare
	repo.add(p1);
	const auto& produse = repo.get_all();
	assert(produse.size() == 1);
	assert(produse.at(0).get_nume() == "Lenovo Legion 5");

	try { repo.add(p1); }
		//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Produsul Lenovo Legion 5 exista deja !\n"); }

	// Modificare
	try { repo.modif("cevadsfsdf", Produs{ "ceva","aa",123,"da" }); }
		//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Produs inexistent !\n"); }

	repo.modif("Lenovo Legion 5", Produs{ "Asus K50IN","Office",500,"Asus" });
	const auto& produse2 = repo.get_all();
	assert(produse2.at(0).get_nume() == "Asus K50IN");
	assert(produse2.at(0).get_tip() == "Office");
	assert(produse2.at(0).get_pret() == 500);
	assert(produse2.at(0).get_producator() == "Asus");

	// Stergere
	try { repo.del("cevadasda"); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Produs inexistent !\n"); }

	repo.del("Asus K50IN");
	const auto& produse3 = repo.get_all();
	assert(produse3.size() == 0);
}

void Tests::testCauta()
{
	RepositoryMemory repo;
	Service srv{ repo };

	srv.Adauga("Lenovo Legion 5", "Gaming", 3999.99, "Lenovo");
	const Produs& gasit = srv.Cauta_nume("lenovo legion 5");
	assert(gasit.get_nume() == "Lenovo Legion 5");
	assert(gasit.get_tip() == "Gaming");
	assert(gasit.get_pret() == 3999.99);
	assert(gasit.get_producator() == "Lenovo");

	try { srv.Cauta_nume("ceva"); }
		//assert(false)
	catch (RepoError& re) { assert(re.get_message() == "Produs inexistent !\n"); }
}

void Tests::testFiltrare()
{
	RepositoryMemory repo;
	Service srv{ repo };

	srv.Adauga("Lenovo Legion 5", "Gaming", 4599.99, "Lenovo");
	srv.Adauga("HP Pavilion", "Gaming", 2999.99, "HP");
	srv.Adauga("Asus TUF F15", "Gaming", 3599.99, "Asus");
	srv.Adauga("Dell Inspiron 3793", "Home", 2699.99, "Dell");
	srv.Adauga("Asus ROG Strix G15", "Gaming", 5999.99, "Asus");
	srv.Adauga("HP 250 G7", "Office", 3999.99, "HP");
	srv.Adauga("Lenovo Legion C7", "Grafica", 9499.99, "Lenovo");
	srv.Adauga("Lenovo IdeaPad 3", "Multimedia", 3299.99, "Lenovo");
	srv.Adauga("Dell Latitude 3510", "Office", 3599.99, "Dell");
	srv.Adauga("Asus K50IN", "Office", 499.99, "Asus");
	srv.Adauga("Acer Aspire 3", "Multimedia", 3199.99, "Acer");

	const auto& produse = srv.Filtrare_pret(300,3000);
	assert(produse.size() == 3);

	const auto& produse2 = srv.Filtrare_nume("on");
	assert(produse2.size() == 4);

	const auto& produse3 = srv.Filtrare_producator("HP");
	assert(produse3.size() == 2);

	try { srv.Filtrare_producator("AVION"); }
		//assert(false)
	catch (ServiceError& se) { assert(se.get_message() == "Nu exista produse care sa satisfaca acest filtru !\n"); }
}

void Tests::testSortare()
{
	RepositoryMemory repo;
	Service srv{ repo };

	srv.Adauga("Lenovo Legion 5", "Gaming", 4599.99, "Lenovo");
	srv.Adauga("HP Pavilion", "Gaming", 2999.99, "HP");
	srv.Adauga("Asus TUF F15", "Gaming", 3599.99, "Asus");
	srv.Adauga("Dell Inspiron 3793", "Home", 2699.99, "Dell");
	srv.Adauga("Asus ROG Strix G15", "Gaming", 5999.99, "Asus");
	srv.Adauga("HP 250 G7", "Office", 3999.99, "HP");
	srv.Adauga("Lenovo Legion C7", "Grafica", 9499.99, "Lenovo");
	srv.Adauga("Lenovo IdeaPad 3", "Multimedia", 3299.99, "Lenovo");
	srv.Adauga("Dell Latitude 3510", "Office", 3599.99, "Dell");
	srv.Adauga("Asus K50IN", "Office", 499.99, "Asus");
	srv.Adauga("Acer Aspire 3", "Multimedia", 3199.99, "Acer");

	const auto& produse1 = srv.Sorteaza(1, true);
	assert(produse1.at(0).get_nume() == "Acer Aspire 3");
	const auto& produse2 = srv.Sorteaza(2, true);
	assert(produse2.at(0).get_nume() == "Asus K50IN");
	const auto& produse3 = srv.Sorteaza(3, true);
	assert(produse3.at(0).get_nume() == "Asus ROG Strix G15");
	const auto& produse4 = srv.Sorteaza(1, false);
	assert(produse4.at(0).get_nume() == "Lenovo Legion C7");
	const auto& produse5 = srv.Sorteaza(2, false);
	assert(produse5.at(0).get_nume() == "Lenovo Legion C7");
	const auto& produse6 = srv.Sorteaza(3, false);
	assert(produse6.at(0).get_nume() == "HP 250 G7");

}

void Tests::testService()
{
	RepositoryMemory repo;
	Service srv{ repo };

	// Adaugare
	assert(srv.GetAll().size() == 0);
	srv.Adauga("Lenovo Legion 5", "Gaming", 3999.99, "Lenovo");
	const auto& produse = srv.GetAll();
	assert(produse.size() == 1);
	assert(produse.at(0).get_nume() == "Lenovo Legion 5");
	assert(produse.at(0).get_tip() == "Gaming");
	assert(produse.at(0).get_pret() == 3999.99);
	assert(produse.at(0).get_producator() == "Lenovo");

	try { srv.Adauga("", "", 0, ""); }
		//assert(false);
	catch (ValidError& ve) { assert(ve.get_message() == "Nume invalid !\nTip invalid !\nPret invalid !\nProducator invalid !\n"); }

	try { srv.Adauga("Lenovo Legion 5", "Gaming", 3999.99, "Lenovo"); }
		//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Produsul Lenovo Legion 5 exista deja !\n"); }

	// Modifica
	srv.Modifica(1, "Asus K50IN", "Office", 500, "Asus");
	const auto& produse2 = srv.GetAll();
	assert(produse2.at(0).get_nume() == "Asus K50IN");
	assert(produse2.at(0).get_tip() == "Office");
	assert(produse2.at(0).get_pret() == 500);
	assert(produse2.at(0).get_producator() == "Asus");
	try { srv.Modifica(10, "Asus K50IN", "Office", 500, "Asus"); }
	catch (ServiceError& se) { assert(se.get_message() == "ID invalid !\n"); }

	try { srv.Modifica(1, "Asus K50IN", "Altceva", 123, "Asus"); }
		//asert(false);
	catch (ServiceError& se) { assert(se.get_message() == "Numele de produs deja existent !\n"); }

	// Stergere
	srv.Adauga("Dell Inspiron 3793", "Home", 2699.99, "Dell");
	try { srv.Sterge(10); }
	catch (ServiceError& se) { assert(se.get_message() == "ID invalid !\n"); }
	assert(srv.GetAll().size() == 2);
	srv.Sterge(1);
	assert(srv.GetAll().size() == 1);
	srv.Sterge(1);
	assert(srv.GetAll().size() == 0);

	// Cauta
	testCauta();
	// Filtrare
	testFiltrare();

	// Sortare
	testSortare();
}

void Tests::testCos()
{
	RepositoryMemory repo;
	Service srv{ repo };

	srv.Adauga("Lenovo Legion 5", "Gaming", 4599.99, "Lenovo");
	srv.Adauga("HP Pavilion", "Gaming", 2999.99, "HP");
	srv.Adauga("Asus TUF F15", "Gaming", 3599.99, "Asus");
	srv.Adauga("Dell Inspiron 3793", "Home", 2699.99, "Dell");
	srv.Adauga("Asus ROG Strix G15", "Gaming", 5999.99, "Asus");
	srv.Adauga("HP 250 G7", "Office", 3999.99, "HP");
	srv.Adauga("Lenovo Legion C7", "Grafica", 9499.99, "Lenovo");
	srv.Adauga("Lenovo IdeaPad 3", "Multimedia", 3299.99, "Lenovo");
	srv.Adauga("Dell Latitude 3510", "Office", 3599.99, "Dell");
	srv.Adauga("Asus K50IN", "Office", 499.99, "Asus");
	srv.Adauga("Acer Aspire 3", "Multimedia", 3199.99, "Acer");

	// Adauga in cos
	assert(srv.GetAllCos().size() == 0);
	assert(srv.GetTotalCos() == 0);
	srv.AdaugaCos("lenovo legion 5");
	assert(srv.GetAllCos().size() == 1);
	assert(srv.GetTotalCos() == 4599.99);

	// Goleste
	srv.GolesteCos();
	assert(srv.GetAllCos().size() == 0);
	assert(srv.GetTotalCos() == 0);

	// Generare
	srv.GenereazaCos(5);
	assert(srv.GetAllCos().size() == 5);

	// Export
	srv.ExportCos("test");
	try{ srv.ExportCos(""); }
	catch (ServiceError& se) { assert(se.get_message() == "Fisier invalid !\n"); }
	
	srv.GolesteCos();
	try { srv.ExportCos("test"); }
	catch (ServiceError& se) { assert(se.get_message() == "Export invalid ! Cosul este gol !\n"); }
}

void Tests::testRaport()
{
	RepositoryMemory repo;
	Service srv{ repo };

	srv.Adauga("Lenovo Legion 5", "Gaming", 4599.99, "Lenovo");
	srv.Adauga("HP Pavilion", "Gaming", 2999.99, "HP");
	srv.Adauga("Asus TUF F15", "Gaming", 3599.99, "Asus");
	srv.Adauga("Dell Inspiron 3793", "Home", 2699.99, "Dell");
	srv.Adauga("Asus ROG Strix G15", "Gaming", 5999.99, "Asus");
	srv.Adauga("HP 250 G7", "Office", 3999.99, "HP");
	srv.Adauga("Lenovo Legion C7", "Grafica", 9499.99, "Lenovo");
	srv.Adauga("Lenovo IdeaPad 3", "Multimedia", 3299.99, "Lenovo");
	srv.Adauga("Dell Latitude 3510", "Office", 3599.99, "Dell");
	srv.Adauga("Asus K50IN", "Office", 499.99, "Asus");
	srv.Adauga("Acer Aspire 3", "Multimedia", 3199.99, "Acer");

	const auto& raport = srv.Raport();
	assert(raport.at("Gaming").get_nr() == 4);
	assert(raport.at("Home").get_nr() == 1);
	assert(raport.at("Office").get_nr() == 3);
	assert(raport.at("Grafica").get_nr() == 1);
}

void Tests::testUndo_Fisier()
{
	std::remove("test.txt");
	RepositoryFile repo{ "test.txt" };
	Service srv{ repo };
	srv.Adauga("1", "1", 1, "1");
	srv.Adauga("2", "2", 2, "2");
	srv.Adauga("3", "3", 3, "3");
	srv.Modifica(3, "5", "5", 5, "5");
	srv.Sterge(2);
	assert(srv.GetAll().size() == 2);
	srv.Undo();
	assert(srv.GetAll().size() == 3);
	assert(srv.GetAll().at(2).get_nume() == "2");	// Ultimul e cel sters
	assert(srv.GetAll().at(1).get_nume() == "5");
	srv.Undo();
	assert(srv.GetAll().at(1).get_nume() == "3");	// Cel modificat
	srv.Undo();
	assert(srv.GetAll().size() == 2);
	assert(srv.GetAll().at(0).get_nume() == "1");
	assert(srv.GetAll().at(1).get_nume() == "2");
	srv.Undo();
	assert(srv.GetAll().size() == 1);
	assert(srv.GetAll().at(0).get_nume() == "1");
	srv.Undo();
	assert(srv.GetAll().size() == 0);
	try { srv.Undo(); }
	catch (ServiceError& se) { assert(se.get_message() == "Nu mai se poate face undo !\n"); }
	std::remove("test.txt");

	std::ofstream tout("test.txt");
	tout << "\n1\n\n2\n2\n\n3\n3\n3.h\n4\n4\n4\n\n5\n5\n5\n5\n6\n6\n6.6.\n";
	tout.close();
	RepositoryFile repo2{ "test.txt" };
	Service srv2{ repo };
	assert(srv2.GetAll().size() == 1);
	assert(srv2.GetAll().at(0).get_nume() == "5");
	std::remove("test.txt");
}

void Tests::testRepoLab0()
{
	RepoLab repo{ 0 };
	Produs p1{ "Lenovo Legion 5", "Gaming", 3999.99, "Lenovo" };
	// Adaugare
	repo.add(p1);
	const auto& produse = repo.get_all();
	assert(produse.size() == 1);
	assert(produse.at(0).get_nume() == "Lenovo Legion 5");

	try { repo.add(p1); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Produsul Lenovo Legion 5 exista deja !\n"); }

	// Modificare
	try { repo.modif("cevadsfsdf", Produs{ "ceva","aa",123,"da" }); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Produs inexistent !\n"); }

	repo.modif("Lenovo Legion 5", Produs{ "Asus K50IN","Office",500,"Asus" });
	const auto& produse2 = repo.get_all();
	assert(produse2.at(0).get_nume() == "Asus K50IN");
	assert(produse2.at(0).get_tip() == "Office");
	assert(produse2.at(0).get_pret() == 500);
	assert(produse2.at(0).get_producator() == "Asus");

	// Stergere
	try { repo.del("cevadasda"); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Produs inexistent !\n"); }

	repo.del("Asus K50IN");
	const auto& produse3 = repo.get_all();
	assert(produse3.size() == 0);

	// Cautare
	repo.add(p1);
	const auto& pr = repo.cauta("Lenovo Legion 5");
	assert(pr.get_nume() == "Lenovo Legion 5");
	try { repo.cauta("cevadasda"); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Produs inexistent !\n"); }
}

void Tests::testRepoLab1()
{
	RepoLab repo{ 1 };
	Produs p1{ "Lenovo Legion 5", "Gaming", 3999.99, "Lenovo" };
	// Adaugare
	try { repo.add(p1); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Ghinion !\n"); }

	// Modificare
	try { repo.modif("cevadsfsdf", Produs{ "ceva","aa",123,"da" }); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Ghinion !\n"); }

	// Stergere
	try { repo.del("cevadasda"); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Ghinion !\n"); }

	// Cautare
	try { repo.cauta("cevadasda"); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Ghinion !\n"); }

	// GetAll
	try { repo.get_all(); }
	//assert(false);
	catch (RepoError& re) { assert(re.get_message() == "Ghinion !\n"); }
}

void Tests::testAll()
{
	testDomain();
	testRepo();
	testService();
	testCos();
	testRaport();
	testUndo_Fisier();
	//testRepoLab0();
	//testRepoLab1();
	//std::cout << "Teste realizate cu succes !\n";
}