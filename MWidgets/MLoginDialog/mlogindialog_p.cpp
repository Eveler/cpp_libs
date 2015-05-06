#include "mlogindialog_p.h"


MLoginDialog_P::MLoginDialog_P( MLoginDialog *parent ) :
  QObject(parent)
{
}

MLoginDialog * MLoginDialog_P::p_dptr() const
{
  return qobject_cast<MLoginDialog *>( parent() );
}
