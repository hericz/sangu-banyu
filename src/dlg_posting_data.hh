// generated 2008/8/8 16:42:57 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_posting_data.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_POSTING_DATA_HH
#  include "dlg_posting_data_glade.hh"
#  define _DLG_POSTING_DATA_HH

#include <gtkmm.h>
#include "sql_routine.h"
#include <string>
#include "common.hh"
#include "dlg_edit_post.hh"

//Tree model columns:
class ModelPosting : public Gtk::TreeModel::ColumnRecord
{
	public:

	ModelPosting()
	{ 
		add(m_col_nomer);
		add(m_col_id); 
		add(m_col_nama_post);
		add(m_col_flag);
		add(m_col_alamat_ip);
		add(m_col_port);
		add(m_col_status);
		add(m_col_periode);
		add(m_col_no_gsm);
		add(m_col_keterangan);
	}
		
	Gtk::TreeModelColumn<int>			m_col_nomer;
	Gtk::TreeModelColumn<int> 			m_col_id;
	Gtk::TreeModelColumn<Glib::ustring> m_col_nama_post;
	Gtk::TreeModelColumn<int>			m_col_flag;
	Gtk::TreeModelColumn<Glib::ustring> m_col_alamat_ip;
	Gtk::TreeModelColumn<Glib::ustring> m_col_port;
	Gtk::TreeModelColumn<Glib::ustring>	m_col_status;
	Gtk::TreeModelColumn<Glib::ustring> m_col_no_gsm;
	Gtk::TreeModelColumn<int> 			m_col_periode;
	Gtk::TreeModelColumn<Glib::ustring>	m_col_keterangan;
};

class dlg_posting_data : public dlg_posting_data_glade
{  
	public:
	
	//konstruktor
	dlg_posting_data();
	
	//Event
	void on_button_tambah_clicked();
	void on_button_hapus_clicked();
	void on_button_edit_clicked();
		
	//deklarasi fungsi
	void ReloadList();
		
	/*VARIABEL */	
	//Model untuk listview Data posting
	ModelPosting m_posting;
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
	
	bool list_ada_kolom;
		
	MyQuery MYQ;
	konfig_file kf_dialog_sumber;
		
	int jumlah_aktif;
};
#endif
