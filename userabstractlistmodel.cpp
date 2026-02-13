#include "userabstractlistmodel.h"
#include <QtSql>

UserAbstractListModel::UserAbstractListModel(QObject *parent)
	: QAbstractListModel{parent} {}

int UserAbstractListModel::rowCount(const QModelIndex &parent) const {
	return this->userDataList.size();
}

QVariant UserAbstractListModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid() || index.row() >= this->userDataList.size()) return QVariant();

	const UserData data = userDataList[index.row()];
	if (role == usernameRole) return data.username;
	if (role == passwordRole) return data.password;
	if (role == fullnameRole) return data.fullname;
	if (role == emailRole) return data.email;
	if (role == phoneRole) return data.phone;
	if (role == ageRole) return data.age;
	if (role == genderRole) return data.gender;
	if (role == userroleRole) return data.userrole;
	return QVariant();
}

QHash<int, QByteArray> UserAbstractListModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[usernameRole] = "username";
	roles[passwordRole] = "password";
	roles[fullnameRole] = "fullname";
	roles[emailRole] = "email";
	roles[phoneRole] = "phone";
	roles[ageRole] = "age";
	roles[genderRole] = "gender";
	roles[userroleRole] = "userrole";
	return roles;
}

void UserAbstractListModel::fetchUsers() {
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
}
