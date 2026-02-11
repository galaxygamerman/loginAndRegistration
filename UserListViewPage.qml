import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
	id: userListPage
	signal goBack

	ColumnLayout {
		anchors.fill: parent
		anchors.margins: 20

		ReturnButton {
			text: "< Back"
			onClicked: userListPage.goBack()
		}

		Text {
			text: "User Directory (ListView)"
			font.pixelSize: 24
			font.bold: true
			Layout.alignment: Qt.AlignHCenter
		}

		ListView {
			id: listView
			Layout.fillWidth: true
			Layout.fillHeight: true
			clip: true
			model: UserListModel{}
			spacing: 5

			delegate: Rectangle {
				width: listView.width
				height: 60
				color: "#f8f9fa"
				radius: 5
				border.color: "#dee2e6"

				RowLayout {
					anchors.fill: parent
					anchors.margins: 10

					Text{text: username}
					Text{text: password}
					Text{text: fullname}
					Text{text: email}
					Text{text: phone}
					Text{text: age}
					Text{text: gender}
					Text{text: userrole}
				}
			}
		}
	}
}
