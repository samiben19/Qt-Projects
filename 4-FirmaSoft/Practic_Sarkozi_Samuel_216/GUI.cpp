#include "GUI.h"

void GUI::update()
{
	addToTable(srv.GetAll());
}

void GUI::clearText()
{
	edit_id->clear();
	edit_descriere->clear();
	for (auto& el : edit_progs)
		el->clear();
	edit_stare->clear();
}

void GUI::initGUI()
{
	// Initializam textfield-urile programatorilor
	for (int i = 0; i < 4; i++)
		edit_progs.push_back(new QLineEdit);

	// Initializam layout-ul principal, in stanga vom avea tabelul si in dreapta
	// Butoane si textfield-uri
	QHBoxLayout* lay_main = new QHBoxLayout;
	setLayout(lay_main);

	// Adaugam tabelul si setam niste flaguri
	lay_main->addWidget(table);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setMinimumHeight(350);

	// Layoutul din dreapta (Sus textfielduri)
	QVBoxLayout* lay_dreapta = new QVBoxLayout;

	QFormLayout* form = new QFormLayout;
	form->addRow("ID", edit_id);
	form->addRow("Descriere", edit_descriere);
	for (int i = 0; i < 4; i++)
		form->addRow("Programator " + QString::number(i + 1), edit_progs[i]);
	form->addRow("Stare", edit_stare);

	lay_dreapta->addLayout(form);
	lay_dreapta->addStretch();

	// (Jos butoane si search)
	lay_dreapta->addWidget(btn_adauga);
	QFormLayout* form2 = new QFormLayout;
	form2->addRow("Search", edit_search);
	lay_dreapta->addLayout(form2);

	// Adaugam toate acestea in layout-ul principal
	lay_main->addLayout(lay_dreapta);
}

void GUI::connectSignals()
{
	// =-=-=-=-=-=-=-=-=-=- Adauga -=-=-=-=-=-=-=-=-=-=
	QObject::connect(btn_adauga, &QPushButton::clicked, this, [=]() {
		int id = edit_id->text().toInt();
		string descriere = edit_descriere->text().toStdString();
		vector<string>programatori;
		for (auto& el : edit_progs)
			if (el->text() != "")
				programatori.push_back(el->text().toStdString());
		string stare = edit_stare->text().toStdString();

		try {
			srv.Adauga(id, descriere, programatori, stare);
			addToTable(srv.GetAll());
		}
		catch (exception& ex) { QMessageBox::critical(this, "Eroare", ex.what()); }
		});

	// =-=-=-=-=-=-=-=-=-=- Search -=-=-=-=-=-=-=-=-=-=
	QObject::connect(edit_search, &QLineEdit::textChanged, this, [=]() {
		string sub = edit_search->text().toStdString();
		addToTable(srv.Search("programatori", sub));
		});

	// =-=-=-=-=-=-=-=-=-=- Selectia in tabel -=-=-=-=-=-=-=-=-=-=
	QObject::connect(table, &QTableWidget::itemSelectionChanged, this, [=]() {
		clearText();
		auto sel = table->selectedItems();

		if (sel.isEmpty())
			return;

		int id = sel.at(0)->data(0).toInt();

		try {
			const Task& task = srv.Cauta(id);
			edit_id->setText(QString::number(task.get_id()));
			edit_descriere->setText(QString::fromStdString(task.get_descriere()));
			int i = 0;
			for (const string& pr : task.get_programatori())
				edit_progs[i++]->setText(QString::fromStdString(pr));
			edit_stare->setText(QString::fromStdString(task.get_stare()));
		}
		catch(exception& ex) { QMessageBox::critical(this, "Eroare", ex.what()); }
		});

}

void GUI::addToTable(vector<Task> v)
{
	sort(v.begin(), v.end(), [](const Task& t1, const Task& t2) {
		return t1.get_stare() < t2.get_stare();});
	table->clear();
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Descriere"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Programatori"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Stare"));
	table->setRowCount(v.size());

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
