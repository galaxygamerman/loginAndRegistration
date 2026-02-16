import QtQuick
import QtQuick.Controls.Material

Dialog {
    id: root

    property alias text: textBox.text
    property string usernameToDelete: ""
    property int rowToDelete: -1

    title: "Confirm Deletion"
    width: 300
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    Material.accent: "#008080"
    Material.background: "snow"
    onAccepted: {
        userAbstractTableModel.removeRows(rowToDelete, 1)
        console.log("Deleted user:", usernameToDelete)
    }

    Text {
        id: textBox
        wrapMode: Text.WordWrap
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
    }
}
