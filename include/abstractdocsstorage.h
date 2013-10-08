#ifndef ABSTRACTDOCSSTORAGE_H
#define ABSTRACTDOCSSTORAGE_H

#include <QObject>
#include <QHash>
#include <QPair>
#include <QDebug>
#include "mfcdocument.h"
#include "export/dossier_export.h"

/** \brief \class AbstractDocsStorage - базовый класс для реализации подсистемы
хранения документов во внешней системе (сервере). Спроектирован по шаблону
Singleton.
  Для получения ссылки на экземпляр класса служит \a addStorage. Для удаления
\a removeStorage
*/
class DOSSIER_EXPORT AbstractDocsStorage : public QObject
{
  Q_OBJECT

protected:
  Q_INVOKABLE explicit AbstractDocsStorage(const QString storageName="__default_storage",
                               QObject *parent = 0);
  virtual ~AbstractDocsStorage();
  static bool registerStorage(const QString storageName,QObject* instance);
  void setError(const QString str);
  static QString errStr;
  bool connected;

public:
  /** Создаёт, если необходимо, и возвращает ссылку на экземпляр класса,
ассоциированный с \arg storageName, увеличивая счётчик ссылок на экземпляр
класса
*/
  static AbstractDocsStorage& addStorage(
      const QString storageName="__default_storage");
  static void removeStorage(const QString storageName);
  virtual void removeStorage();
  static QStringList storagesNames();
  static bool contains(const QString storageName);
  int references();
  /** Устанавливает соединение с сервером хранения \arg host от имени
пользователя \arg user по паролю \arg pass на порту \arg port
*/
  virtual bool connectToHost(const QString user,const QString pass,
                             const QString host,const quint16 port=0)=0;
  virtual int port() const=0;
  static QString errorString();

private:
  static QHash< QString,QPair< AbstractDocsStorage*,int > > instances;
  QString instanceName;

signals:
  void progressRangeChanged(int minimum,int maximum);
  void progressTextChanged(QString progressText);
  void progressValueChanged(int progressValue);
  void dataTransferProgress(qint64 done,qint64 total,MFCDocument* doc);
  void done(bool);
  virtual void error(QString);
  void saved(QString);
  virtual void loaded(MFCDocument*);

public slots:
  virtual bool save(MFCDocument* doc,QString declarNumber=QString())=0;
  virtual bool load(QString documentUrl,MFCDocument*)=0;
  virtual void cancel()=0;

};

#endif // ABSTRACTDOCSSTORAGE_H
