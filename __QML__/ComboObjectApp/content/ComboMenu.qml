import QtQuick 2.1
import QtGraphicalEffects 1.0

Item {
    id: comboMenu
    width: ( poppedup ? poppedupWidth : 0 )
    Behavior on width {
        SpringAnimation { spring: 2; damping: 0.2 }
    }
    height: ( listView.currentItem && poppedup ?
                 ( visibleItemsCount < maxVisibleItemsCount ?
                      listView.currentItem.height*visibleItemsCount :
                      listView.currentItem.height*maxVisibleItemsCount ) : 0 )
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
    readonly property Component delegate: ( control && control.delegate ? control.delegate : menuDelegate )
    readonly property int visibleItemsCount: dataContainer.visibleModel.count

    property bool fontBold
    property int fontPixelSize
    property string fontFamily

    property bool poppedup: false
    property int poppedupWidth: 100

    readonly property int currentIndex: dataContainer.currentIndex

    Component {
        id: menuDelegate

        Rectangle {
            id: menuItem
            width: parent.width
            height: text_Item.contentHeight+(text_Item.anchors.margins*2)

            color: ( mouse_Item.containsMouse ? "#33ffffff" : "transparent" )
            Behavior on color {
                ColorAnimation { duration: 150 }
            }

            Text {
                id: text_Item
                anchors.fill: parent
                anchors.margins: 2

                text: element_Text
                color: "white"
                font.bold: comboMenu.fontBold
                font.pixelSize: comboMenu.fontPixelSize
                font.family: comboMenu.fontFamily
            }

            MouseArea {
                id: mouse_Item
                anchors.fill: parent

                hoverEnabled: true

                onClicked: menuItem.parent.parent.select( model.index )
            }

            Rectangle {
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                height: 1

                visible: ( model.index > 0 )

                color: "#99888888"
            }
        }
    }

    QtObject {
        id: dataContainer

        property int currentIndex: -1

        property ListModel listModel: ListModel {
            ListElement {
                element_Text: "Доверенность"
            }
            ListElement {
                element_Text: "Заявление"
            }
            ListElement {
                element_Text: "Заявление о приостановке"
            }
            ListElement {
                element_Text: "Заявление об аннулировании"
            }
            ListElement {
                element_Text: "Паспорт гражданина РФ"
            }
            ListElement {
                element_Text: "Справка"
            }
        }

        property ListModel visibleModel: ListModel {
            ListElement {
                element_Text: "Доверенность"
            }
            ListElement {
                element_Text: "Заявление"
            }
            ListElement {
                element_Text: "Заявление о приостановке"
            }
            ListElement {
                element_Text: "Заявление об аннулировании"
            }
            ListElement {
                element_Text: "Паспорт гражданина РФ"
            }
            ListElement {
                element_Text: "Справка"
            }
        }

        function append( model, value ) {
            model.append( { "element_Text": value } )
        }
    }

    RectangularGlow {
        id: effect
        anchors.fill: rect_ContentBackground
        glowRadius: 5
        spread: 0.2
        color: "#66000000"
        visible: comboMenu.poppedup
        cornerRadius: rect_ContentBackground.radius + glowRadius
    }
    Rectangle {
        id: rect_ContentBackground
        anchors.fill: parent

        color: "#66000000"
    }


    ListView {
        id: listView
        anchors.fill: parent

        clip: true

        model: dataContainer.visibleModel
        delegate: comboMenu.delegate

        function select( index ) {
            dataContainer.currentIndex = -1
            dataContainer.currentIndex = index
        }
    }

    function clear() {
        dataContainer.listModel.clear()
        dataContainer.visibleModel.clear()
    }

    function append( value ) {
        dataContainer.append( dataContainer.listModel, value )
        dataContainer.append( dataContainer.visibleModel, value )
    }

    function find( value ) {
        dataContainer.visibleModel.clear()
        var result = -1;
        for ( var index = 0; index < dataContainer.listModel.count; index++ )
        {
            var modelText = dataContainer.listModel.get( index ).element_Text
            if ( modelText.toUpperCase().search( value.toUpperCase() ) === 0 )
            {
                if ( result === -1 )
                    result = dataContainer.visibleModel.count
                dataContainer.append( dataContainer.visibleModel, modelText )
            }
        }
        return result
    }

    function value( index ) {
        if ( index < 0 || index >= visibleItemsCount ) return ""

        return dataContainer.visibleModel.get( index ).element_Text
    }

    function select( index ) {
        if ( index < 0 || index >= visibleItemsCount ) return

        listView.select( index )
    }
}