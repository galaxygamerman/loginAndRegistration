import QtQuick
import QtQuick.Controls

Window {
	width: 640
	height: 480
	visible: true
	title: qsTr("Task 1")

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
		}
	}
}
