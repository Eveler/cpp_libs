import QtQuick 2.0
import extensions.mqmllibraries 1.0


ListView {
    id: main

    property TreeModel treeModel: null

    property bool singleSelection: false

    signal selected( TreeItem item )
    signal clicked( TreeItem item )
    signal doubleClicked( TreeItem item )

    onTreeModelChanged: {
        if ( treeModel !== null )
            model = treeModel.tree
        else model = null
    }

    onModelChanged: {
        model = treeModel.tree
    }

    delegate: TreeItemView {
        width: parent.width
    }

    Connections {
        target: main.treeModel
        onTreeChanged: model = treeModel.tree
        onSelectedChanged: {
            if ( main.singleSelection && main.treeModel.selected.length > 1 )
                for ( var iIdx = 0; iIdx < main.treeModel.selected.length; iIdx++ )
                    if ( main.treeModel.selected[iIdx] !== treeItem )
                        main.treeModel.selected[iIdx].selected = false
            main.selected( treeItem )
        }
        onTreeItemClicked: {
            if ( treeItem.selectable )
            {
                if ( main.singleSelection ) treeItem.selected = true
                else treeItem.selected = !treeItem.selected;
            }
            main.clicked( treeItem )
        }
        onTreeItemDoubleClicked: {
            if ( treeItem.expandable ) treeItem.expanded = !treeItem.expanded
            main.doubleClicked( treeItem )
        }
    }
}
