import QtQuick

ListModel {
	id: userListModel

	function loadData() {
		this.clear()
		let users = dbManager.getAllUserData()
		users.forEach(user => this.append(user))
	}
	Component.onCompleted: loadData()
}
