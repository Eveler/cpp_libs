import QtQuick 2.0
import extensions.mqmllibraries 1.0


Item {
    id: treeItemView
    height: i_Content.height+loader_ChildItems.height
    Behavior on height {
        NumberAnimation { easing.type: Easing.OutQuint; duration: 350 }
    }

    clip: true

    Rectangle {
        id: rect_Expander
        anchors.verticalCenter: i_Content.verticalCenter
        anchors.left: parent.left

        width: 20
        height: width

        color: ( modelData.childSelected ? "#55ff8833" : "#88555555" )
        Behavior on color {
            ColorAnimation { duration: 200 }
        }
        border.color: ( modelData.childSelected ? "#ffff8833" : "#88000000" )
        Behavior on border.color {
            ColorAnimation { duration: 200 }
        }
        radius: width/2
        visible: modelData.hasChild

        Image {
            anchors.fill: parent
            anchors.margins: 2

            rotation: modelData.opened ? 90 : 0
            Behavior on rotation {
                NumberAnimation { easing.type: Easing.OutQuint; duration: 350 }
            }

            source: "../images/arrow.png"
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                if ( modelData.hasChild ) modelData.opened = !modelData.opened
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

        color: modelData.selected ? "#55ff8833" : "transparent"
        Behavior on color {
            ColorAnimation { duration: 200 }
        }

        Rectangle {
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: text_ItemText.anchors.topMargin-anchors.topMargin

            color: modelData.selected ? "#ffff8833" : "transparent"
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

            color: modelData.selected ? "#ffff8833" : "transparent"
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

            text: i_Content.itemData()

            font: modelData.font
        }

        MouseArea {
            anchors.fill: parent

            onClicked: modelData.selected = true
            onDoubleClicked: modelData.opened = !modelData.opened
        }

        function itemData()
        {
            var result = modelData.data
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

        color: ( modelData.childSelected ? "#ffff8833" : "#88000000" )
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

        source: modelData.hasChild && modelData.opened ? "TreeItemsList.qml" : ""

        visible: status == Loader.Ready
    }
}
