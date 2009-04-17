// generated 2008/8/4 9:28:45 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_koneksi_sumber.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_KONEKSI_SUMBER_HH
#  include "dlg_koneksi_sumber_glade.hh"
#  define _DLG_KONEKSI_SUMBER_HH

#include "sql_routine.h"
//Tree model columns:

class ModelKoneksiSumber : public Gtk::TreeModel::ColumnRecord
{
	public:

	ModelKoneksiSumber()
	{ 
		add(m_col_nomer);
		add(m_col_id); 
		add(m_col_id_titik);
		add(m_col_nama_titik);
		add(m_col_nama_mesin);
		add(m_col_data_last);
	}
		
	Gtk::TreeModelColumn<int>			m_col_nomer;
	Gtk::TreeModelColumn<int> 			m_col_id;
	Gtk::TreeModelColumn<int> 			m_col_id_titik;
	Gtk::TreeModelColumn<Glib::ustring>	m_col_nama_titik;
	Gtk::TreeModelColumn<Glib::ustring> m_col_nama_mesin;
	Gtk::TreeModelColumn<Glib::ustring> m_col_data_last;
};

class ModelComboPort: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelComboPort()
	{
		add(m_col_nomer);
		add(m_col_port);
	}
	Gtk::TreeModelColumn<int> m_col_nomer;
	Gtk::TreeModelColumn<Glib::ustring> m_col_port;
		
};

class dlg_koneksi_sumber : public dlg_koneksi_sumber_glade
{  
	public:
	void on_combo_port_changed();
	//Fungsi
	dlg_koneksi_sumber(); //constructor
	
	void on_okbutton1_clicked();
	bool ReloadList(int port);
	bool on_refresh_data();
	//Variabel
	//List View
	ModelKoneksiSumber m_konek_sumber;
	Glib::RefPtr<Gtk::ListStore> m_refSumberModel;
	
	//Combo box port
	ModelComboPort m_combo_port;
	Glib::RefPtr<Gtk::ListStore> m_refCombo;
		
	int id_sumber_data;
	int no_port_sekarang;
	int row_konek_sumber;
	int id_timeout;
	//Database
	MyQuery MYQ;
};
#endif
