#pragma once
#include "domain.h"
#include "repository.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {};
};

class UndoAdauga : public ActiuneUndo {
	string nume_prodAdaugat;
	Repo& rep;
public:
	UndoAdauga(Repo& rep, const string& nume) : rep{ rep }, nume_prodAdaugat{ nume }{}
	void doUndo() override {
		rep.del(nume_prodAdaugat);
	}
};

class UndoModifica : public ActiuneUndo {
	string nume_nou;
	Produs prodVechi;
	Repo& rep;
public:
	UndoModifica(Repo& rep, const string& numeNou, const Produs& pVechi) : rep{ rep }, nume_nou{ numeNou }, prodVechi{ pVechi }{}
	void doUndo() override {
		rep.modif(nume_nou,prodVechi);
	}
};

class UndoSterge : public ActiuneUndo {
	Produs prodSters;
	Repo& rep;
public:
	UndoSterge(Repo& rep, const Produs& p) : rep{ rep }, prodSters{ p }{}
	void doUndo() override {
		rep.add(prodSters);
	}
};