#ifndef MREPORTDOCUMENT_H
#define MREPORTDOCUMENT_H

#include <QObject>

#include "mreportsource.h"
#include "mreportparameter.h"
#include "mreportkey.h"

#include <QSqlDatabase>


class MReportDocument;
class MReportDocument_P;
class MReportLoader;

typedef QList<MReportDocument *> MReportDocumentList;

class EXPORT_MREPORTENGINE MReportDocument : public QObject
{
  Q_OBJECT
  friend class MReportDocument_P;
  friend class MReportLoader;


public:
  /** Конструктор класса MReportDocument создает его экземпляр из файла конфигурации отчета
  (*.mra {m-report archive}).
  ВНИМАНИЕ: в случае возникновения ошибки при чтении файла конфигурации отчета,
  вы можете вызвать функцию errorDocument, а за тем lastError, для получения текста ошибки.*/
  explicit MReportDocument( const QString &fileName = QString(), QObject *parent = 0 );
  ~MReportDocument();

  /** Файл конфигурации отчета.*/
  const QString & fileName() const;

  void setBody( const QString &body );

  /** Документ, для которого неудалось загрузить файл конфигурации отчета.
  В случае отсутствия ошибки будет возвращен NULL.*/
  MReportDocument * errorDocument() const;
  /** Текст последней ошибки, возникшей при загрузке файла конфигурации отчета.
  В случае отсутствия ошибки будет возвращен none*/
  const QString & lastError() const;

  MReportDocument * mainDocument() const;
  MReportDocument * addReportDocument( const QString &alias );
  MReportDocument * reportDocument( const QString &alias ) const;
  MReportDocument * parentDocument() const;

  MReportSource * addReportSource( const QString &name );
  const MReportSourceList & reportSources() const;

  /** Добавление параметра в документ. ВНИМАНИЕ: если в дереве документов параметр с
  таким именем уже существует, то функция вернет NULL!*/
  MReportParameter * addReportParameter( const QString &name );
  /** Список параметров документа. ВНИМАНИЕ: функция не возвращает списки параметров
  вложенных документов!*/
  const MReportParameterList & reportParameters() const;
  /** Поиск параметра по его имени во всем дереве документов.*/
  MReportParameter * reportParameter( const QString &name ) const;

  /** Добавление ключа в документ. ВНИМАНИЕ: если в дереве документов ключ с
  таким именем уже существует, то функция вернет NULL!*/
  MReportKey * addReportKey( const QString &name );
  /** Список ключей документа. ВНИМАНИЕ: функция не возвращает списки ключей
  вложенных документов!*/
  const MReportKeyList & reportKeys() const;
  /** Поиск ключа по его имени во всем дереве документов.*/
  MReportKey * reportKey( const QString &name ) const;

  QString exec();


signals:


public slots:


private:
  MReportDocument_P *p;

  /** Конструктор класса MReportDocument создает его экземпляр из файла конфигурации отчета
  (*.mrc {m-report config}).
  ВНИМАНИЕ: в случае возникновения ошибки при чтении файла конфигурации отчета,
  вы можете вызвать функцию errorDocument, а за тем lastError, для получения текста ошибки.*/
  explicit MReportDocument( MReportDocument *parent, const QString &fileName );
};

#endif // MREPORTDOCUMENT_H
