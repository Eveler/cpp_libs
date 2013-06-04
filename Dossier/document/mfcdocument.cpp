#include "mfcdocument.h"

MFCDocument::MFCDocument(QObject *parent) :
    QObject(parent)
{
  init();
}

MFCDocument::~MFCDocument()
{
  delete m_Type;
  delete m_Name;
  delete m_Series;
  delete m_Number;
  delete m_Agency;
//  delete m_File;
  if(m_pages!=NULL) delete m_pages;
  if(m_attachments!=NULL) delete m_attachments;
}

bool MFCDocument::copyFrom(MFCDocument *doc){
  if(doc==NULL) return false;

  if(m_attachments!=NULL) delete m_attachments;
  if(m_pages!=NULL) delete m_pages;

  setType(doc->type());
  setName(doc->name());
  setSeries(doc->series());
  setNumber(doc->number());
  setDate(doc->date());
  setExpiresDate(doc->expiresDate());
  setAgency(doc->agency());
  setCreateDate(doc->createDate());
  setUrl(doc->url());

  if(doc->haveAttachments())
    for(int i=0;i<doc->attachments()->count();i++){
      DocAttachment *att=doc->attachments()->getAttachment(i);
      addAttachment(att->fileName(),att->mimeType(),att->data());
    }

  if(doc->havePages()){
    for(int i=0;i<doc->pages()->count();i++){
      MFCDocumentPage *page=doc->pages()->getPage(i);
      MFCDocumentPage *newPage=new MFCDocumentPage(page->getPageName(),
                                                  page->getBody());
      addPage(*newPage);
    }
  }

  return true;
}

void MFCDocument::setType( const QString &doc_type )
{
  if(!m_Type->isNull() && doc_type!=m_Type &&
     (havePages() || haveAttachments())) changed=true;
  delete m_Type;
  m_Type = new QString( doc_type );
  emit type_Changed();
  emit propertyChanged("type",doc_type);
}

void MFCDocument::setName( const QString &doc_name )
{
  if(!m_Name->isNull() && doc_name!=m_Name &&
     (havePages() || haveAttachments())) changed=true;
  delete m_Name;
  m_Name = new QString( doc_name );
  emit name_Changed();
  emit propertyChanged("name",doc_name);
}

void MFCDocument::setSeries( const QString &doc_series )
{
  if(!m_Series->isNull() && doc_series!=m_Series &&
     (havePages() || haveAttachments())) changed=true;
  delete m_Series;
  m_Series = new QString( doc_series );
  emit series_Changed();
  emit propertyChanged("series",doc_series);
}

void MFCDocument::setNumber( const QString &doc_number )
{
  if(!m_Number->isNull() && doc_number!=m_Number &&
     (havePages() || haveAttachments())) changed=true;
  delete m_Number;
  m_Number = new QString( doc_number );
  emit number_Changed();
  emit propertyChanged("number",doc_number);
}

void MFCDocument::setDate( QDate doc_date )
{
  if(!m_Date.isNull() && doc_date!=m_Date &&
     (havePages() || haveAttachments())) changed=true;
  m_Date = doc_date;
  emit date_Changed();
  emit propertyChanged("date",doc_date);
}

void MFCDocument::setExpiresDate( QDate doc_expires )
{
  if(!m_Expires.isNull() && doc_expires!=m_Expires &&
     (havePages() || haveAttachments())) changed=true;
  m_Expires = doc_expires;
  emit expiresDate_Changed();
  emit propertyChanged("expires",doc_expires);
}

void MFCDocument::setAgency( const QString &doc_agency )
{
  if(!m_Agency->isNull() && doc_agency!=m_Agency &&
     (havePages() || haveAttachments())) changed=true;
  delete m_Agency;
  m_Agency = new QString( doc_agency );
  emit agency_Changed();
  emit propertyChanged("agency",doc_agency);
}

void MFCDocument::setCreateDate( QDateTime doc_createdate )
{
  if(!m_CreateDate.isNull() && doc_createdate!=m_CreateDate &&
     (havePages() || haveAttachments())) changed=true;
  m_CreateDate = doc_createdate;
  emit createDate_Changed();
  emit propertyChanged("createdate",doc_createdate);
}

void MFCDocument::setUrl(const QString docUrl){
  if(!m_url.isNull() && docUrl!=m_url &&
     (havePages() || haveAttachments())) changed=true;
  m_url=docUrl;
  emit urlChanged();
  emit propertyChanged("url",docUrl);
}

void MFCDocument::addPage(MFCDocumentPage &page){
  if(m_pages==NULL) m_pages=new MFCDocumentPages;
//  else changed=true;
  m_pages->addPage(page);
}

bool MFCDocument::replacePage(const int pageNum, MFCDocumentPage &newPage){
  if(pageNum<0 || !newPage.isValid()){
    error(pageNum<0?tr("Номер страницы меньше 0"):tr("Ошибочный объект страницы"));
    return false;
  }
  if(m_pages==NULL) m_pages=new MFCDocumentPages;
  if(!m_pages->removePage(pageNum)){
    error(tr("Ошибка при удалении страницы: %1").arg(m_pages->errorString()));
    return false;
  }
  if(!m_pages->insertPage(pageNum,newPage)){
    error(tr("Ошибка при добавлении страницы: %1").arg(m_pages->errorString()));
    return false;
  }
  changed=true;
  return true;
}

void MFCDocument::addAttachment(const QString fileName, const QString mimeType,
                                const QByteArray &fileData){
  if(m_attachments==NULL) m_attachments=new DocAttachments;
//  else changed=true;
  DocAttachment *att=new DocAttachment(fileName,mimeType,fileData);
  m_attachments->addAttachment(*att);
}

void MFCDocument::addAttachment(DocAttachment &attachment){
  if(m_attachments==NULL) m_attachments=new DocAttachments;
//  else changed=true;
  m_attachments->addAttachment(attachment);
}

const QString & MFCDocument::type()
{
  return *m_Type;
}

const QString & MFCDocument::name()
{
  return *m_Name;
}

const QString & MFCDocument::series()
{
  return *m_Series;
}

const QString & MFCDocument::number()
{
  return *m_Number;
}

const QDate & MFCDocument::date()
{
  return m_Date;
}

const QDate & MFCDocument::expiresDate()
{
  return m_Expires;
}

const QString & MFCDocument::agency()
{
  return *m_Agency;
}

//const QByteArray & MFCDocument::body()
//{
//  DPRINT("DEPRECATED!!!",qApp);
////  QByteArray *b=new QByteArray();
//  m_File->seek(0);
////  b->append(m_File->readAll());
//  m_Body.clear();
//  m_Body.append(m_File->readAll());
//  DPRINT("get: body.size ="<<m_Body.size()<<m_File,qApp);
//  return m_Body;
////  return *m_Body;
//}

const QDateTime & MFCDocument::createDate()
{
  return m_CreateDate;
}

const QString & MFCDocument::url(){
  return m_url;
}

bool MFCDocument::havePages(){
  return m_pages!=NULL && m_pages->count()>0;
}

MFCDocumentPages *MFCDocument::pages(){
  isValid();
  return m_pages;
}

bool MFCDocument::haveAttachments(){
  return m_attachments!=NULL && m_attachments->count()>0;
}

DocAttachments *MFCDocument::attachments(){
  isValid();
  return m_attachments;
}

bool MFCDocument::isChanged(){
  return changed;
}

bool MFCDocument::isValid(){
  bool is=(havePages() || haveAttachments()) && !m_Type->isEmpty() &&
      m_Date.isValid();
  if(!is) emit needBody(url(),this);
  return is;
}

int MFCDocument::size(){
  int s=0;
  if(haveAttachments())
    for(int a=0;a<attachments()->count();a++)
      s+=attachments()->getAttachment(a)->device()->size();
  if(havePages())
    for(int p=0;p<pages()->count();p++)
      s+=pages()->getPage(p)->device()->size();
  return s;
}

QString MFCDocument::errorString(){
  return errStr;
}

void MFCDocument::init(){
  changed=false;
  m_Type = new QString();
  m_Name = new QString();
  m_Series = new QString();
  m_Number = new QString();
  m_Date = QDate();
  m_Expires = QDate();
  m_Agency = new QString();
//  m_Body = new QByteArray();
  m_CreateDate = QDateTime::currentDateTime();
  m_pages=NULL;
  m_attachments=NULL;
  m_url=QString();
//  initFile();
}

//void MFCDocument::initFile(){
//  QDir d=QDir();
//  d.mkdir("temp");
//  m_File=new QTemporaryFile(tr("temp/mfc_doc"),this);
//  if(!m_File->open()){
//    DPRINT(tr("Error")<<m_File->error()<<":"<<m_File->errorString(),qApp);
//    exit(-1);
//  }
//}

void MFCDocument::error(QString str){
  errStr="MFCDocument: "+str;
}
