#include "GUI.h"
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <exception>

using std::exception;

void GUI::initGUI()
{
	QHBoxLayout* main = new QHBoxLayout;
	setLayout(main);
	main->addWidget(list);

	QVBoxLayout* lay1 = new QVBoxLayout;

	QFormLayout* editboxuri = new QFormLayout;
	editboxuri->addRow("Nume", edit_numeAbonat);
	editboxuri->addRow("Numar intrari", edit_numarIntrari);


	lay1->addLayout(editboxuri);

	QStringList optiuni = { "Selectati o optiune","Alergare","Inot","Tenis","Fotbal" };
	combo_alege->addItems(optiuni);
	lay1->addWidget(combo_alege);

	QFormLayout* check = new QFormLayout;
	check->addRow("Saptamanal",sapt);
	check->addRow("Lunar",lunar);
	check->addRow("Anual",anual);
	lay1->addLayout(check);
	lay1->addWidget(slider);
	lay1->addWidget(lbl_slider);
	slider->setMinimum(0);
	slider->setMaximum(0);

	lay1->addWidget(btn_adauga);
	lay1->addWidget(btn_filtrare);
	lay1->addWidget(btn_export);
	lay1->addWidget(btn_revenire);

	main->addLayout(lay1);
}

void GUI::connectSignals()
{
	QObject::connect(slider, &QSlider::valueChanged, this, [=]()
		{
			lbl_slider->setText(QString::number(slider->value()));
		});

	QObject::connect(btn_adauga, &QPushButton::clicked, this, [=]()
		{
			try
			{
				string nume = edit_numeAbonat->text().toStdString();
				int nr = edit_numarIntrari->text().toInt();
				double pret{ 0 };
				string tip = "";
				if (combo_alege->currentIndex() == 0)
				{
					QMessageBox::critical(this, "Atentie !", "Selecteaza un tip");
					return;
				}
				if (combo_alege->currentIndex() == 1)
				{
					tip = "Alergare";
					pret = 5 * nr;
				}
				if (combo_alege->currentIndex() == 2)
				{
					tip = "Inot";
					pret = 20 * nr;
				}
				if (combo_alege->currentIndex() == 3)
				{
					tip = "Tenis";
					pret = 40 * nr;
				}
				if (combo_alege->currentIndex() == 4)
				{
					tip = "Fotbal";
					pret = 50 * nr;
				}
				srv.Adauga(nume, tip, pret, nr);
				slider->setMaximum(srv.GetMax());
				addtoList(srv.GetAll());
			}
			catch (exception& e) {
				QMessageBox::critical(this, "Eroare", e.what());
			}
		});

	QObject::connect(btn_export, &QPushButton::clicked, this, [=]()
		{
			try
			{
				srv.Export(slider->value());
				QMessageBox::information(this, "Info", "Export succes !\n");
			}
			catch (exception& e) {
				QMessageBox::critical(this, "Eroare", e.what());
			}
		});

	QObject::connect(btn_revenire, &QPushButton::clicked, this, [=]()
		{
			addtoList(srv.GetAll());
		});

	QObject::connect(btn_filtrare, &QPushButton::clicked, this, [=]()
		{
			try
			{
				bool bsapt=false;
				bool blunar=false;
				bool banual=false;
				if (sapt->isChecked())
					bsapt = true;
				if (lunar->isChecked())
					blunar = true;
				if (anual->isChecked())
					banual = true;
				addtoList(srv.Filtrare(bsapt,blunar,banual));
			}
			catch (exception& e) {
				QMessageBox::critical(this, "Eroare", e.what());
			}
		});
}

void GUI::setInitialState()
{
}

void GUI::addtoList(const vector<Abonament>& v)
{
	list->clear();
	for (const Abonament& a : v)
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(a.get_nume()) + "," + QString::fromStdString(a.get_tip()) + "," + QString::number(a.get_pret()) + "," + QString::number(a.get_intrari()) };
		if(a.get_tip() == "Alergare")
			item->setBackground(QBrush(QColor("red")));
		if(a.get_tip() == "Inot")
			item->setBackground(QBrush(QColor("blue")));
		list->addItem(item);
	}
}

GUI::GUI(Service& srv): srv{srv}
{
	initGUI();
	connectSignals();
	setInitialState();
}
