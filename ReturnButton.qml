import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Text {
    id: root

    signal clicked

    font.pixelSize: 16
    color: textMouseArea.containsMouse ? "white" : "#e0e0e0"
    z: 10
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.margins: 20

    MouseArea {
        id: textMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
    }
}
