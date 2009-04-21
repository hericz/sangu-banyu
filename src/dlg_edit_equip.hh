// generated 2008/8/26 18:12:38 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_equip.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_EDIT_EQUIP_HH
#  include "dlg_edit_equip_glade.hh"
#  define _DLG_EDIT_EQUIP_HH

#include "sql_routine.h"

//bikin class untuk combo equipment
//Tree model columns:
class ModelJenisEquip : public Gtk::TreeModel::ColumnRecord
{
	public:

	ModelJenisEquip()
	{ 
		add(id_jenis); 
		add(nama_jenis); 
		add(icon);
	}
	
	Gtk::TreeModelColumn<int> id_jenis;
	Gtk::TreeModelColumn<Glib::ustring> nama_jenis;
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
};

class dlg_edit_equip : public dlg_edit_equip_glade
{  
	public:
	dlg_edit_equip();
	~dlg_edit_equip();
	
	//Event handler
	void on_okbutton5_clicked();
		
	//Fungsi-fungsi
	void isi_form();
	int isi_combo();
	
	//Combo jenis equipment
	ModelJenisEquip m_Columns;
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
	bool jenis_ada_kolom;
	
	//Variabel
	int id_equipment;
	int id_dept;
	MyQuery MYQ;
		
};
#endif
