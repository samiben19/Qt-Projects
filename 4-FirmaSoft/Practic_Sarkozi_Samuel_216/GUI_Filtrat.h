#pragma once
#include "Service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <algorithm>

class GUI_Filtrat : public QWidget, public Observer
{
private:
	Service& srv;
	string stare;
	string mod;
	int id = -5;

	QTableWidget* table = new QTableWidget{ 0,4 };

	QPushButton* btn_open = new QPushButton{ "Open" };
	QPushButton* btn_inprog = new QPushButton{ "Inprogress" };
	QPushButton* btn_close = new QPushButton{ "Close" };

	void update() override;

	void initGUI();
	void connectSignals();
	void addToTable(vector<Task> v);
public:
	GUI_Filtrat(Service& srv, string stare) : srv{ srv }, mod{ "stare" }, stare{ stare }{
		srv.addObserver(this);
		initGUI();
		addToTable(srv.Search(mod, stare));
		connectSignals();
	}
	~GUI_Filtrat() {
		srv.removeObserver(this);
	}
};

