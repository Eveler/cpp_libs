import QtQuick 2.1
import com.mihail.qmlcomponents 1.0

Item {
    id: calendar

    property int contentWidth: ( listView.currentItem ?
                                    listView.currentItem.width+(rect_ContentBackground.radius*2) : 0 )
    property int contentHeight: ( listView.currentItem ?
                                     headerContainer.height+listView.currentItem.height+
                                     (rect_ContentBackground.radius*2) : 0 )

    readonly property Component headerDelegate: component_Header
    readonly property Component monthDelegate: component_Month

    property bool fontBold
    property int fontPixelSize
    property string fontFamily

    readonly property int visibleYear: dataContainer.dateModel.get( listView.currentIndex ).yearValue
    readonly property int visibleMonth: dataContainer.dateModel.get( listView.currentIndex ).monthValue

    property date currentDate: minimumDate
    onCurrentDateChanged: {
        listView.setCurrentMonth( currentDate.getFullYear(), currentDate.getMonth()+1 )
    }

    property date minimumDate: "0001-01-01"

    Component {
        id: component_Header

        Item {
            id: headerItem
            height: text_Year.contentHeight+10

            ListView {
                id: list_Months
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.right: text_Year.left

                clip: true
                snapMode: ListView.SnapOneItem
                interactive: false

                property int currentMonth: headerItem.parent.visibleMonth
                onCurrentMonthChanged: {
                    if ( model.count === 0 )
                        for ( var month = 1; month < 13; month++ )
                            model.append( { "month": month } )
                    if ( firstStart )
                    {
                        currentIndex = -1
                        firstStart = false
                    }
                    currentIndex = currentMonth-1
                }

                property bool firstStart: true

                model: ListModel {}
                delegate: Item {
                    width: list_Months.width
                    height: list_Months.height

                    Text {
                        anchors.fill: parent

                        MDate {
                            id: dateInfo
                        }

                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter

                        text: dateInfo.longMonthName( month )

                        font.pixelSize: 13
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    onWheel: {
                        if ( wheel.angleDelta.y > 0 )
                            headerItem.parent.prevMonth()
                        else
                            headerItem.parent.nextMonth()
                    }
                }
            }

            Text {
                id: text_Year
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: contentWidth

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: headerItem.parent.visibleYear+" год"

                font.pixelSize: 13
            }
        }
    }

    Component {
        id: component_Month

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
                var selectIndex = -1
                var date = dateInfo.date( year, month, 1 )
                var date2 = dateInfo.addDays( date, -(dateInfo.dayOfWeak( date )) )
                for ( var day = 1; day<dateInfo.dayOfWeak( date ); day++ )
                {
                    date2 = dateInfo.addDays( date2, 1 )
                    if ( calendarItem.parent.parent.currentDate.toString() === date2.toString() )
                        selectIndex = grid_Content.model.count
                    grid_Content.model.append( { "dateValue": date2 } )
                }

                date = dateInfo.date( year, month, 1 )
                date = dateInfo.addDays( date, -1 )
                for ( var day = 0; day < dateInfo.daysInMonth( year, month ); day++ )
                {
                    date = dateInfo.addDays( date, 1 )
                    if ( calendarItem.parent.parent.currentDate.toString() === date.toString() )
                        selectIndex = grid_Content.model.count
                    grid_Content.model.append( { "dateValue": date } )
                }

                while ( grid_Content.model.count < 7*6 )
                {
                    date = dateInfo.addDays( date, 1 )
                    if ( calendarItem.parent.parent.currentDate.toString() === date.toString() )
                        selectIndex = grid_Content.model.count
                    grid_Content.model.append( { "dateValue": date } )
                }

                grid_Content.currentIndex = selectIndex
            }

            Rectangle {
                id: rect_LeftButton
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: 12

                radius: 3

                color: ( mouse_LeftButton.containsMouse ? "#99ff8833" : "#55ff8833" )
                Behavior on color {
                    ColorAnimation { duration: 120 }
                }

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

                radius: 3

                color: ( mouse_RightButton.containsMouse ? "#99ff8833" : "#55ff8833" )
                Behavior on color {
                    ColorAnimation { duration: 120 }
                }

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

                        property date currentDate: calendarItem.parent.parent.currentDate
                        onCurrentDateChanged: {
                            if ( currentDate.toString() === itemDate.toString() )
                                grid_Content.currentIndex = model.index
                        }
                        property date itemDate: dateValue
                        onItemDateChanged: {
                            if ( currentDate.toString() === itemDate.toString() )
                                grid_Content.currentIndex = model.index
                        }

                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: 1

                            radius: 4

                            color: ( item_Day.itemDate.getMonth()+1 !== calendarItem.month ?
                                        "#33000000" : ( mouse_Day.containsMouse ?
                                                           "#77ffffff" : "#33ffffff" ) )
                            Behavior on color {
                                ColorAnimation { duration: 120 }
                            }

                            scale: ( mouse_Day.containsMouse ? 1.2 : 1.0 )
                            Behavior on scale {
                                NumberAnimation { duration: 120 }
                            }

                            Text {
                                anchors.fill: parent

                                text: item_Day.itemDate.getDate()
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter

                                color: ( item_Day.itemDate.getMonth()+1 !== calendarItem.month ?
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

                                onClicked: {
                                    calendarItem.parent.parent.setCurrentDate( item_Day.itemDate )
                                }
                            }
                        }
                    }

                    highlight: Rectangle {
                        width: grid_Content.cellWidth; height: grid_Content.cellHeight
                        color: "white"; radius: 5
                        x: grid_Content.currentItem.x
                        y: grid_Content.currentItem.y
                        Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
                        Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
                    }
                }
            }
        }
    }

    QtObject {
        id: dataContainer

        property ListModel dateModel: ListModel {}
    }

    Rectangle {
        id: rect_ContentBackground
        anchors.fill: parent
        radius: 5

        color: "#440077ff"
    }


    Item {
        id: headerContainer
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: rect_ContentBackground.radius

        height: headerLoader.item.height

        property int visibleYear: calendar.visibleYear
        property int visibleMonth: calendar.visibleMonth

        Loader {
            id: headerLoader
            sourceComponent: component_Header

            onLoaded: {
                item.parent = headerContainer
                item.anchors.fill = headerContainer
            }
        }

        function prevMonth() { listView.prevMonth() }
        function nextMonth() { listView.nextMonth() }
    }

    ListView {
        id: listView
        anchors.fill: rect_ContentBackground
        anchors.margins: rect_ContentBackground.radius
        anchors.topMargin: headerContainer.height+anchors.margins

        clip: true

        model: dataContainer.dateModel
        delegate: calendar.monthDelegate

        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem

        interactive: false

        readonly property date currentDate: calendar.currentDate

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
            setCurrentMonth( year, month )
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
            setCurrentMonth( year, month )
        }

        function setCurrentMonth( year, month ) {
            var newIndex = listView.currentIndex
            if ( newIndex === -1 )
            {
                newIndex = 0
                listView.model.append( { "yearValue": year, "monthValue": month } )
                listView.currentIndex = newIndex
            }
            else
            {
                var oldYear = listView.model.get( listView.currentIndex ).yearValue
                var oldMonth = listView.model.get( listView.currentIndex ).monthValue
                if ( year < oldYear || ( year === oldYear && month < oldMonth ) )
                {
                    if ( newIndex === 0 )
                    {
                        listView.model.insert( newIndex, { "yearValue": year, "monthValue": month } )
                        listView.currentIndex++
                        listView.positionViewAtIndex( 1, ListView.SnapPosition )
                    }
                    else
                    {
                        newIndex--
                        listView.model.setProperty( newIndex, "yearValue", year )
                        listView.model.setProperty( newIndex, "monthValue", month )
                    }

                    if ( listView.count > 2 )
                        listView.model.remove( listView.count-1 )
                    listView.currentIndex = newIndex
                }
                else if ( year > oldYear || ( year === oldYear && month > oldMonth ) )
                {
                    newIndex++
                    if ( newIndex === listView.count )
                    {
                        listView.model.append( { "yearValue": year, "monthValue": month } )
                        if ( listView.count > 2 )
                        {
                            listView.model.remove( 0 )
                            newIndex--
                        }
                    }
                    else
                    {
                        listView.model.setProperty( newIndex, "yearValue", year )
                        listView.model.setProperty( newIndex, "monthValue", month )
                    }
                    listView.currentIndex = newIndex
                }
            }
        }

        function setCurrentDate( newDate ) {
            calendar.currentDate = newDate
        }
    }
}
