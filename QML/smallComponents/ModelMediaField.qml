import QtQuick 2.0

/*
ListModel {
//Заполнение данный модели названием  из fieldов профиля пользователя

    id: dataModel

    Component.onCompleted: {
  //    console.log("Model field create started");
        append ({text: qsTr ("edit")});                   //Первое поле как бы не заполнено
        var  j=idCollectionModel.fieldCount();        //берем количество списков
        var i;
        for (i=0; i<j;i++)
        {
     //       console.log("Field name - " + idCollectionModel.fieldName(i));
            if (idCollectionModel.fieldsId(i)=== 1)
            {
                idCollectionModel.setNumMediaField(i);
                var k = idCollectionModel.getCountOptionsOfField(i);
     //           console.log("Options count in " + idCollectionModel.fieldName(i) + " - " +k);
                var n;
                for (n=0; n<k;n++)
                {
      //             console.log("Options Media Conditions: " + idCollectionModel.getOptionsInField(i,n));
                   append ({text: idCollectionModel.getOptionsInField(i,n)});
                }

            }
        }

       // idCollectionModel.setIndexActiveFolderName(0);          //Сообщаем в модель индекс записи для фильрации по умолчанию
    }


}
*/
