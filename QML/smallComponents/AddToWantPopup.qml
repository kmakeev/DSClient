import QtQuick 2.0


Rectangle {

    signal close
    property int currentIndex: recipe.currentIndex


    id: addToWantPopup
    //   x: 50; y: 50;

    width: idFone.width/2
    height: idFone.height/2
    anchors.horizontalCenter: idFone.horizontalCenter
    anchors.verticalCenter: idFone.verticalCenter
    focus: true
    color: "gray"
    border.color: "#0f0e0e"
    radius: 5


    Row {
        id: topRow
        x: 5; y: 5; height: addToWantPopup.height - 10; width: addToWantPopup.width -10
        spacing: 5

        Column {
            id: column1

            width: parent.width; height: parent.height
            spacing: 5


            Text {
                id: info
                width: parent.width
                text: qsTr ("Release added to Wantlist")
                anchors.horizontalCenter: column1.horizontalCenter
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: 24; font.bold: true
            }
            Item
            {
                width: column1.width
                height: 100
                Text {
                    text: qsTr ("Rating")
                    anchors.top: parent.tob
                    anchors.left: parent.left
                    font.pixelSize: 24; font.bold: true
                }
                RatedMobail {
                    id: myRating
                    width: 180
                    height: 30
                    anchors.bottom: parent.bottom

                    onChanged: {
                        console.log (" Rating - " + myRating.rated);
                  //      idModelReleases.editReleasesInCollection(addToCollectionPopup.currentIndex, myRating.rated, -1);
                        idModelReleases.editReleasesInWantlist(addToWantPopup.currentIndex, myRating.rated);
                    }

                }
            }



            TextInputMain {
                id: iProfile
                width: column1.width
                height: 200
                fontsize: 30
                color : "white"
                password: false
                label : qsTr ("Notes")
                labelDefault : qsTr ("Notes")
                onTextInputEnter:  {
                console.log ("label");
                idModelReleases.editReleasesInWantlist(addToWantPopup.currentIndex, iProfile.label);
                }
            }


            TextButton {
                id: closeButton

                text: " Close "
                anchors.horizontalCenter: iProfile.horizontalCenter
                onClicked: {
            //        myRating.rated = 0
           //         console.log ("notes " + iProfile.label + "Rating - " + myRating.rated);
                    close();
                }
            }
            /*
            TextButton {
                id: saveButton
                text: " Save "
                anchors.horizontalCenter: iProfile.horizontalCenter
                onClicked: {
             //       console.log ("Save " + iProfile.text + "Rating is - " + myRating.rated);
                   idModelReleases.editReleasesInWantlist(currentIndex, iProfile.label, myRating.rated);
             //       myRating.rated = 0
             //       console.log ("notes " + iProfile.label + "Rating - " + myRating.rated);
            //        myRating.changed();
                    close();
                }
            }
          */

        }
    }
}



