import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import com.mihail.qmlcomponents 1.0

ApplicationWindow {
    id: applicationWindow
    title: qsTr("Hello World")
    width: 500
    height: 300

    Item {
        anchors.fill: parent

        DateTimeEdit {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            width: contentWidth
            height: contentHeight

            fontBold: true
            fontPixelSize: 14
            fontFamily: "Consolas"
            label: "Дата выдачи"

            value: Qt.formatDate( calendar.currentDate, "dd-MM-yyyy" )
        }

        RectangularGlow {
            id: effect
            anchors.fill: calendar
            glowRadius: 10
            spread: 0.1
            color: "#ff000000"
            cornerRadius: glowRadius
            rotation: calendar.rotation
        }
        Calendar {
            id: calendar
            anchors.centerIn: parent
            width: parent.width*0.8
            height: parent.height*0.8

            rotation: ( width > height ? 0 : 90 )
            Behavior on rotation {
                NumberAnimation { duration: 200 }
            }

            MDate {
                id: dateInfo
            }

            changeDateOnHover: true

            currentDate: dateInfo.currentDate()
        }
        Button {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            text: ">>"

            onClicked: calendar.setCurrentMonth( calendar.visibleYear, calendar.visibleMonth+1 )
        }
    }
}
