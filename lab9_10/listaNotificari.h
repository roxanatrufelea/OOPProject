#pragma once
#include"locatar.h"
#include<iostream>
#include<vector>
#include "observer.h"
using namespace std;



class Notificari:public Observable
{
private:
	vector <Locatar> notificari;

public:
	Notificari() = default;

	void golireLista() noexcept;
	void sterge(Locatar& l);

	void addLista(const Locatar& l) noexcept(false);

	vector<Locatar> getNotificari();
};