#pragma once
#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QString>
#define rows 6
#define columns 6

class tableModel: public QAbstractTableModel {
	Q_OBJECT

private:
	QString array[rows][columns];	// where the data are stored

public:
	tableModel(QObject* parent=0);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	//Returns the data at the specified index
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	//headerData allows us to put labels on the rows and columns
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	//Sets the contents of array[r][c] to d.
	int setItem(int r, int c, QString datum);
};

tableModel* table();

#endif
