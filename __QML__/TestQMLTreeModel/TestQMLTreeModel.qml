import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import extensions.mqmllibraries 1.0
import "TreeView"


ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480

    Item {
        id: i_Central
        anchors.fill: parent

        TreeView {
            id: treeView
            anchors.fill: parent
        }
    }

    Component.onCompleted: {
        obj_Information.treeItem = MQML.createTreeItem( "Some text" )
        var treeItemFont = obj_Information.treeItem.font
        treeItemFont.bold = true
        obj_Information.treeItem.font = treeItemFont
        obj_Information.treeItem.addChildItem( MQML.createTreeItem( "Some\ntext 1" ) );
        obj_Information.treeItem.addChildItem( MQML.createTreeItem( "Some text 2" ) );
        obj_Information.treeItem.addChildItem( MQML.createTreeItem( "Some text 3" ) );
        obj_Information.treeModel.addTopLevelItem( obj_Information.treeItem )

        obj_Information.treeItem = obj_Information.treeItem.childItems[1]
        treeItemFont = obj_Information.treeItem.font
        treeItemFont.italic = true
        obj_Information.treeItem.addChildItem( MQML.createTreeItem( "Sub text 1" ) );
        obj_Information.treeItem.addChildItem( MQML.createTreeItem( "Sub\ntext 2" ) );
        obj_Information.treeItem.addChildItem( MQML.createTreeItem( "Sub text 3" ) );

        obj_Information.treeItem = MQML.createTreeItem( "Another text" )
        treeItemFont = obj_Information.treeItem.font
        treeItemFont.bold = true
        obj_Information.treeItem.font = treeItemFont
        obj_Information.treeItem.addChildItem( MQML.createTreeItem() );
        obj_Information.treeItem.addChildItem( MQML.createTreeItem( "Another text 2" ) );
        obj_Information.treeModel.addTopLevelItem( obj_Information.treeItem )

        treeView.treeModel = obj_Information.treeModel
    }

    QtObject {
        id: obj_Information

        property TreeItem treeItem: null
        property TreeModel treeModel: TreeModel {
            columnCount: 1
        }
    }
}
