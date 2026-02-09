import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
	id: dashboard

	property var userData: ({})

	GridLayout {
		anchors.fill: parent
		columns: 2

		Label {
			text: "Username:"
			font.bold: true
		}
		Text{
			text: userData.username
		}

		Label {
			text: "Password:"
			font.bold: true
		}
		Text{
			text: userData.password
		}

		Label {
			text: "Full Name:"
			font.bold: true
		}
		Text{
			text: userData.fullname
		}

		Label {
			text: "Email ID:"
			font.bold: true
		}
		Text{
			text: userData.email
		}

		Label {
			text: "Phone Number:"
			font.bold: true
		}
		Text{
			text: userData.phone
		}

		Label {
			text: "Age:"
			font.bold: true
		}
		Text{
			text: userData.age
		}

		Label {
			text: "Gender:"
			font.bold: true
		}
		Text{
			text: userData.gender
		}

		Label {
			text: "User Role:"
			font.bold: true
		}
		Text{
			text: userData.userrole
		}
	}
}
