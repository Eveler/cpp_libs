import QtQuick 2.2
import QtGraphicalEffects 1.0


Item {
    id: progressBar
    property real progress: 0.0
    onProgressChanged: {
        if ( progress < 0.0 || progress > 1.0 )
            obj_Information.progress = 0.0
        else obj_Information.progress = progress
    }


    RectangularGlow {
        id: effect1
        anchors.fill: stop1
        property real startPoint: 0.0
        glowRadius: ( obj_Information.progress > startPoint ? 10 : 3 )
        Behavior on glowRadius {
            NumberAnimation { duration: 150 }
        }
        spread: ( obj_Information.progress > startPoint ? 0.2 : 0.5 )
        Behavior on spread {
            NumberAnimation { duration: 150 }
        }
        color: ( obj_Information.progress > startPoint ? "cyan" : "#ff444444" )
        Behavior on color {
            ColorAnimation { duration: 150 }
        }
        cornerRadius: stop1.radius + glowRadius
    }

    RectangularGlow {
        id: effect2
        anchors.fill: stop2
        property real startPoint: 0.225
        glowRadius: ( obj_Information.progress > startPoint ? 10 : 3 )
        Behavior on glowRadius {
            NumberAnimation { duration: 150 }
        }
        spread: ( obj_Information.progress > startPoint ? 0.2 : 0.5 )
        Behavior on spread {
            NumberAnimation { duration: 150 }
        }
        color: ( obj_Information.progress > startPoint ? "cyan" : "#ff444444" )
        Behavior on color {
            ColorAnimation { duration: 150 }
        }
        cornerRadius: stop2.radius + glowRadius
    }

    RectangularGlow {
        id: effect3
        anchors.fill: stop3
        property real startPoint: 0.47
        glowRadius: ( obj_Information.progress > startPoint ? 10 : 3 )
        Behavior on glowRadius {
            NumberAnimation { duration: 150 }
        }
        spread: ( obj_Information.progress > startPoint ? 0.2 : 0.5 )
        Behavior on spread {
            NumberAnimation { duration: 150 }
        }
        color: ( obj_Information.progress > startPoint ? "cyan" : "#ff444444" )
        Behavior on color {
            ColorAnimation { duration: 150 }
        }
        cornerRadius: stop3.radius + glowRadius
    }

    RectangularGlow {
        id: effect4
        anchors.fill: stop4
        property real startPoint: 0.715
        glowRadius: ( obj_Information.progress > startPoint ? 10 : 3 )
        Behavior on glowRadius {
            NumberAnimation { duration: 150 }
        }
        spread: ( obj_Information.progress > startPoint ? 0.2 : 0.5 )
        Behavior on spread {
            NumberAnimation { duration: 150 }
        }
        color: ( obj_Information.progress > startPoint ? "cyan" : "#ff444444" )
        Behavior on color {
            ColorAnimation { duration: 150 }
        }
        cornerRadius: stop4.radius + glowRadius
    }

    RectangularGlow {
        id: effect5
        anchors.fill: stop5
        property real startPoint: 0.975
        glowRadius: ( obj_Information.progress > startPoint ? 10 : 3 )
        Behavior on glowRadius {
            NumberAnimation { duration: 150 }
        }
        spread: ( obj_Information.progress > startPoint ? 0.2 : 0.5 )
        Behavior on spread {
            NumberAnimation { duration: 150 }
        }
        color: ( obj_Information.progress > startPoint ? "cyan" : "#ff444444" )
        Behavior on color {
            ColorAnimation { duration: 150 }
        }
        cornerRadius: stop5.radius + glowRadius
    }

    RectangularGlow {
        id: effectProgress
        anchors.fill: progressLine
        glowRadius: 10
        spread: 0.4
        color: "cyan"
        cornerRadius: progressLine.radius + glowRadius
    }

    Rectangle {
        id: progressBorder
        anchors.fill: progressBackground
        anchors.margins: -border.width

        border.color: "#ff333333"
        border.width: 3
    }

    LinearGradient {
        id: progressBackground
        anchors.centerIn: parent
        width: parent.width-stop1.width
        height: stop1.width*0.2

        start: Qt.point(0, 0)
        end: Qt.point(0, parent.height)
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ff333333" }
            GradientStop { position: 1.0; color: "#ff333333" }
        }
    }

    Rectangle {
        id: stop1
        x: 0
        width: height
        height: parent.height

        radius: width/2
        border.color: progressBorder.border.color
        border.width: progressBorder.border.width
        color: ( obj_Information.progress > 0.0 ? "cyan" : "#ffcccccc" )
    }

    Rectangle {
        id: stop2
        x: (parent.width*0.25)-(width*0.25)
        width: height
        height: parent.height

        radius: width/2
        border.color: progressBorder.border.color
        border.width: progressBorder.border.width
        color: ( obj_Information.progress > 0.225 ? "cyan" : "#ffcccccc" )
    }

    Rectangle {
        id: stop3
        x: (parent.width*0.5)-(width*0.5)
        width: height
        height: parent.height

        radius: width/2
        border.color: progressBorder.border.color
        border.width: progressBorder.border.width
        color: ( obj_Information.progress > 0.47 ? "cyan" : "#ffcccccc" )
    }

    Rectangle {
        id: stop4
        x: (parent.width*0.75)-(width*0.75)
        width: height
        height: parent.height

        radius: width/2
        border.color: progressBorder.border.color
        border.width: progressBorder.border.width
        color: ( obj_Information.progress > 0.715 ? "cyan" : "#ffcccccc" )
    }

    Rectangle {
        id: stop5
        x: parent.width-width
        width: height
        height: parent.height

        radius: width/2
        border.color: progressBorder.border.color
        border.width: progressBorder.border.width
        color: ( obj_Information.progress > 0.975 ? "cyan" : "#ffcccccc" )
    }

    Rectangle {
        id: progressLine
        anchors.top: progressBackground.top
        anchors.left: progressBackground.left
        anchors.bottom: progressBackground.bottom

        width: progressBackground.width*obj_Information.progress
        Behavior on width {
            NumberAnimation { duration: 150 }
        }
        radius: 2

        color: "cyan"
    }

    Text {
        anchors.fill: stop1

        property int value: (obj_Information.progress*100.0)

        text: value+"%"
        font.pixelSize: 8
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: ( obj_Information.progress <= effect2.startPoint ? 1.0 : 0.0 )
        Behavior on opacity {
            NumberAnimation { duration: 150 }
        }
    }

    Text {
        anchors.fill: stop2

        property int value: (obj_Information.progress*100.0)

        text: value+"%"
        font.pixelSize: 8
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: ( obj_Information.progress > effect2.startPoint &&
                  obj_Information.progress <= effect3.startPoint ? 1.0 : 0.0 )
        Behavior on opacity {
            NumberAnimation { duration: 150 }
        }
    }

    Text {
        anchors.fill: stop3

        property int value: (obj_Information.progress*100.0)

        text: value+"%"
        font.pixelSize: 8
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: ( obj_Information.progress > effect3.startPoint &&
                  obj_Information.progress <= effect4.startPoint ? 1.0 : 0.0 )
        Behavior on opacity {
            NumberAnimation { duration: 150 }
        }
    }

    Text {
        anchors.fill: stop4

        property int value: (obj_Information.progress*100.0)

        text: value+"%"
        font.pixelSize: 8
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: ( obj_Information.progress > effect4.startPoint &&
                  obj_Information.progress <= effect5.startPoint ? 1.0 : 0.0 )
        Behavior on opacity {
            NumberAnimation { duration: 150 }
        }
    }

    Text {
        anchors.fill: stop5

        property int value: (obj_Information.progress*100.0)

        text: value+"%"
        font.pixelSize: 8
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: ( obj_Information.progress > effect5.startPoint ? 1.0 : 0.0 )
        Behavior on opacity {
            NumberAnimation { duration: 150 }
        }
    }

    QtObject {
        id: obj_Information

        property real progress: 0.0
    }
}
