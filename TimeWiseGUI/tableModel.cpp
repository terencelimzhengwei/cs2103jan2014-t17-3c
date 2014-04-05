#include "tableModel.h"

tableModel* table() {
	static tableModel* p= new tableModel();
	return p;
}
// constructor: initializes the contents of the array with a running counter
tableModel::tableModel( QObject* parent ) : QAbstractTableModel(parent) {
	/*int* count=0;
	for ( int r=0; r<6; r++ )
		for ( int c=0; c<5; c++ )
			array[r][c] = count++;*/
}

// rowCount: returns the number of rows.
int tableModel::rowCount(const QModelIndex &parent ) const {
	return rows;
}

// columnCount: returns the number of columns
int tableModel::columnCount(const QModelIndex &parent ) const {
	return columns;
}

// data: used by the view to get the item stored at a given index (which
//		 contains a row & column field)
QVariant tableModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid() || role != Qt::DisplayRole)
		return QVariant();
	return array[index.row()][index.column()];
	//return qGray(modelImage.pixel(index.column(), index.row()));
}

// headerData: used to define the headers of the rows & column
QVariant tableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	if (orientation == Qt::Horizontal) {
		switch (section) {
		case 0: {
			return QString("ID");
			break;
		}
		case 1: {
			return QString("Description");
			break;
		}
		case 2: {
			return QString("Due Date");
			break;
		}
		case 3: {
			return QString("Due Time");
			break;
		}
		case 4: {
			return QString("Priority");
			break;
		}
		case 5: {
			return QString("Category");
			break;
		}
		}
	}
}

//setItem: sets the item at (row, col) to the value in datum.
//returns 1 if successful, 0 otherwise
int tableModel::setItem(int r, int c, QString datum) {
	//--- sets the data ---
	array[r][c] = datum;

	//--- tell the world ---
	emit dataChanged( createIndex(r, c), createIndex(r, c) );

	return 1;		// success!
}
