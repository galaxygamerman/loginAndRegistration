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

			SwipeView {
				id: view
				currentIndex: 0
				Layout.fillWidth: true
				Layout.fillHeight: true
				clip: true
				interactive: false

				// PAGE 1: Credentials
				ColumnLayout {
					spacing: 5
					Label {
						text: "Username"
						font.bold: true
					}
					TextField {
						id: userField
						placeholderText: "Username"
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
						text: "Confirm Password"
						font.bold: true
					}
					TextField {
						id: confirmPwdField
						placeholderText: "Confirm Password"
						echoMode: TextField.Password
						Layout.fillWidth: true
						Material.accent: "#008080"
						validator: RegularExpressionValidator {
							regularExpression: /^.{6,32}$/
						}
					}

					Item {
						Layout.fillHeight: true
					} // Spacer
				}

				// PAGE 2: Personal Details
				ColumnLayout {
					spacing: 5
					Label {
						text: "Full Name"
						font.bold: true
					}
					TextField {
						id: nameField
						placeholderText: "John \"Nickname\" Doe"
						Layout.fillWidth: true
						Material.accent: "#008080"
						validator: RegularExpressionValidator {
							regularExpression: /^[\w'" ]{2,32}$/
						}
					}

					Label {
						text: "Email ID"
						font.bold: true
					}
					TextField {
						id: emailField
						placeholderText: "email@example.com"
						Layout.fillWidth: true
						Material.accent: "#008080"
						inputMethodHints: Qt.ImhEmailCharactersOnly
						validator: RegularExpressionValidator {
							regularExpression: /^[\w\.+-]+@[\w\.]+\.[\w]{2,4}$/
						}
					}

					Label {
						text: "Phone Number"
						font.bold: true
					}
					TextField {
						id: phoneField
						placeholderText: "12345 67890"
						Layout.fillWidth: true
						Material.accent: "#008080"
						inputMethodHints: Qt.ImhDialableCharactersOnly
						validator: RegularExpressionValidator {
							regularExpression: /^((\+\d{1,3}|\(\+\d{1,3}\)) ?)?\d{5}( )?\d{5}$/
						}
					}

					Item {
						Layout.fillHeight: true
					}
				}

				// PAGE 3: Final Details
				ColumnLayout {
					spacing: 5
					Label {
						text: "Age"
						font.bold: true
					}
					SpinBox {
						id: ageField
						from: 18
						to: 200
						value: 18
						editable: true
						Layout.fillWidth: true
						Material.accent: "#008080"
						contentItem: TextInput {
							text: ageField.textFromValue(ageField.value,
														 ageField.locale)
							font: ageField.font
							color: "#2c3e50"
							selectionColor: "#008080"
							horizontalAlignment: Qt.AlignHCenter
							verticalAlignment: Qt.AlignVCenter
							validator: IntValidator {
								bottom: 18
								top: 200
							}
						}
					}

					Label {
						text: "Gender"
						font.bold: true
					}
					RowLayout {
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
						Material.accent: "#008080"
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

					Item {
						Layout.fillHeight: true
					}
				}
			}

			PageIndicator {
				id: indicator
				count: view.count
				currentIndex: view.currentIndex
				Layout.alignment: Qt.AlignHCenter
			}

			Button {
				id: nextBtn
				text: "Next >"
				Layout.fillWidth: true
				Layout.topMargin: 15
				Material.accent: "#008080"
				visible: {
					if (view.currentIndex === 0)
						return userField.acceptableInput
								&& pwdField.acceptableInput
								&& (pwdField.text === confirmPwdField.text)
					else if (view.currentIndex === 1)
						return nameField.acceptableInput
								&& emailField.acceptableInput
								&& phoneField.acceptableInput
					else if (view.currentIndex === 2)
						return false
				}
				enabled: {
					if (view.currentIndex === 0)
						return userField.acceptableInput
								&& pwdField.acceptableInput
								&& (pwdField.text === confirmPwdField.text)
					else if (view.currentIndex === 1)
						return nameField.acceptableInput
								&& emailField.acceptableInput
								&& phoneField.acceptableInput
					else if (view.currentIndex === 2)
						return false
				}

				onClicked: view.currentIndex += 1
			}
			Button {
				id: registerBtn
				text: "Register"
				Layout.fillWidth: true
				Layout.topMargin: 15
				Material.accent: "#008080"
				visible: userField.acceptableInput
						 && pwdField.acceptableInput
						 && (pwdField.text === confirmPwdField.text)
						 && nameField.acceptableInput
						 && emailField.acceptableInput
						 && phoneField.acceptableInput
						 && ageField.contentItem.acceptableInput
						 && genderGroup.checkedButton !== null
						 && roleBox.selectedValue > 0
						 && view.currentIndex === view.count - 1
				enabled: userField.acceptableInput
						 && pwdField.acceptableInput
						 && (pwdField.text === confirmPwdField.text)
						 && nameField.acceptableInput
						 && emailField.acceptableInput
						 && phoneField.acceptableInput
						 && ageField.contentItem.acceptableInput
						 && genderGroup.checkedButton !== null
						 && roleBox.selectedValue > 0
						 && view.currentIndex === view.count - 1

				onClicked: console.log(
							   `Registered: ${userField.text}`
							   + ` password: ${pwdField.text}`
							   + ` age: ${ageField.value}`
							   + ` name: ${nameField.text}`
							   + ` email: ${emailField.text}`
							   + ` phone: ${phoneField.text}`
							   + ` gender: ${genderGroup.checkedButton.text}`
							   + ` role: ${roleBox.currentText}`)
			}
		}
	}
}
