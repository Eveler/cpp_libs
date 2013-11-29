import QtQuick 2.0
import QtGraphicalEffects 1.0
import extensions.mqmllibraries 1.0


Item {
    id: treeItemView
    height: i_Content.height+loader_ChildItems.height

    clip: true

    property TreeItem treeItem: null

    Rectangle {
        id: rect_Expander
        anchors.verticalCenter: i_Content.verticalCenter
        anchors.left: parent.left

        width: 20
        height: width

        color: ( treeItemView.treeItem && treeItemView.treeItem.childSelected ? "#55ff8833" : "#88555555" )
        Behavior on color {
            ColorAnimation { duration: 200 }
        }
        border.color: ( treeItemView.treeItem && treeItemView.treeItem.childSelected ? "#ffff8833" : "#88000000" )
        Behavior on border.color {
            ColorAnimation { duration: 200 }
        }
        radius: width/2
        visible: treeItemView.treeItem && treeItemView.treeItem.hasChild
        enabled: treeItemView.treeItem && treeItemView.treeItem.itemEnabled && treeItemView.treeItem.expandable

        Image {
            id: image_Arrow
            anchors.fill: parent
            anchors.margins: 2

            visible: false

            source: "./images/arrow.png"
        }
        Desaturate {
            anchors.fill: image_Arrow
            source: image_Arrow

            desaturation: ( !enabled ? 1.0 : ( mouse_Expander.containsMouse ? 0.0 : 0.5 ) )
            Behavior on desaturation {
                NumberAnimation { duration: 200 }
            }

            rotation: treeItemView.treeItem && treeItemView.treeItem.expanded ? 90 : 0
            Behavior on rotation {
                NumberAnimation { easing.type: Easing.OutQuint; duration: 350 }
            }
        }

        MouseArea {
            id: mouse_Expander
            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                if ( treeItemView.treeItem && treeItemView.treeItem.expandable ) treeItemView.treeItem.expanded = !treeItemView.treeItem.expanded
            }
        }
    }

    Rectangle {
        id: i_Content
        anchors.top: parent.top
        anchors.left: rect_Expander.right
        anchors.leftMargin: 2
        width: parent.width
        height: text_ItemText.contentHeight+(text_ItemText.anchors.topMargin*2)

        color: treeItemView.treeItem && treeItemView.treeItem.selected ? "#55ff8833" : "transparent"
        Behavior on color {
            ColorAnimation { duration: 200 }
        }
        enabled: treeItemView.treeItem && treeItemView.treeItem.itemEnabled

        Rectangle {
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: text_ItemText.anchors.topMargin-anchors.topMargin

            color: treeItemView.treeItem && treeItemView.treeItem.selected ? "#ffff8833" : "transparent"
            Behavior on color {
                ColorAnimation { duration: 200 }
            }
        }
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: text_ItemText.anchors.topMargin-anchors.bottomMargin

            color: treeItemView.treeItem && treeItemView.treeItem.selected ? "#ffff8833" : "transparent"
            Behavior on color {
                ColorAnimation { duration: 200 }
            }
        }

        Text {
            id: text_ItemText
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 4
            width: parent.width
            height: contentHeight

            font: ( treeItemView.treeItem ? treeItemView.treeItem.font : f )
            color: ( enabled ? "black" : "#ff555555" )

            text: i_Content.itemData()
            wrapMode: Text.WordWrap

            property font f
        }

        MouseArea {
            anchors.fill: parent

            onClicked: treeItemView.treeItem.click()
            onDoubleClicked: treeItemView.treeItem.doubleClick()
        }

        function itemData()
        {
            var result = ( treeItemView.treeItem ? treeItemView.treeItem.data : undefined )
            if ( result === undefined ) result = ""

            return result
        }
    }

    Rectangle {
        anchors.top: i_Content.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: anchors.topMargin
        anchors.left: parent.left
        anchors.leftMargin: (loader_ChildItems.anchors.leftMargin/2)-(width/2)

        width: 4

        color: ( treeItemView.treeItem && treeItemView.treeItem.childSelected ? "#ffff8833" : "#88000000" )
        Behavior on color {
            ColorAnimation { duration: 200 }
        }
        radius: 2
    }

    Loader {
        id: loader_ChildItems
        anchors.top: i_Content.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20

        width: treeItemView.width
        height: ( item ? item.height : 0 )

        asynchronous: true

        source: treeItemView.treeItem && treeItemView.treeItem.hasChild && treeItemView.treeItem.expanded ? "TreeItemsList.qml" : ""

        visible: status == Loader.Ready
    }

    Component.onCompleted: {
        if ( modelData !== undefined ) treeItem = modelData
    }
    Component.onDestruction: {
        treeItem = null
    }
}
