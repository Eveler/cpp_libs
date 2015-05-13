#include "mreportviewer_p.h"
#include "ui_mreportviewer.h"

#include "mlogindialog.h"
#include "mdatedialog.h"

#include <QMessageBox>
#include <QDateTime>

#include <QDebug>


MReportViewer_P::MReportViewer_P( MReportViewer *parent ) :
  QObject(parent)
{
}

MReportViewer * MReportViewer_P::p_dptr() const
{
  return qobject_cast<MReportViewer *>( parent() );
}

bool MReportViewer_P::populate( MReportDocument *reportDocument ) const
{
  MReportDocument *errorDocument = reportDocument->errorDocument();
  if ( errorDocument != NULL )
  {
    QMessageBox::warning( p_dptr(), QString(), tr( "Ошибка в файле отчета.\n%1" ).arg(
                            errorDocument->lastError() ) );
    return false;
  }

  foreach ( MReportSource *reportSource, reportDocument->reportSources() )
  {
    MLoginDialog *logIn = new MLoginDialog( p_dptr() );
    logIn->setWindowTitle( "Авторизация" );
    bool authd = false;
    if ( !reportSource->userName().isEmpty() &&
         reportSource->password().isEmpty() )
      logIn->setNames( QStringList() << reportSource->userName() );
    authd = ( !reportSource->userName().isEmpty() &&
              !reportSource->password().isEmpty() );
    if ( authd ) authd = reportSource->check();
    while ( !authd )
    {
      if ( logIn->exec() == (int)QDialog::Rejected )
      {
        delete logIn;
        logIn = NULL;
        return false;
      }
      reportSource->setUserName( logIn->selectedName() );
      reportSource->setPassword( logIn->selectedPassword() );
      authd = reportSource->check();
      if ( !authd )
        QMessageBox::warning( p_dptr(), tr( "Ошибка авторизации" ), tr( "Неверный логин или пароль." ) );
    }
    delete logIn;
    logIn = NULL;
  }

  foreach ( MReportParameter *reportParemeter, reportDocument->reportParameters() )
  {
//    qDebug() << __LINE__ << ( reportParemeter->parameterType() == MReportParameter::PT_InputData );
    if ( reportParemeter->parameterType() == MReportParameter::PT_InputData )
    {
//      qDebug() << __LINE__ << ( reportParemeter->dataType() == MReportParameter::DT_Date ) <<
//                  reportParemeter->dataType();
//      qDebug() << __LINE__ << ( reportParemeter->data().isValid() ) <<
//                  reportParemeter->data();
      if ( reportParemeter->dataType() == MReportParameter::DT_Date &&
           !reportParemeter->data().isValid() )
      {
        MDateDialog *date = new MDateDialog( p_dptr() );
        date->setWindowTitle( reportParemeter->dialogTitle() );
        date->setText( reportParemeter->dialogText() );
        date->setDisplayFormat( tr( "dd.MM.yyyy" ) );
        if ( date->exec() == (int)QDialog::Rejected )
        {
          delete date;
          date = NULL;
          return false;
        }
        reportParemeter->setData( date->dateTime().date() );
      }
    }
  }

  return true;
}
