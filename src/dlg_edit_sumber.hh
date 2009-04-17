// generated 2008/7/30 8:32:14 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_sumber.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_EDIT_SUMBER_HH
#  include "dlg_edit_sumber_glade.hh"
#  define _DLG_EDIT_SUMBER_HH
class dlg_edit_sumber : public dlg_edit_sumber_glade
{  
	public:
	//KONSTRUKTOR DESTRUKTOR
	dlg_edit_sumber();
	
	//Event handler
	void on_button_ok_clicked();
	void on_button_cancel_clicked();
	void on_radio_file_group_changed();
	void on_radio_file_toggled();
	void on_radio_modul_toggled();
	void on_radio_pm_server_toggled();
	
	void on_button1_clicked() ;
	//Fungsi-fungsi
	
	//variabel
	bool berubah;
};
#endif
