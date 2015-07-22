import QtQuick 2.0
import "smallComponents"

Rectangle {

    signal close

 //   property string avatarUrl: avatarUrl

    id: profileUser
    x: 50; y: 50;

    width: fieldOne.width - x*2;
    height: fieldOne.height - y*2;

    color: "gray"
    border.color: "#0f0e0e"
    radius: 5


    Row {
        id: topRow
        x: 5; y: 5; height: profileUser.height; width: profileUser.width
        spacing: 5

        Column {
            id: column1

            width: profileUser.width; height: profileUser.height
            spacing: 5

            Image {
                id: urlImage
                width: 150; height: 150
                source:"/pics/green-login-th.png"

            }
/*
            Text {
                id: iName
                width: parent.width
                text: "Name: "
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: 24; font.bold: true
            }
*/
            Text {
                id: iUserName
                width: parent.width
                text: "User name: "
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: 24; font.bold: true
            }
            Text {
                id:iCollection
                width: parent.width
                text: "In Collection - "
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: 24; font.bold: true
            }
            Text {
                id: iWantlist
                width: parent.width
                text: "In WantList - "
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: 24; font.bold: true
            }
            Text {
                id: iRegistered
                width: parent.width
                text: "Registered "
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: 24; font.bold: true
            }

            TextInputMain {
                id: iName
                width: parent.width-10
                height: 40
                fontsize: 30
                color : "white"
                password: false
                label : qsTr ("Name -")
                labelDefault : qsTr ("Name -")

                onTextInputEnter:  {
                        console.log (" Enter" + label);
                }
            }

            TextInputMain {
                id: iProfile
                width: parent.width-10
                height: 120
                fontsize: 30
                color : "white"
                password: false
                label : qsTr ("Profile -")
                labelDefault : qsTr ("Profile -")

                onTextInputEnter:  {
                          console.log ("Profile -" + label);
                }
            }



            TextInputMain {
                id: iGLocation
                width: parent.width-10
                height: 40
                fontsize: 24
                color : "white"
                password: false
                label : qsTr ("Location -")
                labelDefault : qsTr ("Location -")

                onTextInputEnter:  {

                    console.log ("Locate -" + label);
                }
            }

            TextInputMain {
                id: iHomePage
                width: parent.width-10
                height: 40
                fontsize: 30
                color : "white"
                password: false
                label : qsTr ("HomePage:")
                labelDefault : qsTr ("HomePage:")

                onTextInputEnter:  {
                    console.log ("HomePage:" + label);
                }
            }

            TextButton {
                id: logoutButton

                text: " Log out "
                onClicked: {
                    console.log("Clicked logout");

                    idCollectionModel.clear();              //очистка данных в модели
                    idFieldsModel.clear();
                    idWantlistModel.clear();
                    idProfileUser.logout();
                    close();
                }
            }
            TextButton {
                id: closeButton

                text: " Close "
                onClicked: {
                    close();
                }
            }
            TextButton {
                id: saveButton

                text: " Save "
                onClicked: {
                    console.log ("Save " + iUserName.text + " " + iName.label + " " + iHomePage.text + " " + iGLocation.label + " " + iProfile.label);
                    idProfileUser.saveUserProfile(iUserName.text, iName.label, iHomePage.label, iGLocation.label, iProfile.label);
                    close();
                }
            }




        }
    }

    states:[
        State{
            name: "isLoggin"
            when: idProfileUser.isLoggin
            PropertyChanges { target: urlImage; source: idProfileUser.avatarUrl}
            PropertyChanges { target: iName; label: idProfileUser.name; labelDefault : idProfileUser.name }
            PropertyChanges { target: iUserName; text: idProfileUser.userName}
            PropertyChanges { target: iProfile; label: idProfileUser.profile; labelDefault: idProfileUser.profile}
            //      PropertyChanges { target: iLocation; label: idProfileUser.location}
            PropertyChanges { target: iHomePage; label: idProfileUser.homePage; labelDefault: idProfileUser.homePage}
            PropertyChanges { target: iWantlist; text: "In WantList - " + idProfileUser.numWantList}
            PropertyChanges { target: iCollection; text: "In Vollection - " + idProfileUser.numCollection}
            PropertyChanges { target: iRegistered; text: "Registered " + idProfileUser.registered}

            PropertyChanges { target: iGLocation; label: idProfileUser.glocation; labelDefault : idProfileUser.glocation }




        },
        State{
            name: "isNotLoggin"
            when: !idProfileUser.isLoggin
        //    PropertyChanges { target: urlImage; source: "/pics/green-login-th.png"}
        }]


}


