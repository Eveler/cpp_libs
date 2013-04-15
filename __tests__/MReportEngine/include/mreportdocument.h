#ifndef MREPORTDOCUMENT_H
#define MREPORTDOCUMENT_H

#include <QObject>

#include "mreportparameter.h"


class MReportDocument;
class MReportDocument_P;
class MReportLoader;
class MReportParameter;

typedef QList<MReportDocument *> MReportDocumentList;

class EXPORT_MREPORTENGINE MReportDocument : public QObject
{
  Q_OBJECT
  friend class MReportDocument_P;
  friend class MReportLoader;


public:
  /** Конструктор создает экземпляр класса MReportDocument из файла конфигурации отчета.
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
