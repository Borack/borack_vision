import QtQuick        2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: mainWindow;
    width: 320;
    height: 240;
    visible: true;
    color: "green";
    title: "First Window";

    ImageViewer {
        id: viewer
    }

    FileOpener {
        id: fileDialog
        onAccepted: {
            console.log("do something else")
//            viewer.image.source: fileDialog.fileUrl // NEXT -> not working yet.
        }
    }



    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Open...";
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


}
