#include "service.h"
#include<assert.h>
#include<iostream>
#include<numeric>
#include<algorithm>
#include<random>
#include<chrono>
//#include<vector>
//using namespace std;

void LocatarService::add(int apartament, string proprietar, int suprafata, string tip)
{
	Locatar locatar{ apartament,proprietar,suprafata,tip };
	val.validLocatar(locatar);
	repo.salveaza(locatar);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, locatar));
}

Locatar LocatarService::search(int apartament)
{
	Locatar l{ apartament,"hjgh",786,"uyu" };
	return repo.cauta(l);
}

void LocatarService::deletee(int apartament)
{
	Locatar l = repo.cauta(Locatar{ apartament,"hjgh",786,"uyu" });
	repo.sterge(apartament);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, l));
}
void LocatarService::change(int apartament, string proprietar, int suprafata, string tip)
{
	Locatar l = repo.cauta(Locatar{ apartament,"hjgh",786,"uyu" });
	repo.sterge(apartament);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, l));

	Locatar l2{ apartament,proprietar,suprafata,tip };
	val.validLocatar(l2);
	repo.salveaza(l2);

}
vector<Locatar> LocatarService::filtr_tip(string tip)
{
	vector<Locatar> filtru;
	vector<Locatar> locatari = repo.getAll();
	copy_if(locatari.begin(), locatari.end(), back_inserter(filtru), [tip](const Locatar& l) {return l.getTip() == tip; });
	return filtru;
}
vector<Locatar> LocatarService::filtr_suprafata(int suprafata)
{
	vector<Locatar> filtru;
	vector<Locatar> locatari = repo.getAll();
	copy_if(locatari.begin(), locatari.end(), back_inserter(filtru), [suprafata](const Locatar& l)noexcept {return l.getSuprafata() <= suprafata; });
	return filtru;
}
/*
int LocatarService::cmpProprietar(const Locatar& l1, const Locatar& l2)
{
	return l1.getProprietar()>l2.getProprietar(
}
vector<Locatar> LocatarService::sort(FunctieComparare cmpFnct)
{
	vector<Locatar> sort = repo.getAll();

	for (signed int i = 0; i < signed(size(sort) - 1); i++)
		for (signed int j = i + 1; j < signed(size(sort)); j++)
			if (cmpFnct(&sort[i],&sort[j]) > 0)
			{
				Locatar aux = sort[i];
				sort[i] = sort[j];
				sort[j] = aux;
			}
	return sort;
}*/
vector<Locatar> LocatarService::sort_proprietar()
{
	vector<Locatar> locatari = repo.getAll();
	sort(locatari.begin(), locatari.end(), [](Locatar& l1, Locatar& l2) {return l1.getProprietar() < l2.getProprietar(); });
	return locatari;
}

vector<Locatar> LocatarService::sort_suprafata()
{
	vector<Locatar> locatari = repo.getAll();
	sort(locatari.begin(), locatari.end(), [](Locatar& l1, Locatar& l2)noexcept {return l1.getSuprafata() < l2.getSuprafata(); });
	return locatari;
}
vector<Locatar> LocatarService::sort_tip()
{
	vector<Locatar> locatari = repo.getAll();
	sort(locatari.begin(), locatari.end(), [](const Locatar& l1, const Locatar& l2) {return l1.getTip() < l2.getTip(); });
	return locatari;
}
vector <Locatar> LocatarService::getAll()
{
	return repo.getAll();
}

/*
MyLista< string >LocatarDTO::getVector() const
{
	return vector;
}*/
int LocatarDTO::getCount() const noexcept
{
	return count;
}
string LocatarDTO::getNume()const
{
	return nume;
}
void LocatarDTO::setNume(string numee)
{
	nume = numee;
}
string LocatarDTO::getTip() const
{
	return tip;
}
void LocatarDTO::add() noexcept
{
	count++;
}
void LocatarDTO::setTip(string tipp)
{
	this->tip = tipp;
}

std::vector<LocatarDTO> LocatarService::raport() const
{
	map <string, LocatarDTO> m;
	vector<LocatarDTO> lista;
	lista.clear();
	for (const auto& locatar : repo.getAll())
	{
		LocatarDTO dto;
		dto.setNume(locatar.getProprietar());
		dto.setTip(locatar.getTip());
		for (const auto& l : repo.getAll())
			if (dto.getTip() == l.getTip())
				dto.add();
		m.insert(std::pair<string, LocatarDTO>(locatar.getTip(), dto));
	}
	for (const auto& loc : repo.getAll())
	{

		LocatarDTO dto1 = m.find(loc.getTip())->second;
		dto1.setNume(loc.getProprietar());
		lista.push_back(dto1);
	}
	//transform(m.begin(), m.end(), back_inserter(lista) , [](pair<string, LocatarDTO> const& loc) {return loc.second; });
	return lista;
}

void LocatarService::stergeNotificari() noexcept
{
	notificari.golireLista();
}

void LocatarService::addNotificare(int apartament)
{
	Locatar l = search(apartament);
	notificari.addLista(l);
	undoActionsNotif.push_back(std::make_unique<UndoAdaugaNotif>(notificari, l));
}
void LocatarService::undoNotificari()
{
	if (undoActionsNotif.empty()) {
		throw LocatarException{ "Nu mai exista operatii" };
	}
	/*
	ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;
	*/
	// Varianta cu unique_ptr
	//obs: la obiecte unique_ptr nu putem face copie			
	undoActionsNotif.back()->doUndo();
	undoActionsNotif.pop_back();
}

vector<Locatar> LocatarService::getNotificari()
{
	return notificari.getNotificari();
}

void LocatarService::addRandom(int nr)
{
	vector<Locatar> locatari = repo.getAll();
	//auto const  seed = std::chrono::system_clock::now().time_since_epoch().count();
	//std::shuffle(locatari.begin(), locatari.end(), std::default_random_engine(seed));
	auto rng = std::default_random_engine{};
	std::shuffle(locatari.begin(), locatari.end(), rng);
	int count{ 0 };
	for (const Locatar& l : locatari)
	{
		if (count == nr) break;
		notificari.addLista(l);
		count++;
	}
}

int LocatarService::Total()
{
	int suma{ 0 };
	vector<Locatar> locatari = repo.getAll();
	vector<int> suprafata;
	transform(locatari.begin(), locatari.end(), back_inserter(suprafata), [](Locatar& l)noexcept {return l.getSuprafata(); });
	suma = accumulate(suprafata.begin(), suprafata.end(), 0);
	return suma;
}

void LocatarService::exportaCosCVS(std::string fName) {
	exportToCVS(fName, notificari.getNotificari());
}


void LocatarService::undo() {
	if (undoActions.empty()) {
		throw LocatarException{ "Nu mai exista operatii" };
	}
	/*
	ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;
	*/
	// Varianta cu unique_ptr
	//obs: la obiecte unique_ptr nu putem face copie			
	undoActions.back()->doUndo();
	undoActions.pop_back();
}


void testExporta() {
	LocatarRepo rep;
	ValidatorException val;
	Notificari not;
	LocatarService ctr{ rep,not,val };
	ctr.add(1, "aaa", 100, "bbb");
	ctr.add(2, "aaa", 100, "bbb");
	ctr.add(3, "aaa", 100, "bbb");
	ctr.addRandom(3);
	ctr.exportaCosCVS("testexport.cvs");
	std::ifstream in("testexport.cvs");
	assert(in.is_open());
	int countLines = 0;
	while (!in.eof()) {
		string line;
		in >> line;
		countLines++;
	}
	in.close();
	assert(countLines == 4);//avem o linie pentru fiecare pet + o linie goala


	//daca se da un nume de fisier invalid se arunca exceptie
	try {
		ctr.exportaCosCVS("test/export.cvs");
		assert(false);
	}
	catch (LocatarException&) {
		assert(true);
	}

}
void testUndo()
{
	LocatarRepo repo;
	ValidatorException val;
	Notificari not;
	LocatarService srv{ repo,not,val };


	srv.add(12, "Ionut", 56, "loft");
	srv.add(10, "Ionut", 56, "loft");
	srv.add(15, "Ionut", 56, "loft");
	srv.undo();
	assert(srv.getAll().size() == 2);
	srv.undo();
	assert(srv.getAll().size() == 1);

	srv.deletee(12);
	assert(srv.getAll().size() == 0);
	srv.undo();
	assert(srv.getAll().size() == 1);
	srv.change(12, "aaa", 100, "aaa");
	assert(srv.getAll()[0].getSuprafata() == 100);
	srv.undo();
	assert(srv.getAll()[0].getSuprafata() == 56);
	srv.undo();
	assert(srv.getAll().size() == 0);
	try {
		srv.undo();
		assert(false);
	}
	catch (LocatarException const& ex) {
		assert(ex.getMsg() == "Nu mai exista operatii");
	}


}
void testAdd()
{

	LocatarRepo repo;
	ValidatorException val;
	Notificari not;
	LocatarService srv{ repo,not,val };
	//add

	srv.add(12, "Ionut", 56, "loft");
	const auto& locatari = srv.getAll();
	assert(locatari.size() == 1);

	srv.add(23, "Carolina", 876, "studio");
	srv.add(56, "Christian", 400, "loft");
	try
	{
		srv.add(23, "Carolina", 876, "studio");
		assert(false);
	}
	catch (ValidatorException)
	{
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}
	try
	{
		srv.add(-23, "Carolina", 876, "studio");
		assert(false);
	}
	catch (ValidatorException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}
	catch (RepoException)
	{
		assert(false);
	}
	assert(srv.getAll().size() == 3);
	//search

	Locatar l1 = srv.search(23);
	assert(l1.getSuprafata() == 876);
	try
	{
		Locatar l2 = srv.search(204);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}
	//deletee
	srv.deletee(23);
	assert(srv.getAll().size() == 2);
	try
	{
		srv.deletee(204);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}
	//change
	srv.change(12, "Mihai", 300, "studio");
	assert(srv.search(12).getProprietar() == "Mihai");
	try
	{
		srv.change(2004, "Maria", 87, "garsoniera");
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}
	//filtr_tip
	srv.add(23, "Carolina", 876, "studio");

	assert(size(srv.filtr_tip("studio")) == 2);
	//filtr_suprafata

	assert(size(srv.filtr_suprafata(350)) == 1);
	srv.add(15, "Ana", 176, "studio");
	//sort_proprietar
	assert(srv.sort_proprietar()[0].getProprietar() == "Ana");
	//sort_suprafata
	assert(srv.sort_suprafata()[0].getProprietar() == "Ana");
	//sort_tip
	srv.add(1, "Andrei", 100, "garsoniera");
	assert(srv.sort_tip()[0].getProprietar() == "Andrei");


	//raport

	assert(size(srv.raport()) == 5);
	LocatarDTO dto;
	dto.setNume("Ana");
	dto.setTip("loft");
	assert(dto.getCount() == 0);
	assert(dto.getNume() == "Ana");
	assert(dto.getTip() == "loft");

	//notificari
	srv.stergeNotificari();
	assert(size(srv.getNotificari()) == 0);
	srv.addNotificare(15);
	srv.addNotificare(1);
	assert(size(srv.getNotificari()) == 2);
	try
	{
		srv.addNotificare(105);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(size(ex.getMesaj()) > 0);
	}

	srv.stergeNotificari();
	srv.addRandom(3);
	assert(size(srv.getNotificari()) == 3);

	//total
	assert(srv.Total() == 1852);

	testExporta();
}

