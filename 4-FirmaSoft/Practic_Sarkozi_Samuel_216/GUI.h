#pragma once
#include "Service.h"
#include "GUI_Filtrat.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <algorithm>

using std::sort;

class GUI : public QWidget, public Observer
{
private:
	Service& srv;

	QTableWidget* table = new QTableWidget{ 0,4 };

	QPushButton* btn_adauga = new QPushButton{ "Adauga" };

	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_descriere = new QLineEdit;
	vector<QLineEdit*>edit_progs;
	QLineEdit* edit_stare = new QLineEdit;
	QLineEdit* edit_search = new QLineEdit;

	void update() override;

	void clearText();

	void initGUI();
	void connectSignals();
	void addToTable(vector<Task> v);
public:
	GUI(Service& srv) :srv{ srv } {
		srv.addObserver(this);
		GUI_Filtrat* gui_open = new GUI_Filtrat{ srv, "Open" };
		GUI_Filtrat* gui_inprog = new GUI_Filtrat{ srv, "Inprogress" };
		GUI_Filtrat* gui_close = new GUI_Filtrat{ srv, "Close" };
		gui_open->show();
		gui_inprog->show();
		gui_close->show();
		initGUI();
		addToTable(srv.GetAll());
		connectSignals();
	}
	~GUI() {
		srv.removeObserver(this);
	}
	void closeEvent(QCloseEvent*) override {
		QApplication::quit();
	}
};

