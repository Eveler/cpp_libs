#include "macros.h"
#include <QDesktopWidget>

int calculateDateDifference( QDate firstDate, QDate secondDate )
{
  QDate fDate=(firstDate>=secondDate?firstDate:secondDate);
  QDate sDate=(firstDate>=secondDate?secondDate:firstDate);
  int daySum = fDate.dayOfYear();
  int i=fDate.year()-sDate.year()-1;
//  while ( fDate.addYears( -1 ).year() > sDate.year() )
  while(i>0)
  {
//    daySum += fDate.daysInYear();
    daySum+=sDate.addYears(i--).daysInYear();
  }
  daySum += ( (fDate.year()>sDate.year()?sDate.daysInYear():0)-sDate.dayOfYear() );
  return (firstDate>=secondDate?daySum:-daySum);
}

const QString splitText( const QString &text, const QString &sep,
                         const int &minInc, const int &maxInc )

{
  QString newText = text;
  int newInc = minInc;
  int charCnt = newText.length();
  if ( charCnt == 0 || sep.length() == 0 ||
       newInc < 1 || newInc > maxInc ) return newText;
  while ( (charCnt%newInc) != 0 && newInc < maxInc ) newInc++;
  do
  {
    charCnt-=newInc;
    newText.insert( charCnt, sep );
  }while ( charCnt > newInc );
  return newText;
}

const QString monthNameConverter( const QString &monthname )
{
  QString result = monthname;
  if ( result.mid( result.length()-1 ) == "�" ||
       result.mid( result.length()-1 ) == "�" ) result = result.mid( 0, result.length()-1 )+"�";
  if ( result.mid( result.length()-1 ) == "�" ) result = result.mid( 0, result.length()-1 )+"��";
  return result;
}

QVariant getObjectProperty( const QObject *obj, const char *propName )
{
  if ( obj != 0 ) return obj->property( propName );
  else return QVariant();
}

bool isEmptyWidget( QWidget *wgt, const char *propName, const QVariant &emptyValue )
{
  QVariant wgtPropValue = getObjectProperty( (const QObject *)wgt, propName );
  if ( wgtPropValue.isValid() )
  {
    return ( wgtPropValue == emptyValue );
//    switch ( wgtPropValue.type() )
//    {
//    case QVariant::
//    }
  }
  return false;
}

void wait( const qint64 &msecs )
{
  QDateTime startTime = QDateTime::currentDateTime();
  QDateTime endTime = startTime.addMSecs( msecs );
  while( startTime < endTime );
}

const QDate addDays( const QDate &date, const int &days, QList<int> weekend )
{
  QMap<int, int> weekdays;
  foreach( int dayNum, weekend )
    if ( dayNum > 7 ) return QDate();
    else weekdays.insert( dayNum, dayNum );
  if ( weekdays.count() == 7 ) return QDate();

  QDate result = date;
  if ( days == 0 ) return result;

  if ( weekend.count() > 0/* && days > 5*/ )
  {
    int udays = ( days > 0 ? 1 : -1 )*days;
//    DPRINT( udays, qApp );
    for ( int i = 0; i < udays; i++ )
    {
      result = result.addDays( ( days > 0 ? 1 : -1 ) );
      if ( days > 0 )
        while ( weekend.contains( result.dayOfWeek() ) ) result = result.addDays( 1 );
    }
    if ( days < 0 )
      while ( weekend.contains( result.dayOfWeek() ) ) result = result.addDays( 1 );
  }
  else
  {
    weekend << 6 << 7;
    result = result.addDays( days );
    while ( weekend.contains( result.dayOfWeek() ) ) result = result.addDays( 1 );
  }
  return result;
}

int findColumn( QAbstractItemModel *absMdl, const QString &columnName )
{
  if ( absMdl != 0 )
  {
    for ( int cIdx = 0; cIdx < absMdl->columnCount(); cIdx++ )
      if ( absMdl->headerData( cIdx, Qt::Horizontal ).toString() == columnName )
        return cIdx;
  }
  return -1;
}

void setWindowAtCenter( QWidget *childWgt, QWidget *parentWgt )
{
  if ( childWgt == 0 ) return;

  int parentX = ( parentWgt == 0 ? 0 : parentWgt->frameGeometry().x() );
  int parentY = ( parentWgt == 0 ? 0 : parentWgt->frameGeometry().y() );
  int parentWidth = ( parentWgt == 0 ? qApp->desktop()->availableGeometry().width() :
                                       parentWgt->frameGeometry().width() );
  int parentHeight = ( parentWgt == 0 ? qApp->desktop()->availableGeometry().height() :
                                        parentWgt->frameGeometry().height() );

  childWgt->move( parentX+parentWidth/2-childWgt->frameGeometry().width()/2,
                  parentY+parentHeight/2-childWgt->frameGeometry().height()/2 );
}

bool removeTab( QTabWidget *tabWidget, QWidget *widget, QString *err )
{
  if ( tabWidget == 0 )
  {
    if ( err != 0 ) err->append( QObject::tr( "�� ����� ��������� �� ������ tabWidget!" ) );
    return false;
  }
  if ( widget == 0 )
  {
    if ( err != 0 ) err->append( QObject::tr( "�� ����� ��������� �� ������ widget!" ) );
    return false;
  }
  int tabIdx = tabWidget->indexOf( widget );
  if ( tabIdx > -1 ) tabWidget->removeTab( tabIdx );
  else
  {
    if ( err != 0 ) err->append( QObject::tr( "�� ������ ��� � ���-�����!" ) );
    return false;
  }
  return true;
}

QString transliter(const QString str){
  // (C) linux.org.ru wingear
  QHash<QChar, QString> t;

  t.insert('�',"a");  t.insert('�',"b");  t.insert('�',"v");   t.insert('�',"g");
  t.insert('�',"d");  t.insert('�',"ye"); t.insert('�',"yo");  t.insert('�',"zh");
  t.insert('�',"z");  t.insert('�',"i");  t.insert('�',"y");   t.insert('�',"k");
  t.insert('�',"l");  t.insert('�',"m");  t.insert('�',"n");   t.insert('�',"o");
  t.insert('�',"p");  t.insert('�',"r");  t.insert('�',"s");   t.insert('�',"t");
  t.insert('�',"u");  t.insert('�',"f");  t.insert('�',"kh");  t.insert('�',"c");
  t.insert('�',"ch"); t.insert('�',"sh"); t.insert('�',"sch"); t.insert('�',"");
  t.insert('�',"y");  t.insert('�',"");   t.insert('�',"e");   t.insert('�',"yu");
  t.insert('�',"ya");
  t.insert('�',"A");  t.insert('�',"B");  t.insert('�',"V");   t.insert('�',"G");
  t.insert('�',"D");  t.insert('�',"YE"); t.insert('�',"YO");  t.insert('�',"ZH");
  t.insert('�',"Z");  t.insert('�',"I");  t.insert('�',"Y");   t.insert('�',"K");
  t.insert('�',"L");  t.insert('�',"M");  t.insert('�',"N");   t.insert('�',"O");
  t.insert('�',"P");  t.insert('�',"R");  t.insert('�',"S");   t.insert('�',"T");
  t.insert('�',"U");  t.insert('�',"F");  t.insert('�',"KH");  t.insert('�',"C");
  t.insert('�',"CH"); t.insert('�',"SH"); t.insert('�',"SCH"); t.insert('�',"");
  t.insert('�',"Y");  t.insert('�',"");   t.insert('�',"E");   t.insert('�',"YU");
  t.insert('�',"YA");
  t.insert('�',"N");
//  t[0x430] = "a";
//  t[0x410] = "A";
//  t[0x44f] = "ya";
//  t[0x42f] = "Ya";

  QString result;

  foreach(QChar ch,str){
    result+=(t.contains(ch))?t[ch]:ch;
  }

  return result;
}
