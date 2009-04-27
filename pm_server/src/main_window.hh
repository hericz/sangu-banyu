// generated 2008/10/17 18:43:52 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to main_window.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _MAIN_WINDOW_HH
#  include "main_window_glade.hh"
#  define _MAIN_WINDOW_HH

#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <gtkmm.h>
#include "low_mod.h"
#include "mbcrc.h"
//#include "serial.h"

#include "ServerSocket.h"
#include "SocketException.h"


#define TIPE_PM810

#define JUMLAH_PM    10
//#define TIPE_PM710
#define TIPE_PM810
#define FONT_LABEL	"Monospace 14"
#define SOKET_NOBLOK

//SERIAL

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif        

#ifndef _STOP_
#define _STOP_
//int STOP=FALSE;       
#endif


#define BAUDRATE B38400
#define _POSIX_SOURCE 1 /* POSIX compliant source */

//void signal_handler_IO (int status);   /* definition of signal handler */
//Array nama parameter


void signal_handler_IO (int status);
void set_awal_serial(int fd);

//Tree model columns:
class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
	public:

	ModelColumns()
	{ 
		add(m_col_id); 
		add(m_nama); 
		add(m_nilai);
		add(m_satuan);
		add(icon);
		add(use_icon);
	}

	Gtk::TreeModelColumn<int> m_col_id;
	Gtk::TreeModelColumn<Glib::ustring> m_nama;
	Gtk::TreeModelColumn<Glib::ustring> m_nilai;
	Gtk::TreeModelColumn<Glib::ustring> m_satuan;
	
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
	Gtk::TreeModelColumn<bool> use_icon;
};

class main_window : public main_window_glade
{  
	public:
	main_window();
	
	//Inisisasi Serial
		
		
	//EVENT HANDLERNYA
	void on_button_connect_clicked();
	void on_button_1_clicked();
	void on_button_2_clicked();
	void on_button_3_clicked();
	void on_button_4_clicked();
	void on_button_5_clicked();
		
	
		
	//Fungsi lain
	bool saat_kerja();
	unsigned short cek_PM();
	unsigned short get_KTA(unsigned short reg, unsigned char uk);	
	unsigned short get_PM710(unsigned short reg, unsigned char uk);	
		
	void taruh_data_PM810(int pm_dibaca, int urt);
	bool update_tampilan();

		
	//Variabel
		
	//List

	ModelColumns m_Columns;
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
	bool tree_ada_kolom;
	
	//char MODEMDEVICE[];
	unsigned int jum_PM;	
	unsigned short jum_PM710_masuk;

	unsigned short urut_PM710;    //urutan pengambilan data
	//unsigned short jum_balik;

	unsigned char addr_KTA;

	struct d_PM710 data_PM710[JUMLAH_PM];


	//struct t_kontrol_PM kontrol_PM[JUMLAH_PM];

	unsigned short wind_speed;
	unsigned short wind_dir;
	unsigned short wind_satuan;
	unsigned short wind_speed_tr;		// retransmision value
	unsigned short wind_dir_tr;
	

	int fd;
	unsigned short reg_flag;	
	int f;
		
	bool serial_terbuka;
	int t_saat,t_tampil;
	bool timer_on;
	
	//Tampilan
	int id_tampilkan;
	//Server socket
	ServerSocket *server;// (5002);

};
#endif
