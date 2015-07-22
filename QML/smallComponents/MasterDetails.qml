import QtQuick 2.0

Rectangle {

     id: detailRelease


    Text {
        id: format
        text: model.Format
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pointSize: 12; font.bold: true


    }
    Text {
        id: catno
        text: model.Catno
        anchors.top: format.bottom
        anchors.topMargin: 0
        font.pointSize: 12; font.bold: true

    }

    Text {
        id: country
        text: model.Country
        anchors.top: catno.bottom
        anchors.topMargin: 0
        font.pointSize: 12; font.bold: true


    }

    Flickable {
        id: flick
        width: detailRelease.width
        anchors { top: country.bottom; bottom:detailRelease.bottom }
        contentHeight: methodText.height
        clip: true

        Text { id: methodText; text:"Notes: <br/>" + model.MasterNotes; wrapMode: Text.WordWrap; width: detailRelease.width }

    }



    Image {
        anchors { right: flick.right; top: flick.top }
        width: 20; height: 20
        source: "/pics/moreUp.jpg"
        opacity: flick.atYBeginning ? 0 : 1
    }

    Image {
        anchors { right: flick.right; bottom: flick.bottom }
        width: 20; height: 20
        source: "/pics/moreDown.jpg"
        opacity: flick.atYEnd ? 0 : 1
    }


}

