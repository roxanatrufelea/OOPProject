#include "listaNotificari.h"


void Notificari::golireLista() noexcept
{
	notificari.clear();
	notify();
}
void Notificari::addLista(const Locatar& l) noexcept(false)
{
	notificari.push_back(l);
	notify();
}
vector<Locatar> Notificari::getNotificari()
{
	return notificari;
}
void Notificari::sterge(Locatar& l)
{
	vector<Locatar> copy;
	int ok{ 0 };
	for (const Locatar& locatar : notificari)
		if (locatar.getApartament() == l.getApartament())
		{
			ok = 1;
		}
		else
		{
			copy.push_back(locatar);
		}
	notificari.clear();
	notificari = copy;

}