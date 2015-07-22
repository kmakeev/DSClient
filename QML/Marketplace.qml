import QtQuick 2.0

Rectangle {
    id: one
    width: 600
    height: 600

    Text {
        id: commingsoon

        width: parent.width
        height: parent.height
        color: "#a22626"
        text: qsTr("Comming soon ")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 40
    }
}

