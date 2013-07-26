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
  delete m_File;
}

QString DocAttachment::fileName(){
  return fName;
}

QString DocAttachment::mimeType(){
  return mType;
}

QByteArray DocAttachment::data(){
  m_File->seek(0);
  return m_File->readAll();
}

QIODevice *DocAttachment::device(){
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
