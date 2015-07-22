import QtQuick 2.0


import "smallComponents"

import SearchModel 1.0
import ProfileUserModel 1.0
import CollectionModel 1.0
import WantlistModel 1.0
import FieldsModel 1.0

Rectangle {

    id: mainWindow
    color: "#F0F0FF"
    signal clickedFind(var label, var labelDefault, var isLoggin);
    signal clickedProfile(var isLoggin);
    signal clickedFilter ();
 //   signal progressChanged ();

    ProfileUserModel {id: idProfileUser}

    CollectionModel {id: idCollectionModel
        onFolderRead: {                     //Чтение данных в модель если пользователь залогинился в ходе работы программы
            console.log("Folder Changed ");
            console.log("Model folder on filter create started");
            oneFolderModel.clear();
            var  j=idCollectionModel.folderCount();
            var i;
            for (i=0; i<j;i++)
            {
                console.log("Add to model folder name " + idCollectionModel.folderName(i)+ " " + idCollectionModel.folderId(i));
                oneFolderModel.append ({"name": idCollectionModel.folderName(i), "FolderId": idCollectionModel.folderId(i)});
            }

            console.log("Model folder on edit collection create started");
            idModelFolder.clear();
            idModelFolder.append ({name: "Uncategorized", FolderId: 1});

            console.log("Add to model folder name  Uncategorized 1");
            for (i=0; i<j;i++)
            {
                if (idCollectionModel.folderId(i)>1) // Не включаем ALL (id=0) и Uncategorized (id=1)
                {
                    console.log("Add to model folder name " + idCollectionModel.folderName(i)+ " " + idCollectionModel.folderId(i));
                    idModelFolder.append ({"name": idCollectionModel.folderName(i), "FolderId": idCollectionModel.folderId(i)});
                }
            }
        }
/*
        onProgress: {
            console.log("Progress Changed " + idCollectionModel.progressValue());
            progressChanged();
        }

  */
    }
    WantlistModel {id: idWantlistModel}
    FieldsModel {id: idFieldsModel }   // Нужно научиться обновлять по событию из модели
    SearchModel{ id: idModelReleases
        onAddReleasesToWantlist: {                              //Если из Модели WantList пришел сигнал о дабавлении новой записи, читаем wantlist заново
            console.log("Refresh WANTLIST ");
            idWantlistModel.refresh();                        // вместо getReleasesInWantList();
        }
    }

    ModelFolder {
        id: idModelFolder
    }

    ListModel {
        //Заполнение данный модели названием папок из профиля пользователя
        // Модель используется только для фильтрации

        id: oneFolderModel
        Component.onCompleted: {
            console.log("Model folder create started");
            //       append ({name: "edit"});
            //     oneFolderModel.clear();
            var  j=idCollectionModel.folderCount();
            var i;
            for (i=0; i<j;i++)
            {
                console.log("Add to model folder name " + idCollectionModel.folderName(i)+ " " + idCollectionModel.folderId(i));
                append ({"name": idCollectionModel.folderName(i), "FolderId": idCollectionModel.folderId(i)});
                /*      if (idCollectionModel.folderId(i)===0)
           {
            idCollectionModel.setIndexActiveFolderName(i); //Сообщаем в модель индекс записи для фильрации по умолчанию (id - 0 = all)
           }*/ // Делаем это в модели

            }

        }

    }
    ListModel {
        // Модель для фильтрации поиска по типу
        id: idModelFilter
        ListElement {
            itemText: "all"
        }
        ListElement {
            itemText: "releases"
        }
        ListElement {
            itemText: "master"
        }
        ListElement {
            itemText: "artist"
        }
        ListElement {
            itemText: "labels"
        }

    }

    //верхнее меню
    MenuTab {
        id: menuTab
        width: parent.width
        height: 90

    }

    onClickedFind: { //Тут будем отслеживать нажатия иконкb на менюТаб и то на какой странице и при каких условиях это происходит
        console.log("Clicked " + lvList.currentIndex);
     //   console.log("Label " + label + "LabelDefault " + labelDefault);
        if (lvList.currentIndex==0) // Если на первой
        {
            if (!(label === labelDefault)) //были введены параметры то производим поиск
            {
                idModelReleases.search(label);
            }

        } else if (lvList.currentIndex==1 && isLoggin)        //Если на второй и пользователь залогинен
        {

           console.log("Search in collection");
           idCollectionModel.search(label);
        //   idFieldsModel.refresh();

        } else if(lvList.currentIndex==2 && isLoggin)
        {
            console.log("Refresh wantlist");
            idWantlistModel.refresh();
            idFieldsModel.refresh();
        }
    }

    onClickedProfile: {
        if(isLoggin){            //Если пользователь залогинен

        idProfileUserWindow.x = fieldOne.height

        mainWindow.state = "profile";
        console.log("Enter Profile " + idProfileUserWindow.x + " " + idProfileUserWindow.y);

        idAnimation2.start();

        } else {
             console.log("Required login " + isLoggin);
             mainWindow.state = "login"

        }
    }

    onClickedFilter: {
        mainWindow.state = "filter"
        console.log("Window filter");

    }


    ListView {
        id: lvList
        objectName: "lvList"
        width: parent.width
        height: parent.height - menuTab.height
        anchors.top: menuTab.bottom
        clip: true
        spacing: 1
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem
        cacheBuffer: 4000
        highlightRangeMode: ListView.StrictlyEnforceRange

        model: ListModel {
            ListElement { name: "Dashboard " }
            ListElement { name: "Collection" }
            ListElement { name: "Wantlist" }
            ListElement { name: "Marketplace" }
        }
        delegate: AllForm {}
        focus: true
        //Для отладки, смотрим активный итем листвью, В целом можно по данным событиям анимировать смену итемов у листвью, например сменой оконок на табе
        onFlickEnded: {console.log("Changed to " + currentIndex);}

    }

    //Прослойка между литвью и возможными всплываюшими итемами
    Rectangle {
        id: fieldOne
        color: "gray"
        opacity: 0
        anchors.fill: parent
        z: -1
        MouseArea {
            anchors.fill: parent
            onClicked: {}
        }

    }

    ProfileUserWindow{
        id: idProfileUserWindow
        visible:false
        z:10
        /*
           onSave: {
           form.state = "list"

         }*/
        onClose: {
            console.log("Close Profile Windows ");
            mainWindow.state = "default"
        }
    }

    LoginWindow{
        id: idLoginWindow
        visible: false
        z: 11
        onEnter: {
            console.log ("Loginning ...");
   /*         idCollectionModel.clear();              //очистка данных в модели
            idFieldsModel.clear();
            idWantlistModel.clear();
*/
       //     idModelReleases.clear();
            idProfileUser.login();                  //Логинимся через модель профиль
            /*
            console.log ("Refresh ...");
            idCollectionModel.refresh();
            idWantlistModel.refresh();
            */
            mainWindow.state = "default";
        }
        onClose: {
            console.log ("Close ...");
            mainWindow.state = "default";
        }


    }

    FilterWindow{
        id: idFilterWindow
        z: 12
        visible: false
        onClose: {
            console.log ("Close ...");
            mainWindow.state = "default";
        }
    }



    SequentialAnimation {
        id: idAnimation2
        ParallelAnimation {
        //    NumberAnimation {  target: idProfileUserWindow; property: "y"; to: 50; duration: 600}
            NumberAnimation {  target: idProfileUserWindow; property: "x"; to: 50; duration: 600}
            NumberAnimation {  target: fieldOne; property: "opacity"; to: 0.8; duration: 600}
           }
    }

    state: "default"

    states: [
        State {
            name: "profile"
             PropertyChanges {target: idProfileUserWindow; visible: true;}
             PropertyChanges {target: fieldOne; z: 2; opacity: 0;}
             },
        State {
            name: "login"
             PropertyChanges {target: idLoginWindow; visible: true;}
             PropertyChanges {target: fieldOne; z: 2; opacity: 0;}

             },

        State {
            name: "default"
                 PropertyChanges {target: idProfileUserWindow; visible: false;}
                 PropertyChanges {target: idLoginWindow; visible: false;}
                 PropertyChanges {target: idFilterWindow; visible: false;}
                 PropertyChanges {target:fieldOne; z: -1}


        },
        State {
            name: "filter"
            PropertyChanges {target: idFilterWindow; visible: true;}
            PropertyChanges {target: fieldOne; z: 2; opacity: 0.8;}
        }

    ]



}

