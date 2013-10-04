#include <QMetaProperty>
#include "mfcdocument.h"
#include "amslogger.h"

QList<MFCDocument *> MFCDocument::instances = QList<MFCDocument *>();
QHash< QUuid, MFCDocument * > MFCDocument::doclist=QHash< QUuid, MFCDocument * >();

MFCDocument::MFCDocument(QObject *parent) :
    QObject(parent)
{
  init();
}

MFCDocument::~MFCDocument()
{
//  delete m_Type;
//  delete m_Name;
//  delete m_Series;
//  delete m_Number;
//  delete m_Agency;
  if(instances.contains(this)){
    LogWarning()<<"Document"<<this<<"("<<document_properties(this).join("; ")
               <<") deleted directly from destructor! "
                 "Use MFCDocument::remove(doc) instead!";
    instances.removeOne(this);
    doclist.remove( uuid() );
  }
  delete m_pages;
  m_pages = NULL;
  delete m_attachments;
  m_attachments = NULL;
}

MFCDocument *MFCDocument::instance(QString doc_type, QString doc_name,
                                   QString doc_series, QString doc_number,
                                   QDate doc_date, QDate doc_expires,
                                   QString doc_agency, QDateTime doc_createdate,
                                   QObject *parent){
  foreach ( MFCDocument *doc,instances )
  {
    if(doc->type()==doc_type && doc->date()==doc_date
       && doc->createDate()==doc_createdate && doc->number()==doc_number
       && doc->name()==doc_name && doc->series()==doc_series
       && doc->expiresDate()==doc_expires && doc->agency()==doc_agency){
      return doc;
    }
  }

  MFCDocument *doc=new MFCDocument(parent);
  doc->setType(doc_type);
  doc->setDate(doc_date);
  doc->setCreateDate(doc_createdate);
  instances << doc;
  doclist.insert( QUuid::createUuid(), doc );
  LogDebug()<<"Created instance "<<doc<<" ("
           <<document_properties(doc).join("; ")<<")";
  return doc;
}

QStringList MFCDocument::document_properties(MFCDocument *doc){
  QStringList props;
  foreach(QByteArray pn,doc->dynamicPropertyNames())
    props<<pn+" = "+doc->property(pn).toString();
  for(int i=0;i<doc->metaObject()->propertyCount();i++){
    QMetaProperty p=doc->metaObject()->property(i);
    QVariant v=doc->property(p.name());
    props<<tr(p.name())+" = "+(v.isNull() || !v.isValid()?"<NULL>":v.toString());
  }
  return props;
}

MFCDocument * MFCDocument::instance( MFCDocumentIOProvider *provider, QObject *parent )
{
  MFCDocument *doc = new MFCDocument( parent );
  if ( !provider->load( doc ) ) return NULL;

  foreach( MFCDocument *idoc, instances )
  {
    if( idoc->type()==doc->type() && idoc->date()==doc->date() &&
        idoc->createDate()==doc->createDate() && idoc->number()==doc->number() &&
        idoc->name()==doc->name() && idoc->series()==doc->series() &&
        idoc->expiresDate()==doc->expiresDate() && idoc->agency()==doc->agency())
    {
      delete doc;
      doc = NULL;
      return idoc;
    }
  }

  instances << doc;
  doclist.insert( QUuid::createUuid(), doc );
  QStringList props;
  foreach(QByteArray pn,doc->dynamicPropertyNames())
    props<<pn+" = "+doc->property(pn).toString();
  for(int i=0;i<doc->metaObject()->propertyCount();i++){
    QMetaProperty p=doc->metaObject()->property(i);
    QVariant v=doc->property(p.name());
    props<<tr(p.name())+" = "+(v.isNull() || !v.isValid()?"<NULL>":v.toString());
  }
  LogDebug()<<"Created instance "<<doc<<" ("<<props.join("; ")<<")";
  return doc;
}

bool MFCDocument::copyFrom(MFCDocument *doc){
  if(doc==NULL) return false;

  delete m_attachments;
  m_attachments=new DocAttachments( this );
  delete m_pages;
  m_pages=new MFCDocumentPages( this );

  setType(doc->type());
  setName(doc->name());
  setSeries(doc->series());
  setNumber(doc->number());
  setDate(doc->date());
  setExpiresDate(doc->expiresDate());
  setAgency(doc->agency());
  setCreateDate(doc->createDate());

  if(doc->haveAttachments())
    for(int i=0;i<doc->attachments()->count();i++){
      DocAttachment att=doc->attachments()->getAttachment(i);
      addAttachment(att.fileName(),att.mimeType(),att.data());
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
  if(!m_Type.isNull() && doc_type!=m_Type &&
     (havePages() || haveAttachments())) changed=true;
  m_Type=doc_type;
  emit type_Changed();
  emit propertyChanged("type",doc_type);
}

void MFCDocument::setName( const QString &doc_name )
{
  if(!m_Name.isNull() && doc_name!=m_Name &&
     (havePages() || haveAttachments())) changed=true;
  m_Name=doc_name;
  emit name_Changed();
  emit propertyChanged("name",doc_name);
}

void MFCDocument::setSeries( const QString &doc_series )
{
  if(!m_Series.isNull() && doc_series!=m_Series &&
     (havePages() || haveAttachments())) changed=true;
  m_Series=doc_series;
  emit series_Changed();
  emit propertyChanged("series",doc_series);
}

void MFCDocument::setNumber( const QString &doc_number )
{
  if(!m_Number.isNull() && doc_number!=m_Number &&
     (havePages() || haveAttachments())) changed=true;
  m_Number=doc_number;
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
  if(!m_Agency.isNull() && doc_agency!=m_Agency &&
     (havePages() || haveAttachments())) changed=true;
  m_Agency=doc_agency;
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

void MFCDocument::addPage(MFCDocumentPage &page){
//  else changed=true;
  m_pages->addPage(page);
}

bool MFCDocument::replacePage(const int pageNum, MFCDocumentPage &newPage){
  if(pageNum<0 || !newPage.isValid()){
    error(pageNum<0?tr("Номер страницы меньше 0"):tr("Ошибочный объект страницы"));
    return false;
  }
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
//  else changed=true;
  m_attachments->addAttachment( fileName, mimeType, fileData );
}

const QString & MFCDocument::type()
{
  return m_Type;
}

const QString & MFCDocument::name()
{
  return m_Name;
}

const QString & MFCDocument::series()
{
  return m_Series;
}

const QString & MFCDocument::number()
{
  return m_Number;
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
  return m_Agency;
}

const QDateTime & MFCDocument::createDate()
{
  return m_CreateDate;
}

bool MFCDocument::havePages(){
  return m_pages->count()>0;
}

MFCDocumentPages *MFCDocument::pages(){
  return m_pages;
}

bool MFCDocument::haveAttachments(){
  return m_attachments->count()>0;
}

DocAttachments *MFCDocument::attachments(){
  return m_attachments;
}

bool MFCDocument::isChanged(){
  return changed;
}

bool MFCDocument::isValid(){
  bool is=(havePages() || haveAttachments()) && !m_Type.isEmpty() &&
      m_Date.isValid();
  return is;
}

int MFCDocument::size(){
  int s=0;
  if(haveAttachments())
    for(int a=0;a<attachments()->count();a++)
      s+=attachments()->getAttachment(a).device()->size();
  if(havePages())
    for(int p=0;p<pages()->count();p++)
      s+=pages()->getPage(p)->device()->size();
  return s;
}

QString MFCDocument::errorString(){
  return errStr;
}

QUuid MFCDocument::uuid()
{
    return doclist.key( this, QUuid() );
}

MFCDocument * MFCDocument::document( QUuid uuid )
{
    return doclist.value( uuid, NULL );
}

void MFCDocument::removeAll()
{
  while ( !instances.isEmpty() )
  {
    MFCDocument *doc = instances.takeFirst();
    delete doc;
  }
  doclist.clear();
}

void MFCDocument::remove(MFCDocument *doc){
  if( instances.contains( doc ) )
  {
    instances.removeOne(doc);
    doclist.remove( doclist.key( doc ) );
    delete doc;
  }
}

void MFCDocument::remove(){
  remove(this);
}

void MFCDocument::init(){
  changed=false;
  m_Type=QString();
  m_Name=QString();
  m_Series=QString();
  m_Number=QString();
  m_Date = QDate();
  m_Expires = QDate();
  m_Agency=QString();
  m_CreateDate = QDateTime::currentDateTime();
  m_pages=new MFCDocumentPages( this );
  m_attachments=new DocAttachments( this );
  connect(this,SIGNAL(destroyed()),SLOT(remove()));
}

void MFCDocument::error(QString str){
  errStr="MFCDocument: "+str;
}
