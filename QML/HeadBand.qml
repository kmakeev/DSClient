import QtQuick 2.4
import QtQuick.Controls 1.4
// import QtQuick.Controls.Styles 1.1

Rectangle {

    property int isProgress:0

    anchors.fill: parent
    color: "black"
    Image {
        id: idLogo
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        source: "/pics/logo.jpg"
    }
/*
    ProgressBar {
        id: idProgressBar
        value: isProgress
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 200
        anchors.horizontalCenter: parent.horizontalCenter
    //    indeterminate: true

    }
*/
}

