import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1

Rectangle {

    signal close
    property int currentIndex: recipe.currentIndex



    Component {
        id: idFieldListdelegate
        Fieldlistdelegate {}
    }


    id: addToCollectionPopup
    width: idFone.width/2+100
    height: idFone.height/2+100
    anchors.horizontalCenter: idFone.horizontalCenter
    anchors.verticalCenter: idFone.verticalCenter
    focus: true
    color: "gray"
    border.color: "#0f0e0e"
    radius: 5

    Row {
        id: topRow
        x: 5; y: 5; height: addToCollectionPopup.height -10 ; width: addToCollectionPopup.width - 10
        spacing: 5

        Column {
            id: column1

            width: parent.width; height: parent.height
            spacing: 1


            Text {
                id: info
                width: parent.width
                text: qsTr ("Release added to Collection")
                anchors.horizontalCenter: parent.horizontalCenter
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: 18; font.bold: true
            }
            Item
            {
                width: column1.width
                height: 70
                Text {
                    id: raitedText
                    text: qsTr ("Rating")
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 18; font.bold: true
                }
                RatedMobail {
                    id: myRating
                    width: 180
                    height: 30
                    anchors.top: raitedText.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    onChanged: {
                        console.log (" Rating - " + myRating.rated);
                        idModelReleases.editReleasesInCollection(addToCollectionPopup.currentIndex, myRating.rated, -1);

                    }
                }
            }

            Item
            {
                width: column1.width
                height: 100


                Text {
                    id: textFolder
                    text: qsTr ("Folder")
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 18; font.bold: true

                }

                ComboBox {

                    id: comboFolder
                    model: idModelFolder
                    width: parent.width
                    height: parent.height-textFolder.height
                    anchors.top: textFolder.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    textRole: "name"

                    onCurrentIndexChanged: {

                        if (addToCollectionPopup.currentIndex>=0 && currentIndex>=0) // На -1 сброс индекса
                        {
                   //  проверка индекса при вызове редактирования, передаем id сразу, хранится в модели, можно сохранять и другое
                            console.log ("Index - "+addToCollectionPopup.currentIndex + " Rating - " + myRating.rated + ", Folder -" + idModelFolder.get(currentIndex).name + " FolderId - " +  idModelFolder.get(currentIndex).FolderId);
                            idModelReleases.editReleasesInCollection(addToCollectionPopup.currentIndex, myRating.rated,  idModelFolder.get(currentIndex).FolderId);
                        }
                    }

                    onVisibleChanged: {

                      console.log ("ComboBox folder changed " + currentIndex);
                      currentIndex = -1;
             //         comboFolder.model = idModelFolder;



                    }


                }
            }

            ListView {
                id: fieldlist
                width: column1.width
                height: 400
                delegate: idFieldListdelegate
                model: idFieldsModel
                // interactive: false

            }

            Item            //Кнопки в колонке
            {

                width: column1.width
                height: 25

                TextButton {
                    id: closeButton
                    text: " Close "
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {

                        //       console.log ("Rating - " + myRating.rated + ", Folder -" + currentIndex);


                        close();
                    }
                }

            }
        }

    }
}
