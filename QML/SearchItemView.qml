import QtQuick 2.0
import "smallComponents"


Item {
    id: recipe
    property variant model
    property int currentIndex: releases.currentIndex
 //   anchors.fill: parent


    signal close

    // Простой прямоугольник со скругленными углами в качестве фона
    Rectangle {
        id: background
        x: 50; y: 50; width: field.width - x*2; height: field.height - y*2 - 100

        color: "white"
        border.color: "#0f0e0e"
        radius: 5

        Row {
            id: topLayout
            x: 5; y: 5; height: recipeImage.height; width: background.width
            spacing: 5

            Image {
                id: recipeImage
                width: wh; height: wh
              source: model ? "image://MyImageProvider/" + model.Thumb : ""


            }

            Column {
                id: column1

                width: background.width - recipeImage.width -10; height: recipeImage.height
                spacing: 5

                Text {
                    width: parent.width
                    text: model ? model.Title : ""
                    elide: Text.ElideRight
                    font.pixelSize: 24; font.bold: true
                }

                Text {
                    width: parent.width
                    text: model ? model.Type : ""
                    elide: Text.ElideRight
                    font.pixelSize: 24; font.bold: true
                    //       opacity: recipe.detailsOpacity
                }

                Text {
                    width: parent.width
                    text:  model ? model.LabelShort : ""
                    elide: Text.ElideRight
                    font.pixelSize: 24; font.bold: true
                    //   opacity: recipe.detailsOpacity
                }


                Text {
                    width: parent.width
                    elide: Text.ElideRight
                    text: model ? model.Year : ""

                    font.pixelSize: 24; font.bold: true
                    //   opacity: recipe.detailsOpacity
                }


            }
        }

        Item {
            id: details

            x: 10
            width: background.width
            anchors { top: topLayout.bottom; topMargin: 10; bottom: background.bottom; bottomMargin: 10 }
            opacity: 1

            Loader {

                x: 0
                y: 0
                id: detailswiev
                active: stateProperty


                states:[
                    State{
                        name: "Release"
                        when: model.isRelease
                        PropertyChanges { target: detailswiev; source: "/QML/smallComponents/ReleaseDetails.qml"}

                    },
                    State{
                        name: "Master"
                        when: model.isMaster
                        PropertyChanges { target: detailswiev; source: "/QML/smallComponents/MasterDetails.qml"}
                    },
                    State{
                        name: "Artist"
                        when: model.isArtist
                        PropertyChanges { target: detailswiev; source: "/QML/smallComponents/ArtistDetails.qml"}
                    },
                    State{
                        name: "Label"
                        when: model.isLabel
                        PropertyChanges { target: detailswiev; source: "/QML/smallComponents/LabelDetails.qml"}
                    }

                ]
            }


        }

        // Кнопка закрытия детализированного представления, т.е. устанавливает состояние обратно в состояние по умолчанию ('').
        TextButton {
            y: 10
            anchors { right: background.right; rightMargin: 10 }
    //        opacity: recipe.detailsOpacity
            text: "Close"

            onClicked: {
                console.log("Close item..." + currentIndex);
                idItemView.close();

            }
        }


        states:[
            State {
                name: "Details"

                PropertyChanges { target: recipeImage; width: 200; height: 200 } // Делает изображение больше
                PropertyChanges { target:  topLayout; visible: true}
                PropertyChanges { target:  details; visible: true}

                // Запрещает рывки в детализированном представлении
                PropertyChanges { target: recipe.ListView.view; interactive: false }
                //Делает активным загрузчик
                PropertyChanges { target: detailswiev;  active: true}

            }]

    }

    //Прослойка для разделения этого итема и всплавающих окон
    // не работает привязка ко всему экрану
         Rectangle {
             id: idFone
             color: "gray"
             opacity: 0
             anchors.fill: recipe
             z: -3
             MouseArea {
                anchors.fill: parent
                onClicked: {}
             }
         }

         AddToWantPopup{

             id: idAddToWantPopup
             visible:false
             z:11
             onClose: {
                 recipe.state = "defaults"
                 idItemView.close();
             }
         }

         AddToCollectionPopup {
             id: idAddToCollectionPopup
             visible: false
             z: 11
             onClose: {
                 recipe.state = "defaults"
                 idItemView.close();
             }

         }

 //        state: "default"

         states: [
             State {
                 name: "popupToWantList"
                  PropertyChanges {target: idAddToWantPopup; visible: true; }
                  PropertyChanges {target: idFone; z: 3; opacity: 0.8}


                  },
             State {
                 name: "popupToCollection"
                  PropertyChanges {target: idAddToCollectionPopup; visible: true; }
                  PropertyChanges {target: idFone; z: 3; opacity: 0.8}


                  },

             State {
                 name: "default"
                      PropertyChanges {target: idAddToWantPopup; visible: false;}
                      PropertyChanges {target: idAddToCollectionPopup; visible: false; }
                      PropertyChanges {target:idFone; z: -3; opacity: 0}


             }

         ]


}

