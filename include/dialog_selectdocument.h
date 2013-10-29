#ifndef DIALOG_SELECTDOCUMENT_H
#define DIALOG_SELECTDOCUMENT_H

#include <QDialog>

#include "export/docmanagerwidgets_export_lib.h"
#include "docmanager.h"


namespace Ui {
  class Dialog_SelectDocument;
}

class EXPORT_DOCMANAGERWIDGETS Dialog_SelectDocument : public QDialog
{
    Q_OBJECT


  public:
    explicit Dialog_SelectDocument(QWidget *parent = 0);
    ~Dialog_SelectDocument();

    void setAutoExclusive( bool autoExclusive );
    bool autoExclusive() const;

    void setOnlyAllSelect( bool onlyAllSelect );
    bool onlyAllSelect() const;

    void setOriginalsCopies( bool originalsCopies );
    bool originalsCopies() const;

    void setCreatableDoctypes( const QStringList &doctypes );

    const QList<MFCDocumentInfo *> & exec(
        const Docmanager *docmanager, DocumentsModel *documents,
        const QString &clientInfo = QString() );


  public:
    virtual int exec();


  private:
    Ui::Dialog_SelectDocument *ui;

    const Docmanager *m__Docmanager;
    DocumentsModel *m__Documents;
    QList<MFCDocumentInfo *> m__SelectedDocs;
    QList<MFCDocumentInfo *> m__CreatedDocs;
    bool m__AutoExclusive;
    bool m__OnlyAllSelect;
    bool m__OriginalsCopies;

    bool isCompleted() const;


  private slots:
    void docsViewerChanged();
    void hRangeChanged( int min, int max );
    void vRangeChanged( int min, int max );
    void progress( qint64 cur, qint64 all );
    void activateSingleDocument();
    void docmanagerError( QString error );

    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_tBt_Create_triggered(QAction *arg1);
};

#endif // DIALOG_SELECTDOCUMENT_H
