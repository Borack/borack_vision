import QtQuick 2.1
import QtQuick.Dialogs 1.0

FileDialog {
    modality: Qt.WindowModal
    title: "Choose a folder"
    selectExisting: true
    selectMultiple: false
    selectFolder: false
    nameFilters: [ "Image files (*.png *.jpg)", "All files (*)" ]
    selectedNameFilter: "All files (*)"
    onAccepted: { console.log("Accepted: " + fileUrls) }
    onRejected: { console.log("Rejected") }
}
