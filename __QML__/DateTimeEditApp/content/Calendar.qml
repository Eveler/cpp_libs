import QtQuick 2.1
import QtGraphicalEffects 1.0

Item {
    id: calendar
    width: ( listView.currentItem && poppedup ?
                listView.currentItem.width+(rect_ContentBackground.radius*2) : 0 )
    Behavior on width {
        SpringAnimation { spring: 2; damping: 0.2 }
    }
    height: ( listView.currentItem && poppedup ?
                 listView.currentItem.height+(rect_ContentBackground.radius*2) : 0 )
    Behavior on height {
        SpringAnimation { spring: 2; damping: 0.2 }
    }

    property Item control: null
    onControlChanged: {
        if ( !control ) return
        if ( !control.parent ) return

        parent = control.parent
        anchors.top = control.bottom
        anchors.right = control.right
    }

    readonly property int maxVisibleItemsCount: ( control ? control.maxVisibleItemsCount : 0 )
    readonly property Component delegate: ( control && control.delegate ?
                                               control.delegate : calendarDelegate )

    property bool fontBold
    property int fontPixelSize
    property string fontFamily

    property bool poppedup: false

    Component {
        id: calendarDelegate

        Item {
            id: calendarItem
            width: rect_LeftButton.width+item_Content.width+rect_RightButton.width
            height: item_Content.height

            scale: ( calendarItem.ListView.isCurrentItem ? 1.0 : 0.0 )
            Behavior on scale {
                NumberAnimation { duration: 500 }
            }

            Rectangle {
                id: rect_LeftButton
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: 12

//                opacity: ( calendarItem.ListView.isCurrentItem ? 1.0 : 0.0 )
//                Behavior on opacity {
//                    NumberAnimation { duration: 1000 }
//                }

                color: ( model.index > 0 ? "#99888888" : "#33888888" )

                MouseArea {
                    id: mouse_LeftButton
                    anchors.fill: parent

                    hoverEnabled: true

                    onClicked: calendarItem.parent.parent.prevMonth()
                }
            }
            Rectangle {
                id: rect_RightButton
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                width: 12

//                opacity: ( calendarItem.ListView.isCurrentItem ? 1.0 : 0.0 )
//                Behavior on opacity {
//                    NumberAnimation { duration: 1000 }
//                }

                color: ( model.index+1 < calendarItem.parent.parent.count ? "#99888888" : "#33888888" )

                MouseArea {
                    id: mouse_RightButton
                    anchors.fill: parent

                    hoverEnabled: true

                    onClicked: calendarItem.parent.parent.nextMonth()
                }
            }
            Item {
                id: item_Content
                anchors.centerIn: parent
                width: 100
                height: 100
            }
            Text {
                anchors.fill: item_Content

                property date itemDate: dateValue

                text: Qt.formatDate( itemDate,  "dd.MM.yyyy" )

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    QtObject {
        id: dataContainer

        property ListModel dateModel: ListModel {
            ListElement {
                dateValue: "2013-08-08"
            }
            ListElement {
                dateValue: "2013-08-09"
            }
            ListElement {
                dateValue: "2013-08-10"
            }
        }
    }

    RectangularGlow {
        id: effect
        anchors.fill: rect_ContentBackground
        glowRadius: 5
        spread: 0.2
        color: "#66000000"
        visible: calendar.poppedup
        cornerRadius: rect_ContentBackground.radius + glowRadius
    }
    Rectangle {
        id: rect_ContentBackground
        anchors.fill: parent
        radius: 5

        color: "#66000000"
    }


    ListView {
        id: listView
        anchors.fill: rect_ContentBackground
        anchors.margins: rect_ContentBackground.radius

        clip: true

        model: dataContainer.dateModel
        delegate: calendar.delegate

        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem

        function select( index ) {
        }

        interactive: false

        property date curDate: model.get( currentIndex ).dateValue

        function nextMonth() {
            if ( currentIndex+1 < count ) currentIndex++
        }

        function prevMonth() {
            if ( currentIndex-1 > -1 ) currentIndex--
        }
    }

    function setCurrentDate( dateValue ) {

    }

    function setCurrentYear( year ) {

    }

    function setCurrentMonth( month ) {

    }

    function setCurrentDay( day ) {

    }
}
