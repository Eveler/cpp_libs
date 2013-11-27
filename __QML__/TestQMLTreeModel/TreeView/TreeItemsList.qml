import QtQuick 2.0
import extensions.mqmllibraries 1.0


Column{
    id: treeItemList

    Repeater{
        model: modelData.childItems
        delegate: TreeItemView {
            width: treeItemList.width
        }

        onItemAdded: {
            treeItemList.height+=item.height
        }
        onItemRemoved: treeItemList.height-=item.height
    }
}

