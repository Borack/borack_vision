import QtQuick        2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: mainWindow;
    width: row.width + 20;
    height: row.height + 20;
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


    Row{
        id: row
        spacing: 10
        anchors.topMargin: 20


        ImageViewer {
            id: viewer
        }
        CheckBox {
            text: "Show features"
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





}
