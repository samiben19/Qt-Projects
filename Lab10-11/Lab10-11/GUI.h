#pragma once
#include "service.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qslider.h>
#include <QHeaderView>

class GUI: public QWidget, public Observer
{
private:
	Service& srv;
	QListWidget* listProduse = new QListWidget;
	QTableWidget* tableProduse = new QTableWidget{ 0,4 };

	QLineEdit* editNume = new QLineEdit;
	QLineEdit* editTip = new QLineEdit;
	QLineEdit* editPret = new QLineEdit;
	QLineEdit* editProducator = new QLineEdit;
	QPushButton* btnReset = new QPushButton{ "Reset" };

	QPushButton* btnAdauga = new QPushButton{ "Adauga" };
	QPushButton* btnModifica = new QPushButton{ "Modifica" };
	QPushButton* btnSterge = new QPushButton{ "Sterge" };
	QPushButton* btnCauta = new QPushButton{ "Cauta" };
	QPushButton* btnFiltreaza = new QPushButton{ "Filtreaza" };
	QPushButton* btnUndo = new QPushButton{ "Undo" };

	QPushButton* btnCos = new QPushButton{ "Cos" };
	QPushButton* btnCosRONLY = new QPushButton{ "Cos ReadOnly" };
	QPushButton* btnAdaugaCos = new QPushButton{ "Adauga in cos" };
	QPushButton* btnGenereazaCos = new QPushButton{ "Genereaza cos" };
	QPushButton* btnGolesteCos = new QPushButton{ "Goleste cos" };
	QSlider* slider = new QSlider;
	QLabel* lblSlider = new QLabel;
	QLabel* lblInfo = new QLabel;

	int indexSelected = -5;
	int operatii = 0;
	bool sortNume = true;
	bool sortTip = true;
	bool sortPret = true;

	void initGUI();
	void connectSignals();
	void setInitialStateTable();
	void setInitialStateList();
	void addToList(const vector<Produs>& v);
	void addToTable(const vector<Produs>& v);
	
	void update() override;
public:
	GUI(Service& srv);
	~GUI();
	void closeEvent(QCloseEvent* event) override;
};

