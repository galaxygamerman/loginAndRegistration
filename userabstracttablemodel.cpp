#include "userabstracttablemodel.h"
#include <QtSql>

UserAbstractTableModel::UserAbstractTableModel(QObject *parent)
	: QAbstractTableModel{parent} {}

int UserAbstractTableModel::rowCount(const QModelIndex &parent) const {
	return this->userDataList.size();
}

int UserAbstractTableModel::columnCount(const QModelIndex &parent) const {
	return 9;
}

QVariant UserAbstractTableModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid() || index.row() >= this->userDataList.size() || role != DisplayRole)
		return QVariant();
	const UserData data = this->userDataList[index.row()];
	switch (index.column()) {
		case 0: return data.username;
		case 1: return data.password;
		case 2: return data.fullname;
		case 3: return data.email;
		case 4: return data.phone;
		case 5: return data.age;
		case 6: return data.gender;
		case 7: return data.userrole;
		case 8: return QVariant("");
		default: return QVariant();
	}
}

QVariant UserAbstractTableModel::headerData(int section,
											Qt::Orientation orientation,
											int role) const {
	if (role != DisplayRole || orientation != Qt::Horizontal) return QVariant();
	switch (section) {
		case 0: return "Username";
		case 1: return "Password";
		case 2: return "Full Name";
		case 3: return "Email ID";
		case 4: return "Phone";
		case 5: return "Age";
		case 6: return "Gender";
		case 7: return "User Role";
		case 8: return "Actions";
		default: return QVariant();
	}
}

void UserAbstractTableModel::fetchUsers() {
	beginResetModel();
	this->userDataList.clear();
	QSqlQuery query("SELECT * FROM users");
	while (query.next()) {
		this->userDataList.append({query.value("username").toString(),
								   query.value("password").toString(),
								   query.value("fullname").toString(),
								   query.value("email").toString(),
								   query.value("phone").toString(),
								   query.value("age").toString(),
								   query.value("gender").toString(),
								   query.value("userrole").toString()});
	}
	endResetModel();
}

bool UserAbstractTableModel::removeRows(int row, int count, const QModelIndex &parent) {
	if (row < 0 || row + count > this->userDataList.size()) return false;

	QSqlDatabase db = QSqlDatabase::database();
	if (!db.transaction()) return false;

	beginRemoveRows(parent, row, row + count - 1);
	for (uint i = 0; i < count; i++) {
		QString username = this->userDataList.at(row).username;

		QSqlQuery query;
		query.prepare("DELETE FROM users WHERE username = :username");
		query.bindValue(":username", username);

		if (!query.exec()) {
			endRemoveRows();
			db.rollback();
			return false;
		}
		this->userDataList.removeAt(row);
	}

	endRemoveRows();
	db.commit();
	return true;
}
