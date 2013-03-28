#ifndef HTMLREPORT_H
#define HTMLREPORT_H

#include <QObject>
#include <QAbstractItemModel>
#include <QHash>
#include <QStringList>
#include "htmlreport_export.h"

/* <!--section "file_name"--> - добавляет секцию - данные из файла file_name,
 * которые обрабатываются отдельно в процессе просчёта отчёта, заполняются
 * ключами из связанной модели, и заменяют данный текст
 */
/* <!--include "file_name"--> - данные из файла file_name заменяют данный текст
 */

#define MAX_INSERTED_SECTIONS 10

typedef struct{
  QString field;
  QString value;
} ReportKey;

typedef QHash< QString,ReportKey > ReportKeys;

class HTMLREPORTSHARED_EXPORT HtmlReport : public QObject
{
  Q_OBJECT
public:
  explicit HtmlReport(QObject *parent = 0);

  void setSection(const QString &name,const QString &data);
  /** Устанавливает данные отчёта. Вызывать после \a setSection()
   */
  bool setData(const QString &data);
  bool load(const QString &name);
  /** Возвращает готовый отчёт. В зависимости была ли вызвана \a generate()
   * отчёт будет заполнен данными либо ключами
   */
  QString data() const {return generated;}
  QStringList keys(const QString &section=QString()) const;
  QStringList sections() const;

  /// Указывает модель с данными для отчёта
  void assign(QAbstractItemModel *model);
  /// Сопоставляет ключ с полем модели для подстановки значения
  bool assign(const QString &key,const QString &fieldName);
  /// Указывает значение ключа
  bool assign(const QString &key,const QVariant &val);
  /// Указывает модель с данными для секции \param section
  bool assign(const QString &section, QAbstractItemModel *model);
  /** Сопоставляет ключ с полем модели для подстановки значения для секции
   * \param section
   */
  bool assign(const QString &section,const QString &key,
              const QString &fieldName);
  bool assign(const QString &section,const QString &key,const QVariant &val);

  void reset();
  void clear();

  QString errorString() const {return errStr;}

signals:
  void error(QString);
  void rowSelected(QAbstractItemModel*,int);

public slots:
  QString generate();

private slots:
  bool parse(const QString &sectionName=QString());

  QString fillKeys(const QString &section=QString(),
                   const QString &iData=QString(), const int row=0);
  QString fillSection(const QString &name);

  void set_error(const QString &str,const QString file,const int line);

private:
  QString errStr;
  QString repData;
  QAbstractItemModel *repModel;
  QString generated;
  ReportKeys repKeys;
  QHash< QString,QString > repSections;
  QHash< QString,QAbstractItemModel* > sectionsModels;
  QHash< QString,ReportKeys > sectionsKeys;
  int insertedSections;

  QString getFirstSectionName(QString data);
  QByteArray replaceMeta(const QByteArray &msg, QTextCodec *to);
};

#endif // HTMLREPORT_H
