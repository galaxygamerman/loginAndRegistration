#ifndef USERABSTRACTTABLEMODEL_H
#define USERABSTRACTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "userdata.h"

class UserAbstractTableModel : public QAbstractTableModel
{
private:
	Q_OBJECT
	QList<UserData> userDataList;

public:
	explicit UserAbstractTableModel(QObject *parent = nullptr);

	// QAbstractItemModel interface
	enum UserRoles { DisplayRole = Qt::DisplayRole };

	int rowCount(const QModelIndex &parent) const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	bool removeRows(int row, int count, const QModelIndex &parent) override;

	// Q_INVOKABLE methods
	Q_INVOKABLE void fetchUsers();
	Q_INVOKABLE bool updateUsers(const int row, const QVariantMap &newData);
};

#endif // USERABSTRACTTABLEMODEL_H
