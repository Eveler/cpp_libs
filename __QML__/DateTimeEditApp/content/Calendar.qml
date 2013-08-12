import QtQuick 2.1
import QtGraphicalEffects 1.0
import com.mihail.qmlcomponents 1.0

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
            width: rect_LeftButton.width+item_GridContainer.width+rect_RightButton.width
            height: item_GridContainer.height

            scale: ( calendarItem.ListView.isCurrentItem ? 1.0 : 0.0 )
            Behavior on scale {
                NumberAnimation { duration: 500 }
            }

            property int year: yearValue
            property int month: monthValue

            MDate { id: dateInfo }

            property date itemDate
            onMonthChanged: {
                grid_Content.model.clear()
                var date = dateInfo.date( year, month, 1 )
                var date2 = dateInfo.addDays( date, -(dateInfo.dayOfWeak( date )) )
                for ( var day = 1; day<dateInfo.dayOfWeak( date ); day++ )
                {
                    date2 = dateInfo.addDays( date2, 1 )
                    grid_Content.model.append( { "dayValue": date2.getDate(),
                                              "subMonthValue": date2.getMonth()+1 } )
                }

                date = dateInfo.date( year, month, 1 )
                date = dateInfo.addDays( date, -1 )
                for ( var day = 0; day < dateInfo.daysInMonth( year, month ); day++ )
                {
                    date = dateInfo.addDays( date, 1 )
                    grid_Content.model.append( { "dayValue": date.getDate(),
                                                  "subMonthValue": date.getMonth()+1 } )
                }

                while ( grid_Content.model.count < 7*6 )
                {
                    date = dateInfo.addDays( date, 1 )
                    grid_Content.model.append( { "dayValue": date.getDate(),
                                                  "subMonthValue": date.getMonth()+1 } )
                }
            }

            Rectangle {
                id: rect_LeftButton
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: 12

                color: "#99ff8833"

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

                color: "#99ff8833"

                MouseArea {
                    id: mouse_RightButton
                    anchors.fill: parent

                    hoverEnabled: true

                    onClicked: calendarItem.parent.parent.nextMonth()
                }
            }
            Item {
                id: item_GridContainer
                anchors.centerIn: parent
                width: 160
                height: 120

                GridView {
                    id: grid_Content
                    anchors.fill: parent
                    anchors.margins: 1
                    anchors.leftMargin: 3
                    anchors.rightMargin: 3

                    cellWidth: width/7
                    cellHeight: height/6

                    interactive: false

                    model: ListModel{}
                    delegate: Item {
                        id: item_Day
                        width: grid_Content.cellWidth
                        height: grid_Content.cellHeight

                        property int subMonth: subMonthValue

                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: 1

                            radius: 4

                            color: ( item_Day.subMonth !== calendarItem.month ?
                                        "#33000000" : ( mouse_Day.containsMouse ? "#77ffffff" : "#33ffffff" ) )
                            Behavior on color {
                                ColorAnimation { duration: 120 }
                            }

                            scale: ( mouse_Day.containsMouse ? 1.2 : 1.0 )
                            Behavior on scale {
                                NumberAnimation { duration: 120 }
                            }

                            Text {
                                anchors.fill: parent

                                text: dayValue
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter

                                color: ( item_Day.subMonth !== calendarItem.month ?
                                            ( mouse_Day.containsMouse ? "white" : "black" ) : "black" )
                                Behavior on color {
                                    ColorAnimation { duration: 120 }
                                }
                                scale: ( mouse_Day.containsMouse ? 1.3 : 1.0 )
                                Behavior on scale {
                                    NumberAnimation { duration: 120 }
                                }
                            }

                            MouseArea {
                                id: mouse_Day
                                anchors.fill: parent

                                hoverEnabled: true
                            }
                        }
                    }
                }
            }
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

        color: "#440077ff"
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
            var newIndex = listView.currentIndex+1
            var year = listView.model.get( listView.currentIndex ).yearValue
            var month = listView.model.get( listView.currentIndex ).monthValue
            if ( month === 12 )
            {
                year++
                month = 1
            }
            else month++
            if ( newIndex === listView.count ||
                    listView.model.get( newIndex ).yearValue !== year ||
                    listView.model.get( newIndex ).monthValue !== month )
                listView.model.append(
                            { "yearValue": year, "monthValue": month } )
            if ( listView.count > 2 )
            {
                listView.model.remove( 0 )
                newIndex--
            }
            listView.currentIndex = newIndex
        }

        function prevMonth() {
            var year = listView.model.get( listView.currentIndex ).yearValue
            var month = listView.model.get( listView.currentIndex ).monthValue
            if ( month === 1 )
            {
                year--
                month = 12
            }
            else month--
            if ( listView.model.get( 0 ).yearValue !== year ||
                    listView.model.get( 0 ).monthValue !== month )
            {
                listView.model.insert( 0,
                                      { "yearValue": year, "monthValue": month } )
                listView.currentIndex++
                listView.positionViewAtIndex( 1, ListView.SnapPosition )
            }
            if ( listView.count > 2 )
                listView.model.remove( listView.count-1 )
            listView.currentIndex = 0
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
