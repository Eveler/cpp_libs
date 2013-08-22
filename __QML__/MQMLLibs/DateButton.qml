import QtQuick 2.1
import QtQuick.Controls 1.0
import QtGraphicalEffects 1.0
import com.mihail.qmlcomponents 1.0

Item {
    id: dateButton
    width: 100
    height: 62

    readonly property int contentWidth: rect_LabelBackground.width+
                                        input_text.contentWidth+
                                        ( dateButton.checkVisible ? image_Checked.width : 0 )+10+
                                        rect_MenuButton.width
    readonly property int contentHeight: text_Label.contentHeight+8

    property alias label: text_Label.text
    property bool fontBold: text_Label.font.bold
    property int fontPixelSize: text_Label.font.pixelSize
    property string fontFamily: text_Label.font.family
    property Component delegate: null

    property alias currentDate: loader_Calendar.currentDate
    property date minimumDate: "0001-01-01"

    property string replacementText

    property bool checkVisible: false

    readonly property alias poppedup: popupController.poppedup

    RectangularGlow {
        id: effect
        anchors.fill: rect_ContentBackground
        glowRadius: 5
        spread: 0.2
        color: "#66000000"
        visible: popupController.poppedup
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

        clip: true

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

            rotation: ( popupController.poppedup ? 0 : 180 )
            Behavior on rotation {
                NumberAnimation { duration: 200 }
            }

            source: "DateButtonImages/arrow.png"
        }

        MouseArea {
            id: mouse_MenuButton
            anchors.fill: parent

            hoverEnabled: true

            onClicked: popupController.poppedup = !popupController.poppedup
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
        anchors.rightMargin: ( dateButton.checkVisible ? image_Checked.width : 0 )+5

        clip: true

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.bold: dateButton.fontBold
        font.pixelSize: dateButton.fontPixelSize
        font.family: dateButton.fontFamily

        readOnly: true

        property string value: Qt.formatDate( loader_Calendar.currentDate, "dd.MM.yyyy" )

        text: ( value === Qt.formatDate( dateButton.minimumDate, "dd.MM.yyyy" ) &&
               dateButton.replacementText.length > 0 ?
                   dateButton.replacementText : value )

        selectByMouse: true
    }

    Image {
        id: image_Checked
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: rect_MenuButton.left

        width: parent.height
        height: width

        opacity: ( dateButton.checkVisible ? 1.0 : 0.01 )
        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }

        source: ( input_text.text === input_text.value ?
                     "DateButtonImages/check.png" :"DateButtonImages/stop.png" )
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

    Component {
        id: component_Calendar

        Calendar {}
    }

    Loader {
        id: loader_Calendar

        property date currentDate: dateButton.minimumDate

        onLoaded: {
            item.anchors.fill = loader_Calendar
        }

        RectangularGlow {
            anchors.fill: loader_Calendar.item
            glowRadius: 5
            spread: 0.2
            color: "#66000000"
            visible: popupController.poppedup
            cornerRadius: glowRadius
        }

        Connections {
            target: loader_Calendar.item

            onClicked: {
                loader_Calendar.currentDate = loader_Calendar.item.currentDate
                popupController.poppedup = false
            }
        }
    }

    PopupPanel {
        id: popupController

        poppedup: false
        onPoppedupChanged: {
            popAnimation.stop()

            if ( poppedup )
            {
                popAnimation.widthFrom = 0
                popAnimation.widthTo = 250
                popAnimation.heightFrom = 0
                popAnimation.heightTo = 200
                popAnimation.duration = 1500
                popAnimation.easingType = Easing.OutElastic
            }
            else
            {
                popAnimation.widthFrom = 250
                popAnimation.widthTo = 0
                popAnimation.heightFrom = 200
                popAnimation.heightTo = 0
                popAnimation.duration = 300
                popAnimation.easingType = Easing.InBack
            }

            popAnimation.start()
        }
    }

    ParallelAnimation {
        id: popAnimation

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
            if ( poppedup )
                loader_Calendar.sourceComponent = component_Calendar
        }
        onStopped: {
            if ( !poppedup ) loader_Calendar.sourceComponent = null
            else
            {
                loader_Calendar.item.minimumDate = dateButton.minimumDate
                loader_Calendar.item.currentDate = loader_Calendar.currentDate
            }
            loader_Calendar.enabled = true
        }
    }

    onParentChanged: {
        loader_Calendar.parent = dateButton.parent
        loader_Calendar.anchors.top = dateButton.bottom
        loader_Calendar.anchors.topMargin = 1
        loader_Calendar.anchors.right = dateButton.right
        loader_Calendar.anchors.rightMargin = 3
    }
}
