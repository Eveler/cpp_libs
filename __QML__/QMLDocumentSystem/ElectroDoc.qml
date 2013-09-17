import QtQuick 2.1
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0

import com.mihail.qmlcomponents 1.0
import com.mihail.qmldocumentsystem 1.0


ApplicationWindow {
    id: applicationWindow
    minimumWidth: 800
    minimumHeight: 600
    opacity: Qt.application.active ? 1.0 : 0.8
    Behavior on opacity {
        NumberAnimation { duration: 200 }
    }

    title: pagesScroll.contentX+":"+pagesScroll.contentY

    readonly property alias contentEnabled: dataContiner.contentEnabled

    property alias state: dataContiner.electrodocState

    property string documentSource: ""
    onDocumentSourceChanged: dataContiner.document.source = documentSource

    signal accepted;
    signal rejected;

    onVisibleChanged: {
        if ( visible ) dataContiner.changeResultStates()
        else
        {
            if ( dataContiner.save )
            { // Запись новых данных в документ
                dataContiner.document.type = docType.text
                dataContiner.document.name = docName.text
                dataContiner.document.series = docSeries.text
                dataContiner.document.number = docNumber.text
                dataContiner.document.docdate = docDate.currentDate
                dataContiner.document.docexpires = docExpires.currentDate
            }
            else // Очистка новых данных в документе
                dataContiner.document.resetContent()

            if ( dataContiner.success )
                accepted() // Посылаем сигнал о подверждении ввода новых данных
            else
                rejected() // Посылаем сигнал об отмене
        }
    }

    Item {
        id: electrodocStates

        states: [
            State {
                name: "Read"
                PropertyChanges {
                    target: docOk
                    visible: true
                }
                PropertyChanges {
                    target: docSave
                    visible: false
                }
                PropertyChanges {
                    target: docChecked
                    visible: false
                }
                PropertyChanges {
                    target: docCancel
                    visible: false
                }
                PropertyChanges {
                    target: openFile
                    enabled: false
                }
                PropertyChanges {
                    target: openFile
                    enabled: false
                }
                PropertyChanges {
                    target: scannerOptions
                    enabled: false
                }
                PropertyChanges {
                    target: scannerStart
                    enabled: false
                }
                PropertyChanges {
                    target: docType
                    enabled: false
                }
                PropertyChanges {
                    target: docName
                    enabled: false
                }
                PropertyChanges {
                    target: docSeries
                    enabled: false
                }
                PropertyChanges {
                    target: docNumber
                    enabled: false
                }
                PropertyChanges {
                    target: docDates
                    enabled: false
                }
                PropertyChanges {
                    target: docAgency
                    enabled: false
                }
            },
            State {
                name: "Write"
                PropertyChanges {
                    target: docOk
                    visible: false
                }
                PropertyChanges {
                    target: docSave
                    visible: true
                }
                PropertyChanges {
                    target: docChecked
                    visible: false
                }
                PropertyChanges {
                    target: docCancel
                    visible: true
                }
                PropertyChanges {
                    target: openFile
                    enabled: true
                }
                PropertyChanges {
                    target: openFile
                    enabled: true
                }
                PropertyChanges {
                    target: scannerOptions
                    enabled: true
                }
                PropertyChanges {
                    target: scannerStart
                    enabled: true
                }
                PropertyChanges {
                    target: docType
                    enabled: true
                }
                PropertyChanges {
                    target: docName
                    enabled: true
                }
                PropertyChanges {
                    target: docSeries
                    enabled: true
                }
                PropertyChanges {
                    target: docNumber
                    enabled: true
                }
                PropertyChanges {
                    target: docDates
                    enabled: true
                }
                PropertyChanges {
                    target: docAgency
                    enabled: true
                }
            },
            State {
                name: "Check"
                PropertyChanges {
                    target: docOk
                    visible: false
                }
                PropertyChanges {
                    target: docSave
                    visible: false
                }
                PropertyChanges {
                    target: docChecked
                    visible: true
                }
                PropertyChanges {
                    target: docCancel
                    visible: true
                }
                PropertyChanges {
                    target: openFile
                    enabled: false
                }
                PropertyChanges {
                    target: openFile
                    enabled: false
                }
                PropertyChanges {
                    target: scannerOptions
                    enabled: false
                }
                PropertyChanges {
                    target: scannerStart
                    enabled: false
                }
                PropertyChanges {
                    target: docType
                    enabled: false
                }
                PropertyChanges {
                    target: docName
                    enabled: false
                }
                PropertyChanges {
                    target: docSeries
                    enabled: false
                }
                PropertyChanges {
                    target: docNumber
                    enabled: false
                }
                PropertyChanges {
                    target: docDates
                    enabled: false
                }
                PropertyChanges {
                    target: docAgency
                    enabled: false
                }
            }
        ]
    }

    QtObject {
        id: dataContiner

        property int electrodocState: -1
        onElectrodocStateChanged: {
            if ( electrodocState ===  MElectroDoc.Write ) electrodocStates.state = "Write"
            else if ( electrodocState ===  MElectroDoc.Check ) electrodocStates.state = "Check"
            else electrodocStates.state = "Read"

            changeResultStates()
        }

        property bool contentEnabled: false

        property bool reloaded: false
        property QMLDocument document: QMLDocument {
            onSourceChanged: {
                dataContiner.reloaded = true
            }

            onPagesCountChanged: {
                if ( dataContiner.reloaded )
                {
                    pageTools.document = null
                    if ( dataContiner.document.pagesCount === 0 ) return
                    dataContiner.reloaded = false
                    dataContiner.contentEnabled = dataContiner.document.isValid()
                    pageTools.document = dataContiner.document

                    docType.setText( dataContiner.document.type )
                    docName.setText( dataContiner.document.name )
                    docSeries.setText( dataContiner.document.series )
                    docNumber.setText( dataContiner.document.number )
                    docDate.currentDate = dataContiner.document.docdate
                    docExpires.currentDate = dataContiner.document.docexpires
                }
            }
        }

        property bool save: false
        property bool success: false

        function changeResultStates() {
            dataContiner.save = false
            if ( electrodocState === MElectroDoc.Read )
                dataContiner.success = true
            else
                dataContiner.success = false
        }
    }

    toolBar: Rectangle {
        id: mainTools
        width: parent.width
        height: 70

        enabled: dataContiner.contentEnabled

        border.color: "gray"
        clip: true

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ffaaaaaa" }
            GradientStop { position: 0.49; color: "#ff878787" }
            GradientStop { position: 0.5; color: "#ff787878" }
            GradientStop { position: 1.0; color: "#ff999999" }
        }

        ToolBarButton {
            id: openFile
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 5
            implicitWidth: 100

            text: qsTr( "Открыть\nиз файла" )

            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                selectMultiple: true
                nameFilters: [ "Файлы изображений (*.jpg *.png)" ]

                onAccepted: {
                    pageTools.updateOnCountChanged = false
                    for ( var urlIndex = 0; urlIndex < fileDialog.fileUrls.length; urlIndex++ )
                    {
                        if ( urlIndex+1 === fileDialog.fileUrls.length )
                            pageTools.updateOnCountChanged = true
                        dataContiner.document.addPage( fileDialog.fileUrls[urlIndex] )
                    }
                }
            }

            onClicked: fileDialog.visible = true
        }

        Rectangle {
            id: spliter_1
            anchors.top: parent.top
            anchors.left: openFile.right
            anchors.bottom: parent.bottom
            anchors.margins: 5
            width: 1
            color: "gray"
        }

        ToolBarButton {
            id: scannerOptions
            anchors.top: parent.top
            anchors.left: spliter_1.right
            anchors.bottom: parent.bottom
            anchors.margins: 5
            implicitWidth: 100

            text: qsTr( "Настройки\nсканера" )

            onClicked: dataContiner.document.configureScanner()
        }

        ToolBarButton {
            id: scannerStart
            anchors.top: parent.top
            anchors.left: scannerOptions.right
            anchors.bottom: parent.bottom
            anchors.margins: 5
            implicitWidth: 120

            text: qsTr( "Сканировать" )

            onClicked: dataContiner.document.scanPage()
        }

        Rectangle {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: ( docOk.visible ? docOk.width+(docOk.anchors.margins*2) : 0 )+
                   ( docSave.visible ? docSave.width+(docSave.anchors.margins*2) : 0 )+
                   ( docChecked.visible ? docChecked.width+(docChecked.anchors.margins*2) : 0 )+
                   ( docCancel.visible ? docCancel.width+(docCancel.anchors.margins*2) : 0 )

            color: "#55009900"

            Rectangle {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.leftMargin: 1
                width: 1
                color: "gray"
            }

            ToolBarButton {
                id: docOk
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 5
                implicitWidth: 120

                visible: false

                text: qsTr( "OK" )

                onClicked: {
                    dataContiner.save = false
                    dataContiner.success = true
                    applicationWindow.close()
                }
            }

            ToolBarButton {
                id: docSave
                anchors.top: parent.top
                anchors.right: docCancel.left
                anchors.bottom: parent.bottom
                anchors.margins: 5
                implicitWidth: 120

                visible: false

                text: qsTr( "Сохранить" )

                onClicked: {
                    dataContiner.save = true
                    dataContiner.success = true
                    applicationWindow.close()
                }
            }

            ToolBarButton {
                id: docChecked
                anchors.top: parent.top
                anchors.right: docCancel.left
                anchors.bottom: parent.bottom
                anchors.margins: 5
                implicitWidth: 120

                visible: false

                text: qsTr( "Все верно" )

                onClicked: {
                    dataContiner.save = false
                    dataContiner.success = true
                    applicationWindow.close()
                }
            }

            ToolBarButton {
                id: docCancel
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 5
                implicitWidth: 120

                visible: false

                text: qsTr( "Отмена" )

                onClicked: {
                    dataContiner.save = false
                    dataContiner.success = false
                    applicationWindow.close()
                }
            }
        }

        Rectangle {
            anchors.fill: parent

            visible: !dataContiner.contentEnabled

            color: "#77000000"
        }
    }

    Image {
        id: thumbnailsBackground
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: ( Math.floor( toolsContainer.width ) > toolsContainer.closedWidth ?
                    toolsContainer.width+(toolsContainer.anchors.leftMargin*2) : 0 )

        source: "qrc:/images/wg_carbon_fiber_7.png"
        fillMode: Image.TileHorizontally
    }

    Image {
        id: zoomToolsBackground
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 40

        source: "qrc:/images/wg_carbon_fiber_7.png"
        fillMode: Image.TileHorizontally
    }

    Rectangle {
        id: mainContainer
        anchors.top: parent.top
        anchors.left: thumbnailsBackground.right
        anchors.bottom: parent.bottom
        anchors.right: zoomTools.left

        enabled: dataContiner.contentEnabled

        readonly property int borderWidth: 40

        Image {
            id: mainBackground
            anchors.fill: parent

            source: "qrc:/images/wg_carbon_fiber_6.png"
            fillMode: Image.Tile
        }
        Image {
            id: mainBorderLeft
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.borderWidth
            opacity: 0.3

            source: "qrc:/images/under_construction_border.png"
        }
        Image {
            id: mainBorderRight
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.borderWidth
            opacity: 0.3
            mirror: true

            source: "qrc:/images/under_construction_border.png"
        }
    }

    Item {
        anchors.fill: mainContainer
        clip: true

        enabled: dataContiner.contentEnabled

        Flickable {
            id: pagesScroll
            anchors.centerIn: parent
            width: ( contentWidth < (mainContainer.width-(mainContainer.borderWidth*2)) ?
                        contentWidth : (mainContainer.width-(mainContainer.borderWidth*2)) )
            height: ( contentHeight < mainContainer.height ?
                         contentHeight : mainContainer.height )

            clip: true

            contentWidth: page.width*page.scale; contentHeight: page.height*page.scale

            QMLDocumentPage {
                id: page
                anchors.centerIn: parent
                scale: zoomTools.scaleValue

                document: dataContiner.document
            }

            Item {
                id: animationScroll
                NumberAnimation {
                    id: hideAnimation
                    target: page
                    property: "opacity"
                    duration: 200
                    from: 1.0; to: 0.0

                    onStopped: {
                        page.index = pageTools.thumbnails.currentPage
                        toolBarInfo.text = "Страница "+(pageTools.thumbnails.currentPage+1)+
                                " из "+pageTools.thumbnails.count
                        showAnimation.start()
                    }
                }
                NumberAnimation {
                    id: showAnimation
                    target: page
                    property: "opacity"
                    duration: 200
                    from: 0.0; to: 1.0
                }

                function start() { hideAnimation.start() }
            }
        }

        Rectangle {
            id: toolBarInfoPanel

            clip: true
            radius: 8
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: mainContainer.borderWidth+10
            width: toolBarInfo.width+(toolBarInfo.anchors.rightMargin*2)
            height: toolBarInfo.height+(toolBarInfo.anchors.topMargin*2)

            opacity: ( hideToolsContainer.checked ? 0.0 : 0.5 )
            Behavior on opacity {
                NumberAnimation { duration: 200 }
            }

            color: "lightgray"
        }
        Text {
            id: toolBarInfo

            anchors.top: toolBarInfoPanel.top
            anchors.topMargin: 10
            anchors.right: toolBarInfoPanel.right
            anchors.rightMargin: 50

            opacity: ( hideToolsContainer.checked ? 0.0 : 1.0 )
            Behavior on opacity {
                NumberAnimation { duration: 200 }
            }

            verticalAlignment: Text.AlignVCenter
            font.bold: true
            font.pixelSize: 14
        }

        BorderButton {
            id: prevPage
            anchors.top: parent.top
            anchors.topMargin: 100
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            width: mainContainer.borderWidth

            text: ( pageTools.thumbnails.currentPage-1 > -1 ?
                       "Предыдущая страница" : "К последней странице" )
            buttonRotation: 270

            imageSource: "qrc:/images/uparrow_inv.png"

            onClicked: {
                if ( pageTools.thumbnails.count > 0 )
                {
                    if ( pageTools.thumbnails.currentPage-1 > -1 )
                        pageTools.thumbnails.currentPage--
                    else pageTools.thumbnails.currentPage = pageTools.thumbnails.count-1
                }
            }
        }

        BorderButton {
            id: nextPage
            anchors.top: parent.top
            anchors.topMargin: 100
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            anchors.right: parent.right
            width: mainContainer.borderWidth

            text: ( pageTools.thumbnails.currentPage+1 < pageTools.thumbnails.count ?
                       "Следующая страница" : "К первой странице" )
            buttonRotation: 90
            imageSource: "qrc:/images/uparrow_inv.png"

            onClicked: {
                if ( pageTools.thumbnails.count > 0 )
                {
                    if ( pageTools.thumbnails.currentPage+1 < pageTools.thumbnails.count )
                        pageTools.thumbnails.currentPage++
                    else pageTools.thumbnails.currentPage = 0
                }
            }
        }
    }

    ToolsContainer {
        id: toolsContainer
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        enabled: dataContiner.contentEnabled && hideToolsContainer.checked

        closedWidth: hideToolsContainer.width
        closedHeight: hideToolsContainer.height
        openedWidth: 500
        openedHeight: mainContainer.height-(anchors.leftMargin*2)

        state: ( hideToolsContainer.checked ? "maximized" : "minimized" )

        Item {
            id: detailsTool
            anchors.fill: parent
            anchors.bottomMargin: hideToolsContainer.height
            anchors.margins: 5

            z: 1

            Column {
                anchors.fill: parent
                spacing: 5

                ComboObject {
                    id: docType
                    width: parent.width
                    height: contentHeight

                    label: "Тип документа"
                    fontBold: true
                    fontPixelSize: 14
                    checkVisible: true
                }

                ComboObject {
                    id: docName
                    width: parent.width
                    height: contentHeight

                    label: "Наименование документа"
                    fontBold: true
                    fontPixelSize: 14
                }

                Row {
                    id: serNum
                    Layout.fillWidth: true
                    width: parent.width
                    height: childrenRect.height
                    spacing: 5

                    ComboObject {
                        id: docSeries
                        width: parent.width*0.3
                        height: contentHeight

                        label: "Серия"
                        fontBold: true
                        fontPixelSize: 14
                    }

                    ComboObject {
                        id: docNumber
                        width: (parent.width*0.7)-parent.spacing
                        height: contentHeight

                        label: "Номер"
                        fontBold: true
                        fontPixelSize: 14
                    }
                }

                Row {
                    id: docDates
                    width: parent.width
                    height: docDate.height
                    spacing: 5
                    z: ( docType.poppedup ? 0 : 1 )

                    DateButton {
                        id: docDate
                        width: parent.width*0.5
                        height: contentHeight

                        label: "Дата выдачи"
                        fontBold: true
                        fontPixelSize: 14
                        checkVisible: true

                        minimumDate: "2008-01-01"
                        replacementText: " "
                    }

                    DateButton {
                        id: docExpires
                        width: (parent.width*0.5)-parent.spacing
                        height: contentHeight

                        label: "действителен до"
                        fontBold: true
                        fontPixelSize: 14

                        minimumDate: "2008-01-01"
                        replacementText: " "
                    }
                }

                ComboObject {
                    id: docAgency
                    width: parent.width
                    height: contentHeight

                    label: "Наименование выдавшего органа"
                    fontBold: true
                    fontPixelSize: 14
                }

                PageTools {
                    id: pageTools
                    width: parent.width
                    height: parent.height-(docType.height+5+docName.height+5+
                                           serNum.height+5+docDates.height+5+
                                           docAgency.height+5)

                    Connections {
                        target: pageTools.thumbnails

                        onCurrentIndexChanged: {
                            animationScroll.start()
                        }
                    }
                }
            }
        }
    }

    ZoomTools {
        id: zoomTools
        anchors.fill: zoomToolsBackground
        anchors.margins: 3

        enabled: dataContiner.contentEnabled
    }

    Button {
        id: hideToolsContainer
        anchors.right: toolsContainer.right
        anchors.bottom: toolsContainer.bottom
        width: 50
        height: 50

        enabled: dataContiner.contentEnabled

        scale: ( hovered ? 1.2 : 1.0 )
        Behavior on scale {
            NumberAnimation { duration: 200 }
        }

        checkable: true
        checked: true

        style: ButtonStyle {
            background: Rectangle {
                color: "transparent"

                Image {
                    anchors.fill: parent
                    source: "qrc:/images/arrow_down_left.png"
                    rotation: ( control.checked ? 90 : 270 )
                    Behavior on rotation {
                        NumberAnimation { duration: 200 }
                    }
                    opacity: 0.7
                }
            }
        }
    }
    Glow {
        anchors.fill: hideToolsContainer
        enabled: dataContiner.contentEnabled
        radius: 16
        samples: 16
        scale: hideToolsContainer.scale
        source: hideToolsContainer
        color: ( hideToolsContainer.hovered ? "cyan" : "white" )
        Behavior on color {
            ColorAnimation { duration: 200 }
        }
    }

    Rectangle {
        anchors.fill: parent

        color: ( dataContiner.contentEnabled ? "transparent" : "#77999999" )
        Behavior on color {
            ColorAnimation { duration: 200 }
        }
    }

    Component.onCompleted: {
        if ( dataContiner.electrodocState === -1 ) dataContiner.electrodocState = MElectroDoc.Read
    }
}
