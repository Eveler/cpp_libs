#ifndef RECEPTIONDOCMANAGER_P_H
#define RECEPTIONDOCMANAGER_P_H

#include <QObject>

#include "widget_receptiondocmanager.h"
#include "booldelegate.h"
#include "toolbuttondelegate.h"


class Widget_ReceptionDocmanager;

class ReceptionDocmanager_P : public QObject
{
    Q_OBJECT
    friend class Widget_ReceptionDocmanager;


  public:


  signals:


  public slots:


  private:
    Docmanager *m__Docmanager;
    QStringList m__Doctypes;
    QMap<QString, QVariant> m__Clients;
    RequiredDocs *m__RequiredDocs;
    QString m__AppealNum;
    QDate m__AppealDate;
    QDate m__DeclarExpires;

    BoolDelegate *m__BoolDelegate;
    ToolButtonDelegate *m__ButtonDelegate;

    int reqSBVal;
    QModelIndex reqCurIndex;

    explicit ReceptionDocmanager_P( Widget_ReceptionDocmanager *parent );
    ~ReceptionDocmanager_P();

    Widget_ReceptionDocmanager * p_dptr() const;

    DocumentsModel * findDocuments( const QString &doctype ) const;
    DocumentsModel * findClientDocuments( QVariant clientId, const QStringList &doctypes ) const;

    bool newDocument(
        const QString &doctype, const QString &num = QString(),
        QDate date = QDate(), QDate expires = QDate() );

    void recalcNewDocuments( DocumentsModel *dm );
};

#endif // RECEPTIONDOCMANAGER_P_H
