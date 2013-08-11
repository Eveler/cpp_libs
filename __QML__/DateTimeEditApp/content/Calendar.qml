import QtQuick 2.1
import QtGraphicalEffects 1.0

Item {
    id: calendar
    width: ( listView.currentItem && poppedup ?
                listView.currentItem.width+(rect_ContentBackground.radius*2) : 0 )
    height: ( listView.currentItem && poppedup ?
                 listView.currentItem.height+(rect_ContentBackground.radius*2) : 0 )

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
            width: rect_LeftButton.width+grid_Content.width+rect_RightButton.width
            height: grid_Content.height

            scale: ( calendarItem.ListView.isCurrentItem ? 1.0 : 0.0 )
            Behavior on scale {
                NumberAnimation { duration: 500 }
            }

            property int year: yearValue
            property int month: monthValue
            
            property date itemDate
            onMonthChanged: {
                grid_Content.model.append( { "dayValue": 1 } )
            }

            Rectangle {
                id: rect_LeftButton
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: 12

                color: "#99888888"

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

                color: "#99888888"

                MouseArea {
                    id: mouse_RightButton
                    anchors.fill: parent

                    hoverEnabled: true

                    onClicked: calendarItem.parent.parent.nextMonth()
                }
            }
            GridView {
                id: grid_Content
                anchors.centerIn: parent
                width: 140
                height: 100

                cellWidth: width/7
                cellHeight: height/5

                model: ListModel{}
                delegate: Rectangle {
                    width: grid_Content.cellWidth
                    height: grid_Content.cellHeight

                    radius: 4
                }
            }
//            Text {
//                anchors.fill: grid_Content

//                property date itemDate: dateValue

//                text: Qt.formatDate( itemDate,  "dd.MM.yyyy" )

//                horizontalAlignment: Text.AlignHCenter
//                verticalAlignment: Text.AlignVCenter
//            }
        }
    }

    QtObject {
        id: dataContainer

        property ListModel dateModel: ListModel {}
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

        property date curDate

        function nextMonth() {
//            if ( currentIndex+1 < count ) currentIndex++
            var newIndex = listView.currentIndex+1
            listView.model.append(
                        { "yearValue": listView.model.get( listView.currentIndex ).yearValue,
                            "monthValue": listView.model.get( listView.currentIndex ).monthValue+1 } )
            listView.currentIndex = newIndex
        }

        function prevMonth() {
//            if ( currentIndex-1 > -1 ) currentIndex--
        }
    }

    function setCurrentDate( dateValue ) {

    }

    function setCurrentMonth( year, month ) {
        var newIndex = listView.currentIndex
        if ( newIndex === -1 ) newIndex = 0
        listView.model.append( { "yearValue": year, "monthValue": month } )
        listView.currentIndex = newIndex
    }

    function setCurrentDay( day ) {

    }
}
