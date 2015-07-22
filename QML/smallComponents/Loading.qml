import QtQuick 2.2

Item {

    property bool waiting: true
    property int widthI: 100
    property int heightI: 100
    id: loading
//    z:0
/*
    states: [
        State { name: "visible"
                when: loading.visible
        //        PropertyChanges { target: loading; opacity: 1}
                PropertyChanges { target: loading; z: 0}
  //              PropertyChanges { target: rotation; angle:360 }
               },
        State { name: "inVisible"
                when: !loading.visible
          //      PropertyChanges { target: loading; opacity: 0}
                PropertyChanges { target: loading; z: -50}
              }]
*/
    Image {

        id: image
        width: widthI; height: heightI
        source: "../../pics/Disque_Vinyl.png"
        smooth: true

        transform: Rotation {
            id: rotation
            origin.x: widthI/2; origin.y: widthI/2
            axis {x:0; y:0; z:1}
            angle: 0
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }

        states: State {
            name:"wait"
            when: loading.waiting
            PropertyChanges {
                target: rotation
                angle:360
            }
        }


        transitions: Transition {

            NumberAnimation {

                properties: "angle"
                easing.type: Easing.Linear
                duration: 1818
                loops: Animation.Infinite
            }

        }
    }

}

