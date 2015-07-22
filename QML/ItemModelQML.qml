//import QtQuick 2.2
import QtQuick 2.0
import "smallComponents"

Item {
    id: recipe


    width: parent.width
    height: 160



    // Простой прямоугольник со скругленными углами в качестве фона
    Rectangle {
        id: background
        x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
        color: "#b7bfc4"
        border.color: "#0f0e0e"
        radius: 5
        clip: true

        Loading {  // Тупилка для последнего айтема
            id: dummy
            visible: false
            widthI: 60; heightI: 60
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -heightI/2
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }


    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("ListView el#" + index +  "clicked NEW!")
            idModelReleases.readReleases(index);                   //читаем все информацию
            releases.currentIndex = index;
           //переходим к просмотрю в виде отдельной вью
            releases.positionViewAtIndex(index,ListView.Visible);
            var xy = form.mapFromItem(releases, releases.currentItem.x-releases.contentX, releases.currentItem.y-releases.contentY);
            form.clicked(xy.x, xy.y, releases.currentItem.width, releases.currentItem.height, model);  //передаем на основную форму x,y итема, его высоты, ширину и модель данных

        }
    }


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
                text: Title  //"Artist - Album"
                font.bold: true; font.pointSize: 16
                width: parent.width
                elide: Text.ElideRight
                clip: true
            }

            Text {
                text: Type
                font.pointSize: 12; font.bold: true
                width: parent.width
                elide: Text.ElideRight
                clip: true

            }

            Text {
                text:  LabelShort
                font.pointSize: 12; font.bold: true
                width: parent.width
                elide: Text.ElideRight
                clip: true

            }


            Text {
                text: Year
                font.pointSize: 12; font.bold: true
                width: parent.width
                elide: Text.ElideRight
                clip: true

            }


        }
    }




}



