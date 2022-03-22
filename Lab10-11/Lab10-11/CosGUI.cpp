#include "CosGUI.h"
#include "tools.h"

void CosGUI::initGUI()
{
	this->setWindowTitle("Magazin");
	this->setWindowIcon(QIcon("market.png"));
	QHBoxLayout* main = new QHBoxLayout;
	QVBoxLayout* lay1 = new QVBoxLayout;
	QVBoxLayout* lay2 = new QVBoxLayout;
	QVBoxLayout* lay3 = new QVBoxLayout;

	setLayout(main);
	QLabel* text1 = new QLabel{ "Produse" };
	text1->setAlignment(Qt::AlignCenter);
	lay1->addWidget(text1);
	lay1->addWidget(tableProduse);
	tableProduse->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableProduse->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableProduse->setSelectionMode(QAbstractItemView::SingleSelection);
	tableProduse->setMinimumHeight(326);
	main->addLayout(lay1);
	
	QLabel* text2 = new QLabel{ "Cos de cumparaturi" };
	text2->setAlignment(Qt::AlignCenter);
	lay2->addWidget(text2);
	lay2->addWidget(editTxt);
	lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
	lblInfo->setAlignment(Qt::AlignCenter);
	lay2->addWidget(lblInfo);
	lay2->addWidget(spinbox);
	lay2->addStretch();
	lay2->addWidget(btnAdauga);
	lay2->addWidget(btnGenereaza);
	lay2->addWidget(btnGoleste);
	lay2->addWidget(btnExport);
	lay2->addWidget(btnReset);
	btnReset->setEnabled(false);
	main->addLayout(lay2);

	tableCos->setSelectionMode(QAbstractItemView::NoSelection);
	tableProduse->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableCos->setMinimumHeight(326);
	QLabel* text3 = new QLabel{ "Cos" };
	text3->setAlignment(Qt::AlignCenter);
	lay3->addWidget(text3);
	lay3->addWidget(tableCos);
	main->addLayout(lay3);
}

void CosGUI::connectSignals()
{
	QObject::connect(tableProduse->horizontalHeader(), &QHeaderView::sectionClicked, this, [=](int index)
		{
			if (index == 0)
			{
				btnReset->setEnabled(true);
				const auto& v = srv.Sorteaza(1, sortNume);
				sortNume = !sortNume;
				addToTable(tableProduse, v);
			}
			else if (index == 2)
			{
				btnReset->setEnabled(true);
				const auto& v = srv.Sorteaza(2, sortPret);
				sortPret = !sortPret;
				addToTable(tableProduse, v);
			}
		});

	QObject::connect(btnReset, &QPushButton::clicked, this, [=]()
		{
			addToTable(tableProduse, srv.GetAll());
			btnReset->setEnabled(false);
			tableProduse->clearSelection();
		});

	QObject::connect(btnAdauga, &QPushButton::clicked, this, [=]()
		{
			auto sel = tableProduse->selectedItems();
			if (sel.isEmpty())
			{
				QMessageBox::critical(this, "Eroare", "Nu ati selectat niciun produs !");
				return;
			}
			string nume = sel.at(0)->data(0).toString().toStdString();
			try
			{
				srv.AdaugaCos(nume);
				addToTable(tableCos, srv.GetAllCos());
				lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
			}
			catch (ValidError& ve) { QMessageBox::critical(this, "Eroare", QString::fromStdString(ve.get_message())); }
			catch (RepoError& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});

	QObject::connect(btnGenereaza, &QPushButton::clicked, this, [=]()
		{
			if (spinbox->text().toInt() <= 0)
			{
				QMessageBox::critical(this, "Eroare", "Numar de produse invalid !");
				return;
			}
			srv.GenereazaCos(spinbox->text().toInt());
			addToTable(tableCos, srv.GetAllCos());
			lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
		});

	QObject::connect(btnGoleste, &QPushButton::clicked, this, [=]()
		{
			try
			{
				srv.GolesteCos();
				addToTable(tableCos, srv.GetAllCos());
				lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
			}
			catch (ValidError& ve) { QMessageBox::critical(this, "Eroare", QString::fromStdString(ve.get_message())); }
			catch (RepoError& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});

	QObject::connect(btnExport, &QPushButton::clicked, this, [=]()
		{
			try
			{
				srv.ExportCos(editTxt->text().toStdString());
				QMessageBox::information(this, "Info", "Export realizat cu succes");
			}
			catch (ValidError& ve) { QMessageBox::critical(this, "Eroare", QString::fromStdString(ve.get_message())); }
			catch (RepoError& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});
}

void CosGUI::addToTable(QTableWidget* table, const vector<Produs>& v)
{
	table->clear();
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("Nume"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Tip"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Pret"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Producator"));
	table->setRowCount(int(v.size()));
	int linie = 0;
	for (const Produs& p : v)
	{
		table->setItem(linie, 0, new QTableWidgetItem(QString::fromStdString(p.get_nume())));
		table->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(p.get_tip())));
		table->setItem(linie, 2, new QTableWidgetItem(QString::number(p.get_pret())));
		table->setItem(linie, 3, new QTableWidgetItem(QString::fromStdString(p.get_producator())));
		linie++;
	}
	
	table->resizeColumnsToContents();
	int width = table->columnWidth(0) + table->columnWidth(1) +
		table->columnWidth(2) + table->columnWidth(3) + 41;
	table->setFixedWidth(width);
}

void CosGUI::update()
{
	addToTable(tableProduse, srv.GetAll());
	addToTable(tableCos, srv.GetAllCos());
	lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
}

void CosGUI::setInitialStateTable()
{
	addToTable(tableProduse,srv.GetAll());
	addToTable(tableCos,srv.GetAllCos());
}

CosGUI::CosGUI(Service& srvi) : srv{ srvi }
{
	srv.addObserver(this);
	initGUI();
	connectSignals();
	setInitialStateTable();
}

CosGUI::~CosGUI()
{
	srv.removeObserver(this);
}

//void CosGUI::closeEvent(QCloseEvent* event)
//{
//	gui.show();
//	QWidget::closeEvent(event);
//}

void CosReadGUI::update()
{
	repaint();
}

CosReadGUI::CosReadGUI(Service& srvi) :srv{ srvi }
{
	srv.addObserver(this);
}

CosReadGUI::~CosReadGUI()
{
	srv.removeObserver(this);
}

void CosReadGUI::paintEvent(QPaintEvent* ev)
{
	QPaintEvent* copie = ev;
	copie = 0;

	QPainter p{ this };
	int x{ 10 }, y{ 10 };
	for (const auto& el : srv.GetAllCos())
	{
		int r{ rand() % 256 }, g{ rand() % 256 }, b{ rand() % 256 };
		p.fillRect(x, y, 40, 40, QColor(r, g, b));
		x += 50;
		if (x + 50 >= this->width())
		{
			x = 10;
			y += 50;
		}

		el.get_nume();
	}
}
