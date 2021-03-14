#pragma once
#include "locatar.h"
#include "repo.h"
#include "validare.h"
#include<vector>
#include<string>
#include<map>
#include "listaNotificari.h"
#include "export.h"
#include "undo.h"
using namespace std;
using std::unique_ptr;



class LocatarDTO
{
private:
	string tip;
	string nume;
	int count;

public:

	LocatarDTO() noexcept(false) : nume{ "" }, tip{ "" }, count{ 0 }{}
	int getCount() const noexcept;
	string getTip()const;
	string getNume()const;
	void add() noexcept;
	void setTip(string tipp);
	void setNume(string numee);
};

class LocatarService
{
private:
	Repo& repo;
	Notificari& notificari;
	ValidatorException& val;

	//tinem pointeri la ActiuneUndo pentru ca vrem apel polimorfic
	//punem unique_ptr pentru ca avem responsabilitatea de a elibera memoria pentru 
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	std::vector<unique_ptr<ActiuneUndo>> undoActionsNotif;
	//std::vector<ActiuneUndo*> undoActions;

public:
	LocatarService() = default;
	LocatarService(Repo& repo, Notificari& notificari, ValidatorException& val) noexcept : repo{ repo }, notificari{ notificari }, val{ val }{}
	~LocatarService() {};
	LocatarService(const LocatarService& ot) = delete;


	Notificari& getNotif()
	{
		return notificari;
	}
	void operator=(const LocatarService& ot) = delete;//nu vreau sa mearga assignment

	void add(int apartament, string proprietar, int suprafata, string tip);
	/*
	functia adauga un nou locatar cu atributele date
	input:int apartament, string proprietar, double suprafata, string tip
	output:
	raise RepoException-locatarul exista deja
	raise ValidationException- atributele date nu sunt valide
	*/
	Locatar search(int apartament);
	/*
	functia cauta un locatar dupa apartament si il returneaza
	input:int apartament
	output:Locatar l-locatarul cautat
	raise RepoException-locatarul nu exista exista
	*/
	void deletee(int apartament);
	/*
	functia sterge locatarul cu apartamentul si proprietarul respectiv
	input:int apartament, string proprietar
	output:
	raise RepoException-locatarul nu exista exista
	*/
	void change(int apartament, string proprietar, int suprafata, string tip);
	/*
	functia modifica atributele locatarului cu apartamentul apartament, cu urmatoarele atribute date
	input:int apartament, string proprietar, double suprafata, string tip
	output:
	raise RepoException-locatarul nu exista exista
	*/
	std::vector<Locatar> filtr_tip(string tip);
	/*
	functia filtreaza vectorul de locatari dupa tipul dat
	input:string tip
	output:vector<Locatar> locatari-un vector de locatari care respecta filtrul aplicat
	*/
	vector <Locatar> filtr_suprafata(int suprafata);
	/*
	functia filtreaza vectorul de locatari dupa suprafata data
	input:int suprafata
	output:vector<Locatar> locatari-un vector de locatari care respecta filtrul aplicat
	*/
	vector<Locatar> sort_proprietar();
	/*
	functia sorteaza vectorul de locatari dupa proprietar
	input:-
	output:vector<Locatar> locatari-un vector cu toti locatarii in ordinea stabilita
	*/
	vector <Locatar> getAll();
	/*
	functia returneaza vectorul de locatari
	input:-
	output:vector<Locatar> locatari-un vector cu toti locatarii in ordinea stabilita
	*/
	vector<Locatar> sort_suprafata();
	/*
	functia sorteaza vectorul de locatari dupa suprafata
	input:-
	output:vector<Locatar> locatari-un vector cu toti locatarii in ordinea stabilita
	*/
	vector<Locatar> sort_tip();
	/*
	functia sorteaza vectorul de locatari dupa tip
	input:-
	output:vector<Locatar> locatari-un vector cu toti locatarii in ordinea stabilita
	*/
	vector <LocatarDTO> raport() const;
	/*functia afiseaza un raport al locatarilor existenti in baza de date*/

	void stergeNotificari() noexcept;
	//functia sterge toate notificarile despre locatari din lista de notificari

	void addNotificare(int apartament);
	/*
	functia adauga un nou locatar in lista de notificari dupa numrul de apartament
	input:apartament-numar intreg
	output:-
	*/
	vector<Locatar> getNotificari();
	//returneaza toate notificarile

	void addRandom(int nr);

	int Total();

	void exportaCosCVS(std::string fName);

	void undo();
	void undoNotificari();
};

void testUndo();
void testAdd();
