#pragma once
#include<vector>
#include "locatar.h"
#include<map>
#include<fstream>
using namespace std;


class RepoException
{
	string msg;
public:
	RepoException(string msg) :msg{ msg }
	{
	}
	string getMesaj()
	{
		return msg;
	}
};

class Repo
{
private:
	vector <Locatar> locatari;
public:
	Repo() = default;
	Repo(const Repo& ot) = delete;
	virtual ~Repo() = default;

	virtual void salveaza(const Locatar& locatar) = 0;
	virtual Locatar cauta(const Locatar& locatar) = 0;
	virtual void sterge(const int  apartament) = 0;
	virtual vector<Locatar> getAll() = 0;
};

class LocatarRepo :public Repo
{
private:
	map<int, Locatar> locatari;

public:

	LocatarRepo() noexcept :Repo() {};

	void salveaza(const Locatar& locatar) override;
	/*
	functia salveaza locatarul dat in vectorul de locatari, daca acesta nu exista deja
	input:Locatar& locatar
	output:
	raise RepoException daca locatarul nu exista
	*/
	Locatar cauta(const Locatar& locatar)override;
	/*
	functia cauta un locatar dat in baza de date si il returneaza
	input:Locatar& locatar
	output:Locatar
	raise RepoException daca locatarul nu exista
	*/
	void sterge(const int  apartament)override;
	/*
	functia sterge locatarul dat din baza de date, daca exista
	input:Locatar& locatar
	output:
	raise RepoException daca locatarul nu exista
	*/
	vector<Locatar> getAll()override;
	/*
	functia returneaza un vector cu toti locatarii din baza de date
	input:
	output:MyLista<Locatar> :lista cu toti locatarii
	*/

};
class LocatarRepoFile :public Repo {
private:
	std::string fName;

	map<int, Locatar> locatari;
	void loadFromFile();
	void writeToFile();
public:

	LocatarRepoFile(std::string fName) :Repo(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}

	void salveaza(const Locatar& locatar) override;
	/*
	functia salveaza locatarul dat in vectorul de locatari, daca acesta nu exista deja
	input:Locatar& locatar
	output:
	raise RepoException daca locatarul nu exista
	*/
	Locatar cauta(const Locatar& locatar)override;
	/*
	functia cauta un locatar dat in baza de date si il returneaza
	input:Locatar& locatar
	output:Locatar
	raise RepoException daca locatarul nu exista
	*/
	void sterge(const int  apartament)override;
	/*
	functia sterge locatarul dat din baza de date, daca exista
	input:Locatar& locatar
	output:
	raise RepoException daca locatarul nu exista
	*/
	vector<Locatar> getAll()override;
	/*
	functia returneaza un vector cu toti locatarii din baza de date
	input:
	output:MyLista<Locatar> :lista cu toti locatarii
	*/

};
class RepoLab : public Repo
{
private:
	int p;
	map<int, Locatar> locatari;
public:
	RepoLab(int p) noexcept :Repo(), p{ p }
	{

	}
	void salveaza(const Locatar& locatar) override;
	/*
	functia salveaza locatarul dat in vectorul de locatari, daca acesta nu exista deja
	input:Locatar& locatar
	output:
	raise RepoException daca locatarul nu exista
	*/
	Locatar cauta(const Locatar& locatar)override;
	/*
	functia cauta un locatar dat in baza de date si il returneaza
	input:Locatar& locatar
	output:Locatar
	raise RepoException daca locatarul nu exista
	*/
	void sterge(const int  apartament)override;
	/*
	functia sterge locatarul dat din baza de date, daca exista
	input:Locatar& locatar
	output:
	raise RepoException daca locatarul nu exista
	*/
	vector<Locatar> getAll()override;
	/*
	functia returneaza un vector cu toti locatarii din baza de date
	input:
	output:MyLista<Locatar> :lista cu toti locatarii
	*/


};
void testRepo();
void testFileRepo();
