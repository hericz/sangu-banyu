// generated 2008/8/11 20:59:17 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_kalender.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_KALENDER_HH
#  include "dlg_kalender_glade.hh"
#  define _DLG_KALENDER_HH
class dlg_kalender : public dlg_kalender_glade
{  
	public:
		Glib::Date get_date();
};
#endif
