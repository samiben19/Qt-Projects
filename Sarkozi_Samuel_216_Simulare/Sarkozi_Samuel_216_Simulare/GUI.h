#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qslider.h>
#include <QtWidgets/qlabel.h>
#include "Service.h"

using std::vector;

class GUI: public QWidget
{
private:
	Service& srv;
	QLineEdit* edit_numeAbonat = new QLineEdit;
	QLineEdit* edit_numarIntrari = new QLineEdit;

	QComboBox* combo_alege = new QComboBox;

	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QPushButton* btn_filtrare = new QPushButton{ "Filtrare" };
	QPushButton* btn_export = new QPushButton{ "Export" };
	QPushButton* btn_revenire = new QPushButton{ "Revenire" };

	QListWidget* list = new QListWidget;

	QCheckBox* sapt = new QCheckBox;
	QCheckBox* lunar = new QCheckBox;
	QCheckBox* anual = new QCheckBox;

	QSlider* slider = new QSlider;

	QLabel* lbl_slider = new QLabel{"0"};

	void initGUI();
	void connectSignals();
	void setInitialState();
	void addtoList(const vector<Abonament>& v);
public:
	GUI(Service& srv);
};

