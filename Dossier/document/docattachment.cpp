#include <QDir>
#include "docattachment.h"
#include "amslogger.h"

DocAttachment::DocAttachment(const QString fileName, const QString mimeType,
                             const QByteArray &fileData){
  fName=fileName;
  mType=mimeType;
  initFile();
  m_File->write(fileData);
}

DocAttachment::~DocAttachment(){
//  LogDebug()<<"~DocAttachment() BEGIN"<<"fName="<<QUOTED_STR(fName);
//  delete m_File;
//  LogDebug()<<"~DocAttachment() END";
}

QString DocAttachment::fileName() const
{
  return fName;
}

QString DocAttachment::mimeType() const
{
  return mType;
}

QByteArray DocAttachment::data() const
{
  m_File->seek(0);
  return m_File->readAll();
}

QIODevice *DocAttachment::device() const
{
  return m_File;
}

bool DocAttachment::isValid(){
  return !fName.isEmpty() && m_File->size()>0;
}

void DocAttachment::initFile(){
  QDir d=QDir();
  d.mkdir("temp");
  m_File = new QTemporaryFile( QObject::tr( "temp/attach_" )+fName);
  if(!m_File->open()){
    LogWarning()<<QObject::tr("Error")<<m_File->error()<<":"<<
                  m_File->errorString();
    exit(-1);
  }
}
