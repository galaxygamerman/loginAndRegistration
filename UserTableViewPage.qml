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
			text: "User Directory (TableView)"
			font.pixelSize: 24
			font.bold: true
			Layout.alignment: Qt.AlignHCenter
		}

		HorizontalHeaderView {
			syncView: tableView
			model: ["Username", "Password", "Full Name", "Email ID", "Phone", "Age", "Gender", "User Role"]
		}
		TableView {
			id: tableView
			Layout.fillWidth: true
			Layout.fillHeight: true
			columnSpacing: 1
			rowSpacing: 1
			clip: true

			model: UserTableModel {}

			delegate: Rectangle {
				implicitWidth: 150
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
			}
		}
	}
}
