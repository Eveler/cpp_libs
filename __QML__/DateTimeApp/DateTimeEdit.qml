import QtQuick 2.1
import QtQuick.Controls 1.0
import QtGraphicalEffects 1.0

Item {
    id: dateTimeEdit
    width: 100
    height: 62

    readonly property int contentWidth: rect_LabelBackground.width+
                                        input_text.contentWidth+10+
                                        rect_MenuButton.width
    readonly property int contentHeight: text_Label.contentHeight+8

    property string label
    property bool fontBold: text_Label.font.bold
    property int fontPixelSize: text_Label.font.pixelSize
    property string fontFamily: text_Label.font.family

    property int maxVisibleItemsCount: 15

    property Component delegate: null

    property alias value: input_text.text

    state: "DDMMYYYY hhmmss"

    states: [
        State {
            name: "DDMMYYYY hhmmss"
            PropertyChanges {
                target: input_text
                inputMask: "99-99-9999 99:99:99;_"
            }
        },
        State {
            name: "DDMMYYYY"
            PropertyChanges {
                target: input_text
                inputMask: "99-99-9999;_"
            }
        },
        State {
            name: "hhmmss"
            PropertyChanges {
                target: input_text
                inputMask: "99:99:99;_"
            }
        }
    ]

    RectangularGlow {
        id: effect
        anchors.fill: rect_ContentBackground
        glowRadius: 5
        spread: 0.2
        color: "#66000000"
        visible: /*menu.poppedup*/true
        cornerRadius: rect_ContentBackground.radius + glowRadius
    }
    Rectangle {
        id: rect_ContentBackground
        anchors.fill: parent
        anchors.margins: -1

        color: "#66000000"
        border.color: "#66000000"
        radius: 5
    }

    Rectangle {
        id: rect_LabelBackground
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: text_Label.contentWidth+10

        visible: text_Label.text.length > 0

        color: "transparent"
    }
    Text {
        id: text_Label
        anchors.fill: rect_LabelBackground
        anchors.margins: 2

        visible: text.length > 0

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: dateTimeEdit.label
        font.bold: dateTimeEdit.fontBold
        font.pixelSize: dateTimeEdit.fontPixelSize
        font.family: ( dateTimeEdit.fontFamily.length === 0 ? "Consolas" : dateTimeEdit.fontFamily )
        color: "white"
    }

    Rectangle {
        id: rect_MenuButton
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: image_MenuButton.width

        color: "transparent"

        Image {
            id: image_MenuButton
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            width: 24
            height: 24
        }

        MouseArea {
            id: mouse_MenuButton
            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                /*menu.poppedup = !menu.poppedup*/
            }
        }
    }

    Rectangle {
        id: rect_TextBackground
        anchors.top: parent.top
        anchors.left: rect_LabelBackground.right
        anchors.bottom: parent.bottom
        anchors.right: rect_MenuButton.left

        color: "#55ffffff"

        MouseArea {
            anchors.fill: parent

            onClicked: input_text.focus = true
        }
    }
    TextInput {
        id: input_text
        anchors.fill: rect_TextBackground
        anchors.leftMargin: 5

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        selectByMouse: true

        font.bold: dateTimeEdit.fontBold
        font.pixelSize: dateTimeEdit.fontPixelSize
        font.family: dateTimeEdit.fontFamily

        property bool search: true
    }

//    ComboMenu {
//        id: menu
//        anchors.topMargin: 1
//        anchors.rightMargin: 4
//        poppedupWidth: rect_ContentBackground.width-(rect_ContentBackground.radius*2)

//        control: comboObject

//        fontBold: comboObject.fontBold
//        fontPixelSize: comboObject.fontPixelSize
//        fontFamily: comboObject.fontFamily

//        onCurrentIndexChanged: {
//            input_text.search = false
//            input_text.text = value( currentIndex )
//            input_text.search = true
//            menu.poppedup = false
//        }

//        property string currentValue: value( currentIndex )
//    }
}
