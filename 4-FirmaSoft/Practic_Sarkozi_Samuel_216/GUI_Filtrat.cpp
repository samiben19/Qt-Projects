#include "GUI_Filtrat.h"

void GUI_Filtrat::update()
{
	addToTable(srv.Search(mod, stare));
}

void GUI_Filtrat::initGUI()
{
	// Setam numele ferestrei
	this->setWindowTitle(QString::fromStdString(stare));

	// Setam layoutul principal (tabel sub care punem 3 butoane)
	QVBoxLayout* lay_main = new QVBoxLayout;
	setLayout(lay_main);
	lay_main->addWidget(table);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setMinimumHeight(350);

	// Adaugam butoanele
	QHBoxLayout* lay_btn = new QHBoxLayout;
	lay_btn->addWidget(btn_open);
	lay_btn->addWidget(btn_inprog);
	lay_btn->addWidget(btn_close);
	lay_main->addLayout(lay_btn);
}

void GUI_Filtrat::connectSignals()
{
	// =-=-=-=-=-=-=-=-=-=- Selectia in tabel -=-=-=-=-=-=-=-=-=-=
	QObject::connect(table, &QTableWidget::itemSelectionChanged, this, [=]() {
		id = -5;
		auto sel = table->selectedItems();

		if (sel.isEmpty())
			return;

		id = sel.at(0)->data(0).toInt();
		});

	// =-=-=-=-=-=-=-=-=-=- Butonul Open -=-=-=-=-=-=-=-=-=-=
	QObject::connect(btn_open, &QPushButton::clicked, this, [=]() {
		try {
			srv.Modifica_stare(id, "Open");
		}
		catch (exception) { QMessageBox::critical(this, "Eroare", "Selectie invalida !\n"); }
		});

	// =-=-=-=-=-=-=-=-=-=- Butonul Inprogress -=-=-=-=-=-=-=-=-=-=
	QObject::connect(btn_inprog, &QPushButton::clicked, this, [=]() {
		try {
			srv.Modifica_stare(id, "Inprogress");
		}
		catch (exception) { QMessageBox::critical(this, "Eroare", "Selectie invalida !\n"); }
		});

	// =-=-=-=-=-=-=-=-=-=- Butonul Close -=-=-=-=-=-=-=-=-=-=
	QObject::connect(btn_close, &QPushButton::clicked, this, [=]() {
		try {
			srv.Modifica_stare(id, "Close");
		}
		catch (exception) { QMessageBox::critical(this, "Eroare", "Selectie invalida !\n"); }
		});
}

// =-=-=-=-=-=-=-=-=-=- Adaugarea in tabel -=-=-=-=-=-=-=-=-=-=
void GUI_Filtrat::addToTable(vector<Task> v)
{
	sort(v.begin(), v.end(), [](const Task& t1, const Task& t2) {
		return t1.get_stare() < t2.get_stare(); });
	table->clear();
	table->clearSelection();
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Descriere"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Programatori"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Stare"));
	table->setRowCount(v.size());

	id = -5;
	int line = 0;
	for (const Task& t : v)
	{
		table->setItem(line, 0, new QTableWidgetItem(QString::number(t.get_id())));
		table->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(t.get_descriere())));
		table->setItem(line, 2, new QTableWidgetItem(QString::number(t.get_programatori().size())));
		table->setItem(line, 3, new QTableWidgetItem(QString::fromStdString(t.get_stare())));
		line++;
	}

	table->resizeColumnsToContents();
	int width = table->columnWidth(0) + table->columnWidth(1) +
		table->columnWidth(2) + table->columnWidth(3) + 41;
	table->setMinimumWidth(width);
}
