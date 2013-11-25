#ifndef ASSESSMENTLOADER_H
#define ASSESSMENTLOADER_H

#include <QObject>

#include <QtQml>


class AssessmentLoader_P;
class AssessmentList;
class Assessment;

class AssessmentLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AssessmentLoader)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(AssessmentList* source READ source NOTIFY sourceChanged)


  public:
    AssessmentLoader(QObject *parent = 0);
    ~AssessmentLoader();

    Q_INVOKABLE QString error( int errorId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load( const QString &filter = QString() ) const;
    Q_INVOKABLE Assessment * create() const;

    AssessmentList * source() const;


  signals:
    void errorAdded( int errorId ) const;
    void connectionNameChanged() const;
    void started() const;
    void finished() const;
    void sourceChanged() const;


  public slots:


  private:
    AssessmentLoader_P *p;
    QEventLoop *loop;

  private slots:
    void newSource() const;
    void threadFinished();
    void receivedError( QString errorText ) const;
};

QML_DECLARE_TYPE(AssessmentLoader)

#endif // ASSESSMENTLOADER_H
