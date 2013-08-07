import QtQuick 2.1
import QtQuick.Controls 1.0

Item {
    id: comboObject
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

    Rectangle {
        id: rect_ContentBackground
        anchors.fill: parent
    }

    Rectangle {
        id: rect_LabelBackground
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: text_Label.contentWidth+10

        visible: text_Label.text.length > 0

        border.color: "gray"
    }
    Text {
        id: text_Label
        anchors.fill: rect_LabelBackground
        anchors.margins: 2

        visible: text.length > 0

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: comboObject.label
        font.bold: comboObject.fontBold
        font.pixelSize: comboObject.fontPixelSize
        font.family: ( comboObject.fontFamily.length === 0 ? "Consolas" : comboObject.fontFamily )
    }

    Rectangle {
        id: rect_TextBackground
        anchors.top: parent.top
        anchors.left: rect_LabelBackground.right
        anchors.bottom: parent.bottom
        anchors.right: rect_MenuButton.left

        border.color: "gray"

        MouseArea {
            anchors.fill: parent

            onClicked: input_text.focus = true
        }
    }
    TextInput {
        id: input_text
        anchors.fill: rect_TextBackground
        anchors.leftMargin: 5

        verticalAlignment: Text.AlignVCenter

        selectByMouse: true

        font.bold: comboObject.fontBold
        font.pixelSize: comboObject.fontPixelSize
        font.family: comboObject.fontFamily
    }

    Rectangle {
        id: rect_MenuButton
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: image_MenuButton.width
        border.color: "gray"

        Image {
            id: image_MenuButton
            width: 24
            height: 24

            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
        }
    }
}
