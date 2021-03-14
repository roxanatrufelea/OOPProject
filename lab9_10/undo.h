#pragma once
#include "locatar.h"
#include "repo.h"
#include "listaNotificari.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Locatar locatarAdaugat;
	Repo& rep;
public:
	UndoAdauga(Repo& rep, const  Locatar& p) :rep{ rep }, locatarAdaugat{ p } {}

	void doUndo() override {
		rep.sterge(locatarAdaugat.getApartament());
	}
};

class UndoSterge : public ActiuneUndo {
	Locatar LocatarSters;
	Repo& rep;
public:
	UndoSterge(Repo& rep, const Locatar& p) noexcept :rep{ rep }, LocatarSters{ p } {}
	void doUndo() override {
		rep.salveaza(LocatarSters);
	}
};

class UndoModifica : public ActiuneUndo {
	Locatar LocatarModificat;
	Repo& rep;
public:
	UndoModifica(Repo& rep, const Locatar& p) noexcept :rep{ rep }, LocatarModificat{ p } {}
	void doUndo() override {
		rep.sterge(LocatarModificat.getApartament());
		rep.salveaza(LocatarModificat);
	}
};
class UndoAdaugaNotif : public ActiuneUndo {
	Locatar locatarAdaugat;
	Notificari& rep;
public:
	UndoAdaugaNotif(Notificari& rep, const  Locatar& p) noexcept :rep{ rep }, locatarAdaugat{ p } {}

	void doUndo() override {
		rep.sterge(locatarAdaugat);
	}
};