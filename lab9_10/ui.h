#pragma once
#include "service.h"
class UI
{
private:
	LocatarService& serv;
public:
	//functia construieste ui
	UI(LocatarService& serv) noexcept :serv{ serv } {}

	//functia de interactiune cu utilizatorul
	void startUI();

	//functia adauga un nou locatar in baza de date
	void adauga();
	void print();
	void cauta();
	void del();
	void modifica();
	void filtru_tip();
	void filtru_suprafata();
	void sortare_proprietar();
	void sortare_suprafata();
	void sortare_tip_suprafata();
	void raport();
	void printNotificari();
	void delNotif();
	void addNotif();
	void randomAdd();
	void total();
	void exportCVS();
	void undo();
	void undoNotif();

};

//functia citeste de la tastatura un numar intreg
int read_int();

//functia afiseaza meniul
void meniu();