import QtQuick
import QtQuick.Controls.Material

Window {
	width: 640
	height: 1080
	visible: true
	title: qsTr("Task 1")

	RegistrationSuccessDialog {
		id: successDialog
		anchors.centerIn: parent
		title: "Success"
		text: "Account creation was successful!\nYou can now log in."
	}

	StackView {
		id: stack
		anchors.fill: parent
		initialItem: loginPage
	}

	Component {
		id: loginPage
		LoginPage {
			onGoToRegister: stack.push(registerPage)
		}
	}
	Component {
		id: registerPage
		RegisterPage {
			onGoBack: stack.pop()
			onRegistrationCompleted: {
				stack.pop()
				successDialog.open()
			}
		}
	}
}
