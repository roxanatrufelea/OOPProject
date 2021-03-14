#include "LocatarGUI.h"


void LocatarGUI::loadData(vector <Locatar>& locatari)
{
	lst->clear();
	for (const auto& l : locatari)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::number(l.getApartament()));
		item->setData(Qt::UserRole, QString::fromStdString(l.getProprietar()));
		lst->addItem(item);
	}
}

void LocatarGUI::initGUI() {

	setLayout(ly);

	//ly->addWidget(new QLineEdit);
	
	//lst->addItem("item1");
	//ly->addWidget(lst);
	auto lyDr = new QVBoxLayout;
	auto lySt = new QVBoxLayout;
	auto lyBTn = new QHBoxLayout;
	auto lyBTn2 = new QHBoxLayout;
	auto lyBTn3 = new QHBoxLayout;
	auto lyBTn4 = new QHBoxLayout;
	auto lyDrDr = new QVBoxLayout;


	lyBTn->addWidget(btnAdd);
	lyBTn->addWidget(btnDel);
	lyBTn->addWidget(btnChg);
	lyBTn->addWidget(btnSrch);

	lyBTn2->addWidget(btnFltrS);
	lyBTn2->addWidget(btnFltrT);

	lyBTn3->addWidget(btnSortP);
	lyBTn3->addWidget(btnSortS);
	lyBTn3->addWidget(btnSortT);

	lyBTn4->addWidget(btnUndo);
	lyBTn4->addWidget(btnPrint);



	auto formLy = new QFormLayout;
	formLy->addRow("Apartament", txtApartament);
	formLy->addRow("Proprietar", txtProprietar);
	formLy->addRow("Suprafata", txtSuprafata);
	formLy->addRow("Tip", txtTip);

	lySt->addWidget(lst);
	lySt->addWidget(btnNot1);
	lySt->addWidget(btnNot2);
	lySt->addWidget(btnExit);

	lyDr->addLayout(formLy);
	lyDr->addLayout(lyBTn);
	lyDr->addLayout(lyBTn2);
	lyDr->addLayout(lyBTn3);
	lyDr->addLayout(lyBTn4);

	lyDrDr->addWidget(btnAddN);
	lyDrDr->addWidget(btnDelN);
	lyDrDr->addWidget(btnRdmN);

	ly->addLayout(lySt);
	ly->addLayout(lyDr);
	ly->addLayout(butoane);
	ly->addLayout(lyDrDr);
}

void LocatarGUI::connectSignalsSlots()
{
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty())
		{
			txtApartament->setText("");
			txtProprietar->setText("");
			txtSuprafata->setText("");
			txtTip->setText("");
		}
		else
		{
			auto selItem = sel.at(0);
			auto apartament = selItem->text();
			auto proprietar = selItem->data(Qt::UserRole).toString();
			txtApartament->setText(apartament);
			txtProprietar->setText(proprietar);
			auto l = srv.search(apartament.toInt());
			txtSuprafata->setText(QString::number(l.getSuprafata()));
			txtTip->setText(QString::fromStdString(l.getTip()));
		}
		});

	QObject::connect(btnExit, &QPushButton::clicked, [&]() { QMessageBox msgBox;
	msgBox.setText("Ati apasat butonul Exit");
	msgBox.exec();
	close(); });

	QObject::connect(btnPrint, &QPushButton::clicked, [&]() { loadData(srv.getAll()); });
	QObject::connect(btnAdd, &QPushButton::clicked, this, &LocatarGUI::adauga);
	QObject::connect(btnDel, &QPushButton::clicked, this, &LocatarGUI::sterge);
	QObject::connect(btnChg, &QPushButton::clicked, this, &LocatarGUI::modifica);
	QObject::connect(btnSrch, &QPushButton::clicked, this, &LocatarGUI::cauta);

	QObject::connect(btnFltrS, &QPushButton::clicked, this, &LocatarGUI::fltrSrf);
	QObject::connect(btnFltrT, &QPushButton::clicked, this, &LocatarGUI::fltrTip);

	QObject::connect(btnSortP, &QPushButton::clicked, [&]() { loadData(srv.sort_proprietar()); adaugaButoane(srv.sort_proprietar()); });
	QObject::connect(btnSortS, &QPushButton::clicked, [&]() { loadData(srv.sort_suprafata()); adaugaButoane(srv.sort_suprafata()); });
	QObject::connect(btnSortT, &QPushButton::clicked, [&]() { loadData(srv.sort_tip()); adaugaButoane(srv.sort_tip()); });

	QObject::connect(btnUndo, &QPushButton::clicked, this, &LocatarGUI::undo);

	QObject::connect(btnNot1, &QPushButton::clicked, [&]() {
		NotificariGUI* gui2 = new NotificariGUI{ srv, srv.getNotif()};
		gui2->setWindowTitle("Lista de notifificari");
		gui2->show();
		});
	QObject::connect(btnNot2, &QPushButton::clicked, [&]() {
		NotificariRO* gui3 = new NotificariRO{srv.getNotif() };
		gui3->setWindowTitle("Lista de notifificari");
		gui3->show();
		});

	QObject::connect(btnAddN, &QPushButton::clicked, [&]() {srv.addNotificare(txtApartament->text().toInt()); });
	QObject::connect(btnDelN, &QPushButton::clicked, [&]() {srv.stergeNotificari(); });
	QObject::connect(btnRdmN, &QPushButton::clicked, [&]() {srv.addRandom(txtApartament->text().toInt()); });
}



void LocatarGUI::adaugaButoane(vector <Locatar>& locatari)
{
	while (QLayoutItem* buton = butoane->takeAt(0))
	{
		delete buton->widget();
		delete buton;
	}
	for (const auto& l : locatari)
	{
		auto btn = new QPushButton{ QString::number(l.getApartament()) };

		butoane->addWidget(btn);

		QObject::connect(btn, &QPushButton::clicked, [this, btn, l]() {
			try {
				srv.deletee(btn->text().toInt());
				loadData(srv.getAll());
				delete btn;
			}
			catch (RepoException & ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
			}

			});
	}
}


void LocatarGUI::adauga()
{
	try {
		srv.add(txtApartament->text().toInt(), txtProprietar->text().toStdString(), txtSuprafata->text().toInt(), txtTip->text().toStdString());
		loadData(srv.getAll());
		//QPushButton* btn = new QPushButton{ QString::number(txtApartament->text().toInt()) };
		//adaugaButon(btn);
		adaugaButoane(srv.getAll());
	}
	catch (RepoException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
	}
	catch (ValidatorException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
	}

}

void LocatarGUI::sterge()
{
	try {
		srv.deletee(txtApartament->text().toInt());
		loadData(srv.getAll());
		adaugaButoane(srv.getAll());

	}
	catch (RepoException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void LocatarGUI::modifica()
{
	try {
		srv.change(txtApartament->text().toInt(), txtProprietar->text().toStdString(), txtSuprafata->text().toInt(), txtTip->text().toStdString());
		loadData(srv.getAll());
	}
	catch (RepoException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
	}
	catch (ValidatorException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
	}

}

void LocatarGUI::cauta()
{
	try {
		auto l = srv.search(txtApartament->text().toInt());
		loadData(srv.getAll());
		txtApartament->setText(QString::number(l.getApartament()));
		txtProprietar->setText(QString::fromStdString(l.getProprietar()));
		txtSuprafata->setText(QString::number(l.getSuprafata()));
		txtTip->setText(QString::fromStdString(l.getTip()));
	}
	catch (RepoException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void LocatarGUI::fltrSrf()
{
	auto locatari = srv.filtr_suprafata(txtSuprafata->text().toInt());
	if (locatari.size() == 0)
		QMessageBox::information(this, "info", "Nu exista locatari cu aceasta suprafata!!!");
	else loadData(locatari);
}

void LocatarGUI::fltrTip()
{
	auto locatari = srv.filtr_tip(txtTip->text().toStdString());
	if (locatari.size() == 0)
		QMessageBox::information(this, "info", "Nu exista locatari cu aceast tip!!!");
	else loadData(locatari);
}

void LocatarGUI::undo()
{
	try {
		srv.undo();
		loadData(srv.getAll());
	}
	catch (LocatarException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}


void NotificariGUI::loadData(vector <Locatar>& locatari)
{
	lst->clear();
	for (const auto& l : locatari)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::number(l.getApartament()));
		item->setData(Qt::UserRole, QString::fromStdString(l.getProprietar()));
		lst->addItem(item);
	}
}

void NotificariGUI::initGUI() {

	setLayout(ly);



	lst->addItem("item1");
	ly->addWidget(lst, 0, 0);



	ly->addWidget(btnAdd, 3, 1);
	ly->addWidget(btnDel, 3, 2);
	ly->addWidget(btnRandom, 3, 3);


	ly->addWidget(btnUndo, 4, 1);
	ly->addWidget(btnCVS, 4, 2);




	auto formLy = new QFormLayout;
	formLy->addRow("Apartament", txtApartament);
	formLy->addRow("Proprietar", txtProprietar);
	formLy->addRow("Suprafata", txtSuprafata);
	formLy->addRow("Tip", txtTip);


	ly->addWidget(btnExit, 4, 3);

	ly->addLayout(formLy, 0, 2, 2, 2);

}

void NotificariGUI::connectSignalsSlots()
{
	
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty())
		{
			txtApartament->setText("");
			txtProprietar->setText("");
			txtSuprafata->setText("");
			txtTip->setText("");
		}
		else
		{
			auto selItem = sel.at(0);
			auto apartament = selItem->text();
			auto proprietar = selItem->data(Qt::UserRole).toString();
			txtApartament->setText(apartament);
			txtProprietar->setText(proprietar);
			auto l = srv.search(apartament.toInt());
			txtSuprafata->setText(QString::number(l.getSuprafata()));
			txtTip->setText(QString::fromStdString(l.getTip()));
		}
		});

	QObject::connect(btnExit, &QPushButton::clicked, [&]() { QMessageBox msgBox;
	msgBox.setText("Ati apasat butonul Exit");
	msgBox.exec();
	close(); });

	QObject::connect(btnAdd, &QPushButton::clicked, this, &NotificariGUI::adauga);
	QObject::connect(btnDel, &QPushButton::clicked, this, &NotificariGUI::sterge);
	QObject::connect(btnRandom, &QPushButton::clicked, this, &NotificariGUI::addRandom);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &NotificariGUI::undoN);

	QObject::connect(btnCVS, &QPushButton::clicked, this, &NotificariGUI::CVS);

}
void NotificariGUI::adauga()
{

	try {
		srv.addNotificare(txtApartament->text().toInt());
		loadData(srv.getNotificari());
	}
	catch (RepoException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void NotificariGUI::sterge()
{

	srv.stergeNotificari();
	loadData(srv.getNotificari());
}

void NotificariGUI::addRandom()
{

	srv.addRandom(txtApartament->text().toInt());
	loadData(srv.getNotificari());
}

void NotificariGUI::CVS()
{


	try {
		srv.exportaCosCVS(txtProprietar->text().toStdString());
	}
	catch (LocatarException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void NotificariGUI::undoN()
{


	try {
		srv.undoNotificari();
		loadData(srv.getNotificari());
	}
	catch (LocatarException & ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

