import QtQuick 2.1
import QtQuick.Dialogs 1.0

FileDialog {
    modality: Qt.WindowModal
    title: "Choose a folder"
    selectExisting: true
    selectMultiple: true
    selectFolder: false
    nameFilters: [ "Image files (*.png *.jpg)", "All files (*)" ]
    selectedNameFilter: "All files (*)"
    onAccepted: {
        console.log("Accepted: " + fileUrls)
        _commonHandler.loadImage(fileUrls)
    }
//    onRejected: { console.log("Rejected") }
}
