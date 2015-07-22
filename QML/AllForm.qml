import QtQuick 2.0

// import ProfileUserModel 1.0
// import SearchModel 1.0

Rectangle {
   id: allForm
   width: lvList.width
   height: lvList.height

   property int backgroundNumber: index

   color: "#444444"

/*
    Text {
        id: cText
        width: allForm.width
        height: 50
        color: "#ffeeee"
        text: name
        anchors.top: parent.top
        anchors.topMargin: 1
        font.pixelSize: 40
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
/*
    MouseArea {
        anchors.fill: cText
        onClicked: {
            console.log("ListView el#" + index + " clicked!")
 //           idModelReleases.search();
 //           console.log( idModelReleases.rowCount());

        }

    }*/



    Loader {

        x: 0
        y: 0
        id: forms
                width: allForm.width
                height: allForm.height
                anchors.top: allForm.top
       //         anchors.topMargin: 100

        states: [
                State {
                    name: "Dashboard"
                    when: (backgroundNumber ==  0)
                    PropertyChanges { target: forms; sourceComponent: dashboard}


                },
                State {
                name: "Collection"
                when: (backgroundNumber ==  1)
                PropertyChanges { target: forms; sourceComponent: collection}

                                },
            State {
            name: "WantList"
            when: (backgroundNumber ==  2)
            PropertyChanges { target: forms; sourceComponent: wantList; // y: -height;
//            PropertyChanges { target: forms; /*sourceComponent: oneForm;*/  x:-500;

            }

                           },
            State {
            name: "Message"
            when: (backgroundNumber ==  3)
            PropertyChanges { target: forms; sourceComponent: message;

            }

             }
            ]

       onLoaded: { forms.visible = true; forms.item.forceActiveFocus(); }

       Component { id:dashboard; Dashboard {}}
       Component { id:collection; Collection {}}
       Component { id:wantList; WantList {}}
       Component { id:message; Marketplace {}}
    }


}
