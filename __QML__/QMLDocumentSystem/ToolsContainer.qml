import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0

Item {
    id: toolsContainer

    property int closedWidth: 0
    property int closedHeight: 0
    property int openedWidth: 50
    property int openedHeight: 50

    opacity: ( state === "maximized" ? 1.0 : 0.0 )
    Behavior on opacity {
        NumberAnimation { duration: ( toolsContainer.state === "maximized" ? 500 : 700 ) }
    }

    states: [
        State {
            name: "maximized"
            PropertyChanges {
                target: toolsContainer
                width: ( openedWidth > 0 ? openedWidth : parent.width )
                height: ( openedHeight > 0 ? openedHeight : parent.height )
            }
        },
        State {
            name: "minimized"
            PropertyChanges {
                target: toolsContainer
                width: closedWidth
                height: closedHeight
            }
        }
    ]

    state: "maximized"

    Behavior on width {
        NumberAnimation {
            duration: 500
            easing.type: ( state === "maximized" ? Easing.OutBack : Easing.InBack )
        }
    }
    Behavior on height {
        NumberAnimation {
            duration: 500
            easing.overshoot: 0.6;
            easing.type: ( state === "maximized" ? Easing.OutBack : Easing.InBack )
        }
    }

    Item {
        id: background
        anchors.fill: parent
        opacity: parent.opacity
    }
    RectangularGlow {
        id: effect
        anchors.fill: background
        glowRadius: 10
        spread: 0.2
        color: "#5f999999"
        opacity: background.opacity
    }
}
