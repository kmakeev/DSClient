import QtQuick 2.0

Rectangle {
    id: detailArtist

    Text {
        id: namevariations
        text: model.ArtistNamevariations
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pointSize: 16; font.bold: true

    }
    Text {
        id: urls
        text: model.ArtistUrls
        anchors.top: namevariations.bottom
        anchors.topMargin: 0
        font.pointSize: 12; font.bold: true
    }


    Flickable {
        id: flick
        width: detailArtist.width
        anchors { top: urls.bottom; bottom:detailArtist.bottom }
        contentHeight: methodText.height
        clip: true

         Text { id: methodText; text:model.ArtistProfiles; wrapMode: Text.WordWrap; width: detailArtist.width }

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

