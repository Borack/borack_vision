import QtQuick 2.0

Rectangle {
    width: 500
    height: 500
    color: "transparent"

    property alias source: image.source

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "../image.jpeg"
    }
}
