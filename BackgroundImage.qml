import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

Image {
    id: root
    source: "qrc:/assets/TheCrack.jpg"
    fillMode: Image.PreserveAspectCrop

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.2
    }
}
