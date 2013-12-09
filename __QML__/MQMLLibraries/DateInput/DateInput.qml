import QtQuick 2.0
import extensions.mqmllibraries 1.0


TextInput {
    id: dateInput
    width: contentWidth
    height: contentHeight

    inputMask: "99.99.9999;_"
    onInputMaskChanged: {
        inputMask = "99.99.9999;_"
    }
    selectByMouse: true
    color: ( !obj_Information.showPlaceholder ? "black" : "transparent" )

    property date minimumDate: new Date( 100, 0, 1 )
    property date maximumDate: new Date( 7999, 11, 31 )
    property date enteredDate
    onEnteredDateChanged: {
        if ( enteredDate.toString() === "Invalid Date" ) enteredDate = minimumDate
        obj_Information.someDate = enteredDate
        obj_Information.resetDate()
    }
    property string placeholderText: ""

    Text {
        anchors.fill: parent

        text: dateInput.placeholderText
        visible: obj_Information.showPlaceholder
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "#ff222222"
    }

    onTextChanged: {
        var dateVals = text.split( "." )
        var resetDate = false
        obj_Information.day = dateVals[0]
        obj_Information.intMonth = dateVals[1]
        obj_Information.intMonth--
        obj_Information.month = obj_Information.intMonth
        if ( obj_Information.month > 11 )
        {
            resetDate = true
            obj_Information.month = 11
            obj_Information.intMonth = obj_Information.month
        }
        obj_Information.year = dateVals[2]
        if ( obj_Information.day > MQML.daysInMonth( obj_Information.year,
                                                    obj_Information.intMonth+1 ) )
        {
            resetDate = true
            obj_Information.day = MQML.daysInMonth( obj_Information.year,
                                                   obj_Information.intMonth+1 )
        }

        obj_Information.someDate = new Date( obj_Information.year,
                                            obj_Information.month,
                                            obj_Information.day, 0, 0, 0 )
        if ( enteredDate.toString() !== obj_Information.someDate.toString() )
            enteredDate = obj_Information.someDate
        else obj_Information.resetDate()
    }

    QtObject {
        id: obj_Information

        property date someDate
        property string day: ""
        property string month: ""
        property int intMonth: 0
        property string year: ""
        property bool completed: false

        property bool showPlaceholder: ( !dateInput.focus && dateInput.placeholderText.length > 0 &&
                                        dateInput.enteredDate.toString() ===
                                        dateInput.minimumDate.toString() )

        function resetDate()
        {
            day = someDate.getDate()
            while ( day.length < 2 ) day = "0"+day
            month = (someDate.getMonth()+1)
            while ( month.length < 2 ) month = "0"+month
            year = someDate.getFullYear()
            while ( year.length < 4 ) year = "0"+year
            var newDateText = day+"."+month+"."+year
            if ( dateInput.text !== newDateText )
            {
                var oldPos = cursorPosition
                dateInput.text = day+"."+month+"."+year
                cursorPosition = oldPos
            }
        }
    }

    Component.onCompleted: {
        enteredDate = minimumDate
    }
}
