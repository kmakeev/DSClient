import QtQuick 2.0

Rectangle {

     id: detailRelease

//     property variant idIndex: index

//     property bool iWaitLoading: true

/*     Loading {  // Тупилка для загрузки
         id: dummyDetailsLoading
         visible: iWaitLoading
         widthI: 60; heightI: 60
         anchors.verticalCenter: parent.verticalCenter
         anchors.horizontalCenter: parent.horizontalCenter

       }
*/

    Text {
        id: format
        text: model ? model.Format : ""
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pixelSize: 24; font.bold: true
        width: details.width
        elide: Text.ElideRight

    }
    Text {
        id: catno
        text: model ? model.Catno : ""               //+details.width
        anchors.top: format.bottom
        anchors.topMargin: 0
        font.pixelSize: 24; font.bold: true
        width: details.width
        elide: Text.ElideRight

    }

    Text {
        id: country
        text: model ? model.Country : ""               //+ details.height
        anchors.top: catno.bottom
        anchors.topMargin: 0
        font.pixelSize: 24; font.bold: true
        width: details.width
        elide: Text.ElideRight


    }

    Flickable {
        id: flick
        width: details.width
        height: details.height - 100
        anchors.top: country.bottom
        contentHeight: methodText.height
        clip: true
         Text {
             id: methodText
             width: details.width
             text:model ? "Notes: <br/>" + model.ReleaseNotes : "None"
             wrapMode: Text.WordWrap;

         }
//           Text { id: methodText; text: Notes; wrapMode: Text.WordWrap; width: details.width }
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



    TextButton {                                                  //Эти кнопки будут работать только для заголиненного пользователя

        id : addWant
        text: "Add to Wantlist"
        anchors.horizontalCenter: flick.horizontalCenter
        anchors.bottom: flick.bottom
        visible: idProfileUser.isLoggin ? true : false           //Пробуем показать для если есть логин
        onClicked: {
                     //тут нужно подумать будем ли сазу при добавлении в wantlist спрашивать про описание и оценку.
                     console.log("Click Add Release to Wantlist index " + currentIndex)

                     if (idModelReleases.addReleasesInWantlist(currentIndex))
                     {

                     recipe.state = "popupToWantList"
                     } else
                     {
                 //       recipe.state = "error"    //выводим ошибку
                     }

        }
    }


    TextButton {                                                  //Эти кнопки будут работать только для заголиненного пользователя

        id : addCollection
        text: "Add to Collection"
        anchors.horizontalCenter: flick.horizontalCenter
        anchors.bottom: addWant.top
        visible: idProfileUser.isLoggin ? true : false
        onClicked: {

                     console.log("Click Add Release to Collection index " + currentIndex)
                     if (idModelReleases.addReleasesInCollection(currentIndex))
                      {
                        console.log("Release is addet to Collection")
                        recipe.state = "popupToCollection"
                      } else
                     {
                 //       recipe.state = "error"    //выводим ошибку
                     }



        }
    }


}

