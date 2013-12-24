import QtQuick 2.2


Item {
    id: clock
    width: 200; height: 200

    property date clockTime: new Date()
    onClockTimeChanged: {
        obj_Information.hours = obj_Information.shift ? clockTime.getUTCHours() + Math.floor(obj_Information.shift) : clockTime.getHours()
        obj_Information.night = ( obj_Information.hours < 7 || obj_Information.hours > 19 )
        obj_Information.minutes = obj_Information.shift ? clockTime.getUTCMinutes() + ((obj_Information.shift % 1) * 60) : clockTime.getMinutes()
        obj_Information.seconds = clockTime.getUTCSeconds();
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10

        color: ( obj_Information.night ? "#aa333333" : "#aaffffff" )
        Behavior on color { ColorAnimation { duration: 200 } }

        radius: width/2
    }
    Image {
        id: background
        width: parent.width
        height: width
        source: "images/background.png"
    }


    Image {
        x: 92.5; y: 27
        source: "images/hour.png"
        smooth: true
        transform: Rotation {
            id: hourRotation
            origin.x: 7.5; origin.y: 73;
            angle: (obj_Information.hours * 30) + (obj_Information.minutes * 0.5)
            Behavior on angle {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }

    Image {
        x: 93.5; y: 17
        source: "images/minute.png"
        smooth: true
        transform: Rotation {
            id: minuteRotation
            origin.x: 6.5; origin.y: 83;
            angle: obj_Information.minutes * 6
            Behavior on angle {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }

    Image {
        x: 97.5; y: 20
        source: "images/second.png"
        smooth: true
        transform: Rotation {
            id: secondRotation
            origin.x: 2.5; origin.y: 80;
            angle: obj_Information.seconds * 6
            Behavior on angle {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }

    Image {
        anchors.centerIn: background; source: "images/center.png"
    }

    QtObject {
        id: obj_Information

        property int hours
        property int minutes
        property int seconds
        property real shift
        property bool night: false
    }
}
