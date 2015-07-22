import QtQuick 2.0
import "smallComponents"

Rectangle {

    signal enter
    signal close

    id: loginWindow
    x: 100; y: 100;

    width: fieldOne.width - x*2;
    height: fieldOne.height - y*2;

    color: "gray"
    border.color: "#0f0e0e"
    radius: 5

    TextButton {                                                  //Эти кнопки будут работать только для заголиненного пользователя

        id: loginButton
        text: " Log In "
        anchors.horizontalCenter: loginWindow.horizontalCenter
        anchors.verticalCenter:  loginWindow.verticalCenter

        onClicked: {
            console.log("Clicked login")
            enter();
        }
     }
    TextButton {                                                  //Эти кнопки будут работать только для заголиненного пользователя

        id: closeButton
        text: " Close "
        anchors.horizontalCenter: loginWindow.horizontalCenter
        anchors.top: loginButton.bottom
        anchors.topMargin: 5

        onClicked: {
            console.log("Clicked close");
            close();
        }
     }


}

