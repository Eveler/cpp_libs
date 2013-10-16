#ifndef WIDGET_RECEPTIONDOCMANAGER_H
#define WIDGET_RECEPTIONDOCMANAGER_H

#include <QWidget>

#include "docmanager.h"
#include "requireddocs.h"


#define Doc_Pasport tr("Паспорт гражданина РФ")
#define Doc_Agreement tr( "Согласие на обработку ПДн" )
#define Doc_Trustee tr( "Доверенность" )
#define Doc_Warrant tr( "Расписка МФЦ" )
#define Doc_Application tr( "Заявление" )
#define Doc_AppRespite tr("Заявление о приостановке")
#define Doc_AppCancellation tr("Заявление об аннулировании")


namespace Ui {
  class Widget_ReceptionDocmanager;
}

class ReceptionDocmanager_P;

class Widget_ReceptionDocmanager : public QWidget
{
    Q_OBJECT


  public:
    explicit Widget_ReceptionDocmanager(QWidget *parent = 0);
    ~Widget_ReceptionDocmanager();

    void setDocmanager( Docmanager *docmanager );
    Docmanager * docmanager() const;
    void setDoctypes( const QStringList &doctypes );
    void setDeclar( const QVariant &id );
    void addClient( const QVariant &id, const QString &clientInfo );
    void addDocpaths( const QVariant &id );
    void setRequiredDocs( RequiredDocs *requiredDocs );

    void clear();


  signals:
    void newDocument( QString doctype );


  private:
    Ui::Widget_ReceptionDocmanager *ui;
    ReceptionDocmanager_P *p;


  private slots:
    void on_tView_Required_doubleClicked(const QModelIndex &index);
    void on_tView_New_doubleClicked(const QModelIndex &index);
    void on_tBt_Add_clicked();
};

#endif // WIDGET_RECEPTIONDOCMANAGER_H
