#ifndef PLUGINSSOURCELOADER_P_H
#define PLUGINSSOURCELOADER_P_H

#include <QObject>

#include <QStringList>
#include <QHash>
#include <QPair>
#include <QNetworkReply>


class Widget_PluginsSourceLoader;
class QNetworkAccessManager;
class QListWidgetItem;

class PluginsSourceLoader_P : public QObject
{
  Q_OBJECT
  friend class Widget_PluginsSourceLoader;


public:


signals:


public slots:


private:
  QNetworkAccessManager *m__NetworkAM;
  QStringList m__PluginPaths;
  QHash<QString, QByteArray> m__PluginHash;

  QPair<QListWidgetItem *, QByteArray> currentUpdate;
  bool m__FullUpdate;

  explicit PluginsSourceLoader_P( Widget_PluginsSourceLoader *parent );
  ~PluginsSourceLoader_P();

  Widget_PluginsSourceLoader * p_dptr() const;

  bool addPluginSource( const QUrl &source );
  void updatePluginSource( QListWidgetItem *pluginSource );

  void parseXML( const QByteArray &xml );
  void nextPluginSource();


private slots:
  void replyFinished( QNetworkReply *reply );
  void readyReadData();
  void downloadProgress( qint64 current, qint64 overall );
  void downloadError( QNetworkReply::NetworkError );
};

#endif // PLUGINSSOURCELOADER_P_H
