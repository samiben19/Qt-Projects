#pragma once
#include "service.h"
#include "GUI.h"
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
#include <QHeaderView>

#include "Observ.h"
#include <qpainter.h>
#include <qpainterpath.h>

class CosGUI : public QWidget, public Observer
{
private:
	Service& srv;
	//GUI& gui;

	QTableWidget* tableProduse = new QTableWidget{ 0,4 };
	QTableWidget* tableCos = new QTableWidget{ 0,4 };

	QPushButton* btnAdauga = new QPushButton{ "Adauga" };
	QPushButton* btnGenereaza = new QPushButton{ "Genereaza" };
	QPushButton* btnGoleste = new QPushButton{ "Goleste" };
	QPushButton* btnExport = new QPushButton{ "Export" };
	QPushButton* btnReset = new QPushButton{ "Reset" };

	QSpinBox* spinbox = new QSpinBox;

	QLabel* lblInfo = new QLabel;

	QLineEdit* editTxt = new QLineEdit;

	bool sortNume = true;
	bool sortPret = true;

	void initGUI();
	void connectSignals();
	void setInitialStateTable();

	void addToTable(QTableWidget* table, const vector<Produs>& v);
	void update() override;

public:
	CosGUI(Service& srvi);
	~CosGUI();
	//void closeEvent(QCloseEvent* event) override;
};


class CosReadGUI : public QWidget, public Observer
{
private:
	Service& srv;
	void update() override;
public:
	CosReadGUI(Service& srvi);
	~CosReadGUI();

	void paintEvent(QPaintEvent* ev) override;
};