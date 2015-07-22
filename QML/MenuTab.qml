import QtQuick 2.0
import "smallComponents"



Rectangle{


    width: parent.width
    height: 100

    Rectangle {
        id: iconFilter
        width: 80
        height: parent.height
        color: "#d2d1d3"
        anchors.left: parent.left
        anchors.rightMargin: 0
        Item {
            id: item0
            width: 80
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0
            Image {
                id: settings
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                width : parent.width - 10
                height: parent.height - 10
                source: "/pics/Settings.png";


                MouseArea {
                    anchors.fill:parent
                    onClicked: {
                      console.log ("Clicked Settings");
                      clickedFilter();
                    }

                }
            }
        }
    }


    TextInputMain {
        id: menu
        width: parent.width - icon.width-iconFilter.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: iconFilter.right
        password: false
        label : qsTr ("Search artist, album and more ...")
        labelDefault : qsTr ("Search artist, album and more ...")

        onTextInputEnter:  {
            clickedFind(menu.label,menu.labelDefault, idProfileUser.isLoggin); // Аналогично нажатию иконки
 //           console.log (" Enter" + menu.label);
 //           Qt.inputMethod.hide();
 //           if (!(label == labelDefault))
 //           {
 //           idModelReleases.search(label);
 //           }


        }
    }

    Rectangle {
        id: icon
        width: 160
        height: parent.height
        color: "#d2d1d3"
        anchors.right: parent.right
        anchors.rightMargin: 0

        Item {
            id: item1
            width: 80
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0
            Image {
                id: profile
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                width : parent.width - 10
                height: parent.height - 10
                source: "/pics/green-login-th.png";   //Аватар отображать, если пользователь авторизован. Необходимо два состояния.


                MouseArea {
                    anchors.fill:parent
                    onClicked: {
                        clickedProfile(idProfileUser.isLoggin);
                    }

                    Image {
                        id: offline
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        width: 50
                        height: 50
                        source: "/pics/network-offline.png"
                        visible: idProfileUser.isOffline&&idCollectionModel&&idWantlistModel
                    }
                }

            }
            states:[
                State{
                    name: "isLoggin"
                    when: idProfileUser.isLoggin
                    PropertyChanges { target: profile; source: idProfileUser.avatarUrl}

                },
                State{
                    name: "isNotLoggin"
                    when: !idProfileUser.isLoggin
                    PropertyChanges { target: profile; source: "/pics/green-login-th.png"}
                } /*,
                State{
                    name: "isOffline"
                    when: !idProfileUser.isLoggin&&idProfileUser.isOffline
                    PropertyChanges { target: profile; source: "/pics/network-offline.png"}
                }*/
            ]


        }

        Item {
            id: item2
            width: 80
            height: parent.height
            anchors.right: item1.left
            anchors.rightMargin: 0
            Image {
                id: search
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                width : parent.width - 30
                height: parent.height - 30
                source: "/pics/loupe.png"

                MouseArea {
                    id: ifind
                    visible: true
                    anchors.fill: parent
                    onClicked: clickedFind(menu.label,menu.labelDefault,idProfileUser.isLoggin); //Для того что бы определить что введено в поле, в сигнеле передаем два значения, признак того что залогинен
                   }
            }

        }

    }

}


