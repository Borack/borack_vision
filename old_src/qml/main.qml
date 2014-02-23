import QtQuick        2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: mainWindow;
    width: row.width + 20;
    height: column.height + 20;
    visible: true;
    title: "First Window";
    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Open...";
                shortcut: "Ctrl+O"
                onTriggered: {
                    fileDialog.open();
                }
            }
            MenuItem {
                text: "Close"
                onTriggered: Qt.quit();
            }
        }
    }

    Column {
        id: column
        spacing:10
        anchors.topMargin: 20

        Row{
            id: row
            spacing: 10


            ImageViewer {
                id: viewerRef
                index: 0
            }

            ImageViewer {
                id: viewerObs
                index: 1
            }

            CheckBox {
                text: "Show features"
                checked: true
                onClicked:  {
                    viewerRef.featureIimage.visible = checked;
                    viewerObs.featureIimage.visible = checked;
                    matching.featureIimage.visible = checked;
                }
            }
        }

        ImageViewer {
            id: matching
            image.source:  "image://imageprovider/matches"
            featureIimage.source:  "image://imageprovider/matches/ölkjöl"
        }
    }

    Button {
        anchors.bottom:parent.bottom
        anchors.right: parent.right
        anchors.margins: 20
        text: "Quit"
        onClicked: Qt.quit()
    }

    FileOpener {
        id: fileDialog
    }


    Connections {
        target: _commonHandler
        onNewImage:
        {
            viewerRef.reloadAll()
            viewerObs.reloadAll();
            matching.reloadAll();
        }
    }



    Component.onCompleted: {
        _commonHandler.loadImage("file:///Users/sim/Desktop/hugin1/image-1.jpg");
    }


}
