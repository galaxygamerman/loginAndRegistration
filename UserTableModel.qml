import QtQuick
import Qt.labs.qmlmodels

TableModel {
	id: userTableModel

	TableModelColumn {display: "username"}
	TableModelColumn {display: "password"}
	TableModelColumn {display: "fullname"}
	TableModelColumn {display: "email"}
	TableModelColumn {display: "phone"}
	TableModelColumn {display: "age"}
	TableModelColumn {display: "gender"}
	TableModelColumn {display: "userrole"}

	function loadData(){
		this.clear()
		this.rows = Array.from(dbManager.getAllUserData())
	}
	Component.onCompleted: loadData()
}
