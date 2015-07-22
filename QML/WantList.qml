import QtQuick 2.0
import "smallComponents"

Rectangle {

    id: formWantList

    color: "#ffffff"


    Loading {             //Тупилка по свойству из модели
        id: wait
        widthI: 150
        heightI: 150
        visible: idWantlistModel.waitReadWantlist
        anchors.verticalCenter: formWantList.verticalCenter
        anchors.verticalCenterOffset: -heightI/2
        anchors.horizontalCenter: formWantList.horizontalCenter
        anchors.horizontalCenterOffset: -widthI/2

    }

    ListView {

        id:wantlist
        anchors.fill:formWantList

        visible:idProfileUser.isLoggin&&!idWantlistModel.waitReadWantlist
      //  visible:!idWantlistModel.waitReadWantlist

        header:
            Rectangle {
            height: 40
            color: "gray"

            width: parent.width
            border {
                color: "black"
                width: 1
            }
            Text {
                font.pixelSize: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
                renderType: Text.NativeRendering
                text: "WantList " + idProfileUser.name
            }

        }


        model: idWantlistModel
        delegate: ItemWantListModelQML {}
        cacheBuffer: 800 //Размер буфера кеша
    }
    Text {
        id: textForNotLoggin
        visible: !idProfileUser.isLoggin
   //     visible: false
        width: parent.width
        height: parent.height
        color: "#a22626"
        text: qsTr("Please login or register ")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 40
    }
}


