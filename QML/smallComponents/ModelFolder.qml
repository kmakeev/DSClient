import QtQuick 2.0


ListModel {
//Заполнение данный модели названием папок из профиля пользователя

    Component.onCompleted: {
    console.log("Model folder create started");
     append ({name: "Uncategorized", FolderId: 1});

       console.log("Add to model folder name  Uncategorized 1");
        var  j=idCollectionModel.folderCount();
        var i;
        for (i=0; i<j;i++)
        {
            if (idCollectionModel.folderId(i)>1) // Не включаем ALL (id=0) и Uncategorized (id=1)
            {
            console.log("Add to model folder name " + idCollectionModel.folderName(i)+ " " + idCollectionModel.folderId(i));
            append ({"name": idCollectionModel.folderName(i), "FolderId": idCollectionModel.folderId(i)});
            }
        }

    }


}


