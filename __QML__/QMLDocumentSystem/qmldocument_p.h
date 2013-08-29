#ifndef QMLDOCUMENT_P_H
#define QMLDOCUMENT_P_H

#include "qmldocument.h"


class QMLDocument_P : public QObject
{
    Q_OBJECT
    friend class QMLDocument;

public:

signals:

public slots:


private:
    MFCDocument *m__Source;
    QList<MFCDocumentPage *> m__AddedPages;

    explicit QMLDocument_P(QMLDocument *parent);

    QMLDocument * p_dptr() const;
};

#endif // QMLDOCUMENT_P_H
