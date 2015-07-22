import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item
{
    id: idFieldsDelegate

    width: parent.width
    height: 100

    Text {
        id: idText
        text: Name
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 18; font.bold: true
    }
/*
    ListModel {
        id: idModelFiels
        Component.onCompleted: {
            var list = Options;
      //      append ({name: "edit"});
            for (var i=0; i<CountOptions;i++)
            {
               console.log("Add to model " + Name + " "+ list[i]);
               append ({name: list[i]});

            }
             console.log("Model field created");
        }
}
*/

    ComboBox {

        visible: isDropdown ? true : false
        id: combo
        model: Model
        width: parent.width
        height: parent.height-idText.height
        anchors.top: idText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        textRole: "display"
        editable: false


        onCurrentIndexChanged: {
         if (addToCollectionPopup.currentIndex>=0 && currentIndex>=0)
         {

        // проверка индекса при вызове редактирования, передаем id сразу, хранится в модели, можно сохранять и другое
                console.log ("Index - " +addToCollectionPopup.currentIndex + " ID Field - " + id + " Text - " + combo.currentText);
                idModelReleases.editFieldsInCollection(addToCollectionPopup.currentIndex, id, combo.currentText);
         }
        }

  //      style: ComboBoxStyle                // по большому счету можно самому попытаться описать вид ComboBox, пока оставляю по умолчанию


        onVisibleChanged: {

          console.log ("ComboBox changed " + currentIndex);
          currentIndex = -1;

        }

    }

    TextInputMain {

         visible: isDropdown ? false : true
         id: iProfile
         width: parent.width
         height: 100
         anchors.top: idText.bottom
         anchors.horizontalCenter: parent.horizontalCenter

         fontsize: 24
         color : "white"
         password: false
         label : qsTr ("edit")
         labelDefault : qsTr ("edit")


         onTextInputEnter:  {
             console.log ("Index - " +addToCollectionPopup.currentIndex + " ID Field - " + id + " Text - " + label);
             idModelReleases.editFieldsInCollection(addToCollectionPopup.currentIndex, id, label);


         }
     }


}

