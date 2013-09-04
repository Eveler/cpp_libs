import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0

import com.mihail.qmldocumentsystem 1.0


Item {
    id: pageTools
    readonly property ListModel pages: thumbnailsModel
    readonly property GridView thumbnails: thumbnailsView
    property bool updateOnCountChanged: true

    property QMLDocument document: null
    onDocumentChanged: {
        thumbnailsView.currentPage = -1
        thumbnailsModel.clear()
        if ( document === null ) return
        for ( var pageIndex = 0; pageIndex < document.pagesCount; pageIndex++ )
            thumbnailsModel.append( { "updatePage": false } )
        thumbnailsView.currentPage = 0
    }

    Connections {
        id: docConnections
        target: document
        property int newIndex: 0

        onPagesCountChanged: {
            if ( !updateOnCountChanged ) return
            thumbnailsView.currentPage = -1
            thumbnailsModel.clear()
            if ( document === null ) return
            for ( var pageIndex = 0; pageIndex < document.pagesCount; pageIndex++ )
                thumbnailsModel.append( { "updatePage": false } )
            if ( docConnections.newIndex >= document.pagesCount )
                docConnections.newIndex--
            thumbnailsView.currentPage = docConnections.newIndex
        }
    }

    Rectangle {
        id: viewBackground
        anchors.fill: parent

        clip: true
        color: "transparent"
        radius: 7
        border.width: 2
        border.color: "gray"

        ListModel {
            id: thumbnailsModel
        }
        Component {
            id: highlight
            Rectangle {
                width: thumbnailsView.cellWidth;
                height: thumbnailsView.cellHeight
                color: "lightsteelblue"; radius: 5
                visible: ( thumbnailsView.currentPage > -1 &&
                          thumbnailsView.count > 0 )
                x: ( thumbnailsView.currentItem !== null ? thumbnailsView.currentItem.x : 0 )
                Behavior on x {
                    SpringAnimation { spring: 3; damping: 0.2 }
                }
                y: ( thumbnailsView.currentItem !== null ? thumbnailsView.currentItem.y : 0 )
                Behavior on y {
                    SpringAnimation { spring: 3; damping: 0.2 }
                }
            }
        }
        GridView {
            id: thumbnailsView

            anchors.fill: parent
            anchors.margins: 2

            clip: true
            model: thumbnailsModel


            cellWidth: (thumbnailsView.width/2)
            cellHeight: cellWidth+25

            property int currentPage: -1

            delegate: Item {
                id: thumbnailContainer
                width: thumbnailsView.cellWidth
                height: thumbnailsView.cellHeight

                property bool updateThumbnail: updatePage
                onUpdateThumbnailChanged: {
                    if ( updateThumbnail )
                    {
                        thumbnail.updatePage()
                        thumbnailsModel.get( model.index ).updatePage = false
                        console.debug( "updated index: "+model.index )
                    }
                }

                Rectangle {
                    id: rect_Remove

                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.margins: 4

                    width: image_Remove.width+8
                    height: width

                    color: "#55ffffff"
                    radius: 4

                    opacity: ( thumbnailsView.currentPage === model.index &&
                              pageTools.document.removablePage( model.index ) ? 1.0 : 0.0 )
                    Behavior on opacity {
                        NumberAnimation { duration: 200 }
                    }

                    enabled: ( opacity > 0.0 )

                    Image {
                        id: image_Remove
                        anchors.centerIn: parent

                        scale: ( mouse_Remove.containsMouse ? 1.2 : 1.0 )
                        Behavior on scale {
                            NumberAnimation { duration: 150 }
                        }

                        width: 16
                        height: 16

                        source: "qrc:/images/cancel.png"
                    }

                    MouseArea {
                        id: mouse_Remove
                        anchors.fill: parent

                        hoverEnabled: true

                        onClicked: {
                            var idx = model.index
                            docConnections.newIndex = idx
                            thumbnailsModel.clear()
                            pageTools.document.removePage( idx )
                        }
                    }
                }

                Rectangle {
                    id: rect_Thumbnail
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.margins: 5
                    width: parent.width-(anchors.margins*2)
                    height: width

                    color: "transparent"

                    QMLDocumentPage {
                        id: thumbnail
                        anchors.centerIn: parent

                        smooth: false
                        asynchronous: true

                        property real delta: ( sourceSize.width > sourceSize.height ?
                                                  (parent.width/sourceSize.width) :
                                                  (parent.height/sourceSize.height) )

                        width: sourceSize.width*delta
                        height: sourceSize.height*delta

                        document: pageTools.document
                        index: model.index

                        MouseArea {
                            anchors.fill: parent

                            onClicked: thumbnailsView.currentPage = model.index
                        }

//                        Component.onCompleted: {
//                            var idx = model.index
//                            index = idx
//                        }
                    }
                }

                Rectangle {
                    anchors.centerIn: text_Thumbnail
                    width: text_Thumbnail.contentWidth+30
                    height: text_Thumbnail.contentHeight+4

                    radius: 4

                    border.color: "#ff5588bb"
                    color: "#ff77aaee"

                    opacity: ( thumbnailsView.currentPage === model.index ?
                                1.0 : 0.0 )
                    Behavior on opacity {
                        NumberAnimation { duration: 200 }
                    }
                }
                Text {
                    id: text_Thumbnail
                    anchors.top: rect_Thumbnail.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: 5

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: "Страница "+(model.index+1)+" из "+thumbnailsView.count
                    font.pixelSize: 14
                    color: ( thumbnailsView.currentPage === model.index ?
                                "black" : "white" )
                    Behavior on color {
                        ColorAnimation { duration: 200 }
                    }
                }
            }

            highlight: highlight
            highlightFollowsCurrentItem: false
            focus: true

//            remove: Transition {
//                NumberAnimation { properties: "scale"; duration: 200 }
//            }

//            removeDisplaced: Transition {
//                NumberAnimation { properties: "x,y"; duration: 200 }
//            }

            onCurrentPageChanged: {
                currentIndex = currentPage
            }

            onCurrentIndexChanged: {
                if ( currentIndex != currentPage )
                    currentPage = currentIndex
            }
        }
    }
}
