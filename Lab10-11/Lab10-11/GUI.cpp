#include "GUI.h"
#include "FilterGUI.h"
#include "CosGUI.h"
#include "tools.h"

GUI::GUI(Service& srv) : srv{ srv }
{
	srv.addObserver(this);
	initGUI();
	connectSignals();
	setInitialStateList();
	setInitialStateTable();
}

GUI::~GUI()
{
	srv.removeObserver(this);
}

void GUI::setInitialStateList()
{
	addToList(srv.GetAll());
}

void GUI::setInitialStateTable()
{
	addToTable(srv.GetAll());
}

void GUI::closeEvent(QCloseEvent* event)
{
	QWidget::closeEvent(event);
	QApplication::quit();
}

void GUI::update()
{
	addToList(srv.GetAll());
	addToTable(srv.GetAll());
	lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
}

void GUI::initGUI()
{
	this->setWindowTitle("Magazin");
	this->setWindowIcon(QIcon("market.png"));
	QHBoxLayout* main = new QHBoxLayout;
	QVBoxLayout* main_v = new QVBoxLayout;
	setLayout(main);
	main->addWidget(listProduse);
	tableProduse->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableProduse->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableProduse->setSelectionMode(QAbstractItemView::SingleSelection);
	tableProduse->setMinimumHeight(326);
	main_v->addWidget(tableProduse);
	main_v->addWidget(btnReset);
	btnReset->setEnabled(false);
	btnUndo->setEnabled(false);
	main->addLayout(main_v);

	//main->addStretch();
	QVBoxLayout* second = new QVBoxLayout;
	QFormLayout* form = new QFormLayout;
	form->addRow("Nume", editNume);
	form->addRow("Tip", editTip);
	form->addRow("Pret", editPret);
	form->addRow("Producator", editProducator);

	second->addLayout(form);
	
	//second->addStretch();
	QHBoxLayout* line1 = new QHBoxLayout;
	line1->addWidget(btnAdauga);
	line1->addWidget(btnModifica);
	line1->addWidget(btnSterge);
	second->addLayout(line1);

	QHBoxLayout* line2 = new QHBoxLayout;
	line2->addWidget(btnCauta);
	line2->addWidget(btnFiltreaza);
	line2->addWidget(btnUndo);
	second->addLayout(line2);

	second->addStretch();

	lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
	lblInfo->setAlignment(Qt::AlignCenter);
	second->addWidget(lblInfo);

	lblSlider->setText(QString::number(slider->value()));
	lblSlider->setAlignment(Qt::AlignCenter);
	second->addWidget(lblSlider);
	slider->setOrientation(Qt::Horizontal);
	slider->setRange(0, 100);
	second->addWidget(slider);
	QHBoxLayout* line3 = new QHBoxLayout;
	line3->addWidget(btnCos);
	line3->addWidget(btnCosRONLY);
	second->addLayout(line3);

	QHBoxLayout* line4 = new QHBoxLayout;
	line4->addWidget(btnAdaugaCos);
	line4->addWidget(btnGenereazaCos);
	line4->addWidget(btnGolesteCos);
	second->addLayout(line4);

	main->addLayout(second);
}

void GUI::connectSignals()
{
	QObject::connect(slider, &QSlider::valueChanged, this, [=]()
		{
			lblSlider->setText(QString::number(slider->value()));
		});

	QObject::connect(tableProduse, &QTableWidget::itemSelectionChanged, this, [=]() 
		{
			auto sel = tableProduse->selectedItems();
			if (sel.isEmpty())
				return;
			auto select = tableProduse->selectionModel()->selectedRows();
			QModelIndex index = select.at(0);
			if(indexSelected >= 0)
				listProduse->item(indexSelected)->setBackground(QBrush(QColor("white")));
			indexSelected = index.row();
			listProduse->clearSelection();
			listProduse->selectionModel()->setCurrentIndex(index, QItemSelectionModel::SelectionFlag::Select);
			listProduse->item(indexSelected)->setBackground(QBrush(QColor("lime")));

			editNume->setText(sel.at(0)->data(0).toString());
			editTip->setText(sel.at(1)->data(0).toString());
			editPret->setText(sel.at(2)->data(0).toString());
			editProducator->setText(sel.at(3)->data(0).toString());
		});

	QObject::connect(listProduse, &QListWidget::itemSelectionChanged, this, [=]()
		{
			auto sel = listProduse->selectedItems();
			if (sel.isEmpty())
				return;
			auto select = listProduse->selectionModel()->selectedRows();
			QModelIndex index = select.at(0);
			if (indexSelected >= 0)
				listProduse->item(indexSelected)->setBackground(QBrush(QColor("white")));
			indexSelected = index.row();
			listProduse->clearSelection();
			listProduse->item(indexSelected)->setBackground(QBrush(QColor("lime")));
			tableProduse->selectRow(indexSelected);

			QString info = sel.at(0)->data(Qt::UserRole).toString();
			auto info2 = info.split(";");
			editNume->setText(info2.at(0));
			editTip->setText(info2.at(1));
			editPret->setText(info2.at(2));
			editProducator->setText(info2.at(3));
		});

	//auto header = tableProduse->horizontalHeader();
	QObject::connect(tableProduse->horizontalHeader(), &QHeaderView::sectionClicked, this, [=](int index)
		{
			if (index == 0)
			{
				btnReset->setEnabled(true);
				btnModifica->setEnabled(false);
				btnSterge->setEnabled(false);
				const auto& v = srv.Sorteaza(1, sortNume);
				sortNume = !sortNume;
				addToTable(v);
				addToList(v);
				tableProduse->clearSelection();
				listProduse->clearSelection();
			}
			else if (index == 1)
			{
				btnReset->setEnabled(true);
				btnModifica->setEnabled(false);
				btnSterge->setEnabled(false);
				const auto& v = srv.Sorteaza(3, sortTip);
				sortTip= !sortTip;
				addToTable(v);
				addToList(v);
				tableProduse->clearSelection();
				listProduse->clearSelection();
				editNume->clear();
				editTip->clear();
				editPret->clear();
				editProducator->clear();
			}
			else if (index == 2)
			{
				btnReset->setEnabled(true);
				btnModifica->setEnabled(false);
				btnSterge->setEnabled(false);
				const auto& v = srv.Sorteaza(2, sortPret);
				sortPret = !sortPret;
				addToTable(v);
				addToList(v);
				tableProduse->clearSelection();
				listProduse->clearSelection();
				editNume->clear();
				editTip->clear();
				editPret->clear();
				editProducator->clear();
			}
		});

	QObject::connect(btnReset, &QPushButton::clicked, this, [=]()
		{
			addToTable(srv.GetAll());
			addToList(srv.GetAll());
			tableProduse->clearSelection();
			btnReset->setEnabled(false);
			btnModifica->setEnabled(true);
			btnSterge->setEnabled(true);
			editNume->clear();
			editTip->clear();
			editPret->clear();
			editProducator->clear();
			sortNume = true;
			sortTip = true;
			sortPret = true;
		});
	QObject::connect(btnAdauga, &QPushButton::clicked, this, [=]()
		{
			string nume = editNume->text().toStdString();
			string tip = editTip->text().toStdString();
			double pret = editPret->text().toDouble();
			string producator = editProducator->text().toStdString();
			try 
			{ 
				srv.Adauga(nume, tip, pret, producator);  
				indexSelected = int(srv.GetAll().size()) - 1;
				operatii++;
				btnUndo->setEnabled(true);
				addToTable(srv.GetAll()); 
				addToList(srv.GetAll());
			}
			catch (ValidError& ve) { QMessageBox::critical(this, "Eroare", QString::fromStdString(ve.get_message())); }
			catch (RepoError& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});

	QObject::connect(btnModifica, &QPushButton::clicked, this, [=]()
		{
			string nume = editNume->text().toStdString();
			string tip = editTip->text().toStdString();
			double pret = editPret->text().toDouble();
			string producator = editProducator->text().toStdString();
			try 
			{
				srv.Modifica(indexSelected + 1, nume, tip, pret, producator);
				operatii++;
				btnUndo->setEnabled(true);
				addToTable(srv.GetAll());
				addToList(srv.GetAll());
			}
			catch (ValidError& ve) { QMessageBox::critical(this, "Eroare", QString::fromStdString(ve.get_message())); }
			catch (RepoError& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});

	QObject::connect(btnSterge, &QPushButton::clicked, this, [=]()
		{
			try
			{
				srv.Sterge(indexSelected + 1);
				operatii++;
				btnUndo->setEnabled(true);
				addToTable(srv.GetAll());
				addToList(srv.GetAll());
			}
			catch (ValidError& ve) { QMessageBox::critical(this, "Eroare", QString::fromStdString(ve.get_message())); }
			catch (RepoError& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});

	QObject::connect(btnCauta, &QPushButton::clicked, this, [=]()
		{
			try
			{
				string nume = editNume->text().toStdString();
				const Produs& gasit = srv.Cauta_nume(nume);
				editNume->setText(QString::fromStdString(gasit.get_nume()));
				editTip->setText(QString::fromStdString(gasit.get_tip()));
				editPret->setText(QString::number(gasit.get_pret()));
				editProducator->setText(QString::fromStdString(gasit.get_producator()));
				for (int i = 0; i < tableProduse->rowCount(); i++)
				{
					tableProduse->setSelectionBehavior(QAbstractItemView::SelectRows);
					tableProduse->setSelectionMode(QAbstractItemView::SingleSelection);
					tableProduse->selectRow(i);
					auto select = tableProduse->selectionModel()->selectedRows();
					QModelIndex index = select.at(0);
					
					listProduse->clearSelection();
					listProduse->selectionModel()->setCurrentIndex(listProduse->model()->index(i, 0), QItemSelectionModel::SelectionFlag::Select);
					//listProduse->selectionModel()->setCurrentIndex(index, QItemSelectionModel::SelectionFlag::Select);
					indexSelected = i;
					//if (iequals(listProduse->selectedItems().at(0)->data(0).toString().toLower().toStdString(), nume))
						//break;
					if (iequals(tableProduse->selectedItems().at(0)->data(0).toString().toLower().toStdString(),nume))
						break;
				}
			}
			catch (RepoError& re) { 
				tableProduse->clearSelection();
				indexSelected = -5;
				QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(btnUndo, &QPushButton::clicked, this, [=]()
		{
			try 
			{ 
				srv.Undo();
				operatii--;
				if(operatii == 0)
					btnUndo->setEnabled(false);
				addToTable(srv.GetAll());
				addToList(srv.GetAll());
			}
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});

	QObject::connect(btnFiltreaza, &QPushButton::clicked, this, [=]()
		{
			FilterGUI* f = new FilterGUI{ *this, srv };
			f->setWindowTitle("Filtrare");
			f->setWindowIcon(QIcon("market.png"));
			f->show();
			this->hide();
		});

	QObject::connect(btnCos, &QPushButton::clicked, this, [=]()
		{
			CosGUI* f = new CosGUI{ srv };
			f->setWindowTitle("Cos");
			f->setWindowIcon(QIcon("market.png"));
			f->show();
		});
	
	QObject::connect(btnCosRONLY, &QPushButton::clicked, this, [=]()
		{
			CosReadGUI* f = new CosReadGUI{ srv };
			f->setWindowTitle("Cos ReadOnly");
			f->setWindowIcon(QIcon("market.png"));
			f->show();
		});

	QObject::connect(btnAdaugaCos, &QPushButton::clicked, this, [=]()
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
				lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
			}
			catch (ValidError& ve) { QMessageBox::critical(this, "Eroare", QString::fromStdString(ve.get_message())); }
			catch (RepoError& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});

	QObject::connect(btnGenereazaCos, &QPushButton::clicked, this, [=]()
		{
			if (slider->value() <= 0)
			{
				QMessageBox::critical(this, "Eroare", "Numar de produse invalid !");
				return;
			}
			srv.GenereazaCos(slider->value());
			lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
		});

	QObject::connect(btnGolesteCos, &QPushButton::clicked, this, [=]()
		{
			try
			{
				srv.GolesteCos();
				lblInfo->setText("Produse in cos: " + QString::number(srv.GetAllCos().size()) + "\nPret total: " + QString::number(srv.GetTotalCos()));
			}
			catch (ValidError& ve) { QMessageBox::critical(this, "Eroare", QString::fromStdString(ve.get_message())); }
			catch (RepoError& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
			catch (ServiceError& se) { QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); }
		});
}

void GUI::addToList(const vector<Produs>& v)
{
	listProduse->clear();
	indexSelected = -5;
	for (const Produs& p : v)
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(p.get_nume()) };
		QString info = QString::fromStdString(p.get_nume()) + ";" + QString::fromStdString(p.get_tip()) + ";" + QString::number(p.get_pret()) + ";" + QString::fromStdString(p.get_producator());
		item->setData(Qt::UserRole, info);
		listProduse->addItem(item);
	}
	if (indexSelected == -5)
	{
		listProduse->clearSelection();
		editNume->setText("");
		editTip->setText("");
		editPret->setText("");
		editProducator->setText("");
	}
}

void GUI::addToTable(const vector<Produs>& v)
{
	tableProduse->clear();
	indexSelected = -5;
	tableProduse->setHorizontalHeaderItem(0, new QTableWidgetItem("Nume"));
	tableProduse->setHorizontalHeaderItem(1, new QTableWidgetItem("Tip"));
	tableProduse->setHorizontalHeaderItem(2, new QTableWidgetItem("Pret"));
	tableProduse->setHorizontalHeaderItem(3, new QTableWidgetItem("Producator"));
	tableProduse->setRowCount(int(v.size()));
	int linie = 0;
	for (const Produs& p : v)
	{
		tableProduse->setItem(linie, 0, new QTableWidgetItem(QString::fromStdString(p.get_nume())));
		tableProduse->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(p.get_tip())));
		tableProduse->setItem(linie, 2, new QTableWidgetItem(QString::number(p.get_pret())));
		tableProduse->setItem(linie, 3, new QTableWidgetItem(QString::fromStdString(p.get_producator())));
		linie++;
	}
	if (indexSelected == -5)
	{
		tableProduse->clearSelection();
		editNume->setText("");
		editTip->setText("");
		editPret->setText("");
		editProducator->setText("");
	}
	tableProduse->selectRow(indexSelected);
	tableProduse->resizeColumnsToContents();
	int width = tableProduse->columnWidth(0) + tableProduse->columnWidth(1) +
		tableProduse->columnWidth(2) + tableProduse->columnWidth(3) + 41;
	tableProduse->setFixedWidth(width);
}
