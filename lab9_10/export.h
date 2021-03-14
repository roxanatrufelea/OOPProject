#pragma once
#include <string>
#include <vector>
#include "locatar.h"
/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
arunca PetException daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fName, const std::vector<Locatar>& locatari);