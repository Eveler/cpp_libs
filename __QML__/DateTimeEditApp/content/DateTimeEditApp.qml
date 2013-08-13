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
        }

        RectangularGlow {
            id: effect
            anchors.fill: calendar
            glowRadius: 5
            spread: 0.2
            color: "#66000000"
            cornerRadius: glowRadius*2
        }
        Calendar {
            id: calendar
            anchors.centerIn: parent
            width: contentWidth
            height: contentHeight

            MDate {
                id: dateInfo
            }

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
