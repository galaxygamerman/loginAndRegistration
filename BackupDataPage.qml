import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
	id: root
	implicitWidth: 640
	implicitHeight: 480

	signal goBack


	ReturnButton {
		id: backBtn
		text: "< Back"
		onClicked: root.goBack()
	}

	ColumnLayout {
		spacing: 20
		anchors.fill: parent

		Label {
			text: "USB Data Transfer"
			font {
				pixelSize: 20
				bold: true
			}
			Layout.alignment: Qt.AlignHCenter
		}

		RowLayout {
			spacing: 10
			Layout.alignment: Qt.AlignHCenter

			ComboBox {
				id: usbSelector
				model: []
				Layout.preferredWidth: 250
				Material.accent: "#008080"
				Material.background: "snow"

				onPressedChanged: {
					if (this.pressed) {
						model = fileManager.getUsbDrives()
					}
				}
			}

			Button {
				text: "Refresh"
				onClicked: usbSelector.model = fileManager.getUsbDrives()
				Material.accent: "#008080"
				Material.background: "snow"
			}
		}

		Button {
			id: submitBtn
			text: "Transfer CSV to USB"
			enabled: !(usbSelector.currentText === "" || usbSelector.currentText === "C:/")
			Layout.alignment: Qt.AlignHCenter
			focus: enabled
			Material.accent: "#008080"
			Material.background: "snow"

			onClicked: {
				let success = fileManager.copyCsvToDrive(usbSelector.currentText)
				if (success) {
					transferStatus.text = "Transfer Successful!"
					transferStatus.color = "green"
				} else {
					transferStatus.text = "Transfer Failed."
					transferStatus.color = "red"
				}
			}
		}

		Text {
			id: transferStatus
			text: ""
			Layout.alignment: Qt.AlignHCenter
		}
	}
}
