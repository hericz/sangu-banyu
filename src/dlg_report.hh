// generated 2008/9/23 9:54:47 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_report.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_REPORT_HH
#  include "dlg_report_glade.hh"
#include "sql_routine.h"
#  define _DLG_REPORT_HH

#include <stdlib.h>
#include "dlg_kalender.hh"
//Model kolom untuk data tunggal
class ModelPilihTitik: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelPilihTitik()
	{
		add(id_titik);
		add(nomer_titik);
		add(nama_titik);
		add(kode_titik);
		add(is_dipilih);
		add(icon);
	}
	
	Gtk::TreeModelColumn<int> id_titik;
	Gtk::TreeModelColumn<int> nomer_titik;
	Gtk::TreeModelColumn<Glib::ustring> nama_titik;
	Gtk::TreeModelColumn<Glib::ustring> kode_titik;
	Gtk::TreeModelColumn<bool> is_dipilih;
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
	
	Gtk::TreeModelColumn<Glib::ustring> nama_group;
	Gtk::TreeModelColumn<int> id_group;
	
	Gtk::TreeModelColumn<Glib::ustring> nama_equipment;
	Gtk::TreeModelColumn<int> id_equipment;
	
	Gtk::TreeModelColumn<Glib::ustring> nama_dept;
	Gtk::TreeModelColumn<int> id_dept;
	
	Gtk::TreeModelColumn<Glib::ustring> nama_persh;
	Gtk::TreeModelColumn<int> id_persh;
		
};
class dlg_report : public dlg_report_glade
{  
	public:
	//Konstruktor destruktor
	dlg_report();
	virtual ~dlg_report();
	
	//Event Handler
	void on_button_cetak_clicked();
	void on_button_open_kalender_clicked();
	void on_button_tanggal_apply_clicked();
	//Fungsi-fungsi
	int isi_form();
	int ExportCSV(Glib::ustring nama_file,int id_group_tree,Glib::ustring asTanggal);
		
	//Variabel
	int id_group_tree;
	struct tm *tm_pointer;
		
	//Listview untuk daftar titik
	ModelPilihTitik m_daftar_titik;
	Glib::RefPtr<Gtk::ListStore> mRefPilihTitik;
	bool kolom_pilih_ada;
	MyQuery MYQ,MYQ1;
};
#endif
