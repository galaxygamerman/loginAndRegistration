import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
	id: userListPage
	signal goBack

	ReturnButton {
		text: "< Back"
		onClicked: userListPage.goBack()
	}

	ColumnLayout {
		anchors.fill: parent
		anchors.margins: 20

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
			model: UserListModel {}
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

					Text {
						text: username
						Layout.preferredWidth: 100
					}
					Text {
						text: password
						Layout.preferredWidth: 120
					}
					Text {
						text: fullname
						Layout.preferredWidth: 100
						wrapMode: Text.WrapAtWordBoundaryOrAnywhere
					}
					Text {
						text: email
						Layout.preferredWidth: 160
					}
					Text {
						text: phone
						Layout.preferredWidth: 130
					}
					Text {
						text: age
						Layout.preferredWidth: 20
					}
					Text {
						text: gender
						Layout.preferredWidth: 50
					}
					Text {
						text: userrole
						Layout.preferredWidth: 60
					}
				}
			}
		}
	}
}
