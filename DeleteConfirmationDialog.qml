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
    Material.accent: "#008080"
    Material.background: "snow"
    footer: DialogButtonBox {
        Button {
            text: "Delete"
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
            flat: true
        }
        Button {
            text: "Cancel"
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
            flat: true
        }
    }
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
