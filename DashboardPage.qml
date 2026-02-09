import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
	id: dashboardPage

	signal logout

	property var userData: ({})

	BackgroundImage {
		id: backgroundImage
		anchors.fill: parent
	}

	ReturnButton {
		id: logoutBtn
		text: "< Logout"
		onClicked: dashboardPage.logout()
	}

	Item {
		width: parent.width * 0.60
		height: mainLayout.implicitHeight
		anchors.centerIn: parent

		Rectangle {
			id: cardBackground
			anchors.fill: parent
			anchors.margins: -30
			color: "#D9FFFFFF"
			radius: 15
			z: -1
			border.color: "#33000000"
			border.width: 1
		}

		GridLayout {
			id: mainLayout
			anchors.fill: parent
			columns: 2

			Label {
				text: "Username:"
				font.bold: true
			}
			Text {
				text: userData.username
			}

			Label {
				text: "Password:"
				font.bold: true
			}
			Text {
				text: userData.password
			}

			Label {
				text: "Full Name:"
				font.bold: true
			}
			Text {
				text: userData.fullname
			}

			Label {
				text: "Email ID:"
				font.bold: true
			}
			Text {
				text: userData.email
			}

			Label {
				text: "Phone Number:"
				font.bold: true
			}
			Text {
				text: userData.phone
			}

			Label {
				text: "Age:"
				font.bold: true
			}
			Text {
				text: userData.age
			}

			Label {
				text: "Gender:"
				font.bold: true
			}
			Text {
				text: userData.gender
			}

			Label {
				text: "User Role:"
				font.bold: true
			}
			Text {
				text: userData.userrole
			}
		}
	}
}
