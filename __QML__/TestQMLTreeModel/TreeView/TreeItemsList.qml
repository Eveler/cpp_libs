import QtQuick 2.0
import extensions.mqmllibraries 1.0


Column{
    id: treeItemList

    height: childrenRect.height
    Repeater{
        model: modelData.childItems
        delegate: TreeItemView {
            width: treeItemList.width
        }
    }
}

