import QtQuick 2.3

Rectangle {

    id: idRated
    property int selected: 0
    property int rated: 0
    property bool isRated: false
    signal changed

    onChanged: {
    //    console.log ("Rated - " + selected);
        state = selected
    }

    onVisibleChanged: {
       myRating.rated = 0
       state = 0;
   }

    Row {
        spacing: 0
        height: idRated.height
        width: idRated.width

        Item {
            width: parent.width/6
            height: parent.width/6
            Bar {
                id: idStar1
                width_: parent.width
                height_: parent.height
                isSelect: false
            }

            Image {

            }
            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onEntered: { idRated.selected = 1; changed();}
                onExited: {  idRated.selected = idRated.rated; changed();}
                onClicked: { idRated.rated = 1; idRated.isRated = true; changed()}
            }
        }
        Item {
            width: parent.width/6
            height: parent.width/6
            Bar {
                id: idStar2
                width_: parent.width
                height_: parent.height
                isSelect: false
            }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: { idRated.selected = 2; changed();}
                    onExited: {  idRated.selected = idRated.rated; changed();}
                    onClicked: { idRated.rated = 2; idRated.isRated = true; changed()}
                }

        }
        Item {
            width: parent.width/6
            height: parent.width/6
            Bar {
                id: idStar3
                width_: parent.width
                height_: parent.height
                isSelect: false

             }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: { idRated.selected = 3; changed();}
                    onExited: {  idRated.selected = idRated.rated; changed();}
                    onClicked: { idRated.rated = 3; idRated.isRated = true; changed()}
                }

        }
        Item {
            width: parent.width/6
            height: parent.width/6
            Bar {
                id: idStar4
                width_: parent.width
                height_: parent.height
                isSelect: false
            }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: { idRated.selected = 4; changed();}
                    onExited: {  idRated.selected = idRated.rated; changed();}
                    onClicked: { idRated.rated = 4; idRated.isRated = true; changed()}
                }

        }
        Item {
            width: parent.width/6
            height: parent.width/6
            Bar {
                id: idStar5
                width_: parent.width
                height_: parent.height
                isSelect: false
            }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: { idRated.selected = 5; changed();}
                    onExited: {  idRated.selected = idRated.rated; changed();}
                    onClicked: { idRated.rated = 5; idRated.isRated = true; changed()}
                }

        }

        Item {
            width: parent.width/6
            height: parent.width/6
            Image {
                id: idCancel
                visible: isRated
                source: "/pics/cross-lines_2556.ico"
                anchors.fill: parent
                scale: 0.7
               }
                MouseArea {
                anchors.fill: parent
                onClicked: { idRated.rated = 0; idRated.selected = idRated.rated; idRated.isRated = false; changed()}
                }

        }


    }

    states: [

        State {
            name: "1"
            PropertyChanges {target: idStar1; isSelect: true}

        },
        State {
            name: "2"
            PropertyChanges {target: idStar1; isSelect: true}
            PropertyChanges {target: idStar2; isSelect: true}

        },
        State {
            name: "3"
            PropertyChanges {target: idStar1; isSelect: true}
            PropertyChanges {target: idStar2; isSelect: true}
            PropertyChanges {target: idStar3; isSelect: true}

        },
        State {
            name: "4"
            PropertyChanges {target: idStar1; isSelect: true}
            PropertyChanges {target: idStar2; isSelect: true}
            PropertyChanges {target: idStar3; isSelect: true}
            PropertyChanges {target: idStar4; isSelect: true}

        },
        State {
            name: "5"
            PropertyChanges {target: idStar1; isSelect: true}
            PropertyChanges {target: idStar2; isSelect: true}
            PropertyChanges {target: idStar3; isSelect: true}
            PropertyChanges {target: idStar4; isSelect: true}
            PropertyChanges {target: idStar5; isSelect: true}

        },
        State {
            name: "0"
            PropertyChanges {target: idStar1; isSelect: false}
            PropertyChanges {target: idStar2; isSelect: false}
            PropertyChanges {target: idStar3; isSelect: false}
            PropertyChanges {target: idStar4; isSelect: false}
            PropertyChanges {target: idStar5; isSelect: false}

        }
    ]



}
