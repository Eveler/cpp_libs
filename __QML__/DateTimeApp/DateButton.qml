import QtQuick 2.1
import QtQuick.Controls 1.0
import QtGraphicalEffects 1.0
//import com.mihail.qmlcomponents 1.0

Item {
    id: dateButton
    width: 100
    height: 62

    readonly property int contentWidth: rect_LabelBackground.width+
                                        input_text.contentWidth+10+
                                        rect_MenuButton.width
    readonly property int contentHeight: text_Label.contentHeight+8

    property alias label: text_Label.text
    property date selectedDate
    property bool fontBold: text_Label.font.bold
    property int fontPixelSize: text_Label.font.pixelSize
    property string fontFamily: text_Label.font.family
    property Component delegate: null

    property date currentDate: "0001-01-01"


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

        font.bold: dateButton.fontBold
        font.pixelSize: dateButton.fontPixelSize
        font.family: ( dateButton.fontFamily.length === 0 ? "Consolas" : dateButton.fontFamily )
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
            anchors.centerIn: parent
            width: 20
            height: 20

            rotation: ( rect_MenuButton.poppedup ? 0 : 180 )
            Behavior on rotation {
                NumberAnimation { duration: 200 }
            }

            source: "DateButtonImages/arrow.png"
        }

        MouseArea {
            id: mouse_MenuButton
            anchors.fill: parent

            hoverEnabled: true

            onClicked: popAnimation.poppedup = !popAnimation.poppedup
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

        font.bold: dateButton.fontBold
        font.pixelSize: dateButton.fontPixelSize
        font.family: dateButton.fontFamily

        readOnly: true

        text: Qt.formatDate( dateButton.currentDate, "dd.MM.yyyy" )

        selectByMouse: true

        property bool search: true
    }

    Component {
        id: component_Calendar

        Calendar {
            id: calendar
        }
    }


    Loader {
        id: loader_Calendar

        property date currentDate: ( item && enabled ? item.currentDate : bufferDate )
        onCurrentDateChanged: {
            if ( item && enabled )
            {
                bufferDate = currentDate
                dateButton.currentDate = currentDate
            }
        }
        property date bufferDate

        sourceComponent: component_Calendar

        onLoaded: {
            item.anchors.fill = loader_Calendar
        }
    }

    ParallelAnimation {
        id: popAnimation

        property bool poppedup: false
        onPoppedupChanged: {
            stop()

            if ( poppedup )
            {
                widthFrom = 0
                widthTo = 250
                heightFrom = 0
                heightTo = 200
                duration = 1000
                easingType = Easing.OutElastic
            }
            else
            {
                widthFrom = 250
                widthTo = 0
                heightFrom = 200
                heightTo = 0
                duration = 300
                easingType = Easing.InBack
            }

            start()
        }

        property int widthFrom
        property int widthTo
        property int heightFrom
        property int heightTo
        property int duration
        property int easingType

        NumberAnimation {
            target: loader_Calendar
            property: "width"
            from: popAnimation.widthFrom
            to: popAnimation.widthTo
            duration: popAnimation.duration
            easing.type: popAnimation.easingType
        }
        NumberAnimation {
            target: loader_Calendar
            property: "height"
            from: popAnimation.heightFrom
            to: popAnimation.heightTo
            duration: popAnimation.duration
            easing.type: popAnimation.easingType
        }
        onStarted: {
            loader_Calendar.enabled = false
            if ( poppedup ) loader_Calendar.sourceComponent = component_Calendar
        }
        onStopped: {
            if ( !poppedup ) loader_Calendar.sourceComponent = null
            else loader_Calendar.item.currentDate = loader_Calendar.bufferDate
            loader_Calendar.enabled = true
        }
    }

    onParentChanged: {
        loader_Calendar.parent = dateButton.parent
        loader_Calendar.anchors.top = dateButton.bottom
        loader_Calendar.anchors.right = dateButton.right
    }
}
