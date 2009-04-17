// generated 2008/9/8 10:54:12 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_data.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_EDIT_DATA_HH
#  include "dlg_edit_data_glade.hh"
#  define _DLG_EDIT_DATA_HH

#include "sql_routine.h"

class dlg_edit_data : public dlg_edit_data_glade
{  
	public:
	dlg_edit_data();
	virtual ~dlg_edit_data();
		
	//Event handler
	int isi_form();
	
	//Fungsi
		
	//Variabel
	int id_data_harian;
	int id_data_tunggal;
	
		
	Glib::ustring waktu_data,us_data;
	Glib::ustring sumber_data;

	//MyQuery MYQ;
};
#endif
