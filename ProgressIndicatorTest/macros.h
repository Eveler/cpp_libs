#ifndef MACROS_H
#define MACROS_H

#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QTime>
#include <QVariant>
#include <QObject>
#include <QWidget>
#include <QDir>
#include <QFile>
#include <QApplication>
#include <QAbstractItemModel>
#include <QTabWidget>


#define DPRINT(msg, application) { qDebug() << __FILE__ << "(" << __LINE__ << ") [" << \
  QTime::currentTime().toString( "hh:mm:ss.zzz" ) << "]:" << msg; \
  if ( !QDir( "./" ).exists( qAppName()+"_logger" ) ) QDir( "./" ).mkdir( qAppName()+"_logger" ); \
  QString logFile="./"+qAppName()+"_logger/logfile.log"; \
  QFile outFile( logFile ); \
  QString prefix="./"+qAppName()+"_logger/logfile"; \
  if ( !application->property( "file_created" ).isValid() ){\
    if( outFile.exists() ) { \
      for(int i=29;i>0;i--){ \
        QFile::rename(prefix+"_"+QString::number(i)+".log", \
                      prefix+"_"+QString::number(i+1)+".log"); } \
      QFile::remove(prefix+"_30.log"); \
      outFile.rename(prefix+"_1.log"); \
      outFile.setFileName(prefix+".log"); } \
    application->setProperty( "file_created", true ); }\
  if(!outFile.open(QFile::Append | QFile::WriteOnly | QFile::Text)){ \
    fprintf(stderr, "Warning: Error openning log file %s\n", \
            qPrintable(outFile.fileName())); \
    outFile.close(); } \
  else { \
    QDebug out( &outFile ); \
    out << __FILE__ << "(" << __LINE__ << ") [" << \
      QTime::currentTime().toString( "hh:mm:ss.zzz" ) << "]:" << msg << "\n"; \
    outFile.close(); } }



#define ADD_AGREEMENT_REP( clientName, clientAddress, otherTables ) \
{report->addReport("Согласие ПДн");\
/*QString fio=ui->lEdit_ClientSurname->text().mid(0,1).toUpper();\
fio+=ui->lEdit_ClientSurname->text().mid(1).toLower();\
fio+=" "+ui->lEdit_ClientFirstname->text().mid(0,1).toUpper();\
fio+=ui->lEdit_ClientFirstname->text().mid(1).toLower();\
fio+=" "+ui->lEdit_ClientLastname->text().mid(0,1).toUpper();\
fio+=ui->lEdit_ClientLastname->text().mid(1).toLower();\*/\
  QString clientFio = clientName; \
  report->addReportParam( "Согласие ПДн", "$FIO", "text",clientFio ); \
  report->addReportParam( "Согласие ПДн", "$ADDR", "text", \
                          clientAddress ); \
  QAbstractItemModel *abs_Mdl = fmDoclist->getTable( Doclist::DeclarDocs )->model(); \
  QList<QTableWidgetItem *> items = fmDoclist->getTable( Doclist::DeclarDocs )->findItems( \
        "Паспорт гражданина РФ", Qt::MatchFixedString ); \
  int uuid_Idx = -1; \
  for ( int cIdx = 0; cIdx < abs_Mdl->columnCount(); cIdx++ ) \
    if ( abs_Mdl->headerData( cIdx, Qt::Horizontal ).toString() == "UUID" ) uuid_Idx = cIdx; \
  if ( items.count() > 0 && uuid_Idx > -1 ) { \
      QString param_value = abs_Mdl->index( items.first()->row(), uuid_Idx ).data().toString(); \
      QHash<QString, QVariant> doc = fmDoclist->getDocsData().value( QUuid( param_value ) ); \
      report->addReportParam("Согласие ПДн","$SER","text",\
                            doc.value( "doc_series" ).toString()); \
      report->addReportParam("Согласие ПДн","$NUM","text",\
                            doc.value( "doc_number" ).toString()); \
      param_value = doc.value( "doc_agency" ).toString(); \
      DPRINT( param_value, qApp );\
      QList<MFCItem> items = otherTables.value( "docagency" ).findItemsByColName( \
      param_value.toInt(), tr( "cod" ) ); \
      DPRINT( items.count(), qApp );\
      if ( items.count() > 0 ) param_value = otherTables.value( "docagency" ).data( \
        items.first().row(), tr( "name" ) ).toString(); \
      else param_value = ""; \
      report->addReportParam("Согласие ПДн","$WHOM","text",\
                            param_value); \
      QDate docDate = doc.value( "doc_date" ).toDate(); \
      report->addReportParam("Согласие ПДн","$PSDAY","text",\
        docDate.toString( "dd" )); \
      report->addReportParam("Согласие ПДн","$PSMONTH","text",\
        docDate.toString( "MM" )); \
      report->addReportParam("Согласие ПДн","$PSYEAR","text",\
        docDate.toString( "yyyy" )); } \
report->addReportParam("Согласие ПДн","$PDAY","text",\
                      QDate::currentDate().toString("dd"));\
report->addReportParam(\
      "Согласие ПДн","$PMONTH","text",\
      monthNameConverter(QDate::currentDate().toString("MMMM")).toLower());\
report->addReportParam("Согласие ПДн","$PYEAR","text",\
                      QDate::currentDate().toString("yyyy"));\
  DPRINT( clientFio, qApp ); \
  QString initials=clientFio.split( " " ).value( 0 ).mid(0,1).toUpper();\
  initials+=clientFio.split( " " ).value( 0 ).mid(1).toLower();\
initials+=" "+clientFio.split( " " ).value( 1 ).mid(0,1).toUpper();\
initials+=". "+clientFio.split( " " ).value( 2 ).mid(0,1).toUpper();\
initials+=(clientFio.split( " " ).value( 2 ).length()>0?".":"");\
report->addReportParam("Согласие ПДн","$INITIALS","text",initials);}

#define ADD_DECLARATION_REP( otherTables ) \
{   if ( !otherTables.contains( "service_requests" ) || \
        !otherTables.contains( "report_parameters" ) || \
        !otherTables.contains( "docagency" ) ) \
        { report->deleteLater(); return; } \
    MFCTable &service_requests = otherTables["service_requests"]; \
    MFCTable &report_parameters = otherTables["report_parameters"]; \
    QAbstractItemModel *abs_Mdl = fmDoclist->getTable( Doclist::DeclarDocs )->model(); \
    QList<QTableWidgetItem *> items = fmDoclist->getTable( Doclist::DeclarDocs )->findItems( \
          "Паспорт гражданина РФ", Qt::MatchFixedString ); \
    int uuid_Idx = -1; \
    for ( int cIdx = 0; cIdx < abs_Mdl->columnCount(); cIdx++ ) \
    if ( abs_Mdl->headerData( cIdx, Qt::Horizontal ).toString() == "UUID" ) uuid_Idx = cIdx; \
    if ( service_requests.rowCount() == 0 ) { \
    QMessageBox::warning( this, "Ошибка", \
                       "Для данной услуги не определены параметры заявления!\n" \
                       "Сообщите в отдел АСУ по какой услуге " \
                       "не заполнен справочник для запуска заявления." ); \
    report->deleteLater(); return; } \
    for ( int i = 0; i < service_requests.rowCount(); i++ ) { \
    if ( !service_requests.data( i, tr( "req_name" ) ).isNull() ) { \
    QString req_name = service_requests.data( \
         i, tr( "req_name" ) ).toString(); \
    DPRINT( "req_name" << req_name, qApp ); \
    report->addReport( req_name ); \
    for ( int j = 0; j < report_parameters.rowCount(); j++ ) { \
     QString param_name = report_parameters.data( \
           j, report_parameters.findColumn( "param_name" ) ).toString(); \
     DPRINT( "param_name" << param_name, qApp ); \
     QString param_wgt_name = report_parameters.data( \
           j, report_parameters.findColumn( "param_wgt_name" ) ).toString(); \
     QString param_value; \
     DPRINT( "param_wgt_name" << param_wgt_name, qApp ); \
     if ( param_wgt_name.length() == 0 ) { \
       param_value = report_parameters.data( \
             j, report_parameters.findColumn( "param_value" ) ).toString(); \
       DPRINT( "param_value" << param_value, qApp ); } else { \
       if ( report_parameters.data( \
              j, report_parameters.findColumn( "wgt_property" ) ).toString().length() == 0 ) continue; \
       QWidget *wgt = qFindChild<QWidget *>( this, param_wgt_name ); \
       if ( wgt != 0 ) \
         param_value = wgt->property( report_parameters.data( \
                                        j, report_parameters.findColumn( "wgt_property" ) \
                                        ).toString().toLatin1() ).toString(); } \
     if ( param_name == "$DATE" ) \
       param_value = QDate::currentDate().toString( "dd.MM.yyyy" ); \
     if ( param_name == "$NOW" ) \
       param_value = QDateTime::currentDateTime().toString( "dd.MM.yyyy hh:mm:ss" ); \
     if ( param_name == "$PSER" ) { \
       if ( items.count() > 0 && uuid_Idx > -1 ) { \
         param_value = abs_Mdl->index( items.first()->row(), uuid_Idx ).data().toString(); \
         QHash<QString, QVariant> doc = fmDoclist->getDocsData().value( QUuid( param_value ) ); \
         param_value = doc.value( "doc_series" ).toString(); } } \
     if ( param_name == "$PNUM" ) { \
       if ( items.count() > 0 && uuid_Idx > -1 ) { \
         param_value = abs_Mdl->index( items.first()->row(), uuid_Idx ).data().toString(); \
         QHash<QString, QVariant> doc = fmDoclist->getDocsData().value( QUuid( param_value ) ); \
         param_value = doc.value( "doc_number" ).toString(); } } \
     if ( param_name == tr( "$WHOM" ) ) { \
       if ( items.count() > 0 && uuid_Idx > -1 ) { \
         param_value = abs_Mdl->index( items.first()->row(), uuid_Idx ).data().toString(); \
         QHash<QString, QVariant> doc = fmDoclist->getDocsData().value( QUuid( param_value ) ); \
         param_value = doc.value( "doc_agency" ).toString(); \
         DPRINT( param_value, qApp );\
         QList<MFCItem> items = otherTables.value( "docagency" ).findItemsByColName( \
         param_value.toInt(), tr( "cod" ) ); \
         DPRINT( items.count(), qApp );\
         if ( items.count() > 0 ) param_value = otherTables.value( "docagency" ).data( \
           items.first().row(), tr( "name" ) ).toString(); \
         else param_value = ""; } } \
     /*if ( param_name == "$PVIDAN" ) { \
       if ( items.count() > 0 && uuid_Idx > -1 ) { \
         param_value = abs_Mdl->index( items.first()->row(), uuid_Idx ).data().toString(); \
         QHash<QString, QVariant> doc = fmDoclist->getDocsData().value( QUuid( param_value ) ); \
         param_value = doc.value( "doc_agency" ).toString(); \
         QList<MFCItem> items = otherTables.value( "docagency" ).findItemsByColName( \
                param_value.toInt(), "id" ); \
         if ( items.count() > 0 ) param_value = otherTables.value( "docagency" ).data( \
           items.first().row(), tr( "name" ) ).toString(); \
         else param_value = ""; } }*/ \
     if ( param_name == "$PVIDAN" ) { \
       if ( items.count() > 0 && uuid_Idx > -1 ) { \
         param_value = abs_Mdl->index( items.first()->row(), uuid_Idx ).data().toString(); \
         QHash<QString, QVariant> doc = fmDoclist->getDocsData().value( QUuid( param_value ) ); \
         param_value = doc.value( "doc_date" ).toDate().toString( "dd.MM.yyyy" ); } } \
     report->addReportParam( req_name, param_name, "text", param_value ); } } } \
    DPRINT( "TYT", qApp ); \
}

#define ADD_WARRANT_REP( declar_num, service_name, service_idx, \
                         clientName, clientAddress, datein, dateout, user ) \
{report->addReport( "единая расписка" ); \
  report->addReportParam( "единая расписка", "declarnum", "text", declar_num ); \
  report->addReportParam( "единая расписка", "sidx"," text", \
                          service_idx+" "+service_name ); \
  report->addReportParam( "единая расписка", "applicant", "text", clientName ) ;\
  report->addReportParam( "единая расписка", "addr", "text", clientAddress ); \
  report->addReportParam( "единая расписка", "dateout", "text", dateout ); \
  report->addReportParam( "единая расписка", "printdate", "text", \
                          QDate::currentDate().toString( "dd.MM.yyyy" ) ); \
  report->addReportParam( "единая расписка", "operator", "text", user ); \
  report->addReportParam( "единая расписка", "indate", "text", datein ); \
  report->addWarrant( service_name, service_idx, fmDoclist->getTable( Doclist::DeclarDocs ) ); }

#define ADD_WARRANT_REP_V2( declar_num, service_name, service_idx, \
                         clientName, clientAddress, datein, dateout, user, respite, indocs, outdocs ) \
{report->addReport( "единая расписка" ); \
  report->addReportParam( "единая расписка", "declarnum", "text", declar_num ); \
  report->addReportParam( "единая расписка", "sidx"," text", \
                          service_idx+" "+service_name ); \
  report->addReportParam( "единая расписка", "applicant", "text", clientName ) ;\
  report->addReportParam( "единая расписка", "addr", "text", clientAddress ); \
  report->addReportParam( "единая расписка", "dateout", "text", dateout ); \
  report->addReportParam( "единая расписка", "printdate", "text", \
                          QDate::currentDate().toString( "dd.MM.yyyy" ) ); \
  report->addReportParam( "единая расписка", "operator", "text", user ); \
  report->addReportParam( "единая расписка", "indate", "text", datein ); \
  report->addReportParam( "единая расписка", "respite", "text", respite ); \
  report->addWarrant( service_name, service_idx, indocs, outdocs ); }

#define ADD_WARRANT_NOTCOMPLETED_REP( declar_num, service_name, clientName, \
                                      clientAddress, datein, user, neededDocs ) \
{report->addReport("Уведомление о недостающих доках");\
  report->addReportParam( "Уведомление о недостающих доках", "declarnum", "text", declar_num ); \
  report->addReportParam( "Уведомление о недостающих доках", "sidx","text", service_name ); \
  report->addReportParam( "Уведомление о недостающих доках", "applicant", "text", clientName ); \
  report->addReportParam( "Уведомление о недостающих доках", "addr", "text", clientAddress); \
  report->addReportParam( "Уведомление о недостающих доках", "indate", "text", datein ); \
  report->addReportParam( "Уведомление о недостающих доках", "operator", "text", user );\
  report->addReportParam( "Уведомление о недостающих доках", "rdate", "text", \
                        QDate::currentDate().addDays( 30 ).toString( "dd.MM.yyyy" ) ); \
  report->addWarrant_NotCompleted( neededDocs ); }


int calculateDateDifference( QDate firstDate, QDate secondDate );
const QString splitText( const QString &text, const QString &sep,
                         const int &minInc = 1, const int &maxInc = 2 );
const QString monthNameConverter( const QString &monthname );
QVariant getObjectProperty( const QObject *obj, const char *propName );
bool isEmptyWidget( QWidget *wgt, const char *propName, const QVariant &emptyValue );
void wait( const qint64 &msecs );
const QDate addDays( const QDate &date, const int &days, QList<int> workDays = QList<int>() << 6 << 7 );
int findColumn( QAbstractItemModel *absMdl, const QString &columnName );
void setWindowAtCenter( QWidget *childWgt, QWidget *parentWgt = 0 );
bool removeTab( QTabWidget *tabWidget, QWidget *widget, QString *err = 0 );

#endif // MACROS_H
