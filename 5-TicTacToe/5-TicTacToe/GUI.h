#pragma once
#include "Service.h"
#include "MyModel.h"
#include <algorithm>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qlabel.h>

using std::count_if;

class GUI_tabla : public QWidget, public Observer
{
private:
	Service& srv;
	int id;
	string tabla;
	long long ocupate;
	Joc joc;

	QLabel* lbl_jucator = new QLabel;
	QVBoxLayout* lay_main = new QVBoxLayout;
	vector<vector<QPushButton*>>butoane;
	vector<QHBoxLayout*>rows;

	void update() override {
		joc = srv.Cauta(id);
		ocupate = count_if(tabla.begin(), tabla.end(), [](const char& c) {return c == 'X' || c == 'O'; });
		lbl_jucator->setText("Jucatorul curent: " + QString::fromStdString(joc.get_urmator()) + "\nStarea jocului: " + QString::fromStdString(joc.get_stare()));
		initTable();
		connectSignals();
	}

	void initGUI() {
		setLayout(lay_main);
		lbl_jucator->setText("Jucatorul curent: " + QString::fromStdString(joc.get_urmator()) + "\nStarea jocului: " + QString::fromStdString(joc.get_stare()));
		lbl_jucator->setAlignment(Qt::AlignCenter);
		lay_main->addWidget(lbl_jucator);
	}

	void initTable() {
		for (int i = 0; i < butoane.size(); i++)
		{
			delete rows[i];
			for (int j = 0; j < butoane.size(); j++)
				delete butoane[i][j];
		}

		int dim = joc.get_dim();
		tabla = joc.get_tabla();
		int curent = 0;

		butoane.resize(dim);
		rows.resize(dim);
		for (auto& el : butoane) el.resize(dim);

		for (int i = 0; i < dim; i++)
		{
			QHBoxLayout* row = new QHBoxLayout;
			for (int j = 0; j < dim; j++)
			{
				if (tabla[curent] == '-')
					butoane[i][j] = new QPushButton{ "" };
				else
					butoane[i][j] = new QPushButton{ QString(tabla[curent]) };
				curent++;
				row->addWidget(butoane[i][j]);
				butoane[i][j]->setMinimumHeight(100);
				butoane[i][j]->setMinimumWidth(100);
			}
			lay_main->addLayout(row);
		}
	}

	void connectSignals(){
		for (int i = 0; i < joc.get_dim(); i++)
		{
			for (int j = 0; j < joc.get_dim(); j++)
			{
				QObject::connect(butoane[i][j], &QPushButton::clicked, [=]() {
					if (butoane[i][j]->text() == "" && joc.get_stare() != "Terminat")
					{
						ocupate++;
						
						butoane[i][j]->setText(QString::fromStdString(joc.get_urmator()));

						bool X = false, O = false;
						if (joc.get_urmator() == "X")
						{
							joc.set_urmator("O");
							tabla.replace(tabla.begin() + (i * joc.get_dim() + j), tabla.begin() + (i * joc.get_dim() + j) + 1, "X");
							X = verifica(i, j, "X");
						}
						else
						{
							joc.set_urmator("X");
							tabla.replace(tabla.begin() + (i * joc.get_dim() + j), tabla.begin() + (i * joc.get_dim() + j) + 1, "O");
							O = verifica(i, j, "O");
						}
						if (X)
						{
							srv.Modifica(id, joc.get_dim(), tabla, joc.get_urmator(), "Terminat");
							lbl_jucator->setText("Jucatorul curent: " + QString::fromStdString(joc.get_urmator()) + "\nStarea jocului: " + QString::fromStdString(joc.get_stare()));
							QMessageBox::information(this, "TicTacToe", "Jucatorul X a castigat !");
							return;
						}
						if (O)
						{
							srv.Modifica(id, joc.get_dim(), tabla, joc.get_urmator(), "Terminat");
							lbl_jucator->setText("Jucatorul curent: " + QString::fromStdString(joc.get_urmator()) + "\nStarea jocului: " + QString::fromStdString(joc.get_stare()));
							QMessageBox::information(this, "TicTacToe", "Jucatorul O a castigat !");
							return;
						}
						if (ocupate == joc.get_dim() * joc.get_dim())
						{
							srv.Modifica(id, joc.get_dim(), tabla, joc.get_urmator(), "Terminat");
							lbl_jucator->setText("Jucatorul curent: " + QString::fromStdString(joc.get_urmator()) + "\nStarea jocului: " + QString::fromStdString(joc.get_stare()));
							QMessageBox::information(this, "TicTacToe", "Remiza !");
							return;
						}
						srv.Modifica(id, joc.get_dim(), tabla, joc.get_urmator(), "In derulare");
						lbl_jucator->setText("Jucatorul curent: " + QString::fromStdString(joc.get_urmator()) + "\nStarea jocului: " + QString::fromStdString(joc.get_stare()));
					}
					});
			}
		}
	}

	// Vom verifica doar linia si coloana sau si diagonalele daca este cazul
	bool verifica(int linie, int coloana, QString curent){
		int pe_linie{ 0 }, pe_coloana{ 0 }, dP{ 0 }, dS{ 0 };
		for (int i = 0; i < joc.get_dim(); i++)
		{
			if (butoane[linie][i]->text() == curent)
				pe_linie++;
			if (butoane[i][coloana]->text() == curent)
				pe_coloana++;
			if (linie == coloana && butoane[i][i]->text() == curent)
				dP++;
			if (linie + coloana == joc.get_dim() - 1 && butoane[i][joc.get_dim() - 1 - i]->text() == curent)
				dS++;
		}
		if (pe_linie == joc.get_dim() || pe_coloana == joc.get_dim() || dP == joc.get_dim() || dS == joc.get_dim())
			return true;
		return false;
	}
public:
	GUI_tabla(Service& srv, int id) :srv{ srv }, id{ id }, joc{ srv.Cauta(id) }, ocupate{ count_if(tabla.begin(), tabla.end(), [](const char& c) {return c == 'X' || c == 'O'; }) } {
		srv.addObserver(this);
		initGUI();
		initTable();
		connectSignals();
	}
	~GUI_tabla() {
		srv.removeObserver(this);
	}
};

class GUI : public QWidget, public Observer
{
private:
	Service& srv;
	int id = -5;

	MyModel* model; 
	QTableView* table = new QTableView;

	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_dim = new QLineEdit;
	QLineEdit* edit_tabla = new QLineEdit;
	QLineEdit* edit_urmator = new QLineEdit;
	QLineEdit* edit_stare = new QLineEdit;

	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QPushButton* btn_modifica = new QPushButton{ "Modifica" };
	QPushButton* btn_joaca = new QPushButton{ "Joaca" };

	void update() override {
		model->update();
		resize_table();
	}

	void initGUI(){
		model = new MyModel{ srv };
		table->setModel(model);
		table->show();
		resize_table();

		QHBoxLayout* lay_main = new QHBoxLayout;
		setLayout(lay_main);

		lay_main->addWidget(table);
		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);
		table->setSelectionMode(QAbstractItemView::SingleSelection);
		table->setMinimumHeight(326);

		QVBoxLayout* lay_dreapta = new QVBoxLayout;

		QFormLayout* form = new QFormLayout;
		form->addRow("ID", edit_id);
		form->addRow("Dimensiune", edit_dim);
		form->addRow("Tabla", edit_tabla);
		form->addRow("Urmatorul Jucator", edit_urmator);
		form->addRow("Stare", edit_stare);
		lay_dreapta->addLayout(form);

		lay_dreapta->addStretch();

		lay_dreapta->addWidget(btn_adauga);
		lay_dreapta->addWidget(btn_modifica);
		lay_dreapta->addWidget(btn_joaca);

		lay_main->addLayout(lay_dreapta);
	}

	void clear_text() {
		edit_id->clear();
		edit_dim->clear();
		edit_tabla->clear();
		edit_urmator->clear();
		edit_stare->clear();
	}

	void resize_table() {
		id = -5;
		table->clearSelection();
		table->resizeColumnsToContents();
		int width = table->columnWidth(0) + table->columnWidth(1) +
			table->columnWidth(2) + table->columnWidth(3) + table->columnWidth(4) + 41;
		table->setMinimumWidth(width);
	}

	void connectSignals(){
		QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [=]() {
			clear_text();
			auto sel = table->selectionModel()->selectedIndexes();

			if (sel.isEmpty())
			{
				id = -5;
				return;
			}

			int selRow = sel.at(0).row();
			auto cellIndex = table->model()->index(selRow, 0);
			id = table->model()->data(cellIndex, Qt::DisplayRole).toInt();

			try {
				auto joc = srv.Cauta(id);
				edit_id->setText(QString::number(joc.get_id()));
				edit_dim->setText(QString::number(joc.get_dim()));
				edit_tabla->setText(QString::fromStdString(joc.get_tabla()));
				edit_urmator->setText(QString::fromStdString(joc.get_urmator()));
				edit_stare->setText(QString::fromStdString(joc.get_stare()));
			}
			catch (exception& ex) { QMessageBox::critical(this, "Eroare", ex.what()); }
			});
		QObject::connect(btn_adauga, &QPushButton::clicked, this, [=]() {

			int dim = edit_dim->text().toInt();
			string tabla = edit_tabla->text().toStdString();
			string urmator = edit_urmator->text().toStdString();
			string stare = "Neinceput";

			try {
				srv.Adauga(dim, tabla, urmator, stare);
				model->update();
				resize_table();
			}
			catch (exception& ex) { QMessageBox::critical(this, "Eroare", ex.what()); }
			});
		QObject::connect(btn_modifica, &QPushButton::clicked, this, [=]() {
			int id = edit_id->text().toInt();
			int dim_noua = edit_dim->text().toInt();
			string tabla_noua = edit_tabla->text().toStdString();
			string urmator_nou = edit_urmator->text().toStdString();
			string stare_noua = edit_stare->text().toStdString();

			try {
				srv.Modifica(id, dim_noua, tabla_noua, urmator_nou, stare_noua);
				model->update();
				resize_table();
			}
			catch (exception& ex) { QMessageBox::critical(this, "Eroare", ex.what()); }
			});
		QObject::connect(btn_joaca, &QPushButton::clicked, this, [=]() {
			if (id == -5)
			{
				QMessageBox::critical(this, "Eroare", "Selectati un joc !");
				return;
			}
			GUI_tabla* joc_nou = new GUI_tabla{ srv, id };
			joc_nou->show();
			});
	}
public:
	GUI(Service& srv) :srv{ srv } {
		srv.addObserver(this);
		initGUI();
		connectSignals();
	}
	~GUI() {
		srv.removeObserver(this);
	}
};

