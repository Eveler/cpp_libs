#ifndef DIALOG_SELECTDOCUMENT_H
#define DIALOG_SELECTDOCUMENT_H

#include <QDialog>

#include "docmanager.h"


namespace Ui {
  class Dialog_SelectDocument;
}

class Dialog_SelectDocument : public QDialog
{
    Q_OBJECT


  public:
    explicit Dialog_SelectDocument(QWidget *parent = 0);
    ~Dialog_SelectDocument();

    void setAutoExclusive( bool autoExclusive );
    bool autoExclusive() const;

    const QList<MFCDocumentInfo *> & exec(
        Docmanager *docmanager, DocumentsModel *documents , const QString &clientInfo = QString() );


  public:
    virtual int exec();


  private:
    Ui::Dialog_SelectDocument *ui;

    Docmanager *m__Docmanager;
    DocumentsModel *m__Documents;
    QList<MFCDocumentInfo *> m__SelectedDocs;
    bool m__AutoExclusive;


  private slots:
    void docsViewerChanged();
    void hRangeChanged( int min, int max );
    void vRangeChanged( int min, int max );
    void progress( qint64 cur, qint64 all );
    void activateSingleDocument();

    void on_tableView_doubleClicked(const QModelIndex &index);
};

#endif // DIALOG_SELECTDOCUMENT_H
