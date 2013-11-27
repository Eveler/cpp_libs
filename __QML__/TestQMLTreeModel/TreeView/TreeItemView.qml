import QtQuick 2.0
import extensions.mqmllibraries 1.0


Item {
    id: treeItemView
    height: i_Content.height+loader_ChildItems.height

    Rectangle {
        id: i_Content
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: modelData.nestingLevel*20
        width: parent.width
        height: text_ItemText.contentHeight+(text_ItemText.anchors.topMargin*2)

        color: modelData.selected ? "gray" : "transparent"

        Text {
            id: text_ItemText
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 4
            width: parent.width
            height: contentHeight

            text: i_Content.itemData1()

            font: modelData.font
        }

        MouseArea {
            anchors.fill: parent

            onClicked: modelData.selected = true
        }

        function itemData1()
        {
            var result = modelData.data
            if ( result === undefined ) result = ""

            return result
        }
        function itemData2( columnIndex )
        {
            var result = modelData.columnData( columnIndex )
            if ( result === undefined ) result = ""

            return result
        }
    }

    Loader {
        id: loader_ChildItems
        anchors.top: i_Content.bottom
        anchors.left: parent.left

        width: treeItemView.width
        height: ( item ? item.height : 0 )

        source: modelData.hasChild ? "TreeItemsList.qml" : ""

        onStatusChanged: {
            if ( status === Loader.Ready && item )
                item.width = treeItemView.width
        }
    }
}
