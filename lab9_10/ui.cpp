#include "ui.h"
#include<iostream>
#include<vector>
using std::cin;
using std::cout;


void meniu()
{
	cout << "Alegeti una dintre comenzile:\n";
	cout << "0-exit\n1-print\n2-adauga\n3-sterge\n4-modifica\n5-cauta\n";
	cout << "6-filtreaza dupa tip\n7-filtreaza dupa suprafata\n";
	cout << "8-sorteaza dupa proprietar\n9-sorteaza dupa suprafata\n10-sorteaza dupa tip si suprafata\n";
	cout << "11-raport\n12-sterge notificari\n13-adauga notificare\n14-adauga notificari random\n15-print notificari\n";
}

int read_int()
{
	int apartament = 0;
	while (!(cin >> apartament))
	{
		cout << "Introduceti un numar intreg!\n";
		cin.clear();
		cin.ignore(123, '\n');
	}
	return apartament;
}

void UI::print()
{
	try {
		if (size(serv.getAll()) == 0) cout << "Nu exista locatari!\n";
		for (const Locatar& l : serv.getAll())
			cout << l.getApartament() << "  " << l.getProprietar() << "  " << l.getSuprafata() << "  " << l.getTip() << "\n";
	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}
void UI::adauga()
{
	int apartament{};
	string proprietar, tip;
	int suprafata{};

	cout << "Apartament=";
	apartament = read_int();
	cout << "proprietar=";
	cin >> proprietar;
	cout << "suprafata=";
	suprafata = read_int();
	cout << "tip=";
	cin >> tip;
	try
	{
		serv.add(apartament, proprietar, suprafata, tip);
		cout << "Locatar adaugat...\n";

	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
	catch (ValidatorException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}

}
void UI::cauta()
{
	int apartament;
	cout << "Apartament=";
	apartament = read_int();
	try
	{
		Locatar l = serv.search(apartament);
		cout << l.getApartament() << "  " << l.getProprietar() << "  " << l.getSuprafata() << "  " << l.getTip() << "\n";

	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}
void UI::del()
{
	int apartament;
	string  proprietar;
	cout << "Apartament=";
	apartament = read_int();

	try
	{
		serv.deletee(apartament);
		cout << "Locatarul a fost  sters...\n";

	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}
void UI::modifica()
{
	int apartament{};
	string proprietar, tip;
	int suprafata{};

	cout << "Apartament=";
	apartament = read_int();
	cout << "proprietar=";
	cin >> proprietar;
	cout << "suprafata=";
	suprafata = read_int();
	cout << "tip=";
	cin >> tip;
	try
	{
		serv.change(apartament, proprietar, suprafata, tip);
		cout << "Locatar modificat...\n";

	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}
void UI::filtru_tip()
{
	string tip;
	cout << "tip=";
	cin >> tip;

	std::vector<Locatar> filtru = serv.filtr_tip(tip);

	if (size(filtru) == 0) cout << "Nu exista locatari cu acest tip!\n";
	for (const Locatar& l : filtru)
		cout << l.getApartament() << "  " << l.getProprietar() << "  " << l.getSuprafata() << "  " << l.getTip() << "\n";
}
void UI::filtru_suprafata()
{
	int suprafata;
	cout << "suprafata=";
	suprafata = read_int();

	std::vector<Locatar> filtru = serv.filtr_suprafata(suprafata);

	if (size(filtru) == 0) cout << "Nu exista locatari cu acesta suprafata!\n";
	for (const Locatar& l : filtru)
		cout << l.getApartament() << "  " << l.getProprietar() << "  " << l.getSuprafata() << "  " << l.getTip() << "\n";
}
void UI::sortare_proprietar()
{
	if (size(serv.sort_proprietar()) == 0) cout << "Nu exista locatari!\n";
	else {
		for (const Locatar& l : serv.sort_proprietar())
			cout << l.getApartament() << "  " << l.getProprietar() << "  " << l.getSuprafata() << "  " << l.getTip() << "\n";
	}
}
void UI::sortare_suprafata()
{
	if (size(serv.sort_suprafata()) == 0) cout << "Nu exista locatari!\n";
	else {
		for (const Locatar& l : serv.sort_suprafata())
			cout << l.getApartament() << "  " << l.getProprietar() << "  " << l.getSuprafata() << "  " << l.getTip() << "\n";
	}
}
void UI::sortare_tip_suprafata()
{

	if (size(serv.sort_tip()) == 0) cout << "Nu exista locatari!\n";
	else {
		for (const Locatar& l : serv.sort_tip())
			cout << l.getApartament() << "  " << l.getProprietar() << "  " << l.getSuprafata() << "  " << l.getTip() << "\n";
	}
}
void UI::raport()
{
	cout << "Raport:\n";
	for (const LocatarDTO& l : serv.raport())
		cout << "Nume: " << l.getNume() << "---Tip: " << l.getTip() << "---Type Count: " << l.getCount() << "\n";

}

void UI::printNotificari()
{
	try
	{
		if (size(serv.getNotificari()) == 0) cout << "Nu exista notificari!\n";
		for (const Locatar& l : serv.getNotificari())
			cout << l.getApartament() << "  " << l.getProprietar() << "  " << l.getSuprafata() << "  " << l.getTip() << "\n";
	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}

void UI::delNotif()
{
	try 
	{
		serv.stergeNotificari();
		cout << "Lista de notificari a fost stearsa...\n";
	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}

void UI::addNotif()
{
	int apartament{ 0 };
	cout << "Apartament=";
	apartament = read_int();

	try
	{
		serv.addNotificare(apartament);
		cout << "Notificare adaugata...\n";
	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}
void UI::randomAdd()
{
	int nr{ 0 };
	cout << "nr=";
	nr = read_int();
	try 
	{

		serv.addRandom(nr);
	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}

void UI::total()
{
	try
	{
		cout << "total= " << serv.Total() << "\n";
	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}

void UI::exportCVS()
{
	cout << "CVS FILE: ";
	string fName;
	cin >> fName;
	try
	{
		serv.exportaCosCVS(fName);
	}
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}
void UI::undo()
{
	try { serv.undo(); }
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}

void UI::undoNotif()
{
	try { serv.undoNotificari(); }
	catch (RepoException & ex)
	{
		cout << ex.getMesaj() << "\n";
	}
}
void UI::startUI()
{

	while (true)
	{

		int cmd = 0;
		cout << ">>>";
		cmd = read_int();
		if (cmd < 0 || cmd>19) cout << "Comanda invalida!";
		if (cmd == 0) break;
		if (cmd == 1) print();
		if (cmd == 2) adauga();
		if (cmd == 3) del();
		if (cmd == 4) modifica();
		if (cmd == 5) cauta();
		if (cmd == 6) filtru_tip();
		if (cmd == 7) filtru_suprafata();
		if (cmd == 8) sortare_proprietar();
		if (cmd == 9) sortare_suprafata();
		if (cmd == 10) sortare_tip_suprafata();
		if (cmd == 11) raport();
		if (cmd == 12) delNotif();
		if (cmd == 13) addNotif();
		if (cmd == 14) randomAdd();
		if (cmd == 15) printNotificari();
		if (cmd == 16) total();
		if (cmd == 17) exportCVS();
		if (cmd == 18) undo();
		if (cmd == 19) undoNotif();
	}

}