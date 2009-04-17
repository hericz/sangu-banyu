// generated 2008/8/26 17:54:30 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_persh.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_EDIT_PERSH_HH
#  include "dlg_edit_persh_glade.hh"
#  define _DLG_EDIT_PERSH_HH

#include "sql_routine.h"

class dlg_edit_persh : public dlg_edit_persh_glade
{  
	public:
	dlg_edit_persh();
	~dlg_edit_persh();
        
	//Event handler
    void on_okbutton3_clicked();
		
	//Fungsi-fungsi
	void isi_form();
		
	//Variabel
	int id_persh;
	MyQuery MYQ;
};
#endif
