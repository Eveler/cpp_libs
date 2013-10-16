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
    BoolDelegate *m__BoolDelegate;
    ToolButtonDelegate *m__ButtonDelegate;

    explicit ReceptionDocmanager_P( Widget_ReceptionDocmanager *parent );
    ~ReceptionDocmanager_P();

    DocumentsModel * findDocuments( const QString &doctype ) const;
};

#endif // RECEPTIONDOCMANAGER_P_H
