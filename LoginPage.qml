import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import com.company.database 1.0

Item {
	id: loginPage
	implicitWidth: 640
	implicitHeight: 480

	signal goToRegister
	signal loginCompleted

	DatabaseManager{
		id: dbManager
	}

	// Background Image
	Image {
		id: backgroundImage
		source: "qrc:/assets/TheCrack.jpg"
		anchors.fill: parent
		fillMode: Image.PreserveAspectCrop

		Rectangle {
			anchors.fill: parent
			color: "black"
			opacity: 0.2
		}
	}

	// FORM WRAPPER: Separates background from Layout
	Item {
		id: loginContainer
		width: parent.width * 0.60
		height: loginLayout.implicitHeight // Height follows content
		anchors.centerIn: parent

		// Translucent Background Card
		Rectangle {
			id: translucentCard
			anchors.fill: parent
			anchors.margins: -30
			color: "#CCFFFFFF"
			radius: 12
			border.color: "#33000000"
			border.width: 1
			z: -1
		}

		ColumnLayout {
			id: loginLayout
			anchors.fill: parent
			spacing: 15

			Text {
				text: "Login"
				font.pixelSize: 28
				font.bold: true
				color: "#2c3e50"
				Layout.alignment: Qt.AlignHCenter
				Layout.bottomMargin: 10
			}

			TextField {
				id: usernameInput
				placeholderText: "Username"
				Layout.fillWidth: true
				maximumLength: 32
				Material.accent: "#008080"
				validator: RegularExpressionValidator {
					regularExpression: /^\w{2,32}$/
				}
			}

			TextField {
				id: passwordInput
				placeholderText: "Password"
				echoMode: TextField.Password
				Layout.fillWidth: true
				maximumLength: 32
				Material.accent: "#008080"
				validator: RegularExpressionValidator {
					regularExpression: /^.{2,32}$/
				}
			}

			ComboBox {
				id: roleInput
				model: ["Select a Role...", "Admin", "Staff", "Guest"]
				Layout.fillWidth: true
				Material.accent: "#008080"
			}

			Button {
				id: submitBtn
				text: "Sign In"
				Layout.fillWidth: true
				Layout.topMargin: 10
				Material.accent: "#008080"
				enabled: usernameInput.acceptableInput
						 && passwordInput.acceptableInput
						 && roleInput.currentIndex !== 0
				onClicked: {
					console.log("Logging in..." + ` user: ${usernameInput.text}`
								+ ` password: ${passwordInput.text}`
								+ ` role: ${roleInput.currentText}`)
					let success = dbManager.checkUser(usernameInput.text, passwordInput.text, roleInput.currentText)
					if(!success){
						console.error("Login was not possible")
						return
					}
					loginPage.loginCompleted()
				}
			}

			Text {
				text: "New User? <u>Let's get registered"
				horizontalAlignment: Text.AlignHCenter
				Layout.alignment: Qt.AlignHCenter
				color: "black"

				MouseArea {
					id: registerMouse
					anchors.fill: parent
					hoverEnabled: true
					onClicked: goToRegister()
				}
			}
		}
	}
}
