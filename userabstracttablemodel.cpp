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

bool UserAbstractTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	if (!index.isValid() || role != EditRole) return false;

	UserData data = this->userDataList[index.row()];
	QString fieldToBeUpdated;
	switch (index.column()) {
		case 0:
			fieldToBeUpdated = "username";
			data.username = value.toString();
			break;
		case 1:
			fieldToBeUpdated = "password";
			data.password = value.toString();
			break;
		case 2:
			fieldToBeUpdated = "fullname";
			data.fullname = value.toString();
			break;
		case 3:
			fieldToBeUpdated = "email";
			data.email = value.toString();
			break;
		case 4:
			fieldToBeUpdated = "phone";
			data.phone = value.toString();
			break;
		case 5:
			fieldToBeUpdated = "age";
			data.age = value.toString();
			break;
		case 6:
			fieldToBeUpdated = "gender";
			data.gender = value.toString();
			break;
		case 7:
			fieldToBeUpdated = "userrole";
			data.userrole = value.toString();
			break;
		default:
			qCritical() << "UserAbstractTableModel::setData:" << "Column index is not editable.";
			return false;
	}

	QSqlQuery query;
	QString statement = QString("UPDATE users SET %1 = :value where username = :username").arg(fieldToBeUpdated);
	query.prepare(statement);
	query.bindValue(":username", data.username);
	query.bindValue(":value", value);

	if (!query.exec()) {
		qCritical() << "UserAbstractTableModel::setData:" << "Query did not execute successfully";
		return false;
	}

	emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
	qInfo() << "Update signal sent to the table.";
	return true;
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
	const QVariantList newList = this->dbManager->getAllUserData();
	for (const QVariant &row : newList) {
		const QVariantMap user = row.toMap();
		this->userDataList.append((UserData) {.username = user["username"].toString(),
											  .password = user["password"].toString(),
											  .fullname = user["fullname"].toString(),
											  .email = user["email"].toString(),
											  .phone = user["phone"].toString(),
											  .age = user["age"].toString(),
											  .gender = user["gender"].toString(),
											  .userrole = user["userrole"].toString()});
	}
	endResetModel();
}

bool UserAbstractTableModel::updateRow(const int row, const QVariantMap &newData) {
	if (row < 0 || row >= this->userDataList.size()) return false;

	QString oldUsername = this->userDataList[row].username;
	qDebug() << "In the backend:" << row << oldUsername << newData;

	UserData newUserData = {.username = newData["username"].toString(),
							.password = newData["password"].toString(),
							.fullname = newData["fullname"].toString(),
							.email = newData["email"].toString(),
							.phone = newData["phone"].toString(),
							.age = newData["age"].toString(),
							.gender = newData["gender"].toString(),
							.userrole = newData["userrole"].toString()};

	bool success = this->dbManager->updateUser(oldUsername,
											   newUserData.username,
											   newUserData.password,
											   newUserData.fullname,
											   newUserData.email,
											   newUserData.phone,
											   newUserData.age,
											   newUserData.gender,
											   newUserData.userrole);
	if (!success) return false;

	this->userDataList[row] = newUserData;

	emit dataChanged(index(row, 0), index(row, 8), {DisplayRole});
	qDebug() << "User modification completed for" << newData["username"];
	return true;
}
