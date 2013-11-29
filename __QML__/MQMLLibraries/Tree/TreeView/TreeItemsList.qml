import QtQuick 2.0
import extensions.mqmllibraries 1.0


Column{
    id: treeItemList
    height: childrenRect.height

    property TreeItem treeItem: null

    Repeater{
        model: ( treeItemList.treeItem ? treeItemList.treeItem.childItems : 0 )
        delegate: TreeItemView {
            width: treeItemList.width
        }
    }

    Component.onCompleted: {
        if ( modelData !== undefined ) treeItem = modelData
    }
    Component.onDestruction: {
        treeItem = null
    }
}

