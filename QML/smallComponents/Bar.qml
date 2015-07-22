import QtQuick 2.0

Rectangle {

    property int width_: 100
    property int height_: 100
    property bool isSelect: false

    id: iBar
    color: "white"
    width: width_
    height: height_

    Column {
        spacing: 1
        width: parent.width - 5
        height: parent.height - 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Rectangle {
         width: parent.width
         height: (parent.height)/3
         color: isSelect ? "gold" : "white"
         border.color: "gray"
         }
        Rectangle {
         width: parent.width
         height: (parent.height)/3
         color: isSelect ? "gold" : "white"
         border.color: "gray"
         }
        Rectangle {
         width: parent.width
         height: (parent.height)/3
         color: isSelect ? "gold" : "white"
         border.color: "gray"
         }

    }





}

