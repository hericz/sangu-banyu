// generated 2008/7/17 16:11:24 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dialog_sumber.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DIALOG_SUMBER_HH
#  include "dialog_sumber_glade.hh"
#  define _DIALOG_SUMBER_HH

#include <gtkmm.h>
#include "dlg_edit_sumber.hh"
#include "dlg_koneksi_sumber.hh"
#include "sql_routine.h"
#include "common.hh"
#include <string>

#define SUMBER_MODUL 21
#define SUMBER_FOLDER 24

//Tree model columns:
class ModelSumber : public Gtk::TreeModel::ColumnRecord
{
	public:

	ModelSumber()
	{ 
		add(m_col_nomer);
		add(m_col_id); 
		add(m_col_nama_sumber);
		add(m_col_flag);
		add(m_col_alamat_ip);
		add(m_col_port);
		add(m_col_status);
		add(m_col_jum_kanal);
		add(m_col_no_gsm);
		add(m_col_tipe_pm);
		add(m_col_keterangan);
		add(m_col_default_stack);
		add(m_col_directory);
	}
	Gtk::TreeModelColumn<int>			m_col_nomer;
	Gtk::TreeModelColumn<int> 			m_col_id;
	Gtk::TreeModelColumn<Glib::ustring> m_col_nama_sumber;
	Gtk::TreeModelColumn<int>			m_col_flag;
	Gtk::TreeModelColumn<Glib::ustring> m_col_alamat_ip;
	Gtk::TreeModelColumn<Glib::ustring> m_col_port;
	Gtk::TreeModelColumn<Glib::ustring>			m_col_status;
	Gtk::TreeModelColumn<int> 			m_col_jum_kanal;
	Gtk::TreeModelColumn<Glib::ustring> m_col_no_gsm;
	Gtk::TreeModelColumn<int> 			m_col_tipe_pm;
	Gtk::TreeModelColumn<Glib::ustring>	m_col_keterangan;
	Gtk::TreeModelColumn<int> 			m_col_default_stack;
	Gtk::TreeModelColumn<Glib::ustring> m_col_directory;
};

class ModelNoPort: public Gtk::TreeModel::ColumnRecord
{
	public:

	ModelNoPort()
	{ 
		add(m_col_nomer);
		add(m_col_text); 
	}
		
	Gtk::TreeModelColumn<int> 			m_col_nomer;
	Gtk::TreeModelColumn<Glib::ustring> m_col_text;	
};


class dialog_sumber : public dialog_sumber_glade
{  
	public:
	dialog_sumber();
	void on_button_tambah_clicked();
	void on_button_hapus_clicked();
	void on_button_edit_clicked();	
		
	void on_button_koneksi_clicked();	
	
	int reload_list();
	
	ModelSumber m_sumber;
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
	
		
	ModelNoPort m_port;
	Glib::RefPtr<Gtk::TreeStore> m_refNoPort;
		
		
	MyQuery MYQ;
	konfig_file kf_dialog_sumber;
	
	bool list_ada_kolom;
};
#endif
