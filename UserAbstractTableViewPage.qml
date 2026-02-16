import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels 1.0

Item {
	id: root
	signal goBack

	ReturnButton {
		text: "< Back"
		color: "darkgrey"
		onClicked: root.goBack()
	}

	ColumnLayout {
		anchors.fill: parent
		anchors.margins: 20

		Text {
			text: "User Directory (TableView) using QAbstractTableModel"
			font.pixelSize: 24
			font.bold: true
			Layout.alignment: Qt.AlignHCenter
		}

		HorizontalHeaderView {
			syncView: tableView
		}
		TableView {
			id: tableView
			Layout.fillWidth: true
			Layout.fillHeight: true
			columnSpacing: 1
			rowSpacing: 1
			clip: true

			model: userAbstractTableModel

			delegate: Rectangle {
				implicitWidth: column === 8 ? 200 : 150
				implicitHeight: 40
				border.color: "snow"
				color: "white"

				Text {
					text: display
					anchors.centerIn: parent
					font.pixelSize: 13
					color: "#2c3e50"
					elide: Text.ElideRight
					width: parent.width - 10
					horizontalAlignment: Text.AlignHCenter
				}
				RowLayout {
					anchors.fill: parent
					enabled: column === 8
					visible: column === 8
					Button {
						text: "Edit"
						Material.background: "#008080"
						Layout.fillWidth: true
						onClicked: console.debug('edit pressed')
					}
					Button {
						Material.background: "#ff2525"
						text: "Delete"
						Layout.fillWidth: true
						onClicked: userAbstractTableModel.removeRows(row, 1)
					}
				}
			}
			Component.onCompleted: userAbstractTableModel.fetchUsers()
		}
	}
}
