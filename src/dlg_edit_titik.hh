// generated 2008/8/1 0:11:57 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_titik.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_EDIT_TITIK_HH
#  include "dlg_edit_titik_glade.hh"
#  define _DLG_EDIT_TITIK_HH

#include "sql_routine.h"

//id_combo box entry
#define COMBO_SUMBER 		01
#define COMBO_NOMER_BOARD 	02
#define COMBO_NO_KANAL 		03
#define COMBO_SEMUA			99

#include <gtkmm.h>
//#include <gtk/gtk.h>

//Tree model columns:
class ModelAlarm : public Gtk::TreeModel::ColumnRecord
{
	public:

	ModelAlarm()
	{ 
		add(id_action);
		add(nama_alarm); //misal temperature T3 terlalu tinggi
		add(jenis_alarm); // 0: none, 1: min_min 2: min 3: max 4: max_max
		add(kode_alarm); //
		add(jenis_action); //
		add(icon);
		add(use_icon);
	}

	Gtk::TreeModelColumn<int> id_action;
	Gtk::TreeModelColumn<Glib::ustring> nama_alarm;
	Gtk::TreeModelColumn<Glib::ustring> kode_alarm;
	Gtk::TreeModelColumn<int> jenis_alarm;
	
	Gtk::TreeModelColumn<int> jenis_action;
		
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
	Gtk::TreeModelColumn<bool> use_icon;
};

//Titik yang dilist di variabel titik hitung
class ModelTitik: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelTitik()
	{ 
		add(index);
		add(id_titik);
		add(nama_titik); //misal temperature T3 terlalu tinggi
		add(kode_titik);
		add(kode_equip);
		add(icon);
		add(use_icon);
	}
	Gtk::TreeModelColumn<int> index;
	Gtk::TreeModelColumn<int> id_titik;
	Gtk::TreeModelColumn<Glib::ustring> nama_titik;
	Gtk::TreeModelColumn<Glib::ustring> kode_titik;
	Gtk::TreeModelColumn<Glib::ustring> kode_equip;
		
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
	Gtk::TreeModelColumn<bool> use_icon;
};

class ModelOperator:public Gtk::TreeModel::ColumnRecord
{
	public:
		ModelOperator()
	{
		add(index);
		add(simbol);
	}

	Gtk::TreeModelColumn<int> index;
	Gtk::TreeModelColumn<Glib::ustring> simbol;	
};

//Waktu perhitungan
class ModelWaktu: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelWaktu()
	{ 
		add(id_waktu);
		add(nama_waktu); 
		add(icon);
		add(use_icon);
	}

	Gtk::TreeModelColumn<int> id_waktu;
	Gtk::TreeModelColumn<Glib::ustring> nama_waktu;
		
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
	Gtk::TreeModelColumn<bool> use_icon;
};


class dlg_edit_titik : public dlg_edit_titik_glade
{  
	public:
	dlg_edit_titik();
	
	//Event Handler
	void on_okbutton1_clicked();
	//Tree model columns:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
		public:

		ModelColumns()
		{ 
			add(m_index);
			add(m_col_id); 
			add(m_col_name); 
		}
		Gtk::TreeModelColumn<int> m_index;
		Gtk::TreeModelColumn<int> m_col_id;
		Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	};
		
	ModelColumns m_Columns;	
	Glib::RefPtr<Gtk::ListStore> m_refTreeModel,
							m_refTreeModel2,
							m_refTreeModel3;
	//variabel combo box
	ModelAlarm m_alarm;
	Glib::RefPtr<Gtk::ListStore> m_refAlarm_min;

	//Titik ukur yang dipilih untuk opoerasi titik hitung
	ModelTitik m_titik;
	Glib::RefPtr<Gtk::ListStore> m_refTitik;

	//Waktu yang dipilih untuk opoerasi titik hitung
	ModelWaktu m_waktu;
	Glib::RefPtr<Gtk::ListStore> m_refWaktu;

	//Operator Aritmatika
	ModelOperator m_operator;
	Glib::RefPtr<Gtk::ListStore> m_refOperator;
		
	void on_combo_sumber_changed();
	void ReloadCombo(int id_combo);
	void isi_form();
	void UpdateData();	//Mengupdate data yang sudah ada
	void TambahData();
		
	//VARIABEL
	//VARIABLE PENTING
	int id_titik;
		
	int item_index_combo_sumber,
		item_index_combo_nomer_board,
		item_index_combo_kanal;
	
	int id_sumber,id_port,id_kanal;
	int id_group,id_equipment;
		
	int jumlah_kanal;
	
	double kalibrasi_a,kalibrasi_a_baru;
	double kalibrasi_b,kalibrasi_b_baru;

	
	//DATABASE
	MyQuery MYQ;
};

#endif
