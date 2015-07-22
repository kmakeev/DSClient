import QtQuick 2.0
import "smallComponents"


Item {
    id: recipe2

    property real detailsOpacity : 0

    width: parent.width
    height: 160

    Rectangle {
        id: background
        x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
        color: "#b7bfc4"
        border.color: "#0f0e0e"
        radius: 5



        // Эту область мыши охватывает целый делегат.
        // При щелчке он изменяет режим на 'Details'.  Если мы уже
        // в режиме Details, то изменений не будет.
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("ListView el#" + index +  "clicked!")
         //       idCollectionModel.getInstance(index);
                //        detailswiev.iWaitLoading = true;
                recipe2.state = 'Details';
                collection.positionViewAtIndex(index, ListView.Beginning)

            }
        }

        // Располагаем страницу: картинка, заголовок и ингредиенты - вверху, а способ приготовления -
        // внизу.  Обратите внимание на то, что элементам, которые не будут видны в режиме
        // списка, установлена собственная прозрачность в recipe.detailsOpacity.

        Row {
            id: topLayout
            x: 5; y: 5; height: recipeImage.height; width: parent.width
            spacing: 5

            Image {
                id: recipeImage
                width: 150; height: 150
                source: "image://MyImageProvider/" + Thumb

            }

            Column {
                width: background.width - recipeImage.width - 20; height: recipeImage.height
                spacing: 5

                Text {
                    text: ArtistName + " - " + Title
                    font.bold: true; font.pointSize: 16
                }

                Text {
                    text:  LabelShort + " " + Catno
                    font.pointSize: 12; font.bold: true

                }


                Text {
                    text: Year
                    font.pointSize: 12; font.bold: true

                }
                Text {
                    text: Folder
                    font.pointSize: 12; font.bold: true

                }


            }
        }

        Item {
            id: details
            visible: false

            x: 10; width: parent.width - 20
            anchors { top: topLayout.bottom; topMargin: 10; bottom: parent.bottom; bottomMargin: 10 }
            opacity: recipe2.detailsOpacity


            Rectangle {

                id: detailRelease

                Text {
                    id: format
                    text: FormatShort
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    font.pointSize: 12; font.bold: true
                    opacity: recipe2.detailsOpacity

                }
                Text {
                    id: catno
                    text: Catno
                    anchors.top: format.bottom
                    anchors.topMargin: 0
                    font.pointSize: 12; font.bold: true
                    opacity: recipe2.detailsOpacity
                }

                Text {
                    id: raiting
                    text: "Rating " + Rating
                    anchors.top: catno.bottom
                    anchors.topMargin: 0
                    font.pointSize: 12; font.bold: true
                    opacity: recipe2.detailsOpacity

                }
                /*
                Text {
                    id: condition
                    text: Field1 + "<br/>" + Field2
                    anchors.top: raiting.bottom
                    anchors.topMargin: 0
                    font.pointSize: 12; font.bold: true
                    opacity: recipe2.detailsOpacity


                }*/

            }

        }



        // Кнопка закрытия детализированного представления, т.е. устанавливает состояние обратно в состояние по умолчанию ('').
        TextButton {
            y: 10
            anchors { right: background.right; rightMargin: 10 }
            opacity: recipe2.detailsOpacity
            text: "Close"

            onClicked: {
                recipe2.state = '';
                console.log("Button el#" + index + " clicked!")
            }
        }

  }
        states: [
            State {
                name: "Details"

                PropertyChanges { target: background; color: "white" }
                PropertyChanges { target: recipeImage; width: 200; height: 200 } // Делает изображение больше
                PropertyChanges { target: recipe2; detailsOpacity: 1; x: 0 } // Делает видимыми детали
                PropertyChanges { target: recipe2; height: 500 } // Заполняет всю область списка подробным представлением listView.height

                // Смещает список таким образом, что этот элемент оказывается на вершине.
   //             PropertyChanges { target: recipe2.ListView.view; explicit: true; contentY: recipe2.y }

                PropertyChanges { target:  topLayout; visible: true}
                PropertyChanges { target:  details; visible: true}

                // Запрещает рывки в детализированном представлении
                PropertyChanges { target: recipe2.ListView.view; interactive: false }
                //Делает активным загрузчик
                //       PropertyChanges { target: detailswiev;  active: true}

            }
        ]


        transitions: Transition {
            // Делаем смену состояния плавной
            ParallelAnimation {
                ColorAnimation { property: "color"; duration: 500 }
                NumberAnimation { duration: 300; properties: "detailsOpacity,x,contentY,height,width" }
            }
        }

}

