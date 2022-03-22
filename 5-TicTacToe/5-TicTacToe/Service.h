#pragma once
#include "Observer.h"
#include "Repository.h"

class Service : public Observable
{
private:
	Repository& repo;
public:
	Service() = default;
	Service(Repository& repo) : repo{ repo } {}
	Service(const Service& ot) = delete;

	void Adauga(int dim, string tabla, string urmator, string stare) {
		int id = repo.ult() + 1;
		Joc j{ id,dim,tabla,urmator,stare };
		j.validare();
		repo.add(j);
		notify();
	}

	void Modifica(int id, int dim_noua, string tabla_noua, string urmator_nou, string stare_noua) {
		auto existent = Cauta(id);
		int modificari = 0;
		if (dim_noua == 0)
		{
			dim_noua = existent.get_dim();
			modificari++;
		}
		if (tabla_noua == "")
		{
			tabla_noua = existent.get_tabla();
			modificari++;
		}
		if (urmator_nou == "")
		{
			urmator_nou = existent.get_urmator();
			modificari++;
		}
		if (stare_noua == "")
		{
			stare_noua = existent.get_stare();
			modificari++;
		}
		if (modificari == 4)
			return;
		Joc j{ id,dim_noua,tabla_noua,urmator_nou,stare_noua };
		j.validare();
		repo.modif(id, j);
		notify();
	}

	const Joc& Cauta(const int id) {
		if (id <= 0)
			throw exception("ID invalid !\n");
		return repo.cauta(id);
	}

	vector<Joc> GetAll() {
		return repo.get_all();
	}
};

