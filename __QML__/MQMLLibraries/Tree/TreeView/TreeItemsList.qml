import QtQuick 2.0
import extensions.mqmllibraries 1.0


Item{
    id: treeItemList
    height: childrenRect.height

    property TreeModel treeModel: null
    onTreeModelChanged: {
        var index = children.length-1
        while ( index > -1 )
        {
            var curView = treeItemList.children[index];
            curView.destroy()
            index--
        }
        if ( !treeModel ) return;
        for ( index = 0; index < treeItemList.treeModel.tree.length; index++ )
            obj_Information.addView( index, treeItemList.treeModel.tree )
    }

    property TreeItem treeItem: null
    onTreeItemChanged: {
        var index = children.length-1
        while ( index > -1 )
        {
            var curView = treeItemList.children[index];
            curView.destroy()
            index--
        }
        height = 0
        if ( !treeItem ) return;
        for ( index = 0; index < treeItemList.treeItem.childItems.length; index++ )
            obj_Information.addView( index, treeItemList.treeItem.childItems )
    }

    Connections {
        target: treeItemList.treeModel

        onTopLevelItemAdded: obj_Information.addView( index, treeItemList.treeModel.tree )

        onTopLevelItemRemoved: obj_Information.removeView( index )
    }

    Connections {
        target: treeItemList.treeItem

        onChildItemAdded: obj_Information.addView( index, treeItemList.treeItem.childItems )

        onChildItemRemoved: obj_Information.removeView( index )
    }

    QtObject {
        id: obj_Information

        function addView( index, source )
        {
            var prevView = null;
            if ( index > 0 )
                prevView = treeItemList.children[index-1]
            var component = Qt.createComponent("TreeItemView.qml");
            if ( component.status === Component.Ready )
            {
                var curItem = component.createObject(
                            treeItemList, {"prevView": prevView,
                                "treeItem": source[index]} )
            }
        }

        function removeView( index )
        {
            var prevView = null;
            var curView = treeItemList.children[index];
            var nextView = null;

            if ( index > 0  )
                prevView = treeItemList.children[index-1]
            if ( index+1 < children.length )
                nextView = treeItemList.children[index+1]

            if ( prevView && nextView )
                nextView.prevView = prevView
            else if ( !prevView && !nextView )
                treeItemList.height = 0
            else if ( !nextView )
                treeItemList.height = prevView.y+prevView.height
            curView.destroy()
        }
    }
}

