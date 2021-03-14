#include "export.h"
#include "locatar.h"
#include <fstream>
#include <string>
#include <vector>
/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
arunca PetException daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fName, const std::vector<Locatar>& locatari) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw LocatarException("Unable to open file:" + fName);
	}
	for (const auto& l : locatari) {
		out << l.getApartament() << ",";
		out << l.getProprietar() << ",";
		out << l.getSuprafata() << ",";
		out << l.getTip() << std::endl;
	}
	out.close();
}