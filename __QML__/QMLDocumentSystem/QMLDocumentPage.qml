import QtQuick 2.1

import com.mihail.qmldocumentsystem 1.0


Item {
    id: qmlDocumentPage
    width: 100
    height: 100

    property QMLDocument document: null
    onDocumentChanged: image_Page.update()

    property int index: -1
    onIndexChanged: image_Page.update()

    readonly property Image image: image_Page

    QtObject {
        id: dataSource

        property string source: ""
        onSourceChanged: image_Page.source = dataSource.source
    }

    Image {
        id: image_Page
        anchors.fill: parent

        onSourceChanged: source = dataSource.source

        function update() {
            if ( qmlDocumentPage.document === null ) dataSource.source = ""
            else if ( qmlDocumentPage.index > -1 &&
                     qmlDocumentPage.index < qmlDocumentPage.document.pagesCount )
                dataSource.source = qmlDocumentPage.document.page( 0 )
        }
    }

    Connections {
        target: document
        onPagesCountChanged: image_Page.update()
    }
}
