import QtQuick 2.0
import "smallComponents"



Rectangle {

    id: form2

          color: "#ffffff"


          Loading {             //Тупилка по свойству из модели
              id: wait
              widthI: 150
              heightI: 150
              visible: idCollectionModel.waitReadCollection
              anchors.verticalCenter: form2.verticalCenter
              anchors.verticalCenterOffset: -heightI/2
              anchors.horizontalCenter: form2.horizontalCenter
              anchors.horizontalCenterOffset: -widthI/2

          }


    ListView {

        id:collection
        anchors.fill:form2
        //показываем список если залогинен пользователь и нет тупилки
        visible:idProfileUser.isLoggin&&!idCollectionModel.waitReadCollection
     //   visible:!idCollectionModel.waitReadCollection

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
                text: "Коллекция " + idProfileUser.name
            }

        }


   //     model: idCollectionModel.proxy();
        model: idCollectionModel
        delegate: ItemCollectionModelQML {}
        cacheBuffer: 800 //Размер буфера кеша
  //      highlightRangeMode: ListView.StrictlyEnforceRange
  //      Component.onCompleted: {collection.model = idCollectionModel.proxy();}
/*
        Component.onCompleted: {
            console.log("Model Listview created");
            var model = idCollectionModel.proxy();
            collection.model = model;
        }
*/
       }




    Text {
        id: textForNotLoggin
        visible: !idProfileUser.isLoggin
     //   visible: false
        width: parent.width
        height: parent.height
        color: "#a22626"
        text: qsTr("Please login or register")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 40
    }
}


