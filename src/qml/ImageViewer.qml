import QtQuick 2.0

Rectangle {
    width: 500
    height: 500
    color: "transparent"

    property alias image: image
    property alias featureIimage: featureIimage
    property int index: 0

    function reloadAll() {
        image.reload();
        featureIimage.reload();
    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "image://imageprovider/image/" + index

        function reload() {
            var oldSource = source;
            source = "";
            source = oldSource;
        }

    }

    Image {
        id: featureIimage
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "image://imageprovider/features/" + index

        function reload() {
            var oldSource = source;
            source = "";
            source = oldSource;
        }

    }
}
