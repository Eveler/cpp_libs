import QtQuick 2.0
import extensions.mqmllibraries 1.0


Flickable {
    id: treeView

    property TreeModel treeModel: null
    onTreeModelChanged: {
        treeItemList.treeModel = treeModel
    }

    property bool singleSelection: false

    signal selected( TreeItem item )
    signal clicked( TreeItem item )
    signal doubleClicked( TreeItem item )

    contentHeight: treeItemList.height

    TreeItemsList {
        id: treeItemList
        width: parent.width
    }

    Connections {
        target: treeView.treeModel
        onSelectedChanged: {
            if ( treeView.singleSelection && treeView.treeModel.selected.length > 1 )
                for ( var iIdx = 0; iIdx < treeView.treeModel.selected.length; iIdx++ )
                    if ( treeView.treeModel.selected[iIdx] !== treeItem )
                        treeView.treeModel.selected[iIdx].selected = false
            treeView.selected( treeItem )
        }
        onTreeItemClicked: {
            if ( treeItem.selectable )
            {
                if ( treeView.singleSelection ) treeItem.selected = true
                else treeItem.selected = !treeItem.selected;
            }
            treeView.clicked( treeItem )
        }
        onTreeItemDoubleClicked: {
            if ( treeItem.expandable ) treeItem.expanded = !treeItem.expanded
            treeView.doubleClicked( treeItem )
        }
    }
}
