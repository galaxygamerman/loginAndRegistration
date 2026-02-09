import QtQuick
import QtQuick.Controls.Material

Dialog {
    id: successDialog

    property alias text: textBox.text

    width: 300
    modal: true
    standardButtons: Dialog.Ok
    Material.accent: "#008080"
    Material.background: "snow"

    Text {
        id: textBox
        wrapMode: Text.WordWrap
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
    }
}
