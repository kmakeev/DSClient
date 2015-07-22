import QtQuick 2.0


Rectangle {
    id: textInputMain

    property string label: ""
    property string labelDefault : "Search artist, album and more..."
    property bool password: false
    property int fontsize: 80
    property string colorbgr: "#00000000"
 //   property bool cursor: true

    color: colorbgr
    visible: true
    border.color: "black"
    border.width: 1
    opacity: 1

    signal textInputClick()
    signal textInputEnter()
    clip: true

    onTextInputClick:
    {

          if (password){
 //           console.log(input.text + " onPassword" )
            textInput.echoMode = TextInput.PasswordEchoOnEdit }

        if (input.text == labelDefault){
            input.text=  ""
            input.color = "black"
            input.focus = true
            //    textInputpassword.echoMode = 0
            //     echoMode: TextInput.passwordCharacter
        }
        else { input.focus = true }

        console.log(input.text + " clicked, focus " + input.focus )
        input.forceActiveFocus();
    }

    onVisibleChanged: {
       input.text = textInputMain.labelDefault;
       input.color = "#b3b3b3"


    }


/*
    onTextInputEnter:
    {
        console.log(textInput.text + " Enter" )
        textInput.focus = false
        Qt.inputMethod.hide();

    }
*/
    TextInput {
        id: input
        width: parent.width
        height: parent.height
        color: "#b3b3b3"
        font.pixelSize: fontsize
        text: label
        selectionColor: "#040417"
   //     cursorVisible: cursor

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1
        wrapMode: TextInput.WrapAnywhere

        onAccepted: {
            input.focus = false
 //           console.log(input.text + " Enter" )
            label = input.text
            textInputEnter()
        }
        onTextChanged: {
  //          console.log("Text changed "+ input.text);
            label = input.text   //фиксируем введенный текст не дожидаясь нажатия Enter
        }


        MouseArea{
            id: textInputpasswordMouseArea

            anchors.fill: parent
            onClicked: textInputClick()

         }


    }
}
