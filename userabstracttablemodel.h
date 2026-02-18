#ifndef USERABSTRACTTABLEMODEL_H
#define USERABSTRACTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "databasemanager.h"
#include "userdata.h"

class UserAbstractTableModel : public QAbstractTableModel
{
private:
	Q_OBJECT
	QList<UserData> userDataList;
	DatabaseManager *dbManager;

public:
	explicit UserAbstractTableModel(DatabaseManager *dbPtr = new DatabaseManager(), QObject *parent = nullptr);

	// QAbstractItemModel interface
	enum UserRoles { DisplayRole = Qt::DisplayRole, EditRole = Qt::DisplayRole };

	int rowCount(const QModelIndex &parent) const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	bool removeRows(int row, int count, const QModelIndex &parent) override;

	// Q_INVOKABLE methods
	Q_INVOKABLE void fetchUsers();
	Q_INVOKABLE bool updateRow(const int row, const QVariantMap &newData);
	Q_INVOKABLE bool setDataOrUpdateRow(const QModelIndex &index, const QVariantMap &newData, int role = EditRole);
};

#endif // USERABSTRACTTABLEMODEL_H
