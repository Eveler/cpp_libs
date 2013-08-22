import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import com.mihail.qmlcomponents 1.0

ApplicationWindow {
    id: applicationWindow
    title: qsTr("Hello World")
    width: 500
    height: 300

    Image {
        anchors.fill: parent

        fillMode: Image.PreserveAspectCrop
        source: "under-construction-background-1584.png"
    }

    Item {
        anchors.fill: parent

        ComboObject {
            anchors.top: parent.top
            anchors.left: parent.left

            width: 300
            height: contentHeight

            fontBold: true
            fontPixelSize: 14
            fontFamily: "Pluto Bold"

            checkVisible: true

            Component.onCompleted: {
                append( "Доверенность" )
                append( "Заявление" )
                append( "Заявление о приостановке" )
                append( "Заявление об аннулировании" )
                append( "Паспорт гражданина РФ" )
            }
        }

        ComboObject {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left

            width: 300
            height: contentHeight

            fontBold: true
            fontPixelSize: 14
            fontFamily: "Pluto Bold"

            checkVisible: true

            Component.onCompleted: {
                append( "Доверенность" )
                append( "Заявление" )
                append( "Заявление о приостановке" )
                append( "Заявление об аннулировании" )
                append( "Паспорт гражданина РФ" )
            }
        }

        ComboObject {
            anchors.bottom: parent.bottom
            anchors.left: parent.left

            width: 300
            height: contentHeight

            fontBold: true
            fontPixelSize: 14
            fontFamily: "Pluto Bold"
            label: "Тип документа"
        }
    }
}
