import QtQuick 2.2
// import ProfileUserModel 1.0


Rectangle {
        id: profile


  //    anchors.fill: parent
       width:150; height: 200
       gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ffffff"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }

        Image {
            id: avatar

            width: 100
            height: 100
            anchors.left: parent.left
            anchors.leftMargin: 2
            source: avatar_url
        }

        Text {
            id: name_

            width: 150
            height: 28
            text: name
            anchors.horizontalCenterOffset: 0
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: avatar.bottom
            anchors.topMargin: 6
            font.pixelSize: 16
        }

        Text {
            id: usename_
            x: 13
            width: 150
            height: 23
            text: username
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: name_.bottom
            anchors.topMargin: 11
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 16
        }

    }





