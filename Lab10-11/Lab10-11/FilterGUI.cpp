#include "FilterGUI.h"

FilterGUI::FilterGUI(GUI& g, Service& srv) :gui{ g }, srv { srv }
{
	initGUI();
	connectSignals();
	setInitialStateTable();
}

void FilterGUI::closeEvent(QCloseEvent* event)
{
	gui.show();
	QWidget::closeEvent(event);
}

void FilterGUI::initGUI()
{
	setLayout(main);
	tableProduse->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableProduse->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableProduse->setSelectionMode(QAbstractItemView::SingleSelection);
	tableProduse->setMinimumHeight(326);
	main->addWidget(tableProduse);

	QStringList commands = { "Selectati un filtru", "Nume", "Pret", "Producator" };
	dropDown->addItems(commands);

	second->addRow("Filtru",dropDown);
	second->addRow(lbl1,edit1);
	second->addRow(lbl2,edit2);

	lbl1->hide();
	edit1->hide();
	lbl2->hide();
	edit2->hide();

	butoane->addStretch();
	butoane->addWidget(btnFiltreaza);
	second->addRow(butoane);

	main->addLayout(second);
}

void FilterGUI::connectSignals()
{
	QObject::connect(btnFiltreaza, &QPushButton::clicked, this, [=]()
		{
			try
			{
				if (dropDown->currentText() == "Nume")
					addToTable(srv.Filtrare_nume(edit1->text().toStdString()));
				else if (dropDown->currentText() == "Pret")
				{
					auto minp = edit1->text().toDouble(), maxp = edit2->text().toDouble();
					if (maxp < minp)
						std::swap(minp, maxp);
					addToTable(srv.Filtrare_pret(minp, maxp));
				}
				else if (dropDown->currentText() == "Producator")
					addToTable(srv.Filtrare_producator(edit1->text().toStdString()));
			}
			catch(ServiceError& se) { 
				QMessageBox::critical(this, "Eroare", QString::fromStdString(se.get_message())); 
				setInitialStateTable();
			}
		});

	QObject::connect(dropDown, &QComboBox::currentTextChanged, this, [=]()
		{
			if (dropDown->currentText() == "Nume")
			{
				lbl2->hide();
				edit2->hide();

				lbl1->setText("Nume");
				edit1->clear();
				lbl1->show();
				edit1->show();
			}
			else if (dropDown->currentText() == "Pret")
			{
				lbl1->setText("Pret minim");
				edit1->clear();
				lbl1->show();
				edit1->show();

				lbl2->setText("Pret maxim");
				edit2->clear();
				lbl2->show();
				edit2->show();
			}
			else if (dropDown->currentText() == "Producator")
			{
				lbl2->hide();
				edit2->hide();

				lbl1->setText("Producator");
				edit1->clear();
				lbl1->show();
				edit1->show();
			}
			else
				setInitialStateTable();
		});
}

void FilterGUI::setInitialStateTable()
{
	dropDown->setCurrentIndex(0);
	tableProduse->clear();
	edit1->clear();
	edit2->clear();

	lbl1->hide();
	edit1->hide();
	lbl2->hide();
	edit2->hide();
	tableProduse->setRowCount(0);

	tableProduse->setHorizontalHeaderItem(0, new QTableWidgetItem("Nume"));
	tableProduse->setHorizontalHeaderItem(1, new QTableWidgetItem("Tip"));
	tableProduse->setHorizontalHeaderItem(2, new QTableWidgetItem("Pret"));
	tableProduse->setHorizontalHeaderItem(3, new QTableWidgetItem("Producator"));
	tableProduse->resizeColumnsToContents();
	int width = tableProduse->columnWidth(0) + tableProduse->columnWidth(1) +
		tableProduse->columnWidth(2) + tableProduse->columnWidth(3) + 41;
	tableProduse->setFixedWidth(width);
	//editText->hide();
	//editPretMin->hide();
	//editPretMax->hide();
}

void FilterGUI::addToTable(const vector<Produs>& v)
{
	//edit1->clear();
	//edit2->clear();
	
	tableProduse->clear();
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
	tableProduse->resizeColumnsToContents();
	int width = tableProduse->columnWidth(0) + tableProduse->columnWidth(1) +
		tableProduse->columnWidth(2) + tableProduse->columnWidth(3) + 41;
	tableProduse->setFixedWidth(width);
}