#pragma once
#include "locatar.h"
class ValidatorException
{
private:
	string msg;
public:
	ValidatorException() = default;
	ValidatorException(string m) :msg{ m }
	{
	}
	string getMesaj();
	/*
	functia returneaza o eroare care specifica ce atribute ale unui locatar sunt invalide
	input:
	output:string mesaj- mesajul de eroare pentru un locatar
	*/
	void validLocatar(const Locatar& locatar);
	/*
	functia validaza atributele unui locatar dat
	input:Locatar& locatar
	output:
	raise ValidatorException daca exista vreun atribut invalid
	*/
};
void testValid();