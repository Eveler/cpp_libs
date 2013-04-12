#ifndef MREPORTDOCUMENT_H
#define MREPORTDOCUMENT_H

#include <QObject>

#include "mreportparameter.h"


class MReportDocument;
class MReportDocument_P;
class MReportParameter;

typedef QList<MReportDocument *> MReportDocumentList;

class EXPORT_MREPORTENGINE MReportDocument : public QObject
{
  Q_OBJECT
  friend class MReportDocument_P;


public:
  explicit MReportDocument( const QString &fileName = QString(), QObject *parent = 0 );
  ~MReportDocument();

  const QString & fileName() const;

  /** Документ, для которого неудалось загрузить файл конфигурации отчета.
  В случае отсутствия ошибки будет возвращен NULL.*/
  MReportDocument * errorDocument() const;
  /** Текст последней ошибки, возникшей при загрузке файла конфигурации отчета.
  В случае отсутствия ошибки будет возвращен none*/
  const QString & lastError() const;

  MReportDocument * addReportDocument( const QString &alias );
  MReportDocument * reportDocument( const QString &alias ) const;

  /** Добавление параметра в документ. ВНИМАНИЕ: если в дереве документов параметр с
  таким именем уже существует, то функция вернет NULL!*/
  MReportParameter * addReportParameter( const QString &name );
  /** Список параметров в документа. ВНИМАНИЕ: функция не возвращает списки параметров
  вложенных документов!*/
  const QList<MReportParameter *> & reportParameters() const;
  /** Поиск параметра по его имени во всем дереве документов.*/
  MReportParameter * reportParameter( const QString &name ) const;


signals:


public slots:


private:
  MReportDocument_P *p;

  explicit MReportDocument( MReportDocument *parent, const QString &fileName );
};

#endif // MREPORTDOCUMENT_H
