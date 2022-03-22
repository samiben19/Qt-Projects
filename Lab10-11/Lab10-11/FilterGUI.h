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
#include <QtWidgets/qcombobox.h>

class FilterGUI: public QWidget
{
private:
	Service& srv;
	GUI& gui;

	QHBoxLayout* main = new QHBoxLayout;
	QFormLayout* second = new QFormLayout;
	QVBoxLayout* butoane = new QVBoxLayout;

	QTableWidget* tableProduse = new QTableWidget{ 0,4 };

	QComboBox* dropDown = new QComboBox;

	QLabel* lbl1 = new QLabel;
	QLabel* lbl2 = new QLabel;

	QLineEdit* edit1 = new QLineEdit;
	QLineEdit* edit2 = new QLineEdit;

	QPushButton* btnFiltreaza = new QPushButton{ "Filtreaza" };

	void initGUI();
	void connectSignals();
	void setInitialStateTable();
	void addToTable(const vector<Produs>& v);

public:
	//FilterGUI(GUI& g, Service& srv);
	FilterGUI(GUI& g, Service& srv);
	void closeEvent(QCloseEvent* event) override;
};

