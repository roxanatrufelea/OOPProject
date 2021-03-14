#include "validare.h"
#include<string>
#include<assert.h>

string ValidatorException::getMesaj()
{
	return msg;
}
void ValidatorException::validLocatar(const Locatar& locatar)
{
	string error = "";
	if (locatar.getApartament() < 0) error = error + "Apartament_invalid!";
	if (size(locatar.getProprietar()) < 2) error = error + "Proprietar_invalid!";
	if (locatar.getSuprafata() < 5) error = error + "Suprafata_invalida!";
	if (size(locatar.getTip()) < 2) error = error + "Tip_invalid!";
	if (size(error) > 0) throw ValidatorException(error);
}
void testValid()
{
	Locatar locatar1{ 76,"Martin",100,"loft" };
	ValidatorException val;
	val.validLocatar(locatar1);
	assert(size(val.getMesaj()) == 0);

	Locatar locatar2{ -23,"r",2,"l" };
	try
	{
		val.validLocatar(locatar2);
		assert(false);
	}
	catch (ValidatorException)
	{
		assert(true);
	}
}