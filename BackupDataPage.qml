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

				onPressedChanged: {
					if (pressed) {
						model = dbManager.getUsbDrives()
					}
				}
			}

			Button {
				text: "Refresh"
				onClicked: usbSelector.model = dbManager.getUsbDrives()
			}
		}

		Button {
			text: "Transfer CSV to USB"
			enabled: usbSelector.currentText !== ""
			Layout.alignment: Qt.AlignHCenter
			highlighted: true

			onClicked: {
				let success = dbManager.copyCsvToDrive(usbSelector.currentText)
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
