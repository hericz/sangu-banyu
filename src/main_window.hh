// generated 2008/7/14 15:08:43 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to main_window.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _MAIN_WINDOW_HH
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <math.h>
#include <gtkextra/gtkplot.h>
//#include <gtkextra-2.0/gtkplot.h>
#include <dirent.h> 
#include <string.h>

#include "main_window_glade.hh"
#include "db_setting.hh"
#include "common.hh"
#define _MAIN_WINDOW_HH

#include "sql_routine.h"
#include "main_client.hh"
#include "dlg_konfigurasi.hh"
#include "dlg_kalender.hh"
#include "dlg_edit_group.hh"
#include "dlg_edit_persh.hh"
#include "dlg_edit_dept.hh"
#include "dlg_edit_equip.hh"
#include "dlg_koneksi_sumber.hh"

//0-non-aktif 1-aktif_belum_dicoba 2-koneksi OK, 3-data invalid 4-Timeout 5-ERROR 
#define STATUS_NON_AKTIF 	0
#define STATUS_AKTIF_NOTRY 	1
#define STATUS_OK			2
#define STATUS_NOT_FOUND	3
#define STATUS_DATA_INVALID 4
#define STATUS_TIMEOUT		5
#define STATUS_ERROR		6

#define STATE_NORMAL 	1
#define STATE_LOGGING 	2
#define STATE_ERROR_DB	3
#define STATE_ERROR_LAIN 4

#define SKALA_MANUAL	0
#define SKALA_OTOMATIS	1

//status log
#define LOG_INFO 	0
#define LOG_SYSTEM  1
#define LOG_WARNING	2
#define LOG_ALARM_1	3
#define LOG_ALARM_2 4


typedef struct tabel_titik
{
	int id_titik;
	int alarm_setting;
	char nama_titik[64];
	double range_min;
	double range_max;
	double alarm_low;
	double alarm_low_low;
	double alarm_high;
	double alarm_high_high;
	double kalibrasi_a;
	double kalibrasi_b;
};

//Struct data_sumber
typedef struct tabel_sumber
{
	int index;
	int id_sumber;
	Glib::ustring nama_sumber;
	//char nama_sumber[50];
	int flag;
	int jumlah_kanal;//maks 20
		
	Glib::ustring ip_address;
	int ip_port;
	//char ip_address[20]; 
	Glib::ustring no_gsm;
	//char no_gsm[25];
	
	//int id_titik[30];
	tabel_titik titik[30];
	int no_port[30];
	
	int no_stack; //satu sumber satu port saja.
	
	int data_terima;
	char buf_terima[512];
	
	int status; //status penggunaan 0-non_aktif 1-aktif
	int status_koneksi; //0-non-aktif 1-aktif_belum_dicoba 2-koneksi OK, 3-data error 4-Timeout 5-ERROR  
};

//Struct tabel_posting
typedef struct tabel_posting
{
	int index;
	int id_post;
	Glib::ustring nama_post;
	//char nama_sumber[50];
	int flag;
	int jumlah_kanal;//maks 20
		
	Glib::ustring ip_address;
	int ip_port;
	//char ip_address[20]; 
	Glib::ustring no_gsm;
	//char no_gsm[25];
	
	//int id_titik[30];
	tabel_titik titik[30];
	int no_port[30];
	
	int no_stack; //satu sumber satu port saja.
	
	int data_terima;
	char buf_terima[512];
	
	int status; //status penggunaan 0-non_aktif 1-aktif
	int status_koneksi; //0-non-aktif 1-aktif_belum_dicoba 2-koneksi OK, 3-data error 4-Timeout 5-ERROR  
};

struct t_data_float {
	float data[50];
};

struct t_xdata {
	char mon[8];             // id bahwa data monita
    unsigned int nomer;      // urutan pengiriman data
    unsigned char flag;      // belum di definisikan
    unsigned char alamat;    // alamat stacking board (address power meter)
     
	char buf[232];				//16 jan 08, disesuaikan dengan Client Utama
	//float data[100];
};

//Untuk posting data
struct t_loc_data {
     float data[45];
};
struct d3_data {
     char mon[8];             // id bahwa data monita
     unsigned int nomer;      // urutan pengiriman data
     unsigned char flag;      // belum di definisikan
     unsigned char alamat;    // alamat MESIN
     char waktu[32];
     char buf[200];
};

//Tree model columns:
class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
	public:

	ModelColumns()
	{ 
		add(m_col_id); 
		add(m_col_name); 
		add(icon);
		add(use_icon);
	}

	Gtk::TreeModelColumn<int> m_col_id;
	Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
	Gtk::TreeModelColumn<bool> use_icon;
};

//Model kolom untuk list status sumber data 
class ModelStatusSumber: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelStatusSumber()
	{
		add(m_col_id);
		add(m_col_alamat_ip);
		add(m_col_ip_port);
		add(m_col_nama_sumber);
		add(m_col_status);
		add(color);
		add(icon);
	}
		
	Gtk::TreeModelColumn<int> m_col_id;
	Gtk::TreeModelColumn<Glib::ustring> m_col_nama_sumber;
	Gtk::TreeModelColumn<Glib::ustring> m_col_alamat_ip;
	Gtk::TreeModelColumn<int> m_col_ip_port;	
	Gtk::TreeModelColumn<Glib::ustring> m_col_status;
	Gtk::TreeModelColumn<Glib::ustring> color; 	
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
};

//Model kolom untuk data tunggal
class ModelKolomTitik: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelKolomTitik()
	{
		add(m_col_id);
		add(m_col_nomer);
		add(m_col_waktu);
		add(m_col_data);
		add(m_col_data_float);
		add(m_col_status);
		add(icon);
	}
	
	Gtk::TreeModelColumn<int> m_col_id;
	Gtk::TreeModelColumn<int> m_col_nomer;
	Gtk::TreeModelColumn<Glib::ustring> m_col_waktu;
	//Gtk::TreeModelColumn<Glib::ustring> m_col_waktu_lengkap;
	Gtk::TreeModelColumn<Glib::ustring> m_col_data;
	Gtk::TreeModelColumn<float> m_col_data_float;
	Gtk::TreeModelColumn<Glib::ustring> m_col_status;
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
	
};

//model untuk kolom data group
#define MAX_TITIK_PER_GROUP 20

class ModelKolomGroup: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelKolomGroup()
	{
		add(id);
		//for(int i=0;i<MAX_TITIK_PER_GROUP;i++)
		add(data);
	}
	Gtk::TreeModelColumn<int> id;
	
	Gtk::TreeModelColumn<int> data;
};

//model untuk kolom log 
class ModelKolomLog: public Gtk::TreeModel::ColumnRecord
{
	public:
	ModelKolomLog()
	{
		add(log_id);
		add(log_waktu);
		add(log_data);
		add(log_jenis);
		add(icon);
	}
	
	Gtk::TreeModelColumn<int> log_id;
	Gtk::TreeModelColumn<Glib::ustring> log_waktu;
	Gtk::TreeModelColumn<Glib::ustring> log_data;
	Gtk::TreeModelColumn<int> log_jenis;
		
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
};

class main_window : public main_window_glade
{  
	public:
        main_window();
		~main_window();
		
		//Event Handler
		bool on_main_window_delete_event(GdkEventAny *ev);
		
		void on_konfigurasi1_activate();
		void on_database_login_setting1_activate();
		void on_quit1_activate();
		void on_sumber_data1_activate();
		void on_posting_pengiriman_data1_activate();
		void on_mulai_baca_data1_activate();
		void on_stop_baca_data1_activate();
		void on_tambah_entri_perusahaan1_activate();
		void on_buat_laporan_activate();
			
        void on_about1_activate();
        void on_buttonbuka_clicked();
		void on_button_sumber_clicked();
        void on_button_logging_data_clicked();
		void on_button_open_kalender_clicked();
		
		void on_treeview1_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);
		
		void on_treeview1_cursor_changed();
		bool on_treeview1_button_press_event(GdkEventButton *ev);

		void on_menu_file_popup_generic();
		void on_menu_file_popup_tambah();
		void on_menu_file_popup_hapus();
		
		void on_data_popup_info();
		void on_data_popup_hapus();
		
		void on_button_refresh_clicked();
		void on_menu_file_popup_edit();
		void on_button_tanggal_apply_clicked();
		
		void on_tree_status_cursor_changed();
		bool on_tree_status_button_press_event(GdkEventButton *ev);
		
		bool on_drawingarea1_expose_event(GdkEventExpose *ev);
		
		void on_notebook1_switch_page(GtkNotebookPage *p0, guint p1);
		
		bool on_tree_data_button_press_event(GdkEventButton *ev);

		//Fungsi-fungsi
		int UpdateTreeView(int level,int id);
		int UpdateListView(int level, int id);
		int UpdateStatusSumber();
		bool HapusDataJaman (int id_waktu_sekarang);
		
		//Hapus data
		int hapus_titik(int id_titik,Glib::ustring valumenu);
		int hapus_group(int id_group,Glib::ustring valumenu);
		int hapus_equipment (int id_equipment,Glib::ustring valumenu);
		int hapus_departemen (int id_dept,Glib::ustring valumenu);
		int hapus_perusahaan (int id_persh,Glib::ustring valumenu);
		
		virtual bool on_timeout();
		virtual bool on_timeout_2();
		
		//Variabel
		Gtk::Tooltips main_tooltips;
		
		//Integer
		int KonekDB(int jum_db);
		
		int CloseDB(bool semua);
		void CekDB();
		
		int SimpanKonfig(konfig_file* kf);
		int LoadConfig();//konfig_file* kfg);
		int gambar_grafik();
		int selisih_hari(Glib::ustring tanggal);
		
		void push_buffer_switch(float data);
		int cek_mail_dir(Glib::ustring direktori);
		
		Glib::ustring cari_tanggal(Glib::ustring tanggal_sekarang,int selisih_hari);
		Glib::ustring alarm_teks;
		//LOG
		int init_log();
		int add_log(Glib::ustring teks, int status,int level);
		//VARIABEL
		//timer
		int m_connection_id_timeout;
		struct tm *tm_ptr, timestruct;
		struct tm *tm_pointer;
		
		char buf[64],buf2[64],waktu[64];//,waktu_simpan_lalu[32];
		char *result;
		
		int id_titik_lama;
		
		Gtk::AboutDialog m_Dialog;
		//Treeview Utama
  		ModelColumns m_Columns;
		Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
		bool tree_ada_kolom;
		
		//Listview untuk data
		ModelKolomTitik m_kolom_list;
		Glib::RefPtr<Gtk::TreeStore> m_refDataModel;
		bool kolom_data_ada;
		
		//Listview untuk status sumber
		ModelStatusSumber m_status_list;
		Glib::RefPtr<Gtk::TreeStore> m_refStatusModel;
		bool kolom_status_ada;
		
		//Listview untuk log data
		ModelKolomLog m_log_list;
		Glib::RefPtr<Gtk::TreeStore> m_refLogModel;
		bool kolom_log_ada;
		
		
		//Menu popup
		Gtk::Menu m_Menu_Popup,popup_dept,popup_equip,popup_persh,popup_group;
		bool menu_popup_isi,popup_persh_isi,popup_dept_isi,popup_equip_isi,popup_group_isi;
	  	
		Gtk::Menu data_popup; // menu popup untuk tree data
		bool data_popup_isi;
		
		//MySQL instance
		MyQuery MYQ;
		MyQuery MYQLog;
		MyQuery MYQMain[5];
			
		konfig_file kfg;
		konfig_file* conf;
		pthread_t th_timer;
		int ret;
		
		int depth_level_sekarang,id_titik_tampil_sekarang;
		int jumlah_db;
		//Data logging
		int logging_data(char* waktu);
		long long_tick;
		
		//gambar
		int result_7hari;
		bool belum_tanya;
		
		//State Sistem
		int state_sistem; 
		int mode_gambar;
		
		//sumber data email
		int jumlah_sumber_email;
		
		//Icon STATUS
		Glib::RefPtr<Gdk::Pixbuf> icon_info;
		Glib::RefPtr<Gdk::Pixbuf> icon_generic;
		Glib::RefPtr<Gdk::Pixbuf> icon_warning;
		Glib::RefPtr<Gdk::Pixbuf> icon_default;
		Glib::RefPtr<Gdk::Pixbuf> icon_error;
		Glib::RefPtr<Gdk::Pixbuf> icon_important;
		Glib::RefPtr<Gdk::Pixbuf> icon_alarm1;
		Glib::RefPtr<Gdk::Pixbuf> icon_alarm2;
		
		//icon treeview
		Glib::RefPtr<Gdk::Pixbuf> icon_persh,
								icon_dept,
								icon_equip,
								icon_group,
								icon_titik1,
								icon_titik2;
};

int LoadConfig_global();

#endif
