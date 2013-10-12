import QtQuick 2.0

Rectangle {
    width: 500
    height: 500
    color: "transparent"

    property alias image: image

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "image://imageprovider/current"

        function reload() {
            var oldSource = source;
            source = "";
            source = oldSource;
        }

    }
}
