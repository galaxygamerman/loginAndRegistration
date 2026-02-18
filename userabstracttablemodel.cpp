#include "userabstracttablemodel.h"
#include "databasemanager.h"
#include <vector>

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

	// Find out which tablefield to set
	UserData &data = this->userDataList[index.row()];
	QString fieldToBeUpdated;
	switch (index.column()) {
		case 0: fieldToBeUpdated = "username"; break;
		case 1: fieldToBeUpdated = "password"; break;
		case 2: fieldToBeUpdated = "fullname"; break;
		case 3: fieldToBeUpdated = "email"; break;
		case 4: fieldToBeUpdated = "phone"; break;
		case 5: fieldToBeUpdated = "age"; break;
		case 6: fieldToBeUpdated = "gender"; break;
		case 7: fieldToBeUpdated = "userrole"; break;
		default:
			qCritical() << "UserAbstractTableModel::setData:"
						<< "Column index is not editable.";
			return false;
	}

	// Update the Database
	QSqlQuery query;
	QString statement = QString("UPDATE users SET %1 = :value where username = :username").arg(fieldToBeUpdated);
	query.prepare(statement);
	query.bindValue(":username", data.username);
	query.bindValue(":value", value);

	if (!query.exec()) {
		qCritical() << "UserAbstractTableModel::setData:" << "Query did not execute successfully";
		return false;
	}

	// Update the value in the UI
	switch (index.column()) {
		case 0: data.username = value.toString(); break;
		case 1: data.password = value.toString(); break;
		case 2: data.fullname = value.toString(); break;
		case 3: data.email = value.toString(); break;
		case 4: data.phone = value.toString(); break;
		case 5: data.age = value.toString(); break;
		case 6: data.gender = value.toString(); break;
		case 7: data.userrole = value.toString(); break;
		default:
			qCritical() << "UserAbstractTableModel::setData:"
						<< "Column index is not editable.";
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

bool UserAbstractTableModel::addUser(const QVariantMap &newData) {
	UserData newUserData = {.username = newData["username"].toString(),
							.password = newData["password"].toString(),
							.fullname = newData["fullname"].toString(),
							.email = newData["email"].toString(),
							.phone = newData["phone"].toString(),
							.age = newData["age"].toString(),
							.gender = newData["gender"].toString(),
							.userrole = newData["userrole"].toString()};

	bool success = this->dbManager->registerUser(newUserData.username,
												 newUserData.password,
												 newUserData.fullname,
												 newUserData.email,
												 newUserData.phone,
												 newUserData.age,
												 newUserData.gender,
												 newUserData.userrole);
	if (!success) return false;

	this->userDataList.append(newUserData);
	return true;
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

bool UserAbstractTableModel::setDataOrUpdateRow(const QModelIndex &index, const QVariantMap &newData, int role) {
	UserData userData = this->userDataList[index.row()];
	std::vector<bool> wasEdited = {newData["username"] != userData.username,
									newData["password"] != userData.password,
									newData["fullname"] != userData.fullname,
									newData["email"] != userData.email,
									newData["phone"] != userData.phone,
									newData["age"] != userData.age,
									newData["gender"] != userData.gender,
									newData["userrole"] != userData.userrole};

	int total = wasEdited.size(),
		count = std::count(wasEdited.begin(), wasEdited.end(), true);

	if (count >= total / 2) {
		return this->updateRow(index.row(), newData);
	} else {
		QStringList fieldnames
			= {"username", "password", "fullname", "email", "phone", "age", "gender", "userrole"};
		std::vector<bool> &success = wasEdited;
		for (int i = 0; i < total; ++i) {
			success[i] = wasEdited[i]? this->setData(this->index(index.row(), i), newData[fieldnames[i]], EditRole) : true;
		}
		// Check if all succeeded, return false if even one of them returns false
		if (std::count(success.begin(), success.end(), false)) return false;
		return true;
	}
}
