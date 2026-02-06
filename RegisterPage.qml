import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
	id: registrationPage
	anchors.fill: parent

	// Signal to notify the StackView to navigate back
	signal goBack()

	// 1. Background Image
	Image {
		id: backgroundImage
		source: "qrc:/assets/TheCrack.jpg"
		anchors.fill: parent
		fillMode: Image.PreserveAspectCrop

		// Optional darken overlay
		Rectangle {
			anchors.fill: parent
			color: "black"
			opacity: 0.2
		}
	}

	// 2. Fixed Back Button (Top-Left)
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

	// // 3. Scrollable Content
	// ScrollView {
		// anchors.fill: parent
		// contentWidth: parent.width
		// clip: true

		ColumnLayout {
			id: mainLayout
			width: parent.width * 0.60
			anchors.centerIn: parent
			anchors.horizontalCenter: parent.horizontalCenter
			spacing: 12

			// --- Translucent Card Background ---
			Rectangle {
				id: cardBackground
				anchors.fill: parent
				// anchors.margins: -25
				color: "#D9FFFFFF" // Approx 85% white
				radius: 15
				z: -1 // Stay behind inputs
				border.color: "#33000000"
				border.width: 1
			}

			Text {
				text: "Create Account"
				font.pixelSize: 28
				font.bold: true
				color: "#2c3e50"
				Layout.alignment: Qt.AlignHCenter
				Layout.topMargin: 60 // Space for the Back button
				Layout.bottomMargin: 10
			}

			// --- Username ---
			Label { text: "Username"; font.bold: true; Layout.topMargin: 5 }
			TextField {
				id: userField
				placeholderText: "Pick a unique username"
				maximumLength: 20
				Layout.fillWidth: true
			}

			// --- Password ---
			Label { text: "Password"; font.bold: true }
			TextField {
				id: pwdField
				placeholderText: "Min 6 characters"
				echoMode: TextField.Password
				Layout.fillWidth: true
			}

			// --- Age ---
			Label { text: "Age"; font.bold: true }
			TextField {
				id: ageField
				placeholderText: "18 - 99"
				validator: IntValidator { bottom: 18; top: 99 }
				inputMethodHints: Qt.ImhDigitsOnly
				Layout.fillWidth: true
			}

			// --- Gender ---
			Label { text: "Gender"; font.bold: true; Layout.topMargin: 5 }
			RowLayout {
				spacing: 15
				ButtonGroup { id: genderGroup }
				RadioButton {
					id: maleRadio; text: "Male"
					ButtonGroup.group: genderGroup
				}
				RadioButton {
					id: femaleRadio; text: "Female"
					ButtonGroup.group: genderGroup
				}
				RadioButton {
					id: otherRadio; text: "Other"
					ButtonGroup.group: genderGroup
				}
			}

			// --- Role ---
			Label { text: "Account Role"; font.bold: true; Layout.topMargin: 5 }
			ComboBox {
				id: roleBox
				textRole: "text"
				Layout.fillWidth: true
				model: ListModel {
					ListElement { value: 0; text: "Select a Role..." }
					ListElement { value: 1; text: "Developer" }
					ListElement { value: 2; text: "Designer" }
					ListElement { value: 3; text: "Manager" }
				}
				property int selectedValue: model.get(currentIndex).value
			}

			// --- Submit Button ---
			Button {
				id: registerBtn
				text: "Register"
				Layout.fillWidth: true
				Layout.topMargin: 20
				Layout.bottomMargin: 40 // Space at the bottom of the scroll

				enabled: userField.text.length > 0
						 && pwdField.text.length >= 6
						 && ageField.acceptableInput
						 && genderGroup.checkedButton !== null
						 && roleBox.selectedValue > 0

				onClicked: {
					console.log("Registered:", userField.text)
					// Add your transition or logic here
				}
			}
		}
	// }
}
