#include "repo.h"
#include<assert.h>
#include<string>
#include<algorithm>


void LocatarRepo::salveaza(const Locatar& locatar)
{

	for (const pair<int, Locatar>& l : locatari)
	{
		if ((l.second).getApartament() == locatar.getApartament())
		{
			throw RepoException("Locatarul exista deja!");
		}
	}

	locatari.insert(pair<int, Locatar>(locatar.getApartament(), locatar));
}
Locatar LocatarRepo::cauta(const Locatar& locatar)
{

	auto rez = find_if(locatari.begin(), locatari.end(), [locatar](const pair<int, Locatar>& l)noexcept {return l.first == locatar.getApartament(); });
	if (rez == locatari.end())
		throw RepoException("Nu exista acest locatar!");
	else return (*rez).second;


}
void LocatarRepo::sterge(const int  apartament)
{
	std::map<int, Locatar> copy;
	int ok{ 0 };
	for (const pair<int, Locatar>& l : locatari)
		if (l.second.getApartament() == apartament)
		{
			ok = 1;
		}
		else
		{
			copy.insert(l);
		}
	locatari.clear();
	locatari = copy;
	if (ok == 0) throw RepoException("Nu exista acest locatar!");

}

std::vector<Locatar> LocatarRepo::getAll()
{
	vector<Locatar> v;
	transform(locatari.begin(), locatari.end(), back_inserter(v), [](pair<int, Locatar> const& loc) noexcept {return loc.second; });
	return v;
}

void LocatarRepoFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) { //verify if the stream is opened		
		throw LocatarException("Unable to open file:" + fName);
	}
	while (!in.eof()) {

		int apartament;
		in >> apartament;
		if (in.eof()) {	//nu am reusit sa citesc numarul
			break;
		}

		std::string proprietar;
		in >> proprietar;

		int suprafata;
		in >> suprafata;
		if (in.eof()) {	//nu am reusit sa citesc numarul
			break;
		}

		std::string tip;
		in >> tip;

		Locatar l{ apartament, proprietar.c_str(),suprafata, tip.c_str() };
		locatari.insert(pair<int, Locatar>(l.getApartament(), l));
	}
	in.close();
}


void LocatarRepoFile::writeToFile()
{
	std::ofstream out(fName);
	if (!out.is_open()) { //verify if the stream is opened
		throw LocatarException("Unable to open file:");
	}
	for (auto& l : locatari) {
		out << l.second.getApartament();
		out << std::endl;
		out << l.second.getProprietar();
		out << std::endl;
		out << l.second.getSuprafata();
		out << std::endl;
		out << l.second.getTip();
		out << std::endl;
	}
	out.close();
}


void LocatarRepoFile::salveaza(const Locatar& locatar)
{
	loadFromFile();
	for (const pair<int, Locatar>& l : locatari)
	{
		if ((l.second).getApartament() == locatar.getApartament())
		{
			throw RepoException("Locatarul exista deja!");
		}
	}

	locatari.insert(pair<int, Locatar>(locatar.getApartament(), locatar));
	writeToFile();
}
Locatar LocatarRepoFile::cauta(const Locatar& locatar)
{
	loadFromFile();
	auto rez = find_if(locatari.begin(), locatari.end(), [locatar](const pair<int, Locatar>& l)noexcept {return l.first == locatar.getApartament(); });
	if (rez == locatari.end())
		throw RepoException("Nu exista acest locatar!");
	else return (*rez).second;


}
void LocatarRepoFile::sterge(const int  apartament)
{
	loadFromFile();
	std::map<int, Locatar> copy;
	int ok{ 0 };
	for (const pair<int, Locatar>& l : locatari)
		if (l.second.getApartament() == apartament)
		{
			ok = 1;
		}
		else
		{
			copy.insert(l);
		}
	locatari.clear();
	locatari = copy;
	if (ok == 0) throw RepoException("Nu exista acest locatar!");
	writeToFile();
}

std::vector<Locatar> LocatarRepoFile::getAll()
{
	loadFromFile();
	vector<Locatar> v;
	transform(locatari.begin(), locatari.end(), back_inserter(v), [](pair<int, Locatar> const& loc) noexcept {return loc.second; });
	return v;
}


void testRepo()

{
	LocatarRepo repo;
	Locatar locatar1{ 76,"Martin",100,"studio" };
	//salveaza

	repo.salveaza(locatar1);
	const auto& locatari = repo.getAll();
	assert(locatari.size() == 1);

	try {

		repo.salveaza(locatar1);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}
	Locatar locatar2{ 8,"Ana",200,"garsoniera" };
	Locatar locatar3{ 13,"Sofia",50,"loft" };
	repo.salveaza(locatar2);
	repo.salveaza(locatar3);

	assert((repo.getAll()).size() == 3);

	//cauta
	assert(repo.cauta(locatar2).getApartament() == 8);
	try
	{
		Locatar locatar4 = repo.cauta(Locatar{ 23,"ferf",231,"ewfe" });
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}

	//sterge
	repo.sterge(8);
	assert((repo.getAll()).size() == 2);
	try
	{
		repo.sterge(123423);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}

}
void RepoLab::salveaza(const Locatar& locatar)
{
	int x = rand() % 100;
	if (x > p) throw RepoException("ghfgf");
	for (const pair<int, Locatar>& l : locatari)
	{
		if ((l.second).getApartament() == locatar.getApartament())
		{
			throw RepoException("Locatarul exista deja!");
		}
	}

	locatari.insert(pair<int, Locatar>(locatar.getApartament(), locatar));
}
Locatar RepoLab::cauta(const Locatar& locatar)
{
	int x = rand() % 100;
	if (x > p) throw RepoException("ghfgf");
	auto rez = find_if(locatari.begin(), locatari.end(), [locatar](const pair<int, Locatar>& l)noexcept {return l.first == locatar.getApartament(); });
	if (rez == locatari.end())
		throw RepoException("Nu exista acest locatar!");
	else return (*rez).second;


}
void RepoLab::sterge(const int  apartament)
{
	int x = rand() % 100;
	if (x > p) throw RepoException("ghfgf");
	std::map<int, Locatar> copy;
	int ok{ 0 };
	for (const pair<int, Locatar>& l : locatari)
		if (l.second.getApartament() == apartament)
		{
			ok = 1;
		}
		else
		{
			copy.insert(l);
		}
	locatari.clear();
	locatari = copy;
	if (ok == 0) throw RepoException("Nu exista acest locatar!");

}

std::vector<Locatar> RepoLab::getAll()
{
	int x = rand() % 100;
	if (x > p) throw RepoException("ghfgf");
	vector<Locatar> v;
	transform(locatari.begin(), locatari.end(), back_inserter(v), [](pair<int, Locatar> const& loc) noexcept {return loc.second; });
	return v;
}

void testFileRepo()
{
	std::ofstream out("testLocatari.txt", std::ios::trunc);
	out.close();//creez un fisier gol
	LocatarRepoFile repF{ "testLocatari.txt" };
	repF.salveaza(Locatar{ 1,"aaa",100,"bbb" });

	LocatarRepoFile repF2{ "testLocatari.txt" };
	Locatar l1{ 1,"aaa",100,"bbb" };
	Locatar l2{ 2,"bbb",100,"bbb" };
	auto p = repF2.cauta(l1);
	assert(p.getSuprafata() == 100);
	try {
		Locatar l3 = repF2.cauta(l2);
		assert(false);
	}
	catch (RepoException&) {
	}
	repF2.sterge(1);
	assert(repF2.getAll().size() == 0);
	try {
		repF2.sterge(7);
		assert(false);
	}
	catch (RepoException&) {
	}

	LocatarRepoFile repF3{ "testLocatari.txt" };
	assert(repF3.getAll().size() == 0);

	//fisierul nu exista si nu se poate crea (nu se creaza si directoare)
	//ar trebui sa arunce exceptie
	try {
		LocatarRepoFile repF4{ "te/stLocatari.txt" };
		assert(false);
	}
	catch (LocatarException&) {
		assert(true);
	}
}