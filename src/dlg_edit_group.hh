// generated 2008/8/26 10:11:35 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_group.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_EDIT_GROUP_HH
#  include "dlg_edit_group_glade.hh"
#  define _DLG_EDIT_GROUP_HH

#include <gtkmm.h>
#include "sql_routine.h"
#include <string.h>

class ModelJenis: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelJenis()
	{
		add(id_jenis);
		add(nama_jenis);
		add(icon);
	}
	
	Gtk::TreeModelColumn<int> id_jenis;
	Gtk::TreeModelColumn<Glib::ustring> nama_jenis;
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
};

class dlg_edit_group : public dlg_edit_group_glade
{  
	public:
	dlg_edit_group();
	~dlg_edit_group();
	
	//Event Handler
	void on_okbutton2_clicked();
		
	//Fungsi
	void isi_form();
	void isi_combo();
	//Variabel
	int id_group; //ini variabel paling penting
	int id_equipment;
	MyQuery MYQ;
		
	//Listview untuk data
	ModelJenis m_jenis;
	Glib::RefPtr<Gtk::TreeStore> m_refJenisGroup;
	bool kolom_jenis_ada;
		
};
#endif
