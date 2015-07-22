import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.0

// import ProfileUserModel 1.0
import ReleasesModel 1.0

ApplicationWindow {
    visible: true
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    id: mainWindow
    objectName: "mainWindow"
    color: "#F0F0FF"

    ReleasesModel { id: idModelReleases }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
                title: "Edit"
                MenuItem { text: "Cut" }
                MenuItem { text: "Copy" }
                MenuItem { text: "Paste" }
            }
    }

     ListView {
        id: lvList
        objectName: "lvList"
 //       y: 50
        width: parent.width
        height: parent.height
        clip: true
        spacing: 1
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem

        model: ListModel {
            ListElement { name: "Dashboard" }
            ListElement { name: "Collection" }
            ListElement { name: "Want list" }
            ListElement { name: "Message" }
        }
        delegate: AllForm {}
        focus: true


    }


}
