import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import extensions.mqmllibraries 1.0
import "TreeView" as TV


ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480

    Item {
        id: i_Central
        anchors.fill: parent

        TV.TreeView {
            id: treeView
            anchors.fill: parent
            anchors.bottomMargin: row_Buttons.height+5

            clip: true
            singleSelection: true

//            treeModel: obj_Information.treeModel
        }

        Row {
            id: row_Buttons
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            height: childrenRect.height
            Button {
                text: "Добавить"

                onClicked: {
                    if ( obj_Information.treeModel.selected.length > 0 )
                    {
                        obj_Information.treeItem = obj_Information.treeModel.selected[0];
                        obj_Information.treeItem.addChildItem(
                                    MQML.createTreeItem(
                                        "Some text "+obj_Information.treeItem.childItems.length ) )
                        if( obj_Information.treeItem.childItems.length = 1 )
                            obj_Information.treeItem.expanded = true
                        obj_Information.treeItem = null
                    }
                    else
                    {
                        obj_Information.treeItem = MQML.createTreeItem(
                                    "Some text "+obj_Information.treeModel.tree.length )
                        obj_Information.treeModel.addTopLevelItem( obj_Information.treeItem )
                        obj_Information.treeItem = null
                    }
                }
            }
            Button {
                text: "Удалить"

                onClicked: {
                    if ( obj_Information.treeModel.selected.length > 0 )
                    {
                        obj_Information.treeItem = obj_Information.treeModel.selected[0];

                        var parentItem = obj_Information.treeItem.parentItem()
                        var index

                        if ( parentItem )
                        {
                            index = parentItem.childItems.indexOf( obj_Information.treeItem )
                            obj_Information.treeItem.destroy()
                            if ( parentItem.childItems.length === 1 )
                                obj_Information.treeItem = parentItem
                            else if ( index > 0 )
                                obj_Information.treeItem = parentItem.childItems[index-1]
                            else
                                obj_Information.treeItem = parentItem.childItems[index+1]
                        }
                        else
                        {
                            index = obj_Information.treeModel.tree.indexOf(
                                        obj_Information.treeItem )
                            obj_Information.treeItem.destroy()
                            if ( obj_Information.treeModel.tree.length === 1 )
                                obj_Information.treeItem = null
                            else if ( index > 0 )
                                obj_Information.treeItem = obj_Information.treeModel.tree[index-1]
                            else obj_Information.treeItem = obj_Information.treeModel.tree[index+1]
                        }

                        if ( obj_Information.treeItem )
                        {
                            obj_Information.treeItem.selected = true
                            obj_Information.treeItem = null
                        }
                    }
                }
            }
            Button {
                text: "Снять выделение"

                onClicked: {
                    if ( obj_Information.treeModel.selected.length > 0 )
                    {
                        obj_Information.treeItem = obj_Information.treeModel.selected[0];
                        obj_Information.treeItem.selected = false
                        obj_Information.treeItem = null
                    }
                }
            }
            Button {
                text: "Заблокировать/Разблокировать"

                onClicked: {
                    if ( obj_Information.treeModel.selected.length > 0 )
                    {
                        obj_Information.treeItem = obj_Information.treeModel.selected[0];
                        obj_Information.treeItem.itemEnabled = !obj_Information.treeItem.itemEnabled
                        obj_Information.treeItem = null
                    }
                }
            }
        }
    }

    QtObject {
        id: obj_Information

        property TreeItem treeItem: null
        property TreeModel treeModel: TreeModel {}
    }

    Component.onCompleted: {
        console.debug( Date() )
        for ( var idx = 0; idx < 250; idx++ )
            obj_Information.treeModel.addTopLevelItem( MQML.createTreeItem( "Item "+(idx+1)+" lksd;gksd;gons sdlknasdo;gnsd sdopnsdsdophnfiopashab kabsfabsfabf oasbfaiosbfpoasgbfa asfasfaosifha o;ashfoiabhso  poasf[ioasfo;aisf ;pasfpaoihfo[a o;lopdfgbiasfopan p'asoaig]]" ) )
        console.debug( Date() )

        treeView.treeModel = obj_Information.treeModel
        console.debug( Date() )
    }
}
