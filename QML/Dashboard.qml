import QtQuick 2.0
import "smallComponents"



Rectangle {



    signal clicked (var x, var y, var w, var h, var model)
    property alias model: releases.model
    property alias currentIndex: releases.currentIndex
    property alias currentItem: releases.currentItem

    id: form
    color: "#ffffff"

    Loading {
        id: wait
        widthI: 150
        heightI: 150
        visible: idModelReleases.waitFirstSearch
        anchors.verticalCenter: form.verticalCenter
        anchors.verticalCenterOffset: -heightI/2
        anchors.horizontalCenter: form.horizontalCenter
        anchors.horizontalCenterOffset: -widthI/2

    }


    Component {
        id: idDelegate
        ItemModelQML {}
    }




    onClicked: {
        console.debug("clicked " + x + " " + y + " " + w + " " + h);
  //      idItemView.anchors.destroy(); //подумать как развалить старые якоря
        idItemView.x = x;
        idItemView.y = y;
        idItemView.width = w;
        idItemView.height = h;

        form.state = "item";
        var item = model;
        idItemView.model = model;
        console.log("Index in Item " + currentIndex);

        idAnimation.start();        //Запускаем анимацию
    }

    ListView {
        id:releases
        anchors.fill:form


        visible:!idModelReleases.waitFirstSearch

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
                text: "Поиск " + idProfileUser.name
            }
            clip: true

        }
        model: idModelReleases
        delegate: idDelegate
        cacheBuffer: 800 //Размер буфера кеша



    }
    //Прослойка между литвью и итемом
    Rectangle {
        id: field
        color: "gray"
        opacity: 0
        anchors.fill: parent
        z: -1
        MouseArea {
           anchors.fill: parent
           onClicked: {}
        }

    }

    SearchItemView{

       id: idItemView

       property string stateProperty: ""            //Состояние внутри Итема
       property int index: 0
 ///      property real detailsOpacity : 0             //Прозрачность Итема
       property int wh: 150                         //размер картинки

       visible:false
       z:10

          onClose: {
          form.state = "list"
        }
    }






    SequentialAnimation {
        id: idAnimation
        ParallelAnimation {
            NumberAnimation {  target: idItemView; property: "y"; to: 50; duration: 600}
            NumberAnimation {  target: field; property: "opacity"; to: 0.8; duration: 1000}
            NumberAnimation {  target: idItemView; property: "wh"; to: 250; duration: 1000}

        }
        /*
        ScriptAction {
            script : {
                idItemView.anchors.left = form.left;
                idItemView.anchors.right = form.right;
                idItemView.anchors.top = form.top;
                idItemView.anchors.bottom = form.bottom;
                idItemView.anchors.leftMargin = 10
                idItemView.anchors.rightMargin = 10
                idItemView.anchors.topMargin = 10
                idItemView.anchors.bottomMargin = 10

                     }
        }*/
    }


    state: "list"

    states: [
      State {
            name: "item"
            PropertyChanges {target: idItemView; visible: true; height: form.height; wh: 150; stateProperty: "Details";}
        //    PropertyChanges {target: releases; opacity: 0.1;}
            PropertyChanges {target: field; z: 1; opacity: 0;}
            /*          PropertyChanges {target: idItemView; height: form.height;}
            PropertyChanges {target: idItemView; stateProperty: "Details";}
            PropertyChanges {target: idItemView; detailsOpacity: 0;}
            PropertyChanges {target: idItemView; wh: 150;}*/

            },

      State {
            name: "list"
            PropertyChanges {target: idItemView; visible: false; stateProperty: ""; }
            PropertyChanges {target:field; z: -1}
        //    PropertyChanges {target: releases; interactive: true;}

        }]



}






