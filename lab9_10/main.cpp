#include "lab9_10.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include<QtWidgets/qboxlayout.h >
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlistwidget.h>
#include "LocatarGUI.h"
#include"listaNotificari.h"
int main(int argc, char* argv[])
{
	testAdd();
	testFileRepo();
	testRepo();
	testUndo();
	testValid();

	QApplication a(argc, argv);

	//LocatarRepo repo;
	LocatarRepoFile repo{ "locatari.txt" };
	Notificari notif;
	ValidatorException val;
	LocatarService srv{ repo,notif,val };

	LocatarGUI gui{ srv };
	//NotificariGUI gui2{ srv };
	gui.setWindowTitle("Administrare locatari");
	gui.show();
	//gui2.show();
	return a.exec();
}
