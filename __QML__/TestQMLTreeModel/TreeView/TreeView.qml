import QtQuick 2.0
import extensions.mqmllibraries 1.0


ListView {
    id: main

    property TreeModel treeModel: null
    onTreeModelChanged: {
        if ( treeModel !== null )
            model = treeModel.tree
    }

    onModelChanged: {
        model = treeModel.tree
    }

    delegate: TreeItemView {
        width: parent.width
    }

    Connections {
        target: treeModel
        onTreeChanged: model = treeModel.tree
    }
}
