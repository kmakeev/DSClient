import QtQuick 2.0
import "smallComponents"



Rectangle {

    id: filterWindow

    signal close

    property bool isActive: false

    width: 300
    height: 900
    x: fieldOne.width/2-width/2
    y: fieldOne.height/2-height/2
    color: "gray"
    border.color: "#0f0e0e"
    radius: 5

    /*
    ModelFilter {
        id: idModelFilter
    }
*/


    Component {
        id: idSortBy

        Rectangle {
            id: text0
            width: parent.width
            height: 40
            color: ListView.isCurrentItem ? "#5d5959" : "gray"


            Text {
                width: parent.width
                text: itemText
                elide: Text.ElideRight
                font.pixelSize: 24; font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (idSortByList.currentIndex != index)
                    {
                        close ();
                        console.log("Sort " +itemText);
                        idCollectionModel.sortBy(itemText);
                        idSortByList.currentIndex = index

                    }
                }

            }
        }
    }

    ListModel {
        // Модель для фильтрации поиска по типу
        id: idModelSortBy
        ListElement {
            itemText: "Title"
        }
        ListElement {
            itemText: "Artist"
        }
        ListElement {
            itemText: "Rating"
        }
        ListElement {
            itemText: "Format"
        }
        ListElement {
            itemText: "Year"
        }
        ListElement {
            itemText: "Label"
        }
        ListElement {
            itemText: "Catalog"
        }
    }



    Component {
        id: idComponentFilter

        Rectangle {
            id: text
            width: parent.width
            height: 40
            color: ListView.isCurrentItem ? "#5d5959" : "gray"


            Text {
                width: parent.width
                text: itemText
                elide: Text.ElideRight
                font.pixelSize: 24; font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Clicked " +itemText);
                    close();
                    idModelReleases.setFilterToSearch(itemText);
                    idListFilter.currentIndex = index
                }

            }
        }

    }

    Component {
        id: idComponentFolder

        Rectangle {
            id: text2
            width: parent.width
            height: 40
            color: ListView.isCurrentItem ? "#5d5959" : "gray"


            Text {
                width: parent.width
                text: name
                elide: Text.ElideRight
                font.pixelSize: 24; font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Clicked " + name + " ID - " + FolderId);
                    if (idListFoldert.currentIndex != index)
                    {
                        close();
                        idListFoldert.currentIndex = index
                        idCollectionModel.setFolderFilter(FolderId);                   //Фильтруем и сортируем
                        console.log("Sort " +idModelSortBy.get(idSortByList.currentIndex).itemText);
                        idCollectionModel.sortBy(idModelSortBy.get(idSortByList.currentIndex).itemText);

                    }
                }

            }
        }

    }

    Item {
        id: filter
        width: parent.width
        height: parent.height/3
        anchors.top: parent.top
        anchors.topMargin: 0

        TextButton {

            id: close2
            text: " Close "
            anchors.top: parent.top
            anchors.right: parent.right

            onClicked: {
                console.log("Clicked close")
                close();
            }
        }


        ListView {
            id: idListFilter
            anchors.top: close2.bottom
            anchors.bottom: parent.bottom
            x:2
            width: parent.width-4
            delegate: idComponentFilter
            model: idModelFilter
            interactive: false

        }
    }


    Item {
        id: folder

        width: parent.width
        height: parent.height/3
        anchors.top: filter.bottom
        anchors.topMargin: 0

        ListView {
            id: idListFoldert
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            x:2
            width: parent.width-4
            delegate: idComponentFolder
            model: oneFolderModel
            interactive: false


        }

    }

    Item {
        id: sortBy

        width: parent.width
        height: parent.height/3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: folder.bottom
        anchors.topMargin: 0

        ListView {
            id: idSortByList
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            x:2
            width: parent.width-4
            delegate: idSortBy
            model: idModelSortBy
            interactive: false


        }

    }



}

