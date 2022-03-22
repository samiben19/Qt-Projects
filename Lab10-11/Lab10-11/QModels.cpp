#include "QModels.h"

void MyTableModel::update()
{
	emit layoutChanged();
}

int MyTableModel::rowCount(const QModelIndex& parent) const
{
	return (int)srv.GetAll().size();
}

int MyTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		Produs p = srv.GetAll()[index.row()];
		if (index.column() == 0)
			return QString::fromStdString(p.get_nume());
		else if(index.column() == 1)
			return QString::fromStdString(p.get_tip());
		else if (index.column() == 1)
			return QString::number(p.get_pret());
		else
			return QString::fromStdString(p.get_producator());
	}
	return QVariant();
}
