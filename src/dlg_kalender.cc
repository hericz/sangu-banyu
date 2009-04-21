// generated 2008/8/11 20:59:17 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_kalender.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "dlg_kalender.hh"

Glib::Date dlg_kalender::get_date()
{
  using Glib::Date;
  Date date;
  calendar1->get_date(date);
  
  return date;  
}
