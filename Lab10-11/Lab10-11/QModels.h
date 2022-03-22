#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "service.h"

using std::vector;

class MyTableModel: public QAbstractTableModel, public Observer
{
private:
	Service& srv;
public:
	MyTableModel(Service& s) : srv{ s } {
		srv.addObserver(this);
	}

	void update() override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

