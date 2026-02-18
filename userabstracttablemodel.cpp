#include "userabstracttablemodel.h"
#include "databasemanager.h"

UserAbstractTableModel::UserAbstractTableModel(DatabaseManager *dbPtr, QObject *parent)
	: QAbstractTableModel{parent}
	, dbManager(dbPtr) {}

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

bool UserAbstractTableModel::removeRows(int row, int count, const QModelIndex &parent) {
	if (row < 0 || row + count > this->userDataList.size()) return false;

	QStringList usernames;
	for (int i = 0; i < count; i++) {
		usernames.append(this->userDataList.at(row + i).username);
	}

	if (!this->dbManager->deleteUsers(usernames)) {
		return false;
	}

	beginRemoveRows(parent, row, row + count - 1);
	for (int i = 0; i < count; i++) {
		this->userDataList.removeAt(row);
	}
	endRemoveRows();

	return true;
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

bool UserAbstractTableModel::updateRows(const int row, const QVariantMap &newData) {
	if (row < 0 || row >= this->userDataList.size()) return false;

	QString oldUsername = this->userDataList[row].username;

	qDebug() << "In the backend:" << row << oldUsername << newData["username"]
			 << newData["password"] << newData["fullname"] << newData["email"] << newData["phone"]
			 << newData["age"] << newData["gender"] << newData["userrole"];

	QSqlQuery query;
	query.prepare("UPDATE users"
				  " SET "
				  "username = :newUsername,"
				  "password = :password,"
				  "fullname = :fullname,"
				  "email = :email,"
				  "phone = :phone,"
				  "age = :age,"
				  "gender = :gender,"
				  "userrole = :userrole"
				  " WHERE username = :oldUsername");
	query.bindValue(":oldUsername", oldUsername);
	query.bindValue(":newUsername", newData["username"]);
	query.bindValue(":password", newData["password"]);
	query.bindValue(":fullname", newData["fullname"]);
	query.bindValue(":email", newData["email"]);
	query.bindValue(":phone", newData["phone"]);
	query.bindValue(":age", newData["age"]);
	query.bindValue(":gender", newData["gender"]);
	query.bindValue(":userrole", newData["userrole"]);

	if (!query.exec()) {
		qCritical() << "User modification failed:" << query.lastError().text();
		return false;
	}

	this->userDataList[row] = (UserData) {.username = newData["username"].toString(),
										  .password = newData["password"].toString(),
										  .fullname = newData["fullname"].toString(),
										  .email = newData["email"].toString(),
										  .phone = newData["phone"].toString(),
										  .age = newData["age"].toString(),
										  .gender = newData["gender"].toString(),
										  .userrole = newData["userrole"].toString()};

	emit dataChanged(index(row, 0), index(row, 8), {DisplayRole});
	qDebug() << "User modification completed for" << newData["username"];
	return true;
}
