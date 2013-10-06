import QtQuick 2.0

Rectangle {
    width: parent.width / 2
    height: parent.height / 2

    property alias source: image.source

    Image {
        id: image
        anchors.fill: parent
        source: "../image.jpeg"
    }
}
