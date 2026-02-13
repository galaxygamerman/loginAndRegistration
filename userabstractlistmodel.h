#ifndef USERABSTRACTLISTMODEL_H
#define USERABSTRACTLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "userdata.h"

class UserAbstractListModel : public QAbstractListModel
{
private:
	Q_OBJECT
	QList<UserData> userDataList;

public:
	enum UserRoles {
		usernameRole = Qt::UserRole + 1,
		passwordRole,
		fullnameRole,
		emailRole,
		phoneRole,
		ageRole,
		genderRole,
		userroleRole
	};

	explicit UserAbstractListModel(QObject *parent = nullptr);

	// QAbstractItemModel interface
	int rowCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;

	// Q_INVOKABLE methods
	Q_INVOKABLE void fetchUsers();
};

#endif // USERABSTRACTLISTMODEL_H
