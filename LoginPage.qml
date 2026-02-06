import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
    id: loginPage
    signal goToRegister
    anchors.fill: parent

    // 1. The Background Image (from previous step)
    Image {
        id: backgroundImage
        source: "qrc:/assets/TheCrack.jpg" // Ensure this matches your qrc path
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop

        // Optional darken overlay to help the translucent card pop
        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.2
        }
    }

    // 2. The Login Content
    ColumnLayout {
        id: loginLayout
        width: parent.width * 0.60
        anchors.centerIn: parent
        spacing: 15

        // --- Translucent Background Card ---
        Rectangle {
            id: translucentCard
            // Anchor to the layout and add some padding/margins
            anchors.fill: parent
            anchors.margins: -30

            // #CC (Alpha) provides roughly 80% opacity
            color: "#CCFFFFFF"
            radius: 12

            // Ensure it stays behind the text fields
            z: -1

            // Optional: Soft border to define the edge
            border.color: "#33000000"
            border.width: 1
        }

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
            // Material theme styling
            Material.accent: "#008080"
            background: Rectangle { color: "transparent"; border.width: 0 }
        }

        TextField {
            id: passwordInput
            placeholderText: "Password"
            echoMode: TextField.Password
            Layout.fillWidth: true
            Material.accent: "#008080"
            background: Rectangle { color: "transparent"; border.width: 0 }
        }

        ComboBox {
            id: roleInput
            model: ["Role", "Admin", "Staff", "Guest"]
            Layout.fillWidth: true
            Material.accent: "#008080"
        }

        Button {
            id: submitBtn
            text: "Sign In"
            Layout.fillWidth: true
            Layout.topMargin: 10
            enabled: usernameInput.text.length > 0 && roleInput.currentIndex !== 0

            onClicked: console.log("Logging in...")
        }

        Text {
            text: "New User? <u>Let's get registered"
            horizontalAlignment: Text.horizontalAlignment
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
