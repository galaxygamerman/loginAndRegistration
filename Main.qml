import QtQuick
import QtQuick.Controls.Material

Window {
	width: 640
	height: 1080
	visible: true
	title: qsTr("Task 1")

	AuthStatusDialog {
		id: authStatusDialog
		anchors.centerIn: parent
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
			onLoginCompleted: userData => {
								  stack.push(dashboardPage, { "userData": userData })
							  }
			onLoginFailed: {
				authStatusDialog.title = "Failure"
				authStatusDialog.text = "Your credentials are wrong.\nPlease try again."
				authStatusDialog.open()
			}
		}
	}
	Component {
		id: registerPage
		RegisterPage {
			onGoBack: stack.pop()
			onRegistrationCompleted: {
				stack.pop()
				authStatusDialog.title = "Success"
				authStatusDialog.text = "Account creation was successful!\nYou can now log in."
				authStatusDialog.open()
			}
		}
	}
	Component {
		id: dashboardPage
		DashboardPage {
			onLogout: stack.pop()
		}
	}
	Component{
		id: userAbstractTableViewPage
		UserAbstractTableViewPage{
			onGoBack: stack.pop()
			onEditPressed: row => {stack.push(editPage,{currentRow: row})}
		}
	}
	Component{
		id: editPage
		EditPage{
			onGoBack: stack.pop()
			onEditCompleted: stack.pop()
		}
	}
}
