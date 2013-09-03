import QtQuick 2.1

import com.mihail.qmldocumentsystem 1.0


Image {
    id: qmlDocumentPage

    property QMLDocument document: null
    onDocumentChanged: updatePage()

    property int index: -1
    onIndexChanged: updatePage()

    onSourceChanged: source = dataSource.source

    QtObject {
        id: dataSource

        property string source: ""
        onSourceChanged: {
            qmlDocumentPage.source = dataSource.source
        }
    }

    Connections {
        target: document
        onPagesCountChanged: updatePage()
        onSourceChanged: updatePage()
    }

    function updatePage() {
        dataSource.source = ""
        if ( qmlDocumentPage.document !== null &&
                qmlDocumentPage.document.isValid() &&
                 qmlDocumentPage.index > -1 &&
                 qmlDocumentPage.index < qmlDocumentPage.document.pagesCount )
            dataSource.source = qmlDocumentPage.document.page( qmlDocumentPage.index )
        qmlDocumentPage.update()
    }
}
