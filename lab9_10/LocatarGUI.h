#pragma once
#include <QtWidgets/qlabel.h>
#include<QtWidgets/qboxlayout.h >
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qradiobutton.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qwidget.h>
#include<QtWidgets/qmessagebox.h>
#include<qdebug.h>
#include "service.h"
#include "observer.h"
#include"listaNotificari.h"
#include<qpainter>
#include<qinputdialog.h>
#include<random>

class NotificariGUI : public QWidget, public Observer
{

private:
	LocatarService& srv;
	Notificari& notif;
	QListWidget* lst = new QListWidget;
	QGridLayout* ly = new QGridLayout;

	QPushButton* btnAdd = new QPushButton{ "&Adauga " };
	QPushButton* btnDel = new QPushButton{ "&Sterge " };
	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnRandom = new QPushButton{ "&Adauga  Random" };
	QPushButton* btnUndo = new QPushButton{ "&Undo " };
	QPushButton* btnCVS = new QPushButton{ "&Export CVS " };


	QLineEdit* txtApartament = new QLineEdit;
	QLineEdit* txtProprietar = new QLineEdit;
	QLineEdit* txtSuprafata = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;

	void connectSignalsSlots();
	void loadData(vector <Locatar>& locatari);
	void initGUI();

	void adauga();
	void sterge();
	void addRandom();
	void CVS();
	void undoN();

public:
	NotificariGUI(LocatarService& srv, Notificari& notif) : srv{ srv }, notif{ notif } {
		notif.addObserver(this);
		initGUI();
		connectSignalsSlots();
		loadData(srv.getNotificari());
	}
	void update() override {
		loadData(notif.getNotificari());
	}
	~NotificariGUI()
	{
		notif.removeObserver(this);
	}
	NotificariGUI() = default;
};
class NotificariRO: public QWidget, public Observer
{

private:
	
	Notificari& notif;
	

public:
	NotificariRO( Notificari& notif) : notif{ notif } {
		notif.addObserver(this);
	}
	void update() override {
		repaint();
	}
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int poz = 0;
		int i = 0;
		int x = rand() % 100 +10;
		for (auto& act : notif.getNotificari()) {
			if (i % 3 == 0) p.drawRect(x + poz * 60, x, i*10+50, 40);
			if (i % 3 == 1)p.drawRect(x + poz * 60, x, i*10+20, 50);
			if (i % 3 == 2) {
				QRectF rectangle(10.0*i, 20.0*i,10.0*x, 60.0*i);
				p.drawEllipse(rectangle);
			}
			i++;
			poz += 2;
		}
	}
};
class LocatarGUI : public QWidget
{

private:
	LocatarService& srv;
	QListWidget* lst = new QListWidget;
	QHBoxLayout* ly = new QHBoxLayout;

	QPushButton* btnAdd = new QPushButton{ "&Adauga" };
	QPushButton* btnPrint = new QPushButton{ "&Print" };
	QPushButton* btnDel = new QPushButton{ "&Sterge" };
	QRadioButton* btnExit = new QRadioButton{ "&Exit" };
	QPushButton* btnSrch = new QPushButton{ "&Cauta" };
	QPushButton* btnChg = new QPushButton{ "&Modifica " };
	QPushButton* btnFltrS = new QPushButton{ "& Filtru Suprafata" };
	QPushButton* btnFltrT = new QPushButton{ "& Filtru Tip" };
	QPushButton* btnSortP = new QPushButton{ "& Sort Proprietar" };
	QPushButton* btnSortS = new QPushButton{ "&Sort Suprafata" };
	QPushButton* btnSortT = new QPushButton{ "&Sort Tip" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };
	QRadioButton* btnNot1 = new QRadioButton{ "&NotificariGUI" };
	QRadioButton* btnNot2 = new QRadioButton{ "&NotificariRO" };
	QVBoxLayout* butoane = new QVBoxLayout;

	QRadioButton* btnAddN = new QRadioButton{ "&Adauga notificari" };
	QRadioButton* btnDelN = new QRadioButton{ "&Sterge notificari " };
	QRadioButton* btnRdmN = new QRadioButton{ "&Notificari random" };



	QLineEdit* txtApartament = new QLineEdit;
	QLineEdit* txtProprietar = new QLineEdit;
	QLineEdit* txtSuprafata = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	void initGUI();
	void connectSignalsSlots();
	void loadData(vector <Locatar>& locatari);
	void adaugaButoane(vector <Locatar>& locatari);


	void adauga();
	void sterge();
	void modifica();
	void cauta();
	void fltrSrf();
	void fltrTip();
	void undo();

public:
	LocatarGUI(LocatarService& srv) : srv{ srv } {
		initGUI();
		connectSignalsSlots();
		loadData(srv.getAll());

	}

};

