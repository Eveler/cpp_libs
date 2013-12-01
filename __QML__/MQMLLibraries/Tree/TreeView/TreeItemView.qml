import QtQuick 2.0
import QtGraphicalEffects 1.0
import extensions.mqmllibraries 1.0


Item {
    id: treeItemView
    anchors.top: ( prevView ? prevView.bottom : parent.top )
    width: parent.width-parent.anchors.leftMargin
    height: rect_TextContent.height+
            ( obj_Information.expanded ? treeItemList.height : 0 )
    Behavior on height {
        NumberAnimation { duration: 200 }
    }

    x: 0

    onYChanged: {
        if ( !treeItem || !treeItem.parentItem() ||
                treeItem.parentItem().childItems.indexOf( treeItem ) <
                treeItem.parentItem().childItems.length-1 )
            return;

        parent.height = y+height
    }
    onHeightChanged: {
        if ( !treeItem || !treeItem.parentItem() ||
                treeItem.parentItem().childItems.indexOf( treeItem ) <
                treeItem.parentItem().childItems.length-1 )
            return;

        parent.height = y+height
    }

    clip: true
    enabled: ( treeItem !== null )

    property Item prevView: null
    property TreeItem treeItem: null
    onTreeItemChanged: obj_Information.itemPropertiesChanged()

    Rectangle {
        id: rect_Expander
        anchors.verticalCenter: rect_TextContent.verticalCenter
        anchors.left: parent.left

        width: 20
        height: width

        color: ( obj_Information.childSelected ? "#55ff8833" : "#88555555" )
        Behavior on color {
            ColorAnimation { duration: 400 }
        }
        border.color: ( obj_Information.childSelected ? "#ffff8833" : "#88000000" )
        Behavior on border.color {
            ColorAnimation { duration: 400 }
        }
        radius: width/2
        opacity: ( obj_Information.hasChild ? 1.0 : 0.0 )
        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
        enabled: obj_Information.itemEnabled && obj_Information.expandable

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

            rotation: obj_Information.expanded ? 90 : 0
            Behavior on rotation {
                NumberAnimation { easing.type: Easing.OutQuint; duration: 350 }
            }
        }

        MouseArea {
            id: mouse_Expander
            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                if ( treeItemView.treeItem.expandable )
                    treeItemView.treeItem.expanded = !treeItemView.treeItem.expanded
            }
        }
    }

    Rectangle {
        id: rect_TextContent
        anchors.top: parent.top
        anchors.left: rect_Expander.right
        anchors.leftMargin: 2
        anchors.right: parent.right
        height: text.contentHeight+8

        color: ( obj_Information.selected ? "#55ff8833" : "transparent" )
        Behavior on color {
            ColorAnimation { duration: 200 }
        }

        Rectangle {
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 1

            color: ( obj_Information.selected ? "#ffff8833" : "transparent" )
            Behavior on color {
                ColorAnimation { duration: 400 }
            }
        }
        Text {
            id: text
            anchors.centerIn: parent
            width: parent.width-10

            text: obj_Information.value
            color: ( obj_Information.itemEnabled ?
                        ( obj_Information.childSelected ? "#ffff8833" : "black" ) : "#ff555555" )
            Behavior on color {
                ColorAnimation { duration: 400 }
            }
            font: obj_Information.itemFont
            wrapMode: Text.WordWrap
        }
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 1

            color: ( obj_Information.selected ? "#ffff8833" : "transparent" )
            Behavior on color {
                ColorAnimation { duration: 400 }
            }
        }
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 1

            color: ( obj_Information.selected ? "transparent" : "#aa000000" )
            Behavior on color {
                ColorAnimation { duration: 400 }
            }
        }

        MouseArea {
            id: mouse_TextContent
            anchors.fill: parent

            hoverEnabled: true

            onClicked: treeItem.click()
            onDoubleClicked: treeItem.doubleClick()
        }
    }

    Rectangle {
        anchors.top: rect_TextContent.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: anchors.topMargin
        anchors.left: parent.left
        anchors.leftMargin: (treeItemList.anchors.leftMargin/2)-(width/2)

        width: 4

        color: ( obj_Information.childSelected ? "#ffff8833" : "#88000000" )
        Behavior on color {
            ColorAnimation { duration: 400 }
        }
        radius: 2
    }

    TreeItemsList {
        id: treeItemList
        anchors.top: rect_TextContent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width

        opacity: ( obj_Information.expanded ? 1.0 : 0.0 )
        Behavior on opacity {
            NumberAnimation { duration: 400 }
        }

        treeItem: treeItemView.treeItem
    }

    QtObject {
        id: obj_Information

        property string value: ""
        property font defFont
        property font itemFont: defFont
        property bool hasChild: false
        property bool itemEnabled: false
        property bool selectable: false
        property bool selected: false
        property bool childSelected: false
        property bool expandable: false
        property bool expanded: false

        function itemPropertiesChanged()
        {
            if ( treeItemView.treeItem )
            {
                value = treeItemView.treeItem.value
                itemFont = treeItemView.treeItem.font
                hasChild = treeItemView.treeItem.hasChild
                itemEnabled = treeItemView.treeItem.itemEnabled
                selectable = treeItemView.treeItem.selectable
                selected = treeItemView.treeItem.selected
                childSelected = treeItemView.treeItem.childSelected
                expandable = treeItemView.treeItem.expandable
                expanded = treeItemView.treeItem.expanded
            }
            else
            {
                value = ""
                itemFont = defFont
                hasChild = false
                itemEnabled = false
                selectable = false
                selected = false
                childSelected = false
                expandable = false
                expanded = false
            }
        }
    }

    Connections {
        target: treeItemView.treeItem
        onValueChanged: obj_Information.itemPropertiesChanged()
        onItemEnabledChanged: obj_Information.itemPropertiesChanged()
        onSelectableChanged: obj_Information.itemPropertiesChanged()
        onSelectedChanged: obj_Information.itemPropertiesChanged()
        onExpandableChanged: obj_Information.itemPropertiesChanged()
        onExpandedChanged: obj_Information.itemPropertiesChanged()
    }
}
