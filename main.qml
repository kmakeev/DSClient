import QtQuick 2.2
import QtQuick.Controls 1.3
// import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.0
import "QML"



ApplicationWindow {

    property bool isHeadBand: true


    visible: true
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    objectName: "mainWindow"
    HeadBand {
        id: headBand
        isProgress:0


    }

    Loader {
        id: window
        x: 0
        y: 0
        anchors.fill: parent
        //   active: false

        sourceComponent: mainWindow
        asynchronous: true
  //      visible: status == Loader.Ready
        onLoaded: { headBand.visible = false;
                    console.log("Loader complited ");

        }
    }

    Component {
        id: mainWindow
        MainWindow{
            anchors.fill : parent
   //         onProgressChanged: {isProgress=idCollectionModel.progressValue();}

        }
    }
}
