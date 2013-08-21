import QtQuick 2.1
import QtQuick.Controls 1.0
import QtGraphicalEffects 1.0

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
    property bool checkVisible: false

    property int maxVisibleItemsCount: 15

    property Component delegate: null

    readonly property int count: menu.count
    readonly property string text: input_text.text
    readonly property int textIndex: dataContainer.textIndex

    QtObject {
        id: dataContainer

        property int textIndex: -1
    }

    RectangularGlow {
        id: effect
        anchors.fill: rect_ContentBackground
        glowRadius: 5
        spread: 0.2
        color: "#66000000"
        visible: menu.poppedup
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

        text: comboObject.label
        font.bold: comboObject.fontBold
        font.pixelSize: comboObject.fontPixelSize
        font.family: ( comboObject.fontFamily.length === 0 ? "Consolas" : comboObject.fontFamily )
        color: "white"
    }

    Rectangle {
        id: rect_MenuButton
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: height

        visible: ( comboObject.count > 0 )

        color: "transparent"

        Image {
            id: image_MenuButton
            anchors.centerIn: parent
            width: 20
            height: 20

            rotation: ( menu.poppedup ? 0 : 180 )
            Behavior on rotation {
                NumberAnimation { duration: 200 }
            }

            source: "ComboObjectImages/arrow.png"
        }

        MouseArea {
            id: mouse_MenuButton
            anchors.fill: parent

            hoverEnabled: true

            onClicked: menu.poppedup = !menu.poppedup
        }
    }

    Rectangle {
        id: rect_TextBackground
        anchors.top: parent.top
        anchors.left: rect_LabelBackground.right
        anchors.bottom: parent.bottom
        anchors.right: ( comboObject.count > 0 ? rect_MenuButton.left : parent.right )
        anchors.rightMargin: ( comboObject.count > 0 ? 0 : rect_ContentBackground.radius )

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

        verticalAlignment: Text.AlignVCenter

        selectByMouse: true

        font.bold: comboObject.fontBold
        font.pixelSize: comboObject.fontPixelSize
        font.family: comboObject.fontFamily

        property bool search: true

        Image {
            id: image_Checked
            anchors.top: parent.top
            anchors.left: parent.right
            anchors.leftMargin: -(parent.height+3)

            width: parent.height
            height: width

            visible: ( comboObject.checkVisible && comboObject.count > 0 )

            source: ( comboObject.textIndex > -1 ?
                         "ComboObjectImages/check.png" :"ComboObjectImages/stop.png" )
            onSourceChanged: {
                anim_Source.stop()
                anim_Source.start()
            }

            SequentialAnimation {
                id: anim_Source
                NumberAnimation { target: image_Checked; property: "scale"; from: 1.0; to: 1.3; easing.type: Easing.OutBack; duration: 300 }
                NumberAnimation { target: image_Checked; property: "scale"; from: 1.3; to: 1.0; easing.type: Easing.OutBack; duration: 300 }
            }
        }

        onTextChanged: {
            dataContainer.textIndex = -1
            if ( !search ) return

            var index = menu.find( text )
            var count = menu.visibleItemsCount
            if ( count > 1 )
            {
                if ( text.length > 0 ) menu.poppedup = true
            }
            else
            {
                if ( count === 1 && text.length > 0 )
                {
                    if ( menu.currentValue === menu.visibleValue( 0 ) )
                        text = menu.currentValue
                    else menu.selectVisible( 0 )
                }
                menu.poppedup = false
            }

            if ( index > -1 )
                dataContainer.textIndex = index
        }
    }

    ComboMenu {
        id: menu
        anchors.topMargin: 1
        anchors.rightMargin: 4
        poppedupWidth: rect_ContentBackground.width-(rect_ContentBackground.radius*2)

        control: comboObject

        fontBold: comboObject.fontBold
        fontPixelSize: comboObject.fontPixelSize
        fontFamily: comboObject.fontFamily

        onCurrentIndexChanged: {
            input_text.search = false
            input_text.text = visibleValue( currentIndex )
            dataContainer.textIndex = originalIndex( currentIndex )
            input_text.search = true
            menu.poppedup = false
        }

        property string currentValue: visibleValue( currentIndex )
    }

    function clear() {
        menu.clear()
    }

    function append( value ) {
        menu.append( value )
    }
}
