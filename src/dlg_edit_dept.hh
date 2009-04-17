// generated 2008/8/26 18:01:18 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_dept.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_EDIT_DEPT_HH
#  include "dlg_edit_dept_glade.hh"
#  define _DLG_EDIT_DEPT_HH

#include "sql_routine.h"

class dlg_edit_dept : public dlg_edit_dept_glade
{  
	public:
	dlg_edit_dept();
	~dlg_edit_dept();
	
	//Event handler
	void on_okbutton4_clicked();
		
	//Fungsi
	void isi_form();
		
	//Variabel
	int id_persh;
	int id_dept;
	MyQuery MYQ;
};
#endif
