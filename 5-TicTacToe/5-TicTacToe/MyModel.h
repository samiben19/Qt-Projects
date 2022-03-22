#pragma once
#include "Service.h"
#include <QAbstractTableModel>
#include <algorithm>

class MyModel : public QAbstractTableModel
{
private:
	Service& srv;
public:
	MyModel(Service& srv) :srv{ srv } {}

	void update() {
		emit layoutChanged();
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return srv.GetAll().size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole)
		{
			vector<Joc> alls = srv.GetAll();
			
			std::sort(alls.begin(), alls.end(), [](Joc& j1, Joc& j2) { return j1.get_stare() < j2.get_stare(); });
			Joc j = alls[index.row()];
			if (index.column() == 0)
				return QString::number(j.get_id());
			else if (index.column() == 1)
				return QString::number(j.get_dim());
			else if (index.column() == 2)
				return QString::fromStdString(j.get_tabla());
			else if (index.column() == 3)
				return QString::fromStdString(j.get_urmator());
			else
				return QString::fromStdString(j.get_stare());
		}
		return QVariant();
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal && section == 0)
				return QString("ID");// .arg(section);
			else if (orientation == Qt::Horizontal && section == 1)
				return QString("Dimensiune");// .arg(section);
			else if (orientation == Qt::Horizontal && section == 2)
				return QString("Tabla");// .arg(section);
			else if (orientation == Qt::Horizontal && section == 3)
				return QString("Jucatorul urmator");// .arg(section);
			else if (orientation == Qt::Horizontal && section == 4)
				return QString("Stare");// .arg(section);
		}
		return QVariant();
	}

};

