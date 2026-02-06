import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
	id: registrationPage
	implicitWidth: 640
	implicitHeight: 480

	signal goBack

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

	Text {
		id: backBtn
		text: "< Back"
		font.pixelSize: 16
		color: backMouseArea.containsMouse ? "white" : "#e0e0e0"
		z: 10
		anchors.left: parent.left
		anchors.top: parent.top
		anchors.margins: 20

		MouseArea {
			id: backMouseArea
			anchors.fill: parent
			hoverEnabled: true
			onClicked: registrationPage.goBack()
		}
	}

	// FORM WRAPPER: Ensures Layout doesn't overflow
	Item {
		id: registerContainer
		width: parent.width * 0.60
		// Use implicitHeight to ensure the background covers all fields
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

		ColumnLayout {
			id: mainLayout
			anchors.fill: parent
			spacing: 8 // Tighter spacing for more fields

			Text {
				text: "Create Account"
				font.pixelSize: 28
				font.bold: true
				color: "#2c3e50"
				Layout.alignment: Qt.AlignHCenter
				Layout.bottomMargin: 10
			}

			Label {
				text: "Username"
				font.bold: true
			}
			TextField {
				id: userField
				placeholderText: "Username"
				maximumLength: 32
				Layout.fillWidth: true
				Material.accent: "#008080"
				validator: RegularExpressionValidator {
					regularExpression: /^\w{2,32}$/
				}
			}

			Label {
				text: "Password"
				font.bold: true
			}
			TextField {
				id: pwdField
				placeholderText: "Min 6 characters"
				echoMode: TextField.Password
				Layout.fillWidth: true
				Material.accent: "#008080"
				validator: RegularExpressionValidator {
					regularExpression: /^.{6,32}$/
				}
			}

			Label {
				text: "Age"
				font.bold: true
			}
			TextField {
				id: ageField
				placeholderText: "18 - 99"
				validator: IntValidator {
					bottom: 18
					top: 99
				}
				inputMethodHints: Qt.ImhDigitsOnly
				Layout.fillWidth: true
				Material.accent: "#008080"
			}

			Label {
				text: "Gender"
				font.bold: true
			}
			RowLayout {
				Layout.alignment: Qt.AlignLeft
				ButtonGroup {
					id: genderGroup
				}
				RadioButton {
					id: maleRadio
					text: "Male"
					ButtonGroup.group: genderGroup
					Material.accent: "#008080"
				}
				RadioButton {
					id: femaleRadio
					text: "Female"
					ButtonGroup.group: genderGroup
					Material.accent: "#008080"
				}
				RadioButton {
					id: otherRadio
					text: "Other"
					ButtonGroup.group: genderGroup
					Material.accent: "#008080"
				}
			}

			Label {
				text: "Account Role"
				font.bold: true
			}
			ComboBox {
				id: roleBox
				textRole: "text"
				Layout.fillWidth: true
				model: ListModel {
					ListElement {
						value: 0
						text: "Select a Role..."
					}
					ListElement {
						value: 1
						text: "Admin"
					}
					ListElement {
						value: 2
						text: "Staff"
					}
					ListElement {
						value: 3
						text: "Guest"
					}
				}
				property int selectedValue: model.get(currentIndex).value
			}

			Button {
				id: registerBtn
				text: "Register"
				Layout.fillWidth: true
				Layout.topMargin: 15
				enabled: userField.acceptableInput && pwdField.acceptableInput
						 && ageField.acceptableInput
						 && genderGroup.checkedButton !== null
						 && roleBox.selectedValue > 0

				onClicked: console.log("Registered:", userField.text)
			}
		}
	}
}
