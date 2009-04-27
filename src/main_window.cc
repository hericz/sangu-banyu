// generated 2008/7/14 15:08:43 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to main_window.cc_new

// This file is for your program, I won't touch it again!
#include <pthread.h>

#include "config.h"
#include "common.hh"
#include "main_window.hh"
#include "db_setting.hh"
#include "db_dialog.hh"
#include "dialog_sumber.hh"
#include "dlg_edit_titik.hh"
#include "dlg_posting_data.hh"
#include "dlg_edit_group.hh"
#include "dlg_edit_equip.hh"	
#include "dlg_edit_data.hh"
#include "dlg_report.hh"

#define MAX_DB_CONNECT 10
#define JUMLAH_THREAD 20		//Jumlah thread maksimum

//FUNGSI
//void *f_timer(void *data);


bool timer_on,timer2_on;
MyQuery myq_global;
konfig_file kfg_global;

//VARIABEL
//String & Buffer
Glib::ustring utemp_global,asTemp;
Glib::ustring asQuery;


std::string std_ip_address;

char monita1_check_string[8];
char buf_terima[1024];
char sTemp[512];
char waktu_simpan_sekarang[32],waktu_simpan_lalu[32];
char tanggal_sekarang[32],tanggal_yang_lalu[32];

char buf_data[JUMLAH_THREAD][512];
int ukuran_terima2[JUMLAH_THREAD];

//int
long int id_waktu_simpan;
int jumlah_sumber;
int jumlah_post;

int port_num;
int ukuran_terima,id_titik_simpan;
int time_counter,waktu_simpan_counter;

int index_sumber[JUMLAH_THREAD];
int index_post[JUMLAH_THREAD];

int res,sisa_thread,sisa_thread_post;

int index_sumber_a,index_sumber_b,index_sumber_c,index_sumber_d;
int index_post_a, index_post_b,index_post_c,index_post_d;
int giliran_lokal;
//float
float fdata_tunggal_simpan;

//struct
struct tabel_sumber tsumber[JUMLAH_THREAD];
struct tabel_posting tposting[JUMLAH_THREAD];

struct t_data_float data_float;
struct t_xdata xdata;

struct t_xdata *p_xdata;
struct t_data_float *pdata_float;

struct d3_data eth_loc_data;
struct t_loc_data loc_data[10];
//bool
bool saatnya_simpan;

//FIle
FILE *fp;

void *thread_result;
char cTemp[16],cwaktu_tampil[64];

//Thread
pthread_t a_thread[JUMLAH_THREAD];
pthread_t post_thread[JUMLAH_THREAD];

bool th_selesai[JUMLAH_THREAD],th_joined[JUMLAH_THREAD];
bool th_post_selesai[JUMLAH_THREAD],th_post_joined[JUMLAH_THREAD];

bool telah_error;

//Bulan

Glib::ustring bulan[12]={"Januari",
						"Februari",
						"Maret",
						"April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"};


int max_tanggal[12]={31,28,31,30,31,30,31,31,30,31,30,31};

//Alarm switch buffer
float alarm_switch_buffer[30];
int buffer_counter;
#define BUFFER_DELAY 20	//maximum 30

//THREAD PENGAMBILAN DATA
void *thread_function(void *arg)
{
    //struct tabel_sumber tsumber_th = *(tabel_sumber *)arg;
    int index=*(int*) arg;
	
	std_ip_address=tsumber[index].ip_address;
	int port_num=tsumber[index].ip_port;
	printf("\n |--@ Thread %d => Koneksi ke: %s port: %d ",index, tsumber[index].ip_address.c_str(),port_num);
	
	if(tsumber[index].flag==21)
		ukuran_terima2[index]=main_client(std_ip_address,port_num,(char*)&(tsumber[index].buf_terima));
	else if(tsumber[index].flag==22) //PM server
	{
		int nomer_stack=tsumber[index].no_stack;
		ukuran_terima2[index]=main_client_stack(std_ip_address,port_num,(char*)&(tsumber[index].buf_terima),nomer_stack);
	}	
	
	th_selesai[index]=true;
    //printf("Bye from %d\n", tsumber_th.index);
	if(ukuran_terima2[index]>0)
	{
		printf(" |  |--@ Thread %d Sukses: %d byte data [%s]\n", index,ukuran_terima2[index],&(tsumber[index].buf_terima));
		
		
		tsumber[index].status_koneksi=STATUS_OK;
	}
	else if(ukuran_terima2[index]<0)
	{
		printf(" |  |--@ Gagal koneksi ke sumber data");
		tsumber[index].status_koneksi=STATUS_NOT_FOUND;
	}
	pthread_exit(NULL);
}

void *thread_posting(void *arg)
{
	int index=*(int*) arg;
	
	std_ip_address=tposting[index].ip_address;
	int port_num=tposting[index].ip_port;
	printf("\n |--@ Thread %d => Koneksi ke: %s port: %d ",index, tposting[index].ip_address.c_str(),port_num);
	
	main_client_sendbuf (std_ip_address,port_num,(char *) &eth_loc_data, sizeof (eth_loc_data));
	//main_client(std_ip_address,port_num,(char*)&(tposting[index].buf_terima));
   //kirim data ke simple monitor
   /*if (FormUtama->Server1->Active == true)
   {
          for (i=0; i<FormUtama->Server1->Socket->ActiveConnections; i++)
          {
               Server1->Socket->Connections[i]->SendBuf((char *) &eth_loc_data, sizeof (eth_loc_data));
               Memo1->Lines->Add("-**-> "+FormUtama->Server1->Socket->Connections[i]->RemoteAddress+ ": U :"+IntToStr(giliran_lokal));
          }
   }*/
	
	th_post_selesai[index]=true;
	pthread_exit(NULL);
}

void main_window::on_buttonbuka_clicked()
{  
	int result;
	char cTemp[32];
	Glib::ustring uTemp;
	
	printf("Button Buka Clicked\n");
	
	db_dialog *db_dlg = new class db_dialog();
	
	uTemp.assign(kfg.db_host);
	db_dlg->entry_host->set_text(uTemp);//"192.168.1.13");
	
	uTemp.assign(kfg.db_port);
	db_dlg->entry_port->set_text(uTemp);
	
	uTemp.assign(kfg.db_username);
	db_dlg->entry_username->set_text(uTemp);
	
	uTemp.assign(kfg.db_pass);
	db_dlg->entry_password->set_text(uTemp);
	db_dlg->entry_password->set_visibility(false);
	
	uTemp.assign(kfg.nama_db);
	db_dlg->entry_namadb->set_text(uTemp);
	
	result=db_dlg->run();
	
	switch (result)
	{
		case GTK_RESPONSE_OK:
			printf("DIALOG OK\n");
			uTemp=db_dlg->entry_host->get_text();
			printf("Host: %s\n",uTemp.c_str());
			strcpy(kfg.db_host,uTemp.c_str());//"192.168.1.13");
			
			uTemp=db_dlg->entry_port->get_text();
			strcpy(kfg.db_port,uTemp.c_str());
			
			uTemp=db_dlg->entry_username->get_text();
			strcpy(kfg.db_username,uTemp.c_str());			
			
			uTemp=db_dlg->entry_password->get_text();
			strcpy(kfg.db_pass,uTemp.c_str());
	
			uTemp=db_dlg->entry_namadb->get_text();
			strcpy(kfg.nama_db,uTemp.c_str());
			
			SimpanKonfig (&kfg);
			//KonekDB ();
			this->UpdateTreeView(-1,0);//,*iter);
		break;
		default:
			printf("DIALOG CANCEL\n");
		break;//label_status_waktu
	}

	printf("Selesai buat instance dari class db_setting\n");
	
	delete db_dlg;
}

main_window::~main_window()
{
	
	printf("[Dekonstruktor main window]\n");
	MYQ.Close();
	CekDB();
	printf("---------- BYE BYE ----------\n");
	add_log("======== MONITA APP CLOSING =========",0,0);
	add_log("============ BYE BYE ===============",0,0);
}

main_window::main_window()
{
	printf("Mulai main_window\n");
	this->init_log();
	int level;
	int iwidth,iheight;
	
	timer_on=false;
	timer2_on=false;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;
	
	refTreeSelection= this->treeview1->get_selection();
	iter = refTreeSelection->get_selected();
	
	this->resize(800,600);
	this->set_default_size(800, 600);
	
	//init icon
	printf("icon/emblem-generic16.png\n");
	icon_generic=Gdk::Pixbuf::create_from_file("icon/emblem-generic16.png");
	printf("icon/emblem-default.png\n");
	icon_default=Gdk::Pixbuf::create_from_file("icon/emblem-default.png");
	printf("icon/dialog-warning.png\n");
	icon_warning=Gdk::Pixbuf::create_from_file("icon/dialog-warning.png");
	printf("icon/dialog-error.png\n");
	icon_error=Gdk::Pixbuf::create_from_file("icon/dialog-error.png");
	printf("icon/emblem-info.png\n");
	icon_info=Gdk::Pixbuf::create_from_file("icon/emblem-info.png");
	printf("icon/emblem-important.png\n");
	icon_important=Gdk::Pixbuf::create_from_file("icon/emblem-important.png");
	printf("icon/dialog-error.png\n");
	icon_alarm1=Gdk::Pixbuf::create_from_file("icon/dialog-error.png");
	printf("icon/dialog-error.png\n");
	icon_alarm2=Gdk::Pixbuf::create_from_file("icon/dialog-error.png");
	printf("icon loading selesai\n");
	
	icon_persh=Gdk::Pixbuf::create_from_file("emblem-persh.png");
	icon_dept=Gdk::Pixbuf::create_from_file("emblem-dept.png");
	icon_equip=Gdk::Pixbuf::create_from_file("emblem-equipment.png");
	icon_group=Gdk::Pixbuf::create_from_file("emblem-group.png");
	icon_titik1=Gdk::Pixbuf::create_from_file("emblem-titik.png");
	icon_titik2=Gdk::Pixbuf::create_from_file("emblem-titik-nc-16.png");
	
	//progress_koneksi->set_height(200);
	printf("LoadConfig ()\n");
	this->add_log("Load file konfigurasi",0,0);
	LoadConfig();
	
	//Init paramater treeview
	tree_ada_kolom=false;	
	m_refTreeModel = Gtk::TreeStore::create(m_Columns);
	treeview1->set_model(m_refTreeModel);
	
	kolom_log_ada=false;
	//Init paremeter waktu
	id_waktu_simpan=0;
	long_tick=0;
	
	//Init Parameter listview
	kolom_data_ada=false;
	kolom_status_ada=false;
	
	//Tes koneksi database
	if(this->KonekDB(1))
	{
		printf("Gagal saat koneksi database!\n");
	}
	else
	{
		this->CloseDB(true);
		//Isi TreeView	
		this->UpdateTreeView(-1,0);//,*iter);
		
		//kopi parameter db ke MYQLogging
		//memcpy(&MYQLogging,(void*)&MYQ,sizeof(MyQuery));
	}
	
	//Apply konfigurasi
	if(kfg.mode==10)
	{	
		button_logging_data->set_sensitive(false);
		//vpaned_status->set_visible(false);
	}
	else
	{
		button_logging_data->set_sensitive(true);
		//vpaned_status->set_visible(true);
		vpaned_status->show();
	}

	
	//Inisialisasi List view data dan tanggal
	int itanggal,ibulan,itahun;
	int ijam,imenit,idetik;
	
	char cwaktu[32];
	time_t the_timelist;
	
	(void) time(&the_timelist);
	tm_pointer = localtime(&the_timelist);
	
	printf("[Inisialisasi Waktu]\n");
	strftime(cwaktu,32,"%d",tm_pointer);
	itanggal=atoi(cwaktu);
	printf(" |-- tanggal: %d\n",itanggal);
	
	strftime(cwaktu,32,"%m",tm_pointer);
	ibulan=atoi(cwaktu);
	printf(" |-- bulan: %d\n",ibulan);
	
	strftime(cwaktu,32,"%Y",tm_pointer); //%H:%M:%S
	itahun=atoi(cwaktu);
	printf(" |-- tahun: %d\n",itahun);
	
	strftime(cwaktu,32,"%H",tm_pointer);//%H:%M:%S
	ijam=atoi(cwaktu);
	printf(" |-- jam: %d\n",ijam);
	
	strftime(cwaktu,32,"%M",tm_pointer);
	imenit=atoi(cwaktu);
	printf(" |-- menit: %d\n",imenit);
	
	strftime(cwaktu,32,"%S",tm_pointer);
	idetik=atoi(cwaktu);
	printf(" |-- detik: %d\n",idetik);
	
	
	spin_tanggal->set_value(itanggal);
	spin_bulan->set_value(ibulan);
	spin_tahun->set_value(itahun);
	
	Glib::ustring usTemp;
	char asTemp[512];
	
	sprintf(asTemp,"<b>%d-%s-%d\n%d:%d:%d</b>",itanggal,bulan[ibulan-1].c_str(),itahun,ijam,imenit,idetik);
	usTemp.assign(asTemp);
	
	label_status_waktu->set_text(usTemp);
	label_status_waktu->set_use_markup(true);
	
	//Inisialisasi jumlah sumber dan jumlah post_thread
	jumlah_sumber=0;
	jumlah_post=0;
	
	//Update listview
	this->UpdateListView(-1,0);
	
	//Inisialisai port 
	port_num=5001;
	
	//Inisiasi variabel pengatur thread
	
	//Inisialisasi Menu Popup
	Gtk::Image *image_tambah = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-add"), Gtk::IconSize(1)));
	menu_popup_isi=false;
	
	  //Fill popup menu titik ukur
	if(menu_popup_isi==false)
	{
		Gtk::Menu::MenuList& menulist = m_Menu_Popup.items();
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Hapus Titik Ukur",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_hapus) ) );
		
		menulist.push_back(Gtk::Menu_Helpers::SeparatorElem());
		
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Informasi Titik Ukur",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_edit) ) );
		menu_popup_isi=true;
	}
	
	m_Menu_Popup.accelerate(*this);
	
	//Fill popup menu group
	popup_group_isi=false;
	if(popup_group_isi==false)
	{
		Gtk::Menu::MenuList& menulist = popup_group.items();
	
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Tambah Titik Ukur",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_tambah) ) );
		
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Hapus Group",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_hapus) ) );
		
		menulist.push_back(Gtk::Menu_Helpers::SeparatorElem());
   		// separator_persh = (Gtk::MenuItem *)&menulist->items().back();
		
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Informasi Group",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_edit) ) );
	}
	popup_group.accelerate(*this);
	
	//Fill popup menu persh
	popup_persh_isi=false;
	if(popup_persh_isi==false)
	{
		Gtk::Menu::MenuList& menulist = popup_persh.items();
	
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Tambah Departemen",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_tambah) ) );
		
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Hapus Perusahaan",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_hapus) ) );
		menulist.push_back(Gtk::Menu_Helpers::SeparatorElem());
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Informasi Perusahaan",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_edit) ) );
	}
	popup_persh.accelerate(*this);

	//Fill popup menu Departemen
	popup_dept_isi=false;
	if(popup_dept_isi==false) //jelaslah
	{
		Gtk::Menu::MenuList& menulist = popup_dept.items();
	
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Tambah Peralatan",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_tambah) ) );
		
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Hapus Departemen",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_hapus) ) );
		
		menulist.push_back(Gtk::Menu_Helpers::SeparatorElem());
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Informasi Departemen",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_edit) ) );
	}
	popup_dept.accelerate(*this);
	
	//Fill popup menu Equipment
	popup_equip_isi=false;
	if(popup_equip_isi==false) //jelaslah
	{
		Gtk::Menu::MenuList& menulist = popup_equip.items();
	
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Tambah Group",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_tambah) ) );
		
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Hapus Peralatan",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_hapus) ) );
		
		menulist.push_back(Gtk::Menu_Helpers::SeparatorElem());
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Informasi Peralatan",
		  sigc::mem_fun(*this, &main_window::on_menu_file_popup_edit) ) );
	}
	popup_equip.accelerate(*this);
	
	//Menu Popup untuk data view
	data_popup_isi=false;
	if(data_popup_isi==false) //jelaslah
	{
		Gtk::Menu::MenuList& menulist = data_popup.items();
		
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Hapus data",
		  sigc::mem_fun(*this, &main_window::on_data_popup_hapus) ) );
		
		menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Informasi data",
		  sigc::mem_fun(*this, &main_window::on_data_popup_info) ) );
		//menulist.push_back(Gtk::Menu_Helpers::SeparatorElem());
		//menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Informasi Peralatan",
		//  sigc::mem_fun(*this, &main_window::on_menu_file_popup_edit) ) );
	}
	data_popup.accelerate(*this);
	
	delete image_tambah;
	//Inisialisasi variabel
	strcpy(monita1_check_string,"monita1");
	
	//Curve
	//curve1->set_curve_type();
	//curve1->
	
	time_counter=0;
	telah_error=false;
	//Timer
	//m_connection_id_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this,
    //          &main_window::on_timeout), 1000 );
	 
	//m_connection_id_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this,
    //          &main_window::on_timeout_2),2000 );
	
	
	buffer_counter=0;
	for(int i=0;i<BUFFER_DELAY;i++)
	{
		alarm_switch_buffer[i]=0;
	}
	//show_all_children();
}
bool main_window::on_timeout_2()
{
	
	if(telah_error)
		return false;

	if(!timer2_on)
	{
		//jika tiba2 timer dimatikan, maka cancel semua thread yang masih berjalan
		time_counter=2; //Cancel dan matikan thread
		
		//return false;
	}
	
	char sTemp[512];
	//Periksa apakah database siap?
	if(!MYQLog.isConnected)
	{
		if(MYQLog.init_lengkap()!=1)
		{
			printf("Gagal melakukan inisialisasi database\n");
			Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
			dialog.set_secondary_text("Periksa parameter koneksi database");
			
			dialog.run();
			return false;
		}
	}
	
	time_t the_time;
	(void) time(&the_time);
	tm_ptr = localtime(&the_time);
	
	strftime(waktu,32,"%Y%m%d-%H%M%S",tm_ptr);
	strftime(cwaktu_tampil,64,"%d-%m-%Y\n%H:%M:%S",tm_ptr);
	
	//20080210-102346
	printf("[%d]-- TIME:%s\n",time_counter,&waktu,waktu);
	sprintf(sTemp,"[%d]-- TIME:%s\n",time_counter,&waktu,waktu);
	printlog(sTemp,0);
	
	label_status_waktu->set_text(cwaktu_tampil);
	
	if(time_counter==0)
	{
		progress_koneksi->set_fraction(0.0);
		//start thread
		printf(" |-- INIT THREAD SUMBER DATA\n");
		for(index_sumber_a=0;index_sumber_a<jumlah_sumber;index_sumber_a++)
		{
				//Inisialisasi variabel kontrol thread
			th_selesai[index_sumber_a]=false;
			th_joined[index_sumber_a]=false;
			ukuran_terima2[index_sumber_a]=0;
			memset(&(buf_data[index_sumber_a]),0x00,512);
			index_sumber[index_sumber_a]=index_sumber_a;
			
			printf(" |--* Start Thread %d (%s)",index_sumber_a,tsumber[index_sumber_a].ip_address.c_str());
			res = pthread_create(&(a_thread[index_sumber_a]), NULL, 
								thread_function, (void*)&index_sumber[index_sumber_a]);
			if (res != 0)
			{
				perror(" -> Thread creation failed\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				sisa_thread++;
				//printf("-> %s OK\n",tsumber[index_sumber_a].ip_address.c_str());
			}
			printf ("\n");
		}		
		
		//buat thread posting data disini saja
		printf(" |-- INIT THREAD POST DATA\n");
		for(index_post_a=0;index_post_a<jumlah_post;index_post_a++)
		{
			//Inisialisasi variabel kontrol thread
			th_post_selesai[index_post_a]=false;
			th_post_joined[index_post_a]=false;
			ukuran_terima2[index_post_a]=0;
			
			memset(&(buf_data[index_post_a]),0x00,512);
			index_post[index_post_a]=index_post_a;
			
			printf(" |--* Start Thread %d (%s)",index_post_a,tposting[index_post_a].ip_address.c_str());
			res = pthread_create(&(post_thread[index_post_a]), NULL, 
								thread_posting, (void*)&index_post[index_post_a]);
			if (res != 0) 
			{
				perror(" -> Thread creation failed\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				sisa_thread_post++;
				//printf("-> %s OK\n",tsumber[index_sumber_a].ip_address.c_str());
			}
			printf ("\n");
		}
		
		progress_koneksi->set_fraction(0.25);
		//Sambil menunggu, hapus database data_jaman yang telah lampau
		this->HapusDataJaman(id_waktu_simpan); //Yang dihapus adalah waktu 2 periode sebelumnya
		
		time_counter++;	
	}
	else if(time_counter==1)
	{
		progress_koneksi->set_fraction(0.30);
		//cek thread
		printf(" |-- CEK THREAD SUMBER DATA\n");
		for(index_sumber_b=0;index_sumber_b<jumlah_sumber;index_sumber_b++)
		{
			printf(" |--|-- [%d][%d]",th_selesai[index_sumber_b],th_joined[index_sumber_b]); 
			if(th_selesai[index_sumber_b])
			{
				//printf(" Thread %d sudah selesai",index_sumber_b);
				
				res = pthread_join(a_thread[index_sumber_b], &thread_result);
				if (res != 0) {
					perror(" ->Join Failed\n");
					exit(EXIT_FAILURE);
				}
				else
				{
					sisa_thread--;
					th_joined[index_sumber_b]=true;
					printf(" ->Join OK\n");
				}
			}
			else 
			{
				//thread belum selesai, lanjutkan timer
				printf("->Wait\n");

			}
		}
		printf(" |-- Sisa thread: %d\n",  sisa_thread);
		
		//Cek progres koneksi Post data
		printf(" |-- CEK THREAD POST DATA\n");
		for(index_post_b=0;index_post_b<jumlah_post;index_post_b++)
		{
			printf(" |--|-- [%d][%d]",th_post_selesai[index_post_b],th_post_joined[index_post_b]); 
			if(th_post_selesai[index_post_b])
			{
				//printf(" Thread %d sudah selesai",index_sumber_b);
				
				res = pthread_join(post_thread[index_post_b], &thread_result);
				if (res != 0) {
					perror(" ->Join Failed\n");
					exit(EXIT_FAILURE);
				}
				else
				{
					sisa_thread_post--;
					th_post_joined[index_post_b]=true;
					printf(" ->Join OK\n");
				}
			}
			else 
			{
				//thread belum selesai, lanjutkan timer
				printf("->Wait\n");

			}
		}
		printf(" |-- Sisa thread post data: %d\n",  sisa_thread_post);
		
		progress_koneksi->set_fraction(0.5);
		time_counter++;

	}
	else if(time_counter==2)
	{
		//cek sekaligus cancel thread
		printf(" |-- CEK DAN CANCEL THREAD SUMBER DATA\n");
		progress_koneksi->set_fraction(0.55);
		for(index_sumber_c=0;index_sumber_c<jumlah_sumber;index_sumber_c++)
		{
			printf(" |--|-- [%d][%d]",th_selesai[index_sumber_c],th_joined[index_sumber_c]); 
			if((th_selesai[index_sumber_c]==true)&& (th_joined[index_sumber_c]==false)) //sudah selesai dan belum dijoin
			{
				//printf(" Thread %d SUDAH selesai BELUM Join",index_sumber_c);
				printf(" %d Koneksi OK!",index_sumber_c);
				res = pthread_join(a_thread[index_sumber_c], &thread_result);
				if (res != 0) {
					
					perror(" -> Join failed");
					tsumber[index_sumber_c].status_koneksi=STATUS_ERROR;
					exit(EXIT_FAILURE);
				}
				else
				{
					th_joined[index_sumber_c]=true;
					sisa_thread--;
					printf("-> Join OK\n");
					
					//Not found dan OK sama menghentikan thread dengan baik. 
					if(tsumber[index_sumber_c].status_koneksi!=STATUS_NOT_FOUND)
						tsumber[index_sumber_c].status_koneksi=STATUS_OK;
				}
			}
			else if((th_selesai[index_sumber_c]==false)&& (th_joined[index_sumber_c]==false)) //belum selesai dan belum dijoin
			{
				//printf(" Thread %d BELUM selesai -> Cancel paksa",index_sumber_c);
				printf(" %d Timeout!",index_sumber_c);
				tsumber[index_sumber_c].status_koneksi=STATUS_TIMEOUT;
				//Yak waktu habis, bunuh threadnya
				res = pthread_cancel(a_thread[index_sumber_c]);
				if (res != 0) {
					printf(" -> Cancel FAILED\n");
					perror(" -> Thread cancelation failed\n");
					tsumber[index_sumber_c].status_koneksi=STATUS_ERROR;
					exit(EXIT_FAILURE);
				}
				else
				{
					printf("->Cancel Paksa OK");
					//printf(" -> OK");
				}
				
				//printf(" |--|-- Waiting for thread to finish...\n");
				//printf(" -> Join");
				res = pthread_join(a_thread[index_sumber_c], &thread_result);
				if (res != 0) {
					tsumber[index_sumber_c].status_koneksi=STATUS_ERROR;
					perror(" ->Join Failed");
					exit(EXIT_FAILURE);
				}
				else
				{
					printf(" ->Join Paksa OK\n");
					th_joined[index_sumber_c]=true;
					sisa_thread--;
					//printf(" -> Join OK -> Data %d Header [%s]\n",
					//	   ukuran_terima2[index_sumber_c],&(tsumber[index_sumber_c].buf_terima));
				}
			}
			else
			{
				printf(" Selesai+Join OK\n");
				//	   index_sumber_c,ukuran_terima2[index_sumber_c],&(tsumber[index_sumber_c].buf_terima));
				
				//Not found dan OK sama menghentikan thread dengan baik. 
				if(tsumber[index_sumber_c].status_koneksi!=STATUS_NOT_FOUND)
					tsumber[index_sumber_c].status_koneksi=STATUS_OK;
			}
		}
		printf(" |-- Sisa Thread: %d\n",sisa_thread);
		
		//CEK POST DATA
		printf(" |-- CEK DAN CANCEL THREAD POST DATA\n");
		for(index_post_c=0;index_post_c<jumlah_post;index_post_c++)
		{
			printf(" |--|-- %d [%d][%d]",index_post_c, th_post_selesai[index_post_c],th_post_joined[index_post_c]); 
			if((th_post_selesai[index_post_c]==true)&& (th_post_joined[index_post_c]==false)) //sudah selesai dan belum dijoin
			{
				//printf(" Thread %d SUDAH selesai BELUM Join",index_post_c);
				printf("Koneksi OK!");
				res = pthread_join(post_thread[index_post_c], &thread_result);
				if (res != 0) {
					
					perror(" -> Join failed");
					tposting[index_post_c].status_koneksi=STATUS_ERROR;
					exit(EXIT_FAILURE);
				}
				else
				{
					th_post_joined[index_post_c]=true;
					sisa_thread_post--;
					printf("-> Join OK\n");
					
					//Not found dan OK sama menghentikan thread dengan baik. 
					if(tposting[index_post_c].status_koneksi!=STATUS_NOT_FOUND)
						tposting[index_post_c].status_koneksi=STATUS_OK;
				}
			}
			else if((th_post_selesai[index_post_c]==false)&& (th_post_joined[index_post_c]==false)) //belum selesai dan belum dijoin
			{
				//printf(" Thread %d BELUM selesai -> Cancel paksa",index_sumber_c);
				printf(" %d Timeout!",index_post_c);
				tposting[index_post_c].status_koneksi=STATUS_TIMEOUT;
				
				//Yak waktu habis, bunuh threadnya
				res = pthread_cancel(post_thread[index_post_c]);
				if (res != 0) {
					printf(" -> Cancel FAILED (res:%d)\n",res);
					perror(" -> Thread cancelation failed\n");
					tposting[index_post_c].status_koneksi=STATUS_ERROR;
					exit(EXIT_FAILURE);
					//stop timer
					//timer2_on=false;
					//this->add_log("ERROR: Thread cancelation gagal. Data logging dihentikan",0,0);
					//exit(EXIT_FAILURE);
				}
				else
				{
					printf("->Cancel Paksa OK");
					//printf(" -> OK");
				}
				
				//printf(" |--|-- Waiting for thread to finish...\n");
				//printf(" -> Join");
				res = pthread_join(post_thread[index_post_c], &thread_result);
				if (res != 0) {
					tposting[index_post_c].status_koneksi=STATUS_ERROR;
					perror(" ->Join Failed");
					exit(EXIT_FAILURE);
				}
				else
				{
					printf(" ->Join Paksa OK\n");
					th_post_joined[index_post_c]=true;
					sisa_thread_post--;
					//printf(" -> Join OK -> Data %d Header [%s]\n",
					//	   ukuran_terima2[index_sumber_c],&(tsumber[index_sumber_c].buf_terima));
				}
			}
			else
			{
				printf(" Selesai+Join OK\n");
				//	   index_sumber_c,ukuran_terima2[index_sumber_c],&(tsumber[index_sumber_c].buf_terima));
				
				//Not found dan OK sama menghentikan thread dengan baik. 
				if(tposting[index_post_c].status_koneksi!=STATUS_NOT_FOUND)
					tposting[index_post_c].status_koneksi=STATUS_OK;
			}
		}
		
		printf(" |-- Reset Counter\n");
		//reset counter
		progress_koneksi->set_fraction(0.75);
		time_counter++;
		return timer2_on; //Jika timer mati, langsung keluar
	}
	else if(time_counter==3)
	{
		//simpan datanya
		printf(" |--# Simpan data yang sudah terkumpul\n");
		progress_koneksi->set_fraction(0.8);
		//Simpan Waktu
		utemp_global="INSERT INTO waktu(waktu) VALUES('";
		utemp_global.append(waktu);
		utemp_global.append("')");
		strcpy(MYQLog.Text,utemp_global.c_str());
		printf(" |--* Query: %s\n",MYQLog.Text);
		
		try
		{
			printf(" |-- Insert data\n");
			MYQLog.Insert();
			printf(" |--|-- Selesai insert data waktu. Cari ID waktu\n");
		}
		catch(...)
		{
			printf(" |--|-- ERROR saat menginput data waktu\n");
			return -1;
		}
		
		//Cari id_waktu_simpan yang terakhir tersimpan
		id_waktu_simpan=MYQLog.last_id();
		
		//tentukan pakah sekarang saatnya menyimpan data 
		strftime(waktu_simpan_sekarang,32,"%Y%m%d-%H%M",tm_ptr);
		printf(" |-- waktu sekarang: %s, simpan yang lalu: %s\n",
			   waktu_simpan_sekarang,waktu_simpan_lalu);
		
		if(strncmp(waktu_simpan_lalu,waktu_simpan_sekarang,sizeof(waktu_simpan_sekarang)))
	   	{
			saatnya_simpan=true;
			strncpy(waktu_simpan_lalu,waktu_simpan_sekarang,sizeof(waktu_simpan_sekarang));
	   	}
		else
		   saatnya_simpan=false;
		   	
		progress_koneksi->set_fraction(0.9);
		
		for(index_sumber_d=0;index_sumber_d<jumlah_sumber;index_sumber_d++)
		{
			asTemp=tsumber[index_sumber_d].ip_address;
			printf(" |  |--* Simpan data sumber %d: (%s)\n",
				   index_sumber_d,asTemp.c_str());
			
			if(tsumber[index_sumber_d].status_koneksi==STATUS_TIMEOUT)
			{
				printlog (asTemp + ": Timeout",0);
				printf(" |  |--* Komunikasi Timeout\n");
				continue;
			}
			if(tsumber[index_sumber_d].status_koneksi==STATUS_NOT_FOUND)
			{
				printf(" |  |--* Sumber tidak ditemukan\n");
				continue;
			}
	
			if(ukuran_terima<0)
			{
				printf(" |  |--* Komunikasi ERROR\n");
				tsumber[index_sumber_d].status_koneksi=STATUS_DATA_INVALID;
			}
			else
			{
				printf(" |  |--* Koneksi OK");

				//cek ukuran apakah sama dengan ukuran struct x_data
				if(sizeof(t_xdata)-ukuran_terima2[index_sumber_d])
				{
					//Ukuran berbeda
					printf("->Ukuran data berbeda. Data dibuang.\n");
					tsumber[index_sumber_d].status_koneksi=STATUS_DATA_INVALID;
					continue;
					//return -2;
				}
				
				//Cek header apakah benar (header harusnya 'monita1')
				if(strncmp((char*)&(tsumber[index_sumber_d].buf_terima),monita1_check_string,sizeof(monita1_check_string)))
				{
					//strncpy(cTemp,(const char*) &(buf_data[i]),sizeof(monita1_check_string));
					printf("->Data check: header invalid [%s] seharusnya [%s]\n",
						   &(tsumber[index_sumber_d].buf_terima),monita1_check_string);
					
					tsumber[index_sumber_d].status_koneksi=STATUS_DATA_INVALID;
					continue;
					//return -1;
				}
				else
				{
					tsumber[index_sumber_d].status_koneksi=STATUS_OK;
					printf("->Data check: OK\n");
				}
				//sampai disini seharusnya penomeran 
				
				//jika benar, masukkan ke masing2 data titik ukur
				//kopi alamat data ke pointer struct data
				p_xdata=(t_xdata*) &(tsumber[index_sumber_d].buf_terima);
				pdata_float=(t_data_float*) &p_xdata->buf;
				
				printf(" |  |--* Simpan data\n");
				for(int k=0;k<=tsumber[index_sumber_d].jumlah_kanal;k++)
				{
					printf(" |  |  |--* Kanal %d\n",k+1);
					
					//Kalibrasi disini
					
					//fdata_tunggal_simpan=pdata_float->data[k];
					fdata_tunggal_simpan=pdata_float->data[k]*tsumber[index_sumber_d].titik[k].kalibrasi_a
										+ tsumber[index_sumber_d].titik[k].kalibrasi_b;
					
					id_titik_simpan=tsumber[index_sumber_d].titik[k].id_titik;
					printf(" |  |  |--* data:%0.2f ->id: %d ((%0.2f x %0.2f)+ %0.2f)\n",
						   fdata_tunggal_simpan,id_titik_simpan,pdata_float->data[k],
						   tsumber[index_sumber_d].titik[k].kalibrasi_a,
							tsumber[index_sumber_d].titik[k].kalibrasi_b);
					
					if(id_titik_simpan)
					{
						//Tiap saat disimpan di data_jaman
						sprintf(sTemp,"INSERT DELAYED INTO data_jaman (id_titik, data, waktu) ");
                    	sprintf(sTemp,"%s VALUES('%d','%f','%s')",sTemp,id_titik_simpan,fdata_tunggal_simpan,waktu);
						//printf(" |  |  |  |--* Query: %s\n",sTemp);
						printf(" |  |  |  |--* Simpan data jaman: ");
					
						strcpy(MYQLog.Text,sTemp);
						if(MYQLog.Insert())
						{
							printf("ERROR\n");
							continue;
						}
						else
							printf("OK\n");
		
						//CEK ALARM
						if(fdata_tunggal_simpan<tsumber[index_sumber_d].titik[k].range_min)
						{
							sprintf(sTemp,"ALARM: Data Titik %d (%s) diluar jangkauan ukur",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							add_log (sTemp,LOG_ALARM_2,-1);
						}
						else if(fdata_tunggal_simpan>tsumber[index_sumber_d].titik[k].range_max)
						{
							sprintf(sTemp,"ALARM: Data Titik %d (%s) diluar jangkauan ukur",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							//alarm_teks=Glib::ustring::compose("ALARM: Data Titik %1 (%s) diluar jangkauan ukur",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							add_log (sTemp,LOG_ALARM_2,-1);
						}
						else if((fdata_tunggal_simpan<tsumber[index_sumber_d].titik[k].alarm_low)&&
						   (tsumber[index_sumber_d].titik[k].alarm_setting & 0x01))
						{
							sprintf(sTemp,"ALARM: Data Titik %d (%s) rendah",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							//alarm_teks=Glib::ustring::compose("ALARM: Data Titik %1 (%s) rendah",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							add_log (sTemp,LOG_ALARM_1,1);
						}
						else if((fdata_tunggal_simpan<tsumber[index_sumber_d].titik[k].alarm_low)&&
						   (tsumber[index_sumber_d].titik[k].alarm_setting & 0x02))
						{
							sprintf(sTemp,"ALARM: Data Titik %d (%s) sangat rendah",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							//alarm_teks=Glib::ustring::compose("ALARM: Data Titik %1 (%s) sangat rendah",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							add_log (sTemp,0,2);
						}
						else if((fdata_tunggal_simpan>=tsumber[index_sumber_d].titik[k].alarm_high)&&
						   (tsumber[index_sumber_d].titik[k].alarm_setting& 0x04))
						{
							sprintf(sTemp,"ALARM: Data Titik %d (%s) tinggi (0x%X)",
									id_titik_simpan,
									tsumber[index_sumber_d].titik[k].nama_titik,
									tsumber[index_sumber_d].titik[k].alarm_setting);
							
							alarm_teks.assign(sTemp);
							add_log (alarm_teks,LOG_ALARM_1,1);
							
							//khusus pintu
							/*if(tsumber[index_sumber_d].titik[k].alarm_setting & 0x20)  //alarm pintu
							{
								add_log("ALARM: Pintu terbuka",LOG_ALARM_1,0);
								//sprintf (sTemp,"ls %s","/home");
								if(buffer_counter>BUFFER_DELAY)
									sprintf(sTemp,"alarmKeras hidup!","/home");
								//else
								//	sprintf(sTemp,"alarmKeras mati!","/home");
								printf(" |-- Kirim command: %s\n",sTemp);
								add_log (sTemp,LOG_INFO,0);
								
								fp = popen (sTemp,"r");	
								fscanf (fp,"%s",sTemp);
								printf(" |-- Hasil command: %s\n",sTemp);
								
								//add_log(sTemp,LOG_INFO,0);
							}
							else if(tsumber[index_sumber_d].titik[k].alarm_setting & 0x40) //tombol pembunuh alarm
							{
								add_log("SET: Alarm off",LOG_INFO,0);
								//sprintf (sTemp,"ls %s","/home");
								sprintf(sTemp,"alarmKeras mati!","/home");
								fp = popen (sTemp,"r");
								fscanf (fp,"%s",sTemp);
								add_log(sTemp,LOG_INFO,0);
								printf(" |--Hasil command: %s\n",sTemp);
								buffer_counter=0;
							}*/
						}
						else if((fdata_tunggal_simpan>=tsumber[index_sumber_d].titik[k].alarm_high_high)&
						   (tsumber[index_sumber_d].titik[k].alarm_setting & 0x08))
						{
							sprintf(sTemp,"ALARM: Data Titik %d (%s) sangat tinggi (0x%X)",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							//alarm_teks=Glib::ustring::compose("ALARM: Data Titik %1 (%s) sangat tinggi (0x%X)",id_titik_simpan,tsumber[index_sumber_d].titik[k].nama_titik);
							add_log (sTemp,LOG_ALARM_1,2);
						}
						
						
						//Khusus switch alarm diperlakukan lain
						if(tsumber[index_sumber_d].titik[k].alarm_setting & 0x40) //tombol pembunuh alarm
						{
							
							if(alarm_switch_buffer[0]>tsumber[index_sumber_d].titik[k].alarm_high)
							{
								add_log("SET: Alarm off. Reset buffer alarm",LOG_INFO,0);
								//sprintf (sTemp,"ls %s","/home");
								sprintf(sTemp,"alarmKeras mati!","/home");
								fp = popen (sTemp,"r");
								fscanf (fp,"%s",sTemp);
								
								printf(" |--Hasil command: %s\n",sTemp);
								
								//reset buffer
								buffer_counter=0;
								for(int i=0;i<BUFFER_DELAY;i++)
									alarm_switch_buffer[i]=0;
							}
							else
								//buffer_counter++;
								push_buffer_switch(1);
								
						}
						
						if(saatnya_simpan)
						{
							printf(" |  |  |  |--* Simpan data tunggal\n"); 
							//Tiap Menit simpan data ke database
							//5 Agustus -> pindah data ke data_harian
							//sprintf(sTemp,
							//	"INSERT INTO data_harian(id_titik_ukur,id_waktu,data_tunggal) VALUES('%d','%d','%f')",
							//	id_titik_simpan,id_waktu_simpan,fdata_tunggal_simpan);	
							sprintf(sTemp,
								"INSERT INTO data_tunggal(id_titik_ukur,id_waktu,data_tunggal) VALUES('%d','%d','%f')",
								id_titik_simpan,id_waktu_simpan,fdata_tunggal_simpan);	
							
							
							printf(" |  |  |  |--* QUERY: %s\n",sTemp);
							printf(" |  |  |  |--* Simpan data tunggal: ");
							strcpy(MYQLog.Text,sTemp);
							if(MYQLog.Insert())
							{
								printf("ERROR\n");
								continue;
							}
							else
								printf("OK\n");
							
							//Tiap menit disimpan di data_harian
							sprintf(sTemp,"INSERT INTO data_harian(id_titik_ukur,id_waktu,data_tunggal)");
							sprintf(sTemp,"%s VALUES('%d','%d','%f')",sTemp,id_titik_simpan,id_waktu_simpan,fdata_tunggal_simpan);
							//printf(" |  |  |  |--* Query: %s\n",sTemp);
							printf(" |  |  |  |--* Simpan data temporary: ");
						
							strcpy(MYQLog.Text,sTemp);
							if(MYQLog.Insert())
							{
								printf("ERROR\n");						
								continue;
							}
							else
								printf("OK\n");
							
							//if(depth_level_sekarang==5)
							//	this->UpdateListView(depth_level_sekarang,id_titik_tampil_sekarang);
						}
						else
							printf(" |  |--*(tidak simpan data harian)\n");
					}
					
				}
			}
		}
		
		//Buat data untuk POSTING DATA
		giliran_lokal=0;
		
		strcpy(eth_loc_data.mon, "monita2");
		eth_loc_data.alamat = giliran_lokal;
		eth_loc_data.nomer = long_tick;
		strcpy(eth_loc_data.waktu, waktu);
		memcpy((char *) eth_loc_data.buf, (char *) &loc_data[giliran_lokal], sizeof (loc_data[0]));
		
		//Hapus file data_harian yang sudah kadaluarsa
		//jika ganti hari saja							
		strftime(tanggal_sekarang,32,"%Y%m%d",tm_ptr);
		printf(" |-- waktu sekarang: %s, simpan yang lalu: %s\n",
			   tanggal_sekarang,tanggal_yang_lalu);
		
		if(strncmp(tanggal_yang_lalu,tanggal_sekarang,sizeof(tanggal_yang_lalu)))
	   	{
			//Cari tanggal 7 hari yang lalu
			asTemp=cari_tanggal("",-7);
			   
			 //Cari id-nya
			sprintf(sTemp,"DELETE FROM data_harian WHERE id_waktu<=(select MAX(id_waktu) as max from waktu WHERE waktu.waktu like '%s%%')",asTemp.c_str());
			printf(" |-- Query: %s\n",sTemp);
			strcpy(MYQLog.Text,sTemp);
			   
			MYQLog.Delete();
			
			strncpy(tanggal_yang_lalu,tanggal_sekarang,sizeof(waktu_simpan_sekarang));
	   	}
		
		long_tick++;
		this->UpdateStatusSumber();
		progress_koneksi->set_fraction(1.0);
		time_counter=0;
	}
	
	//MONITOR DIRECTORY EMAIL
	//if(ada sumber directory)
	for(int i=0;i<jumlah_sumber_email;i++)
	{
		cek_mail_dir("/home/herry/mail-archive/");
	}	
	return true;
}

bool main_window::on_timeout()
{
	//printf("+\n");
	if(timer_on)
	{
		
		time_t the_time;
		(void) time(&the_time);
		tm_ptr = localtime(&the_time);
		
		strftime(waktu,32,"%Y%m%d-%H%M%S",tm_ptr);
		//20080210-102346
		printf("\nTIME:%s\n",&waktu,waktu);
		
		if(MYQ.isConnected==false)
		{
			printf("Koneksi database global\n");
			if(this->KonekDB(1)==1)
			{
				printf("Gagal koneksi ke database\n");
				timer_on=false;	
				
				
				Gtk::MessageDialog dialog(NULL, "Gagal koneksi ke database");
				dialog.set_secondary_text("Periksa parameter koneksi database");

				dialog.run();
			}
				
		}
		
		if(MYQ.isConnected)
		{
			//printf("==Logging Data==\n",waktu);
			this->logging_data(waktu);
			//printf("==Return dari logging data(%s)\n",waktu);
		}			
	}
	return true;
}

int main_window::UpdateTreeView(int level,int id)//,const Gtk::TreeModel::iterator& iter)//,Glib::TreeModel::Path path)
{
	printf("[UpdateTreeView] level: %d, id: %d\n",level,id);
	Glib::ustring uTemp,uPath,u_nama_group;  //uPath=String representation dari path
	Glib::ustring uid_titik;
	char cTemp[256];
	int jum_pers, jum_dep;
	int i,id_persh ;
	
	int id_equipment;
	int count_persh=0,
		count_dept=0,
	 	count_equip=0,
		count_group=0,
		count_titik=0;
	
	int id_sumber_temp,id_port_temp,id_kanal_temp;
	//Inisiasi isi treeview
	//create the Tree model:
		//All the items to be reordered with drag-and-drop:
	//treeview1->set_reorderable();
	
	//Create the Tree model:
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
	
	
	uPath="0";
	
	m_refTreeModel = Gtk::TreeStore::create(m_Columns);
	treeview1->set_model(m_refTreeModel);

	printf("Konek DB\n");
	this->KonekDB(5);
	
	if(MYQ.isConnected)
	{
		printf(" |-- Level 0\n");	

		uTemp="SELECT * FROM perusahaan";
		strcpy(MYQ.Text,uTemp.c_str());
		//printf(" |--* Query: %s\n",MYQ.Text);
		
		MYQ.Query();
		
		//CekDB();
		
		jum_pers=MYQ.jum_row;
		printf(" |--* Jumlah perusahaan: %d\n",jum_pers);
		
		if(jum_pers>0)
		{
			
			for(i=0;i<jum_pers;i++)
			{
				//Fill the TreeView's model
				
				Gtk::TreeModel::Row row =*(m_refTreeModel->append());
				//printf(" |--|--* isi Row\n");
				
				Glib::ustring unama_persh=MYQ.ambil_string("nama_pers");
				row[m_Columns.m_col_name] = unama_persh;			
				
				uTemp=MYQ.ambil_string("id_pers");
				id_persh=atoi(uTemp.c_str());
				row[m_Columns.m_col_id]=id_persh;
				printf(" |--|--[%d] id:%d\n",i,id_persh);
				
				
				row[m_Columns.icon]=icon_persh;//Gdk::Pixbuf::create_from_file("emblem-persh.png");
				
				//Cek path
				if((level==0)&&(id==id_persh))
				{
					uPath=Glib::ustring::compose("%1",i);
				}
				
				//QUERY DEPARTEMEN DIBAWAH PERUSAHAAN
				uTemp="SELECT * FROM departemen WHERE id_pers='" + uTemp + "'";
				strcpy(MYQMain[0].Text,uTemp.c_str());
				//printf(" |--|--* %s\n",MYQMain[0].Text);
				
				MYQMain[0].Query();
				
				int jum_dept=MYQMain[0].jum_row;
				printf(" |--|--[%s] Jumlah departemen: %d\n",unama_persh.c_str(),jum_dept);
				
				if(jum_dept>0)
				for(int j=0;j<jum_dept;j++)
				{
					Gtk::TreeModel::Row deptrow = *(m_refTreeModel->append(row.children()));
					
					Glib::ustring unama_dept=MYQMain[0].ambil_string("nama_dep");
					deptrow[m_Columns.m_col_name] =unama_dept;
					Glib::ustring uid_dept=MYQMain[0].ambil_string("id_dep");
					int id_dept=atoi(uid_dept.c_str());
					printf(" |--|--|--[%d] id:%d\n",i,id_dept);
					
					deptrow[m_Columns.m_col_id]=id_dept;
					deptrow[m_Columns.icon]=icon_dept;//Gdk::Pixbuf::create_from_file("emblem-dept.png");
					
					//Cek path
					if((level==1)&&(id==id_dept))
					{
						uPath=Glib::ustring::compose("%1:%2",i,j);
					}
					
					//QUERY EQUIPMENT DIBAWAH DEPARTEMEN 
					uTemp="SELECT * FROM equipment WHERE id_dept='" + uid_dept + "'";
					strcpy(MYQMain[1].Text,uTemp.c_str());
					//printf(" |--|--|--* Query: %s\n",MYQMain[1].Text);
					
					MYQMain[1].Query();
					
					int jum_equip=MYQMain[1].jum_row;
					printf(" |--|--|--[%s] Jumlah equipment: %d\n",unama_dept.c_str(),jum_equip);
					
					for(int k=0;k<jum_equip;k++)
					{
						printf(" 	- tambahi cucu: %d\n",k);
						Gtk::TreeModel::Row equip_row = *(m_refTreeModel->append(deptrow.children()));
						
						Glib::ustring unama_equip=MYQMain[1].ambil_string("nama_equipment");
						equip_row[m_Columns.m_col_name] =unama_equip;
						
						Glib::ustring uid_equip=MYQMain[1].ambil_string("id_equipment");
						id_equipment=atoi(uid_equip.c_str());
						equip_row[m_Columns.m_col_id]=id_equipment;
						equip_row[m_Columns.icon]=icon_equip;//Gdk::Pixbuf::create_from_file("emblem-equipment.png");
						Glib::ustring ujenis_equip=MYQMain[1].ambil_string("jenis_equipment");
						
						//Cek path
						if((level==2)&&(id==id_equipment))
						{
							uPath=Glib::ustring::compose("%1:%2:%3",i,j,k);
						}
						
						//QUERY GROUP DIBAWAH EQUIPMENT 
						uTemp="SELECT * FROM group_titik_ukur WHERE ID_equipment='" + uid_equip + "'";
						
						strcpy(MYQMain[2].Text,uTemp.c_str());
						//printf(" |--|--|--|--* Query: %s\n",MYQMain[2].Text);
						
						MYQMain[2].Query();
						
						int jum_group=MYQMain[2].jum_row;
						printf(" |--|--|--|--[%s] Jumlah group: %d\n",unama_equip.c_str(),jum_group);
						
						
						for(int l=0;l<jum_group;l++)
						{
							//printf(" 	- tambahi cucu: %d\n",k);
							Gtk::TreeModel::Row group_row = *(m_refTreeModel->append(equip_row.children()));
							
							u_nama_group=MYQMain[2].ambil_string("nama_group");
							group_row[m_Columns.m_col_name] =u_nama_group;
							
							Glib::ustring uid_group=MYQMain[2].ambil_string("id_group");
							group_row[m_Columns.m_col_id]=atoi(uid_group.c_str());
							group_row[m_Columns.icon]=icon_group;//Gdk::Pixbuf::create_from_file("emblem-group.png");
							

							//Cek path
							if((level==3)&&(id==group_row[m_Columns.m_col_id]))
							{
								uPath=Glib::ustring::compose("%1:%2:%3:%4",i,j,k,l);
							}
							
							//QUERY TITIK UKUR DIBAWAH GROUP
							uTemp="SELECT * FROM titik_ukur WHERE id_group_titik_ukur = " + uid_group +
								 " AND id_equipment = " + uid_equip;
							strcpy(MYQMain[3].Text,uTemp.c_str());
							//printf(" |--|--|--|--|--* %s\n",MYQMain[3].Text);
							
							MYQMain[3].Query();
							
							int jum_titik=MYQMain[3].jum_row;
							printf(" |--|--|--|--|--[%s] Jumlah titik: %d\n",u_nama_group.c_str(),jum_titik);
							
							for(int m=0;m<jum_titik;m++)
							{
								//printf("--tambah titik %d\n",m);
								
								Gtk::TreeModel::Row titik_row = *(m_refTreeModel->append(group_row.children()));
							
								uTemp=MYQMain[3].ambil_string("nama_titik");
								titik_row[m_Columns.m_col_name] =uTemp;
								
								uid_titik=MYQMain[3].ambil_string("id_titik");
								titik_row[m_Columns.m_col_id]=atoi(uid_titik.c_str());
								
								uTemp=MYQMain[3].ambil_string("sumber_data");
								id_sumber_temp=atoi(uTemp.c_str());
								
								uTemp=MYQMain[3].ambil_string("no_port");
								id_port_temp=atoi(uTemp.c_str());
								
								uTemp=MYQMain[3].ambil_string("no_kanal");
								id_kanal_temp=atoi(uTemp.c_str());
								
								if(id_sumber_temp)
									titik_row[m_Columns.icon]=icon_titik1;//Gdk::Pixbuf::create_from_file("emblem-titik.png");
								else
									titik_row[m_Columns.icon]=icon_titik2;//Gdk::Pixbuf::create_from_file("emblem-titik-nc-16.png");
								//Cek path
								if((level==4)&&(id==titik_row[m_Columns.m_col_id]))
								{
									uPath=Glib::ustring::compose("%1:%2:%3:%4:%5",i,j,k,l,m);
								}
								
								MYQMain[3].Next();
							}
							
							MYQMain[3].Buang();
							MYQMain[2].Next();
						}
						MYQMain[2].Buang();
						MYQMain[1].Next();
					}
					
					MYQMain[1].Buang();
					MYQMain[0].Next();
				}			
				
				MYQMain[0].Buang();
				MYQ.Next();
			}
			MYQ.Buang();
			if(!tree_ada_kolom)
			{
				Gtk::TreeView::Column* pColumn=Gtk::manage( new Gtk::TreeView::Column("Nama"));
				pColumn->pack_start(m_Columns.icon,false);
				pColumn->pack_start(m_Columns.m_col_name,true);

				treeview1->append_column(*pColumn);
				
				//treeview1->append_column("Nama", m_Columns.m_col_name);
				tree_ada_kolom=true;
				delete pColumn;
			}
		}
	}
	
	CloseDB(false);
	
	if(level>=0)
	{
		//expand ke titik sesuai rekuest
		//uPath="1:0:0:3";
		printf(" |-- expand_to_path: %s\n",uPath.c_str());
		Gtk::TreePath* tpath= new Gtk::TreePath(uPath);
		treeview1->expand_to_path(*tpath);
		
		//Glib::ustring temp=tpath->to_string();
		//printf(" |-- tes path: %s\n",temp.c_str());
		delete tpath;
	}
	//this->CloseDB(true);
	printf("[/UpdateTreeView]\n");
}

int main_window::KonekDB(int jum_db)
{
	Glib::ustring utemp,uhost,uusername,upassword,uport,unama_db;
	//MYSQL my_connection;
	char ctemp[256];
	const char* cctemp;
	int i;
	
	cctemp=(const char*) &ctemp;
	
	//catat_log("Coba koneksi ke database",0);
	printf("\nCoba koneksi ke database\n");
	
	if(jum_db<1)
		jum_db=1;
	else if (jum_db>MAX_DB_CONNECT)
		jum_db=MAX_DB_CONNECT;

	
	//Init database MySQL 
   	//unsigned int timeout = 7;
   
 	
	//uhost="192.168.1.13";
	//uusername="herry";
	//upassword="";
	//uport="3306";
	//unama_db="monita_db";
	
	//strcpy(MYQ.server,uhost.c_str());
	strcpy(MYQ.server,kfg.db_host);
	strcpy(MYQ.user,kfg.db_username);
	strcpy(MYQ.psw,kfg.db_pass);
	strcpy(MYQ.port,kfg.db_port);
	strcpy(MYQ.db,kfg.nama_db);

	
	printf("Init MYQ instance\n");
	printf("-server	: %s\n",MYQ.server);
	printf("-user	: %s\n",MYQ.user);
	printf("-psw	: %s\n",MYQ.psw);
	printf("-port	: %s\n",MYQ.port);
	printf("-db	: %s\n",MYQ.db);
	
	if(MYQ.init_lengkap()==1)
	{
		printf("Inisialisasi database MYQ sukses\n");
		//catat_log("init db sukses",0);
		jumlah_db=1;
	}
	else
	{
		printf("init db gagal\n");
		
		Gtk::MessageDialog dialog(*this, "Gagal inisialisasi database");
  		dialog.set_secondary_text("Periksa parameter koneksi database");

  		dialog.run();
		
		return 1;
	}
	
		
	strcpy(MYQLog.server,kfg.db_host);
	strcpy(MYQLog.user,kfg.db_username);
	strcpy(MYQLog.psw,kfg.db_pass);
	strcpy(MYQLog.port,kfg.db_port);
	strcpy(MYQLog.db,kfg.nama_db);
	if(MYQLog.init_lengkap()==1)
	{
		printf("Inisialisasi database MYQLog sukses\n");
		//catat_log("init db sukses",0);
		jumlah_db=1;
		MYQLog.Close();
	}
	else
	{
		printf("init db gagal\n");
		
		Gtk::MessageDialog dialog(*this, "Gagal inisialisasi database untuk sistem Logging Data");
  		dialog.set_secondary_text("Periksa parameter koneksi database");

  		dialog.run();
		
		return 1;
	}
	
	if(jum_db==1)
	{
		jumlah_db=jum_db;
		return 0;
	}
	
	//Jika sukses
	//Kopi parameter ke MYQ yang lain
	if(jum_db>0)
	{
		for(i=0;i<jum_db;i++)
		{
			memcpy(&MYQMain[i],(void*)&MYQ,sizeof(MyQuery));
			if(MYQMain[i].init_lengkap())
			{
				printf("Inisialisasi database %d sukses",i);
				jumlah_db++;
			}
			else
			{
				printf("Inisialisasi database %d gagal",i);
				return 1;
			}
		}
	}
	//catat_log("Selesai koneksi ke database\n",0);
	
	return 0;
}

int main_window::CloseDB(bool semua)
{
	if(semua)
	{
		try
		{
			MYQ.Close();
			jumlah_db--;
		}
		catch(...)
		{
			printf("ERROR: Gagal saat menutup database MYQ\n");
		}
	}
	
	//Tutup semua/sebagian koneksi database
	printf("Tutup semua koneksi database kecuali database utama \n");
	try
	{
		//MYQ.Close();
		int temp=jumlah_db-1;
		for(int i=0;i<temp;i++)
		{
			if(MYQMain[i].isConnected)
			{
				printf(" |-- MYQMain[%d].Close()... ",i);
				MYQMain[i].Close();
				printf(" OK\n");
				jumlah_db--;
			}
		}
	}
	catch(...)
	{
		printf("ERROR: gagal saat menutup database\n");
		return -1;
	}
	
	printf("OK");
	
	//CekDB();
	return 0;
}
void main_window::on_button_sumber_clicked()
{
	int result;
	
	printf("button sumber clicked \n");
	dialog_sumber *dlg_sumber=new dialog_sumber();
	
	memcpy(&dlg_sumber->MYQ,(void*) &MYQ,sizeof(MyQuery));
	dlg_sumber->reload_list();
	result=dlg_sumber->run();
	switch(result)
	{
		case GTK_RESPONSE_OK:
		printf("dialog response OK\n");
		break;
			
		default:
			printf("Default\n");
		break;
	}
	
	delete dlg_sumber;
}

void main_window::on_button_logging_data_clicked()
{
	
	if(kfg.mode!=20)//bukan server mode
	{
		printf("Software di komputer ini diset untuk mode monitoring saja\n");
		Gtk::MessageDialog dialog(*this, "Software di komputer ini diset untuk mode monitoring saja");
		dialog.set_secondary_text("Periksa konfigurasi software");

		dialog.run();	
		return;
	}
	
	Glib::ustring sQuery,sTemp;
	int jumlah_kanal;
	Glib::ustring id_sumber,no_kanal,id_titik,usNoPort;
	char cTemp[32];
	double dTemp;
	//Mulai logging data
	printf("button logging\n");
	if(timer2_on==false)  //if(timer_on==false)
	{
		//Periksa apakah database siap?
		if(!MYQ.isConnected)
		{
			if(MYQ.init_lengkap()!=1)
			{
				printf("Gagal melakukan inisialisasi database\n");
				Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
				dialog.set_secondary_text("Periksa parameter koneksi database");

				dialog.run();
				return ;
			}
		}

		//MULAI THREAD TIMER DISINI
		this->add_log("Mulai logging data",0,0);
		printf("======Inisialisasi proses logging data======\n");
		//Inisialisasi struct data
		sQuery="SELECT * FROM sumber_data WHERE status=1 ORDER BY flag DESC";
		
		strcpy(MYQ.Text,sQuery.c_str());
		
		MYQ.Query();
		
		jumlah_sumber=MYQ.jum_row;
		if(jumlah_sumber>0) 
		{
			printf("Jumlah: %d\n",jumlah_sumber);
			
			if(jumlah_sumber>JUMLAH_THREAD)
			{
				sTemp=Glib::ustring::compose("Jumlah sumber aktif=<i>'%1'</i> dari maksimum yang diijinkan='%2'. Set menjadi %2'?",
											 jumlah_sumber,JUMLAH_THREAD);
				Gtk::MessageDialog dialog(*this,sTemp,
        		true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

				dialog.set_secondary_text("Peringatan: Sumber data yang dinon-aktifkan adalah nomer urut bawah.");
				
				int result=dialog.run();
				switch(result)
				{
					case(Gtk::RESPONSE_OK):
						jumlah_sumber=JUMLAH_THREAD;
						
						break;
					default:
						//Keluar dari fungsi
						return;
				}
			}
			
			for(int i=0;i<jumlah_sumber;i++)
			{
				//Nama sumber
				sTemp=MYQ.ambil_string("nama_sumber");
				tsumber[i].nama_sumber=sTemp;
				printf("[%d]Nama Sumber: %s\n",i,tsumber[i].nama_sumber.c_str());
				
				//id sumber
				id_sumber=MYQ.ambil_string("id_sumber");
				tsumber[i].id_sumber=atoi(id_sumber.c_str());
				printf(" -ID Sumber: %d\n",tsumber[i].id_sumber);
				
				//ip_address
				tsumber[i].ip_address=MYQ.ambil_string("alamat_ip");

				//ip_port
				sTemp=MYQ.ambil_string("port");
				tsumber[i].ip_port=atoi(sTemp.c_str());
				printf(" -ip_port: %d\n",tsumber[i].ip_port);
				
				//flag
				sTemp=MYQ.ambil_string("flag");
				tsumber[i].flag=atoi(sTemp.c_str());
				
				//jumlah kanal
				sTemp=MYQ.ambil_string("jum_kanal");
				jumlah_kanal=atoi(sTemp.c_str());
				tsumber[i].jumlah_kanal=jumlah_kanal;
				printf(" -Jumlah kanal: %d\n",jumlah_kanal);
				
				//status_koneksi
				int istatus;
				sTemp=MYQ.ambil_string("status");
				if(sTemp=="0")
					istatus=0;
				else
					istatus=1;
				
				tsumber[i].status_koneksi=istatus;
				tsumber[i].status=istatus;
				
				sTemp=MYQ.ambil_string("default_stack");
				tsumber[i].no_stack=atoi(sTemp.c_str());
					
				if(MYQMain[0].isConnected==false)
				{
					printf("Buat Database Connection\n");
					MYQMain[0].init_lengkap();
				}
				
				if(MYQMain[0].isConnected==true)
				{
					printf("Database OK\n");
					//Cari titik-ukur yang bersesuaian untuk masing-masing sumber dan kanal
					for(int j=0;j<jumlah_kanal;j++)
					{
						printf(" --Kanal  %d ->",j);
						//PENTING! No kanal dimulai dari angka 1
						sprintf(cTemp,"%d",j+1);
						no_kanal.assign(cTemp);
						
						sQuery="SELECT * FROM titik_ukur WHERE sumber_data='" + id_sumber + 
							"' AND no_kanal='" + no_kanal + "'";
						printf(" |--Query: %s\n",sQuery.c_str());
						strcpy(MYQMain[0].Text,sQuery.c_str());
						
						MYQMain[0].Query();
						
						//if(MYQMain[0].jum_row==1)
						if(MYQMain[0].jum_row>=1)
						{
							id_titik=MYQMain[0].ambil_string("id_titik");
							
							//id_titik
							tsumber[i].titik[j].id_titik=atoi(id_titik.c_str());
							
							//nama titik
							sTemp=MYQMain[0].ambil_string("nama_titik");
							strcpy(tsumber[i].titik[j].nama_titik,sTemp.c_str());
							try
							{
							//range dan alarm
							sTemp=MYQMain[0].ambil_string("range_min");
							dTemp=strtod(sTemp.c_str(),NULL);
							tsumber[i].titik[j].range_min=dTemp;
							
							sTemp=MYQMain[0].ambil_string("range_max");
							dTemp=strtod(sTemp.c_str(),NULL);
							tsumber[i].titik[j].range_max=dTemp;
							
							sTemp=MYQMain[0].ambil_string("alarm_low2");
							dTemp=strtod(sTemp.c_str(),NULL);
							tsumber[i].titik[j].alarm_low_low=dTemp;
							
							sTemp=MYQMain[0].ambil_string("alarm_low1");
							dTemp=strtod(sTemp.c_str(),NULL);
							tsumber[i].titik[j].alarm_low=dTemp;

							sTemp=MYQMain[0].ambil_string("alarm_high1");
							dTemp=strtod(sTemp.c_str(),NULL);
							tsumber[i].titik[j].alarm_high=dTemp;
							
							sTemp=MYQMain[0].ambil_string("alarm_high2");
							dTemp=strtod(sTemp.c_str(),NULL);
							tsumber[i].titik[j].alarm_high_high=dTemp;
							
							sTemp=MYQMain[0].ambil_string("alarm_setting");
							tsumber[i].titik[j].alarm_setting=atoi(sTemp.c_str()); //enable semua
							
							sTemp=MYQMain[0].ambil_string("kalibrasi_a");
							dTemp=strtod(sTemp.c_str(),NULL);
							tsumber[i].titik[j].kalibrasi_a=dTemp;
								
							sTemp=MYQMain[0].ambil_string("kalibrasi_b");
							dTemp=strtod(sTemp.c_str(),NULL);
							tsumber[i].titik[j].kalibrasi_b=dTemp;	
							}
							catch(...)
							{
								printf("ERROR: Gagal konversi bilangan\n");
							}
							//printf("Titik ukur: %d\n",tsumber[i].titik[j].id_titik);
						}
						else
						{
							tsumber[i].titik[j].id_titik=0;
							printf("NULL\n");
						}
												
						if(MYQMain[0].jum_row>1)
						{
							printf("WARNING: Kesalahan pada database: Multiple port entri. jumlah titik: %d\n",MYQMain[0].jum_row);
						}
						MYQMain[0].Buang();
					}
				}
				MYQ.Next();
			}
			MYQ.Buang();
			MYQMain[0].Close(); 
			
			//Load posting data
			/*printf("--- Load posting data ----\n");
			sQuery="SELECT * FROM posting_data WHERE status=1 ORDER BY flag DESC";
		
			strcpy(MYQ.Text,sQuery.c_str());
		
			MYQ.Query();
		
			jumlah_post=MYQ.jum_row;
			if(jumlah_post>0)
			{
				Glib::ustring id_post;
				for(int i=0;i<jumlah_post;i++)
				{
					//Nama post
					sTemp=MYQ.ambil_string("nama_post");
					tposting[i].nama_post=sTemp;
					printf("[%d]Nama Post: %s\n",i,tposting[i].nama_post.c_str());
					
					//id sumber
					id_post=MYQ.ambil_string("id_post");
					tposting[i].id_post=atoi(id_post.c_str());
					printf(" -id_post: %d\n",tposting[i].id_post);
					
					//ip_address
					tposting[i].ip_address=MYQ.ambil_string("alamat_ip");

					//ip_port
					sTemp=MYQ.ambil_string("port");
					tposting[i].ip_port=atoi(sTemp.c_str());
					printf(" -ip_port: %d\n",tsumber[i].ip_port);
					
					//flag
					sTemp=MYQ.ambil_string("flag");
					tposting[i].flag=atoi(sTemp.c_str());
					
					MYQ.Next();
				}
			}
			else
				printf(" -> Tidak ada item Posting data\n");*/
			MYQ.Close();
			//JALANKAN THREAD LOGGING DATA
			printf("======LOGGING DATA MULAI======\n");
			
			//INISIALISASI VARIABEL LOGGING DATA
			waktu_simpan_counter=0;
			saatnya_simpan=false;
			
			time_counter=0;
			
			//update dulu status sumber
			this->UpdateStatusSumber();
			timer2_on=true;
			
			//Siapkan database
			//Periksa apakah database siap?
			if(!MYQLog.isConnected)
			{
				if(MYQLog.init_lengkap()!=1)
				{
					printf("Gagal melakukan inisialisasi database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return;
				}
			}
			//reset counter switch
			buffer_counter=0;
			for(int i=0;i<BUFFER_DELAY;i++)
				alarm_switch_buffer[i]=0;

			printf("Database MYQLog OK\n");
			memset(waktu_simpan_lalu,0x00,sizeof(waktu_simpan_lalu));
			
			
			m_connection_id_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this,
              &main_window::on_timeout_2),1000 );
			
			//timer_on=true; 
			button_logging_data->set_label("_Stop Ambil Data");
		}
		else
		{
			printf("Tidak ditemukan informasi Sumber Data\n");
		}
		
	}
	else
	{
		this->add_log("Stop logging data",0,0);
		timer2_on=false;
		//timer_on=false;
		//catat_log("Stop timer...",0);
		//pthread_join(th_timer, NULL);
		//catat_log("OK",0);
		button_logging_data->set_label("_Mulai Ambil Data");
	}
}

int main_window::LoadConfig()
{
    //Baca file konfigurasi
	add_log("Baca konfig",0,0);
	printf("Load file konfigurasi...\n");
    FILE *stream;
	
    //konfig_file* pkf;
	Glib::ustring asFilePath;
	char cTemp[32];


    asFilePath="konfigurasi.kfg";
	//asFilePath=ExtractFilePath(Application->ExeName) + "konfigurasi.kfg";
    
	if ((stream = fopen(asFilePath.c_str(), "rb"))== NULL)
    {
        fprintf(stderr, "Cannot open output file.\n");
		add_log("Baca konfig: Gagal membuka file",0,0);
        return 1;
    }

    fread(&kfg, sizeof(konfig_file), 1, stream);

    fclose(stream);
    
	//periksa file konfigurasi
	printf("-db_host:%s\n",kfg.db_host);
    
	if(!(strcmp(kfg.db_host,"")))
        strcpy(kfg.db_host,"localhost");
    if(!(strcmp(kfg.db_port,"")))
        strcpy(kfg.db_port,"3306");
    if(!(strcmp(kfg.db_username,"")))
        strcpy(&kfg.db_username[0],"monita");            
    if(!(strcmp(kfg.db_pass,"")))
        strcpy(&kfg.db_pass[0],"");
    if(!(strcmp(kfg.nama_db,"diesel")))
        strcpy(&kfg.nama_db[0],"monita_db");

    /*if (kfg_file.data_ditampilkan == NULL) kfg_file.data_ditampilkan = 2000;

    //cek jika mode tidak sama dengan nol atau 1 maka default adalah 1 (browsing & analisis)
	/*
    //if (kf.mode != 0 || kf.mode != 1)
    if (kfg_file.mode == 0)
          kfg_file.mode = 20;       //browsing, 10 server, 20 browsing
    //else if (kf.mode == 1) kf.mode = 1;
    //else kf.mode = 1;
	*/
	
	if(kfg.cek_konf != 2857740885)
	{
		printf("File konfigurasi rusak. Set ke default");
		add_log("Baca konfig: File konfigurasi rusak. Set ke default",0,0);
		return 1;
	} //0xAA55AA55
	else
	{
		add_log("Baca konfig: OK",0,0);
		printf("OK\n");
	}
    return 0;
}

int main_window::SimpanKonfig(konfig_file* kf)
{
	FILE *stream;
	Glib::ustring asFilePath;
	
	add_log("Simpan konfig",0,0);
	printf("Simpan konfigurasi...");
	asFilePath="konfigurasi.kfg";
    
	if ((stream = fopen(asFilePath.c_str(), "wb"))== NULL)
    {
        fprintf(stderr, "Cannot open output file.\n");
        printf("Gagal membuka file\n");
		add_log("Simpan konfig: Gagal membuka file",0,0);
		return 1;
    }
	kf->cek_konf=2857740885; //0xAA55AA55
    fwrite(kf, sizeof(konfig_file), 1, stream);
	
    fclose(stream);
	
	//kf->cek_konf=2857740885; //0xAA55AA55
	
	printf("OK\n");
	add_log("Simpan konfig: OK",0,0);
	/*
	//Simpan konfig dalam bentuk file conf standard
	 GKeyFile *keyfile;
 	 GKeyFileFlags flags;
  	 GError *error = NULL;
  	 gsize length;
	
	// Create a new GKeyFile object and a bitwise list of flags. 
	keyfile = g_key_file_new ();
	//flags = G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;
	flags = G_KEY_FILE_KEEP_COMMENTS;// | G_KEY_FILE_KEEP_TRANSLATIONS;

	// Load the GKeyFile from keyfile.conf or return.
	//if (!g_key_file_load_from_file (keyfile, "keyfile.conf", flags, &error))
	//{
	//	g_error (error->message);
	//	return -1;
	//}
	
	  conf = g_slice_new (konfig_file);
	  g_key_file_set_string(keyfile,"database","db_host",kf->db_host);
  
	  //conf->angka = g_key_file_get_integer(keyfile,"username","Angka",NULL);
	  printf("Angka: %d\n",conf->db_host);
	  
	  int bufsize;
	  gchar *buffer = g_key_file_to_data(keyfile,(gsize*) &bufsize, NULL);
		
	  g_key_file_free(keyfile);
	  
	  printf("Buffer ==============n%s\n ==============\n",buffer);
	  //simpan filenya
		if ((stream = fopen(asFilePath.c_str(), "wb"))== NULL)
		{
			fprintf(stderr, "Cannot open output file.\n");
			printf("Gagal membuka file\n");
			//add_log("Simpan konfig: Gagal membuka file",0,0);
			return 1;
		}
  	//fwrite(buffer, bufsize, 1, stream);
  	//fclose(stream);*/
  
	return 0;
}

void main_window::on_treeview1_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path)
{  
	int level;
	
	printf("Row expanded: \n");
	Glib::ustring strText;
	
	
	Gtk::TreeModel::Row row=*iter;
	
	strText= row[m_Columns.m_col_name];
	printf("-Column Name: %s\n",strText.c_str());
	
	strText=path.to_string();
	printf("-Path: %s\n",strText.c_str());
	
	printf("-Path Depth: %d\n",path.get_depth());
	//level=path.get_depth();
	//UpdateTreeView(level-1,"",row.parent());
}

void main_window::on_treeview1_cursor_changed()
{
	//printf("Cursor changed\n");
	int id;
	
	Glib::ustring strText;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;
	
	refTreeSelection= this->treeview1->get_selection();
	iter = refTreeSelection->get_selected();

	id_titik_lama=id_titik_tampil_sekarang;
	if(iter) //If anything is selected
	{
		Gtk::TreePath *tpath= new Gtk::TreePath(iter);
		int depth=tpath->get_depth();
		
		row = *iter;
	  	//Do something with the row.
		strText= row[m_Columns.m_col_name];
		//printf("-Column Name: %s\n",strText.c_str());
		id=row[m_Columns.m_col_id];
		
		id_titik_tampil_sekarang=id;
		
		if(id!=id_titik_lama)
		{
			this->label_titik_ukur->set_text(strText);
			this->UpdateListView(depth,id);
			belum_tanya=true;
		}
		
		delete tpath;
		//strText.append("-klik");
		//row[m_Columns.m_col_name]=strText;
	}
}


/*
int konek_db_global()
{

	
	printf("Load konfigurasi file\n");
	LoadConfig_global ();
	//-------------ISI MYQ global -------------------
	strcpy(myq_global.server,kfg_global.db_host);
	strcpy(myq_global.user,kfg_global.db_username);
	strcpy(myq_global.psw,kfg_global.db_pass);
	strcpy(myq_global.port,kfg_global.db_port);
	strcpy(myq_global.db,kfg_global.nama_db);
	
	printf("Init MYQ instance\n");
	printf("-server	: %s\n",myq_global.server);
	printf("-user	: %s\n",myq_global.user);
	printf("-psw	: %s\n",myq_global.psw);
	printf("-port	: %s\n",myq_global.port);
	printf("-db	: %s\n",myq_global.db);
	if(myq_global.init_lengkap()==1)
	{
		printf("init db sukses\n");
		
		//catat_log("init db sukses",0);
		
	}
	else
	{
		printf("init db gagal\n");
		//catat_log("init db gagal",0);
		Gtk::MessageDialog dialog(NULL, "Gagal inisialisasi database");
  		dialog.set_secondary_text("Periksa parameter koneksi database");

  		dialog.run();
		return 1;
	}
	
	//catat_log("Selesai koneksi ke database\n",0);
	printf("\nSelesai koneksi ke database\n");
	return 0;
}*/

int main_window::logging_data(char* waktu)
{
	printf("+ Logging Data session mulai (%s)\n",waktu);
	
	utemp_global="INSERT INTO waktu(waktu) VALUES('";
	utemp_global.append(waktu);
	utemp_global.append("')");
	strcpy(MYQ.Text,utemp_global.c_str());
	//printf("%s\n",MYQ.Text);
	
	try
	{
		MYQ.Insert();
	}
	catch(...)
	{
		printf("ERROR saat menginput data waktu\n");
		return -1;
	}
	
	//Cari id_waktu_simpan yang terakhir tersimpan

	id_waktu_simpan=MYQ.last_id();
					
	printf(" |-- Jumlah Sumber: %d\n",jumlah_sumber);

	for(int i=0;i<jumlah_sumber;i++)
	{
		printf("|  |--# Mulai  : %s [%s](%s)\n",
			   tsumber[i].nama_sumber.c_str(),
			   tsumber[i].ip_address.c_str(),waktu);
		
		std_ip_address=tsumber[i].ip_address;
		
		//****** DISINI LOGGING DATA DILAKUKAN ******
		ukuran_terima=main_client (std_ip_address,port_num,(char*)&buf_terima);
		//****** DISINI LOGGING DATA DILAKUKAN ******
		
		if(ukuran_terima<0)
		{
			printf("|  |--* Komunikasi ERROR\n");
		}
		else 
		{
			printf("|  |--* Koneksi OK");
			/*
			for(int u=0;u<ukuran_terima;u++)
			{
				printf("0x%x ",buf_terima[u]);
				if(u%8==7)
					printf("\n");
			}
			printf("\n");
			*/
			//cek ukuran apakah sama dengan ukuran struct x_data
			if(sizeof(t_xdata)-ukuran_terima)
			{
				//Ukuran berbeda
				printf("->Ukuran data berbeda. Data dibuang.\n");
				return -2;
			}
			
			//Cek header apakah benar (header harusnya 'monita1')
			if(strncmp(buf_terima,monita1_check_string,sizeof(monita1_check_string)))
			{
				printf("->Data check: invalid ->buang\n");
				return -1;
			}
			else
				printf("->Data check: OK\n");
			
			//jika benar, masukkan ke masing2 data titik ukur
			//kopi alamat data ke pointer struct data
			p_xdata=(t_xdata*) &buf_terima;
			pdata_float=(t_data_float*) &p_xdata->buf;
			
			for(int k=0;k<tsumber[i].jumlah_kanal;k++)
			{
				fdata_tunggal_simpan=pdata_float->data[k];
				id_titik_simpan=tsumber[i].titik[k].id_titik;
				printf(" |  |  |-- Kanal %d-> data:%0.2f \t-> id: %d",k,fdata_tunggal_simpan,id_titik_simpan);
				
				if(id_titik_simpan)
				{
					//simpan data ke database
					
					sprintf(sTemp,
						"INSERT INTO data_harian(id_titik_ukur,id_waktu,data_tunggal) VALUES('%d','%d','%f')",
						id_titik_simpan,id_waktu_simpan,fdata_tunggal_simpan);	
					
					printf("QUERY: %s\n",sTemp);
					printf("->Simpan: ");
					strcpy(MYQ.Text,sTemp);
					if(MYQ.Insert())
					{
						printf("ERROR");
					}
					else
						printf("OK");
					
					sprintf(sTemp,
						"INSERT INTO data_tunggal(id_titik_ukur,id_waktu,data_tunggal) VALUES('%d','%d','%f')",
						id_titik_simpan,id_waktu_simpan,fdata_tunggal_simpan);	
					
					
					printf("QUERY: %s\n",sTemp);
					printf("->Simpan: ");
					strcpy(MYQ.Text,sTemp);
					if(MYQ.Insert())
					{
						printf("ERROR");
					}
					else
						printf("OK");
				}
				printf("\n");
				
				if(!timer_on) //Control thread dari instance main_window
					return 1;
			}
		}
		
		printf("|  |--# Selesai: %s [%s]\n",
	   		tsumber[i].nama_sumber.c_str(),
	   		tsumber[i].ip_address.c_str());
			//update UI
		while(Gtk::Main::instance()->events_pending())
			Gtk::Main::instance()->iteration();
	}
	printf("+ Logging Data session selesai\n");

	return 0;
}

/*
void *f_timer(void *data)
{
	struct tm *tm_ptr, timestruct;
	time_t the_time;
	char buf[32],buf2[32],waktu[32];
	char *result;
	
	printf("\n===THREAD TIMER DIMULAI===\n");

	while(timer_on)
	{
		(void) time(&the_time);
		tm_ptr = localtime(&the_time);
		strftime(buf, 256, "%A %d %B, %I:%M:%S %p\n", tm_ptr);

		
		//if(!strcmp("buf","10"))
		if(strcmp(buf,buf2)) //Update setiap detik
		{
			//printf(buf);
			strcpy(buf2,buf);
			printf("[%d]:%s\n", timer_on,buf);
			
			strftime(waktu,32,"%Y%m%d-%H%M%S",tm_ptr);
			//20080210-102346
			//printf("-waktu[0x%X]:%s\n",&waktu,waktu); 
			
			if(myq_global.isConnected==false)
			{
				printf("Koneksi database global\n");
				if(konek_db_global()==1)
				{
					printf("Gagal koneksi ke database\n");
					timer_on=false;	
					
					Gtk::MessageDialog dialog(NULL, "Gagal koneksi ke database");
  					dialog.set_secondary_text("Periksa parameter koneksi database");


  					dialog.run();
				}
					
			}
			
			if(myq_global.isConnected)
			{
				printf("call logging_data (%s)\n",waktu);
				logging_data(waktu);
				printf("return from logging data(%s)\n",waktu);
			}
		}
		else
		{
			//printf(buf);
		}
	}
	
	printf("close myq_global\n");
	myq_global.Close();
	
	printf("\n===THREAD TIMER DITUTUP===\n");
	return 0;
}*/

/*int LoadConfig_global()
{
    //Baca file konfigurasi
	printf("Load file konfigurasi...");
    FILE *stream;
    //konfig_file* pkf;
	Glib::ustring asFilePath;
	char cTemp[32];


    asFilePath="konfigurasi.kfg";
	//asFilePath=ExtractFilePath(Application->ExeName) + "konfigurasi.kfg";
    
	if ((stream = fopen(asFilePath.c_str(), "rb"))== NULL)
    {
        fprintf(stderr, "Cannot open output file.\n");
        return 1;
    }

    fread(&kfg_global, sizeof(konfig_file), 1, stream);

    fclose(stream);
    
	sprintf(cTemp,"db_host: %s",kfg_global.db_host);
	//periksa file konfigurasi

	printf("OK\n");
    return 0;
}*/

void main_window::on_menu_file_popup_edit()
{
	printf("menu popup edit\n");
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = treeview1->get_selection();
	if(refSelection)
	{
		Gtk::TreeModel::iterator iterx = refSelection->get_selected();
		Gtk::TreePath *tpath= new Gtk::TreePath(iterx);
		
		int id = (*iterx)[m_Columns.m_col_id];
		int depth=tpath->get_depth();
		Glib::ustring valumenu=(*iterx)[m_Columns.m_col_name];
		
		//cari parent id	
		
		if(depth==1)
		{
			printf("-Persh: %s\n",valumenu.c_str());
			printf("-ID Persh: %d\n",id);
			
			dlg_edit_persh* dlg_persh=new dlg_edit_persh();
			
			memcpy(&dlg_persh->MYQ,(void*) &MYQ,sizeof(MyQuery));
			
			dlg_persh->id_persh=id;
			
			dlg_persh->isi_form();
			
			if(dlg_persh->run()==GTK_RESPONSE_OK)
				this->UpdateTreeView(0,id);
			
			dlg_persh->hide();
			//delete dlg_persh;
			
		}
		else if(depth==2)
		{
			printf("-Dept: %s\n",valumenu.c_str());
			printf("-ID dept: %d\n",id);
			
			dlg_edit_dept* dlg_dept=new dlg_edit_dept();
			
			memcpy(&dlg_dept->MYQ,(void*) &MYQ,sizeof(MyQuery));
			
			dlg_dept->id_dept=id;
			
			dlg_dept->isi_form();
			
			if(dlg_dept->run()==GTK_RESPONSE_OK)
				this->UpdateTreeView(1,id);
			dlg_dept->hide();
			//delete dlg_dept;
			
		}
		else if(depth==3)
		{
			printf("-Equipment: %s\n",valumenu.c_str());
			printf("-ID Equipment: %d\n",id);
			
			dlg_edit_equip* dlg_equip=new dlg_edit_equip();
			
			memcpy(&dlg_equip->MYQ,(void*) &MYQ,sizeof(MyQuery));
			
			dlg_equip->id_equipment=id;
			
			dlg_equip->isi_form();
			
			if(dlg_equip->run()==GTK_RESPONSE_OK)
				this->UpdateTreeView(2,id);
			
			dlg_equip->hide();
			//delete dlg_equip;
			
		}
		else if(depth==4)
		{
			printf("-Group: %s\n",valumenu.c_str());
			printf("-ID Group: %d\n",id);
			
			
			dlg_edit_group* dlg_group=new dlg_edit_group();
			
			memcpy(&dlg_group->MYQ,(void*) &MYQ,sizeof(MyQuery));
			
			dlg_group->id_group=id;
			
			dlg_group->isi_form();
			
			if(dlg_group->run()==GTK_RESPONSE_OK)
				this->UpdateTreeView(3,id);
			dlg_group->hide();
			//delete dlg_group;
			
		}
		else if(depth==5)
		{
			printf("-Titik Ukur: %s\n",valumenu.c_str());
			printf("-ID titik: %d\n",id);	
			int result;
	
			//Buat instance dialog edit titik
			dlg_edit_titik *dlg_titik=new dlg_edit_titik();
			
			//Init dialog
			memcpy(&dlg_titik->MYQ,(void*) &MYQ,sizeof(MyQuery));
			dlg_titik->id_titik=id;
			
			//dlg_titik->ReloadCombo(COMBO_SEMUA);
			dlg_titik->isi_form();
			dlg_titik->ReloadCombo(COMBO_SEMUA);
			
			result=dlg_titik->run();
			
			switch(result)
			{
				case GTK_RESPONSE_OK:
					this->UpdateTreeView(4,id);
				break;
			}
			
			dlg_titik->hide();
			//delete dlg_titik;
			
		}
		
		delete tpath;
	}
}

void main_window::on_menu_file_popup_tambah()
{
	printf("[on_menu_file_popup_tambah]\n");
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = treeview1->get_selection();
	if(refSelection)
	{
		Gtk::TreeModel::iterator iterx = refSelection->get_selected();
		if(iterx)
		{
			Gtk::TreePath *tpath= new Gtk::TreePath(iterx);
			Glib::ustring valumenu=(*iterx)[m_Columns.m_col_name];
			
			int depth;
			int id = (*iterx)[m_Columns.m_col_id];
			 
			depth=tpath->get_depth();
			
			printf("Depth: %d\n",depth);
			if(depth==1)
			{
				printf("-Persh: %s\n",valumenu.c_str());
				printf("-ID Persh: %d\n",id);
				//Tambah departemen
				dlg_edit_dept* dlg_dept=new dlg_edit_dept();
			
				memcpy(&dlg_dept->MYQ,(void*) &MYQ,sizeof(MyQuery));
				
				dlg_dept->id_persh=id;
				dlg_dept->id_dept=0;
				
				dlg_dept->isi_form();
				
				dlg_dept->run();
				dlg_dept->hide();
				this->UpdateTreeView(0,id);
			}
			else if(depth==2)
			{
				printf("-Dept: %s\n",valumenu.c_str());
				printf("-ID dept: %d\n",id);
				
				//tambah equipment
				dlg_edit_equip* dlg_equip=new dlg_edit_equip();
			
				memcpy(&dlg_equip->MYQ,(void*) &MYQ,sizeof(MyQuery));
				
				dlg_equip->id_dept=id;
				dlg_equip->id_equipment=0;
				dlg_equip->isi_form();
				dlg_equip->run();
				dlg_equip->hide();
				//dlg_equip->~dlg_equip();
				//delete dlg_equip;
				this->UpdateTreeView(1,id);
			}
			else if(depth==3)
			{
				printf("-Equipment: %s\n",valumenu.c_str());
				printf("-ID Equipment: %d\n",id);
				
				//Tambah Group
				dlg_edit_group* dlg_group=new dlg_edit_group();
			
				memcpy(&dlg_group->MYQ,(void*) &MYQ,sizeof(MyQuery));
				
				dlg_group->id_group=0;
				dlg_group->id_equipment=id;
				dlg_group->isi_form();
				
				dlg_group->run();
				dlg_group->hide();
				//delete dlg_group;
				this->UpdateTreeView(2,id);
			}
			else if(depth==4)
			{
				int id_equipment;
				printf("-Group: %s\n",valumenu.c_str());
				printf("-ID Group: %d\n",id);
				
				printf("[Tambah Titik Ukur]\n");
				if(!MYQ.isConnected)
				{
					if(MYQ.init_lengkap()!=1)
					{
						printf("Gagal melakukan inisialisasi database\n");
						Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
						dialog.set_secondary_text("Periksa parameter koneksi database");

						dialog.run();
						return ;
					}
				}
				
				Glib::ustring usQuery,usTemp;
				usQuery=Glib::ustring::compose("SELECT * FROM group_titik_ukur WHERE id_group='%1'",id);
				
				strcpy(MYQ.Text,usQuery.c_str());
				
				if(MYQ.Query())
				{
					printf("error saat query\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan query ke database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return ;
				}	
				
				if(MYQ.jum_row!=1)
				{
					printf("error saat query\n");
					Gtk::MessageDialog dialog(*this, "Kesalahan data pada database");
					usTemp=Glib::ustring::compose("Terdapat multiple entri untuk group id:'%1'",id);
					dialog.set_secondary_text(usTemp);

					dialog.run();
					return ;
				}
				
				usQuery=MYQ.ambil_string("id_equipment");
				id_equipment=atoi(usQuery.c_str());
				//Buat instance dialog edit titik
				dlg_edit_titik *dlg_titik=new dlg_edit_titik();
				
				//Init dialog
				memcpy(&dlg_titik->MYQ,(void*) &MYQ,sizeof(MyQuery));
				MYQ.Buang();
				
				dlg_titik->id_titik=0;
				dlg_titik->id_group=id;
				dlg_titik->id_equipment=id_equipment;
				dlg_titik->isi_form();
				dlg_titik->ReloadCombo(COMBO_SEMUA);
				int result=dlg_titik->run();
				
				dlg_titik->hide();
				//delete dlg_titik;
				this->UpdateTreeView(3,id);
			}
			else if(depth==5)
			{
				printf("-Titik Ukur: %s\n",valumenu.c_str());
				printf("-ID titik: %d\n",id);	
			}
			
			delete tpath;
		}
	}
}



void main_window::on_menu_file_popup_generic()
{
	printf("menu popup\n");
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = treeview1->get_selection();
	if(refSelection)
	{
		Gtk::TreeModel::iterator iterx = refSelection->get_selected();
		if(iterx)
		{
			Gtk::TreePath *tpath= new Gtk::TreePath(iterx);
			Glib::ustring valumenu=(*iterx)[m_Columns.m_col_name];
			
			int depth;
			int id = (*iterx)[m_Columns.m_col_id];
			 
			depth=tpath->get_depth();
			
			printf("Depth: %d\n",depth);
			if(depth==1)
			{
				printf("-Persh: %s\n",valumenu.c_str());
				printf("-ID Persh: %d\n",id);
			}
			else if(depth==2)
			{
				printf("-Dept: %s\n",valumenu.c_str());
				printf("-ID dept: %d\n",id);
			}
			else if(depth==3)
			{
				printf("-Equipment: %s\n",valumenu.c_str());
				printf("-ID Equipment: %d\n",id);
			}
			else if(depth==4)
			{
				printf("-Group: %s\n",valumenu.c_str());
				printf("-ID Group: %d\n",id);
				
				
			}
			else if(depth==5)
			{
				printf("-Titik Ukur: %s\n",valumenu.c_str());
				printf("-ID titik: %d\n",id);	
			}
			
			delete tpath;
		}
	}
}

bool main_window::on_treeview1_button_press_event(GdkEventButton *event)
{
	int tree_depth;
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = treeview1->get_selection();	
	Gtk::TreeModel::iterator iterx;
	Gtk::TreePath *tpath;
	
	if(refSelection)
	{
		iterx = refSelection->get_selected();
		tpath= new Gtk::TreePath(iterx);
		tree_depth=tpath->get_depth();
		delete tpath;
	}
	//else 
	//	return false	
	if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
	{
		//printf("klik kanan\n");
		if(tree_depth==5)
		{
		  m_Menu_Popup.popup(event->button, event->time);
		}
		else if(tree_depth==4)
		{
			popup_group.popup(event->button,event->time);
		}
		else if(tree_depth==3)
		{
			popup_equip.popup(event->button,event->time);
		}
		else if(tree_depth==2)
		{
			popup_dept.popup(event->button,event->time);
		}
		else if(tree_depth==1)
		{
			popup_persh.popup(event->button,event->time);
		}
	}
 
  return false;
}

void main_window::CekDB()
{
	printf("[CEK DB]\n");
	printf(" +-- jumlah_db terkoneksi: %d\n",jumlah_db);
	
	printf(" |-- MYQ: ");
	if(MYQ.isConnected)
	{
		printf("Connected\n");
		printf(" -query_count: %d\n", MYQ.query_count);
	}
	else
		printf("Not Connected\n");
		
	for(int i=0;i<5;i++)
	{
		printf(" |-- MYQMain[%d]:",i);
		if(MYQMain[i].isConnected)
		{
			printf("Connected\n");
			printf(" -query_count: %d\n", MYQMain[i].query_count);
			
		}
		else
			printf("Not Connected\n");
	}	
	
	printf(" +-- jumlah_db terkoneksi: %d\n",jumlah_db);
	//printf(" +-- Total query count: %d\n",MYQ.CekUnclean());
	//printf("CEK DB SELESAI ===\n");
}

int main_window::UpdateListView (int level,int id)
{
	int tahun_tampilkan,bulan_tampilkan,tanggal_tampilkan;
	int tahun_sekarang,bulan_sekarang,tanggal_sekarang;
	double dTemp,dTemp1;
	double d_range_min,d_range_max,d_alarm_min,d_alarm_min_min,d_alarm_max,d_alarm_max_max;
	Glib::ustring strQuery,asTanggal,asID,asTemp;
	
	//Buat/Baca waktu yang harus ditampilkan
	char cwaktu[32];
	sprintf(cwaktu,"%04d%02d%02d",spin_tahun->get_value_as_int(),
							spin_bulan->get_value_as_int(),
							spin_tanggal->get_value_as_int());
	printf("Update List View(astanggal=%s)\n",cwaktu);
	asTanggal=cwaktu;
	
	//Variabel untuk listview
	m_refDataModel = Gtk::TreeStore::create(m_kolom_list);
	
	tree_data->set_model(m_refDataModel);

	Gtk::TreeModel::Row row;
	
	switch(level)
	{
		case 0:
		case 1:
		case 2:
		case 3: 
		case 4:
			printf(" |--* Update Group. Group ID: %d\n",id);
			
			
		break;
		
		case 5:
		printf("Konek ke database\n");
		//Konek Database
		if(!MYQ.isConnected)
		{
			KonekDB (1);
		}
		
		//Buat Query
		asID=Glib::ustring::compose("%1",id);
		//asTanggal.assign(cwaktu);
		//Buat query untuk mencari data tentan titik ukur ybs (19 september 08)
		strQuery="SELECT * FROM titik_ukur WHERE id_titik='" + asID + "'";
			
		strcpy(MYQ.Text,strQuery.c_str());
		MYQ.Query();
		if(MYQ.jum_row!=1)
			return -2;		
		
		//d_range_min,d_range_max,d_alarm_min,d_alarm_min_min,d_alarm_max,d_alarm_max_max;
		
			
		//7 Agustus, data dibaca dari tabel temporer
		asTemp=MYQ.ambil_string("range_min");
		d_range_min=strtod(asTemp.c_str(),NULL);
			
		asTemp=MYQ.ambil_string("range_max");
		d_range_max=strtod(asTemp.c_str(),NULL);

		asTemp=MYQ.ambil_string("alarm_low1");
		d_alarm_min=strtod(asTemp.c_str(),NULL);

		asTemp=MYQ.ambil_string("alarm_low2");
		d_alarm_min_min=strtod(asTemp.c_str(),NULL);			
			
		asTemp=MYQ.ambil_string("alarm_high1");
		d_alarm_max=strtod(asTemp.c_str(),NULL);

		
		asTemp=MYQ.ambil_string("alarm_high2");
		d_alarm_max_max=strtod(asTemp.c_str(),NULL);

		int selisih=selisih_hari(asTanggal);
		printf(" |--* Tanggal data tampil: %s, selisih hari %d\n",asTanggal.c_str(),selisih);
		
		if(selisih<0)
		{
			Gtk::MessageDialog dialog(*this,"Data yang dipilih belum ada!",
			true /*use markup*/, Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK);

			//dialog.set_secondary_text("Tidak bisa menampilkan data yang belum ada");
			
			int result=dialog.run();
			
			return -1;
		}
			
		//jika kurang dari 1 hari baca data dari data_harian
		if(selisih<7)
		{
			strQuery="SELECT * FROM data_harian RIGHT JOIN waktu on waktu.id_waktu=data_harian.id_waktu ";
        	strQuery+="WHERE id_titik_ukur='" + asID + "' AND waktu.waktu LIKE '" + asTanggal + "%'";
        	strQuery+="ORDER BY waktu ASC LIMIT 2880";
		}	
		//jika lebih dari 7 hari, baca data langsung dari data_tunggal (lebih lama)
		else
		{
			Gtk::MessageDialog dialog(*this,"Data yang dipilih lebih dari 7, lanjutkan?",
			true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

			dialog.set_secondary_text("Data yang lebih lama dari 7 hari di simpan \ndalam database yang lebih besar \nsehingga memerlukan waktu pembacaan yang lebh lama");
			
			int result=dialog.run();
			switch(result)
			{
				case(Gtk::RESPONSE_OK):
					strQuery="SELECT * FROM data_tunggal RIGHT JOIN waktu on waktu.id_waktu=data_tunggal.id_waktu ";
        			strQuery+="WHERE id_titik_ukur='" + asID + "' AND waktu.waktu LIKE '" + asTanggal + "%'";
        			strQuery+="ORDER BY waktu ASC LIMIT 2880"; //was 1440, ganti 25 sept 2008
					
					break;
				default:
					//Keluar dari fungsi
					return -1;
			}
		}
		//strrQuery="SELECT * FROM data_tunggal RIGHT JOIN waktu on data_tunggal.id_waktu=waktu.id_waktu ";
		//strQuery+="WHERE id_titik_ukur='"+ asID +"' ORDER BY data_tunggal.id_waktu DESC LIMIT 100";	
		
		//select * from data_tunggal RIGHT JOIN waktu on data_tunggal.id_waktu=waktu.id_waktu WHERE id_titik_ukur='6' ORDER BY data_tunggal.id_waktu ASC LIMIT 10;
		
		printf(" |--|-- Query: %s\n",strQuery.c_str());
		
		strcpy(MYQ.Text,strQuery.c_str());
		
		if(MYQ.Query())
		{
			printf("Error saat query\n");
			return 1;
		}
		
		printf(" |--* List data (%d)\n",MYQ.jum_row);	
		for(int i=0;i<MYQ.jum_row;i++)
		{
			//printf("|  |-- %d\n",i);
			Glib::ustring data_waktu, data_waktu_tampil;
			row=*(m_refDataModel->append());
			
			row[m_kolom_list.m_col_nomer]=i;
			
			asTemp=MYQ.ambil_string("id_data");
			row[m_kolom_list.m_col_id]=atoi(asTemp.c_str());
			
			//20080805-225432	
			data_waktu= MYQ.ambil_string("waktu");
			data_waktu_tampil=data_waktu.substr(9,2) + ":" 
							  + data_waktu.substr(11,2); //+":"
							  //+data_waktu.substr(13,2);
			
			row[m_kolom_list.m_col_waktu]=data_waktu_tampil;
			
			asTemp=MYQ.ambil_string("data_tunggal");
			row[m_kolom_list.m_col_data]=asTemp;
			
			dTemp=strtod(asTemp.c_str(),NULL);
			
			if(dTemp<d_range_min)
				row[m_kolom_list.m_col_status]="ERROR: Dibawah range ukur";
			else if(dTemp>d_range_max)
				row[m_kolom_list.m_col_status]="ERROR: Diatas range";
			else if(dTemp<d_alarm_min)
				row[m_kolom_list.m_col_status]="ALARM: Rendah";
			else if(dTemp<d_alarm_min_min)
				row[m_kolom_list.m_col_status]="ALARM: Terlalu Rendah";
			else if(dTemp>d_alarm_max)
				row[m_kolom_list.m_col_status]="ALARM: Tinggi";
			else if(dTemp>d_alarm_max_max)
				row[m_kolom_list.m_col_status]="ALARM: Terlalu Tinggi";
			else 
				row[m_kolom_list.m_col_status]="OK";
			
			//asTemp=row[m_kolom_list.m_col_waktu];
			//printf("|  |-- %s",asTemp.c_str());
			
			//asTemp=row[m_kolom_list.m_col_data];
			//printf(":%s\n",asTemp.c_str());
			MYQ.Next();
		}
		
		if(!kolom_data_ada)
		{
			tree_data->append_column("No.",m_kolom_list.m_col_nomer);
			tree_data->append_column("Waktu",m_kolom_list.m_col_waktu);
			tree_data->append_column("Data",m_kolom_list.m_col_data);
			tree_data->append_column("Status",m_kolom_list.m_col_status);
			kolom_data_ada=true;
		}
		
		MYQ.Buang();
		break;
	}
	
	depth_level_sekarang=level;
	id_titik_tampil_sekarang=id;
	//gambar_grafik();
	
	// paksa untuk gambar ulang.
    Glib::RefPtr<Gdk::Window> win = drawingarea1->get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
		//on_tree_status_button_press_event(NULL);
    }
	
	return 0;
}

int main_window::UpdateStatusSumber()
{
	printf("\n |-- * UPDATE STATUS SUMBER\n");
	Glib::ustring strQuery,asTanggal,asID,asTemp;
	
	m_refStatusModel = Gtk::TreeStore::create(m_status_list);
	
	tree_status->set_model(m_refStatusModel);

	Gtk::TreeModel::Row row;
	printf(" |  |--* jumlah sumber: %d\n",jumlah_sumber);
	
	for(int i=0;i<jumlah_sumber;i++)
	{
		printf(" |  |  |--* %d: %d\n",i,tsumber[i].status_koneksi);
		row=*(m_refStatusModel->append());
		
		row[m_status_list.m_col_id]=tsumber[i].id_sumber;
		row[m_status_list.m_col_nama_sumber]=tsumber[i].nama_sumber;
		row[m_status_list.m_col_alamat_ip]=tsumber[i].ip_address;
		row[m_status_list.m_col_ip_port]=tsumber[i].ip_port;
		//0-non-aktif 1-aktif_belum_dicoba 
		//2-koneksi OK, 3-data error 4-Timeout 5-ERROR 
		row[m_status_list.icon]=icon_generic;//Gdk::Pixbuf::create_from_file("emblem-generic16.png");
		if(tsumber[i].status_koneksi==STATUS_NON_AKTIF)
		{
				
			row[m_status_list.m_col_status]="Non-Aktif";
		}
		else if(tsumber[i].status_koneksi==STATUS_AKTIF_NOTRY)
		{ //Inisialisasi
			row[m_status_list.icon]=icon_default;//Gdk::Pixbuf::create_from_file("emblem-default.png");
			row[m_status_list.m_col_status]="Aktif";
		}
		else if(tsumber[i].status_koneksi==STATUS_OK)
		{
			row[m_status_list.m_col_status]="Baik";
			row[m_status_list.icon]=icon_generic;//Gdk::Pixbuf::create_from_file("emblem-default.png");
		}
		else if(tsumber[i].status_koneksi==STATUS_DATA_INVALID)
		{
			row[m_status_list.m_col_status]="Data-Invalid";
		}
		else if(tsumber[i].status_koneksi==STATUS_TIMEOUT)
		{
			row[m_status_list.icon]=icon_warning;//Gdk::Pixbuf::create_from_file("icon/dialog-warning.png");
			row[m_status_list.m_col_status]="Timeout";
		}
		else if(tsumber[i].status_koneksi==STATUS_NOT_FOUND)
		{
			row[m_status_list.icon]=icon_error;//Gdk::Pixbuf::create_from_file("dialog-error.png");
			row[m_status_list.m_col_status]="Koneksi Gagal";
		}
		else
			row[m_status_list.m_col_status]="ERROR";
			
	}
	
	if(!kolom_status_ada)
	{
		//tree_data->append_column("No.",m_status_list.m_col_id);
		Gtk::TreeView::Column* pColumn=Gtk::manage( new Gtk::TreeView::Column("Sumber Data"));
		pColumn->pack_start(m_status_list.icon,false);
		pColumn->pack_start(m_status_list.m_col_alamat_ip,true);

		tree_status->append_column(*pColumn);
		
		//tree_status->append_column("Sumber Data",m_status_list.m_col_alamat_ip);
		tree_status->append_column("Port",m_status_list.m_col_ip_port);
		//tree_data->append_column("Data",m_status_list.m_col_data);
		tree_status->append_column("Status",m_status_list.m_col_status);
		kolom_status_ada=true;
		delete pColumn;
	}
	
	return 0;
}

int main_window::gambar_grafik()
{
	printf("\n[Gambar Grafik]\n");
	char cwaktu[32];
	
	//waktu saat ini
	int jam_skr,menit_skr;
	time_t the_timelist;
	
	(void) time(&the_timelist);
	tm_pointer = localtime(&the_timelist);
	
	printf("[selisih_hari]\n");
	
	printf(" |--* Sekarang:\n");  //%H:%M:%S
	strftime(cwaktu,32,"%H",tm_pointer);
	jam_skr=atoi(cwaktu);
	printf(" |-- jam: %d (%s)\n",jam_skr,cwaktu);
	
	strftime(cwaktu,32,"%M",tm_pointer);
	menit_skr=atoi(cwaktu);
	printf(" |-- jam: %d (%s)\n",menit_skr,cwaktu);
	
	//Buat/Baca waktu yang harus ditampilkan
	
	sprintf(cwaktu,"%04d%02d%02d",spin_tahun->get_value_as_int(),
							spin_bulan->get_value_as_int(),
							spin_tanggal->get_value_as_int());
	printf("astanggal=%s)\n",cwaktu);
	Glib::ustring asTanggal=cwaktu;
	Glib::ustring strQuery,usTemp;
	
	//Init variabel array data
	double data_tampil[24][60];
	bool ada_data_tampil[24][60];
	for(int jam=0;jam<24;jam++)
	{
		for(int menit=0;menit<60;menit++)
		{
			data_tampil[jam][menit]=0.0;
			ada_data_tampil[jam][menit]=false;
		}
	}
	
	//Database
	printf(" |--* Konek Database\n");
	//Konek Database
	if(!MYQ.isConnected)
	{
		if(MYQ.init_lengkap()!=1)
		{
			printf("Gagal melakukan inisialisasi database\n");
			return false;
		}
	}
	Glib::ustring asID=Glib::ustring::compose("%1",id_titik_tampil_sekarang);
	
	//Buat Query parameter 
	strQuery="SELECT * FROM titik_ukur WHERE id_titik= '" + asID + "'";
	printf(" |-- Query: %s\n",strQuery.c_str());
	strcpy(MYQ.Text,strQuery.c_str());
	if(MYQ.Query())
	{
		printf("error saat query\n");
		return 1;
	}
	
	if(MYQ.jum_row!=1)
	{
		printf("ERROR: data tidak ditemukan (ditemukan: %d)\n",MYQ.jum_row);
		return 1;
	}	
	
	int range_min,range_max,alarm_low1,alarm_low2,alarm_high1,alarm_high2;
	Glib::ustring usatuan,unama_titik;
	
	usTemp=MYQ.ambil_string("range_min");
	range_min=atoi(usTemp.c_str());
	printf(" |-- Range min: %d\n",range_min);
	
	usTemp=MYQ.ambil_string("range_max");
	range_max=atoi(usTemp.c_str());
	printf(" |-- Range max:%dnn",range_max);
	
	usTemp=MYQ.ambil_string("alarm_low1");
	alarm_low1=atoi(usTemp.c_str());
	printf(" |-- Range max:%dnn",range_max);
	
	usTemp=MYQ.ambil_string("alarm_low2");
	alarm_low2=atoi(usTemp.c_str());
	printf(" |-- Range max:%dnn",range_max);
	
	usTemp=MYQ.ambil_string("alarm_high1");
	alarm_high1=atoi(usTemp.c_str());
	printf(" |-- Range max:%dnn",range_max);
	
	usTemp=MYQ.ambil_string("alarm_high2");
	alarm_high2=atoi(usTemp.c_str());
	printf(" |-- Range max:%dnn",range_max);
	
	usatuan=MYQ.ambil_string("satuan");
	unama_titik=MYQ.ambil_string("nama_titik");
	
	MYQ.Buang();
	//Buat Qu'ery Data
	
	//asTanggal.assign(cwaktu);
	printf(" |--* Buat Query. asID:%s, asTanggal:%s\n",asID.c_str(),asTanggal.c_str());
	
	//Lama
	
	//Glib::ustring strQuery="SELECT * FROM data_tunggal RIGHT JOIN waktu on waktu.id_waktu=data_tunggal.id_waktu ";
	//strQuery+="WHERE id_titik_ukur='" + asID + "' AND waktu.waktu LIKE '" + asTanggal + "%'";
	//strQuery+="ORDER BY waktu ASC LIMIT 1440";

	//Baru
	int selisih=selisih_hari(asTanggal);
	printf(" |--* Tanggal data tampil: %s, selisih hari %d\n",asTanggal.c_str(),selisih);
	
	if(selisih<0)
	{
		Gtk::MessageDialog dialog(*this,"Data yang dipilih belum ada!",
		true /*use markup*/, Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK);

		//dialog.set_secondary_text("Tidak bisa menampilkan data yang belum ada");
		
		int result=dialog.run();
		
		return -1;
	}
		
	//jika kurang dari 1 hari baca data dari data_harian
	if(selisih<7)
	{
		strQuery="SELECT * FROM data_harian RIGHT JOIN waktu on waktu.id_waktu=data_harian.id_waktu ";
		strQuery+="WHERE id_titik_ukur='" + asID + "' AND waktu.waktu LIKE '" + asTanggal + "%'";
		strQuery+="ORDER BY waktu ASC LIMIT 2880";
	}	
	//jika lebih dari 7 hari, baca data langsung dari data_tunggal (lebih lama)
	else
	{
		if(belum_tanya)
		{
			Gtk::MessageDialog dialog(*this,"Data yang dipilih lebih dari 7, lanjutkan?",
			true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

			dialog.set_secondary_text("Data yang lebih lama dari 7 hari di simpan \ndalam database yang lebih besar \nsehingga memerlukan waktu pembacaan yang lebh lama");
			
		   result_7hari=dialog.run();
			belum_tanya=false;
		}
		
		switch(result_7hari)
		{
			case(Gtk::RESPONSE_OK):
				strQuery="SELECT * FROM data_tunggal RIGHT JOIN waktu on waktu.id_waktu=data_tunggal.id_waktu ";
				strQuery+="WHERE id_titik_ukur='" + asID + "' AND waktu.waktu LIKE '" + asTanggal + "%'";
				strQuery+="ORDER BY waktu ASC LIMIT 2880"; //was 1440
				
				break;
			default:
				//Keluar dari fungsi
				return -1;
		}
	}
	
	strcpy(MYQ.Text,strQuery.c_str());
	printf("Query: %s\n",strQuery.c_str());
	
	if(MYQ.Query())
	{
		printf("error saat query\n");
		return 1;
	}
	
	//End of Baru
	printf(" |--* List data (%d)\n",MYQ.jum_row);
	Glib::ustring data_waktu, data_waktu_temp,data_temp;
	
	int ijam,imenit,ijumlah_data,data_counter;
	double max_nilai=0, min_nilai=9999;
	
	for(int i=0;i<MYQ.jum_row;i++)
	{
		data_waktu= MYQ.ambil_string("waktu");
		//printf(" |  |--* %s\n",data_waktu.c_str());		
		//20080805-225432
		//jam
		data_waktu_temp=data_waktu.substr(9,2);
		ijam=atoi(data_waktu_temp.c_str());
		
		//menit
		data_waktu_temp=data_waktu.substr(11,2);
		imenit=atoi(data_waktu_temp.c_str());
									
		//data_temp
		data_temp=MYQ.ambil_string("data_tunggal");
		
		if((ijam<=24)&&(imenit<=60))
		{
			data_tampil[ijam][imenit]=strtod(data_temp.c_str(),NULL);
			ada_data_tampil[ijam][imenit]=true;
			
			if(data_tampil[ijam][imenit]>max_nilai)
				max_nilai=data_tampil[ijam][imenit];
			
			//if(data_tampil[ijam][imenit]<min_nilai)
				min_nilai=data_tampil[ijam][imenit];
			
			//printf(" |  |-- %d->[%d][%d]=%f\n",i,ijam,imenit,data_tampil[ijam][imenit]);
		}
		else
			ada_data_tampil[ijam][imenit]=false;
			
		
		MYQ.Next();			
	}
	
	MYQ.Buang();
	
	//Init variabel gambar_grafik
	int xc, yc,tinggi,lebar;
	tinggi=drawingarea1->get_height();
	lebar=drawingarea1->get_width();
	xc = drawingarea1->get_width() / 2;
	yc = drawingarea1->get_height() / 2;
	
	Cairo::RefPtr<Cairo::Context> DC = drawingarea1->get_window()->create_cairo_context();
	//Init variabel
	//DC ->set_source_rgb(1.0, 0.0, 0.0);
	DC ->set_line_width(1.0);


	//double max_range=15;
	int x_lama,y_lama;
	double dy;
	int x_baru,y_baru;
	double skala_menit,skala_tinggi;
	int pengali;
	
	skala_menit=(double)lebar/(24.0*60.0);
	mode_gambar=SKALA_MANUAL;
	
	//menurut data
	if(mode_gambar==SKALA_MANUAL)
	{
		skala_tinggi=(double)tinggi/range_max;
		
		vruler1->set_range(range_max,0,range_max,0);
		pengali=1;
	}
	
	//otomatis
	else if(mode_gambar==SKALA_OTOMATIS)
	{
		skala_tinggi=(double)tinggi/max_nilai;
		printf(" |--Mulai Gambar. skala_menit:%f,skala_tinggi:%f\n",skala_menit,skala_tinggi);
		//Mulai Gambar
		
		if(max_nilai<10)
		{
			vruler1->set_range(max_nilai,0,max_nilai,0);
			pengali=1;
		}
		else if(max_nilai<100)
		{
			vruler1->set_range((double)max_nilai/10.0,0,max_nilai/10,0);
			pengali=10;
		}
		else if(max_nilai<1000)
		{
			vruler1->set_range((double)max_nilai/100.0,0,max_nilai/100,0);
			pengali=100;
		}
		else if(max_nilai<10000)
		{
			vruler1->set_range((double)max_nilai/1000.0,0,max_nilai/1000,0);
			pengali=1000;
		}
		else if(max_nilai<100000)
		{
			vruler1->set_range((double)max_nilai/1000.0,0,max_nilai/1000,0);
			pengali=10000;
		}
		else
		{
			vruler1->set_range(max_nilai,0,max_nilai,0);
			pengali=1;
		}
	}
	
	//Gambar garis waktu

	//Garis jam 
	DC ->set_line_width(0.25);
	DC ->set_source_rgb(0.0, 0.5, 0.0);
	for(int i=0;i<24;i++)
	{
		DC->move_to((i*60)*skala_menit,0);
		DC->line_to((i*60)*skala_menit,tinggi);
	}
	DC->stroke();
	//Garis waktu sekarang
	DC ->set_line_width(1.0);
	DC ->set_source_rgb(0.0, 0.0, 1.0);
	DC->move_to((jam_skr*60+menit_skr)*skala_menit,0);
	DC->line_to((jam_skr*60+menit_skr)*skala_menit,tinggi);
	DC->stroke();
	
	//garis batas-batas alarm
	DC->set_line_width(0.25);
	DC->set_source_rgb(0.0,0.5,0.5);
	
	//alarm high 1
	DC->move_to(0,alarm_high1*skala_tinggi);
	DC->line_to(lebar,alarm_high1*skala_tinggi);
	
	//alarm high 2
	DC->move_to(0,alarm_high2*skala_tinggi);
	DC->line_to(lebar,alarm_high2*skala_tinggi);
	
	//alarm low 1s
	DC->move_to(0,alarm_low1*skala_tinggi);
	DC->line_to(lebar,alarm_low1*skala_tinggi);
	
	//alarmlow 2
	DC->move_to(0,alarm_low2*skala_tinggi);
	DC->line_to(lebar,alarm_low2*skala_tinggi);
	
	DC->stroke();
	
	//Gambar garis 
	DC ->set_line_width(1.0);
	//set_range (double lower, double upper, double position, double max_size)
	hruler1->set_range(0,24,(double)jam_skr+((double)menit_skr/60.0),10);
	printf(" |-- set ruler, posisi: %0.2f\n",(double)jam_skr+((double)menit_skr/60.0));
	//gambar grafik chart
	//DC ->set_source_rgb(1.0, 0.0, 0.0);
	DC->set_source_rgb(0.8, 0.0, 0.0);
	
	x_baru=0;
	y_baru=tinggi;
	DC->move_to(x_baru,y_baru);
	bool last_valid=false;
	
	for(int jam=0;jam<24;jam++)
	{
		for(int menit=0;menit<60;menit++)
		{
			
			x_baru=(int)(skala_menit*((double)menit+((double)jam*60.0)));

			y_baru=tinggi-(int)(skala_tinggi*data_tampil[jam][menit]);
			
			if(!last_valid)
			{
				DC->move_to(x_baru,y_baru);
			}
			//sprintf(
			//printf(" |--[%d][%d]line_to(%d,%d) data_tampil:%f\n",jam,menit,x_baru,y_baru,data_tampil[jam][menit]);
			if(ada_data_tampil[jam][menit]==true)
			{
				DC->line_to(x_baru,y_baru);
				last_valid=true;
			}
			else	
			{
				DC->move_to(x_baru,tinggi);
				last_valid=false;
			}
		}
	}
	
	//Gambarkan
	DC->stroke();
	usTemp=Glib::ustring::compose("skala x %1 ",pengali);
	label_info->set_text(usTemp + usatuan);
	label_waktu->set_text(asTanggal.substr(6,2) + "-" + asTanggal.substr(4,2) + "-" + asTanggal.substr(0,4));
	printf(" |--* Selesai gambar\n");
	//MYQ.Close();
}

bool main_window::on_drawingarea1_expose_event(GdkEventExpose *ev)
{
	gambar_grafik();
}

bool main_window::HapusDataJaman(int id_waktu_sekarang)
{
	Glib::ustring usQuery;
	//printf("[main_window::HapusDataJaman]\n");
	usQuery=Glib::ustring::compose(
			"DELETE from data_jaman WHERE waktu<(SELECT waktu.waktu FROM waktu WHERE id_waktu='%1')",
			id_waktu_sekarang-2);
	//printf(" |--* Hapus Data Jaman:\n|--|--* Query : %s\n",usQuery.c_str());
	if(!MYQ.isConnected)
	{
		if(MYQ.init_lengkap()!=1)
		{
			printf("Gagal melakukan inisialisasi database\n");
			return false;
		}
	}
	
	strcpy(MYQ.Text,usQuery.c_str());
	if(MYQ.Delete())
	{
		//printf(" |--* Delete OK\n");			
	}
	else
	{
		printf("->Hapus data_jaman Gagal\n");
		//MYQ.Close();
		return false;
	}
	MYQ.Close();
	//printf("[/main_window::HapusDataJaman]\n");
	return true;
}

void main_window::on_button_tanggal_apply_clicked()
{
	UpdateListView (depth_level_sekarang,id_titik_tampil_sekarang);
}

void main_window::on_konfigurasi1_activate()
{
	printf("[Konfigurasi 1 Activate]\n");
	int result;
	
	this->LoadConfig();
	
	//Buat instance dlg_konfigurasi
	dlg_konfigurasi *dlg_konfig = new class dlg_konfigurasi();
	
	//Isi variabel
	//Mode
	if(kfg.mode==10) //mode monitor/browsing
	{
		dlg_konfig->radio_mode_monitor->set_active(true);	
	}
	else if(kfg.mode==20)
	{
		//server mode
		dlg_konfig->radio_mode_server->set_active(true);
	}
	else
	{
		//set ke default
		kfg.mode=10; //browsing mode
		dlg_konfig->radio_mode_monitor->set_active(true);
	}
	
	//Autostart
	if(kfg.auto_start==1)
	{
		printf("AutoStart enabled\n");
	}
	else
	{
		printf("AutoStart disabled\n");
	}
	
	//if(dlg_konfig->check_autostart->get_active())
	//{
	//	kfg.auto_start=1;
	//}
	//else
	//{
	//	kfg.auto_start=0;
//	}
	//Timing data logging
	dlg_konfig->spin_periode_logging->set_value((double)kfg.siklus_ambil_data);
	dlg_konfig->spin_periode_simpan->set_value((double)kfg.waktu_simpan_data);
	dlg_konfig->spin_refresh_list->set_value((double)kfg.waktu_refresh_tabel_utama);
	dlg_konfig->spin_refresh_grafik->set_value((double)kfg.waktu_refresh_grafik_utama);
	
	//Timing database temporer
	dlg_konfig->spin_periode_db_temp->set_value((double)kfg.waktu_simpan_data_harian);
	
	//Tampilkan
	result=dlg_konfig->run();
	
	switch(result)
	{
		case GTK_RESPONSE_OK:
		printf(" |-- Edit setting\n");
			
		//Baca konfigurasi
		//Mode (10: browsing/monitor, 20: server)
		if(dlg_konfig->radio_mode_monitor->get_active())
		{
			kfg.mode=10;	
		}
		else if(dlg_konfig->radio_mode_server->get_active())
		{
			kfg.mode=20;
			
			if(kfg.auto_start==1)
			{
				dlg_konfig->check_autostart->set_active(true);
			}
			
		}
		else
			kfg.mode=10;
		
		//Timing data logging
		kfg.siklus_ambil_data=(int)(dlg_konfig->spin_periode_logging->get_value());
		kfg.waktu_simpan_data=(int)dlg_konfig->spin_periode_simpan->get_value();
		kfg.waktu_refresh_tabel_utama=(int)dlg_konfig->spin_refresh_list->get_value();
		kfg.waktu_refresh_grafik_utama=(int)dlg_konfig->spin_refresh_grafik->get_value();
		
		//Timing database
		kfg.waktu_simpan_data_harian=(int)dlg_konfig->spin_periode_db_temp->get_value();	
			
		this->SimpanKonfig(&kfg);
		dlg_konfig->hide();
		break;
		default:
			printf(" |-- Batal edit setting\n");
			dlg_konfig->hide();
		break;
	}
	
	//Apply konfig
	if(kfg.mode==10)
	{	
		button_logging_data->set_sensitive(false);
	}
	else
		button_logging_data->set_sensitive(true);
	
	delete dlg_konfig;
}

void main_window::on_database_login_setting1_activate()
{
	printf("[Database login 1 Activate]\n");
	
	this->on_buttonbuka_clicked();
	
}

void main_window::on_sumber_data1_activate()
{
	printf("[Sumber Data 1 Activate]\n");
	this->on_button_sumber_clicked();
}

void main_window::on_posting_pengiriman_data1_activate()
{
	printf("[Posting Pengiriman 1 Activate]\n");
	//Buat instance dialog edit titik
	dlg_posting_data *dlg_post=new dlg_posting_data();
	
	//Init dialog
	memcpy(&dlg_post->MYQ,(void*) &MYQ,sizeof(MyQuery));
	
	//dlg_titik->ReloadCombo(COMBO_SEMUA);
	dlg_post->ReloadList();
	
	int result=dlg_post->run();
	
	switch(result)
	{
		case GTK_RESPONSE_OK:
			printf("->GTK Response OK\n");
			
			
		break;
		
		default:
			printf("->default\n");
		break;
	}
	delete dlg_post;
}
void main_window::on_mulai_baca_data1_activate()
{
	printf("[Mulai Baca Data 1 Activate]\n");
}

void main_window::on_stop_baca_data1_activate()
{
	printf("[Stop Baca Data 1 Activate]\n");
}
void main_window::on_quit1_activate()
{
	printf("[Quit 1 Activate]\n");
	this->~main_window();
}

/*selisih hari
 
 menghitung selisih hari suatu tanggal dengan sekarang
 Jika sekarang tanggal 20080807 dan dibandingkan dengan 20080806
 maka selisih 
 
 */
int main_window::selisih_hari(Glib::ustring tanggal) //format YYYYmmdd
{
	
	int itahun,itanggal,ibulan;
	int itahun_skr,ibulan_skr,itanggal_skr;
	Glib::ustring usTemp;
	char cwaktu[64];
	time_t the_timelist;
	
	(void) time(&the_timelist);
	tm_pointer = localtime(&the_timelist);
	
	printf("[selisih_hari]\n");
	
	printf(" |--* Sekarang:\n");
	strftime(cwaktu,32,"%d",tm_pointer);
	itanggal_skr=atoi(cwaktu);
	printf(" |-- tanggal: %d (%s)\n",itanggal,cwaktu);
	
	strftime(cwaktu,32,"%m",tm_pointer);
	ibulan_skr=atoi(cwaktu);
	printf(" |-- bulan: %d (%s)\n",ibulan,cwaktu);
	
	strftime(cwaktu,32,"%Y",tm_pointer);
	itahun_skr=atoi(cwaktu);
	printf(" |-- tahun: %d (%s)\n",itahun,cwaktu);
	
	printf(" |--* Data tanggal :%s\n",tanggal.c_str());

	usTemp=tanggal.substr(0,4);
	itahun=atoi(usTemp.c_str());
	printf(" |-- tahun : %d\n",itahun);
	
	usTemp=tanggal.substr(4,2);
	ibulan=atoi(usTemp.c_str());
	printf(" |-- bulan : %d\n",ibulan);
	
	usTemp=tanggal.substr(6,2);
	itanggal=atoi(usTemp.c_str());
	printf(" |-- tanggal : %d\n",itanggal);
	
	int selisih_tahun=itahun_skr-itahun;
	int selisih_bulan=ibulan_skr-ibulan;
	int selisih_tanggal=itanggal_skr-itanggal;
		

	int selisih=(selisih_tahun*365+selisih_bulan*30+selisih_tanggal);
	printf(" |--* Selisih hari: %d\n",selisih);
	
	return selisih;
	
	//cara lain menurut web
	/*
	 
	 */
}

Glib::ustring main_window::cari_tanggal(Glib::ustring tanggal_sekarang,int selisih_hari)
{
	int itahun,itanggal,ibulan;
	int itahun_skr,ibulan_skr,itanggal_skr;
	Glib::ustring usTemp,tanggal_hasil;
	Glib::ustring usTahun,usBulan,usTanggal;
	
	char cwaktu[64];
	time_t the_timelist;
	
	(void) time(&the_timelist);
	tm_pointer = localtime(&the_timelist);
	
	//printf("[cari_tanggal]\n");
	if(tanggal_sekarang=="")//dari waktu sekarang
	{
		//printf(" |--* Sekarang:\n");
		strftime(cwaktu,32,"%d",tm_pointer);
		itanggal_skr=atoi(cwaktu);
		//printf(" |-- tanggal: %d (%s)\n",itanggal_skr,cwaktu);
		
		strftime(cwaktu,32,"%m",tm_pointer);
		ibulan_skr=atoi(cwaktu);
		//printf(" |-- bulan: %d (%s)\n",ibulan_skr,cwaktu);
		
		strftime(cwaktu,32,"%Y",tm_pointer);
		itahun_skr=atoi(cwaktu);
		//printf(" |-- tahun: %d (%s)\n",itahun_skr,cwaktu);
	}		
	else
	{
		//parsing 
		usTemp=tanggal_sekarang.substr(0,4);
		itahun_skr=atoi(usTemp.c_str());
		//printf(" |-- tahun : %d (%s)\n",itahun_skr,usTemp.c_str());
		
		usTemp=tanggal_sekarang.substr(4,2);
		ibulan_skr=atoi(usTemp.c_str());
		//printf(" |-- bulan : %d (%s)\n",ibulan_skr,usTemp.c_str());
		
		usTemp=tanggal_sekarang.substr(6,2);
		itanggal_skr=atoi(usTemp.c_str());
		//printf(" |-- tanggal : %d (%s)\n",itanggal_skr,usTemp.c_str());		
	}
	//printf(" |--* selisih hari: %d\n",selisih_hari);
	
	if(selisih_hari<0) //hari sebelumnya
	{
		//printf(" |-- Selisih <0\n");
		if(itanggal_skr<=-(selisih_hari)) //minus diminuskan
		{
			//printf(" |--|-- %d<=%d\n",itanggal_skr,-(selisih_hari)); 
			if(ibulan_skr==1)
			{
				itahun=itahun_skr-1;
				ibulan=12;
				itanggal=max_tanggal[ibulan-1]+itanggal_skr+selisih_hari;
			}
			else
			{
				itahun=itahun_skr;
				ibulan=ibulan_skr-1;
				itanggal=max_tanggal[ibulan-1]+itanggal_skr+selisih_hari;
			}
		}
		else
		{
			//printf(" |--|-- %d>=%d\n",itanggal_skr,selisih_hari);
			itanggal=itanggal_skr+selisih_hari;
			ibulan=ibulan_skr;
			itahun=itahun_skr;
		}
	}
	else
	{
			itanggal=itanggal_skr+selisih_hari;
			ibulan=ibulan_skr;
			itahun=itahun_skr;
	}
	
	//printf(" |--* Hasil: \n");
	//printf(" |--|-- tanggal: %d\n",itanggal);
	//printf(" |--|-- bulan: %d\n",ibulan);
	//printf(" |--|-- tahun: %d\n",itahun);
	
	//formatnya yyyymmdd
	//tanggal_hasil=Glib::ustring::compose("%0.1%0.2%03",itahun,ibulan,itanggal);
	sprintf(cwaktu,"%0.4d%0.2d%0.2d",itahun,ibulan,itanggal);
	tanggal_hasil.assign(cwaktu);
	//printf(" |--* Hasil tanggal: %s\n", tanggal_hasil.c_str());
	//printf("[/cari_tanggal]\n");
	return tanggal_hasil;
}

void main_window::on_notebook1_switch_page(GtkNotebookPage *p0, guint p1)
{
	printf("[notebook1 switch page]\n");
}
      
void main_window::on_button_refresh_clicked() 
{
	this->gambar_grafik();
}

void main_window::on_tree_status_cursor_changed() 
{
	//printf("Cursor changed\n");
	int id;
	
	Glib::ustring strText;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;
	
	refTreeSelection= this->tree_status->get_selection();
	iter = refTreeSelection->get_selected();
	
	Gtk::Tooltips* tooltips=new Gtk::Tooltips;
	
	if(iter) //If anything is selected
	{
		Gtk::TreePath *tpath= new Gtk::TreePath(iter);
		int depth=tpath->get_depth();
		
		row = *iter;
	  	//Do something with the row.
		
		strText= row[m_status_list.m_col_nama_sumber];
		main_tooltips.set_tip(*tree_status, strText, "");
	}
	else
	{
		
	}
	delete tooltips;
		//tree_status.set_tooltips(*tooltips,"Pilih kolom untuk melihat nama Sumber");
}

void main_window::on_button_open_kalender_clicked()
{
	printf("[button open kalender]\n");
	
	int result;
	Glib::Date date;
	struct tm tm_tanggal;
	int itanggal,ibulan,itahun;
	char cwaktu[32];
	
	dlg_kalender *dlg_kal = new class dlg_kalender();
	
	result=dlg_kal->run();
	
	switch(result)
	{
		case GTK_RESPONSE_OK:
			printf("+-- Set tanggal\n");
		
			
			dlg_kal->calendar1->get_date(date);
			date.to_struct_tm(tm_tanggal);
			
			printf("[Inisialisasi Waktu]\n");
			strftime(cwaktu,32,"%d",&tm_tanggal);
			itanggal=atoi(cwaktu);
			printf(" |-- tanggal: %d\n",itanggal);
			strftime(cwaktu,32,"%m",&tm_tanggal);
			ibulan=atoi(cwaktu);
			printf(" |-- bulan: %d\n",ibulan);
			strftime(cwaktu,32,"%Y",&tm_tanggal);
			itahun=atoi(cwaktu);
			printf(" |-- tahun: %d\n",itahun);
			
			spin_tanggal->set_value(itanggal);
			spin_bulan->set_value(ibulan);
			spin_tahun->set_value(itahun);
			
			
			dlg_kal->hide();
			
		break;
		default:
			dlg_kal->hide();
		break;
	}
	
	delete dlg_kal;
}

int main_window::init_log()
{
	printf("[init_log]\n");
	m_refLogModel = Gtk::TreeStore::create(m_log_list);
	tree_log->set_model(m_refLogModel);
	Gtk::TreeModel::Row row;
	
	row=*(m_refLogModel->append());
	
	row[m_log_list.log_data]="Inisialiasi Log";
	row[m_log_list.icon]=Gdk::Pixbuf::create_from_file("emblem-generic16.png");
	
	kolom_log_ada=false; //ah useless
	
	if(!kolom_log_ada)
	{
		//tree_log->append_column("waktu",m_log_list.log_waktu);
		Gtk::TreeView::Column* pColumn=Gtk::manage( new Gtk::TreeView::Column("Log"));
		pColumn->pack_start(m_log_list.icon,false);
		pColumn->pack_start(m_log_list.log_waktu,false);
		pColumn->pack_start(m_log_list.log_data,true);

		tree_log->append_column(*pColumn);
		
		//tree_log->append_column("Port",m_status_list.m_col_ip_port);
		//tree_log->append_column("Status",m_status_list.m_col_status);
		kolom_log_ada=true;
		
		delete pColumn;
	}
	expander_log->set_expanded(false);
	printlog("======== MONITA APP STARTING ===========",0);
	printf("[\\init_log]\n");
}

int main_window::add_log(Glib::ustring teks, int status,int level)
{
	//printf("[add_log]\n");
	
	FILE *stream;
	Glib::ustring asFilePath;
	Glib::ustring uwaktu;
	char waktu[32];
	time_t the_time;
	(void) time(&the_time);
	tm_ptr = localtime(&the_time);
	
	strftime(waktu,32,"%H:%M:%S",tm_ptr); //"%Y%m%d-%H%M%S",tm_ptr);
	
	Gtk::TreeModel::Row row;
	
	row=*(m_refLogModel->append());
	
	row[m_log_list.log_data]=teks;
	//tree_log->set_selected(row);
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection;
	refSelection=tree_log->get_selection();
	refSelection->select(row);
	
	uwaktu.assign(waktu);
	row[m_log_list.log_waktu]=uwaktu;
	if(status==LOG_INFO)
		row[m_log_list.icon]=icon_info;//Gdk::Pixbuf::create_from_file("emblem-generic16.png");
	else if(status==LOG_WARNING)
		row[m_log_list.icon]=icon_warning;//Gdk::Pixbuf::create_from_file("emblem-generic16.png");
	else if(status==LOG_ALARM_1)
		row[m_log_list.icon]=icon_alarm1;//Gdk::Pixbuf::create_from_file("emblem-important.png");
	else if(status==LOG_ALARM_2)
		row[m_log_list.icon]=icon_alarm2;//Gdk::Pixbuf::create_from_file("emblem-important.png");
	else
		row[m_log_list.icon]=icon_default;//Gdk::Pixbuf::create_from_file("emblem-important.png");

	printlog(teks,level);
	//printf("[\\add_log]\n");
	
	return 0;
}

void main_window::on_tambah_entri_perusahaan1_activate()
{
	printf("[on_tambah_entri_perusahaan1_activate]\n");
	dlg_edit_persh* dlg_persh=new dlg_edit_persh();
	
	memcpy(&dlg_persh->MYQ,(void*) &MYQ,sizeof(MyQuery));
	
	dlg_persh->id_persh=0; //data baru
	
	dlg_persh->isi_form();
	dlg_persh->run();
	dlg_persh->hide();
	
	UpdateTreeView (0,0);
	
	delete dlg_persh;
}

void main_window::on_about1_activate()
{
	printf("[on_about1_activate]\n");
	
	//dlg_about* about=new class dlg_about();
	char my_date[] = "Compile Date = " __DATE__;
	char my_time[] = "Compile Time = " __TIME__;
	char compile_time[]= "Compile time: " __DATE__ " " __TIME__;
	Glib::ustring waktu_compile;
	
	//about.present();
	
	//delete about;
	m_Dialog.set_transient_for(*this);

	m_Dialog.set_name("Monita Application");
	m_Dialog.set_version("1.0.1");
	m_Dialog.set_copyright("PT Daun Biru Engineering");
	m_Dialog.set_comments(compile_time);//"Software untuk Monitoring dan display");
    
	//m_Dialog.set_license("LGPL");

	m_Dialog.set_website("http://www.daunbiru.com");
	m_Dialog.set_website_label("Daun Biru Engineering Website");

	std::list<Glib::ustring> list_authors;
	list_authors.push_back("Herry Susanto");
	list_authors.push_back("Fana Akbarkan");
	list_authors.push_back("Wawan");
						 
	//list_authors.push_back("R&D D");
	m_Dialog.set_authors(list_authors);

	m_Dialog.show_all_children();

	m_Dialog.show();

 	//Bring it to the front, in case it was already shown:
  	m_Dialog.present();
}

void main_window::on_menu_file_popup_hapus()
{
	printf("[on_menu_file_popup_hapus]\n");

	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = treeview1->get_selection();
	if(refSelection)
	{
		Gtk::TreeModel::iterator iterx = refSelection->get_selected();
		Gtk::TreePath *tpath= new Gtk::TreePath(iterx);
		
		int id = (*iterx)[m_Columns.m_col_id];
		int depth=tpath->get_depth();
		Glib::ustring valumenu=(*iterx)[m_Columns.m_col_name];
		
		//cari parent id	
		
		if(depth==1)
		{
			printf("-Persh: %s\n",valumenu.c_str());
			printf("-ID Persh: %d\n",id);
			
			this->hapus_perusahaan(id,valumenu);
		}
		else if(depth==2)
		{
			printf("-Dept: %s\n",valumenu.c_str()); 
			printf("-ID dept: %d\n",id);
			
			this->hapus_departemen(id,valumenu);
		}
		else if(depth==3)
		{
			printf("-Equipment: %s\n",valumenu.c_str());
			printf("-ID Equipment: %d\n",id);
			
			this->hapus_equipment(id,valumenu);
		}
		else if(depth==4)
		{
			printf("-Group: %s\n",valumenu.c_str());
			printf("-ID Group: %d\n",id);
			
			this->hapus_group(id,valumenu);
		}
		else if(depth==5)
		{
			printf("-Titik Ukur: %s\n",valumenu.c_str());
			printf("-ID titik: %d\n",id);	
			
			this->hapus_titik(id,valumenu);
			
		}
		
		delete tpath;
	}
}

int main_window::hapus_titik(int id_titik,Glib::ustring valumenu)
{
	printf("[hapus_titik]\n");
	Glib::ustring sTemp;
	int result,id_parent;
			
	sTemp="Hapus titik ukur [" + valumenu + "]?";
	Gtk::MessageDialog dialog(*this,sTemp,
	true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

	dialog.set_secondary_text("Peringatan: Menghapus titik ukur juga akan menghapus \nsemua data dari titik ukur ini");
	
	result=dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			printf(" |-- Hapus titik ukur\n");
			//konek database
			if(!MYQ.isConnected)
			{
				if(MYQ.init_lengkap()!=1)
				{
					printf(" |--|-- Gagal melakukan inisialisasi database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return false;
				}
			}
			
			//Ambil data 
			sTemp=Glib::ustring::compose("SELECT * FROM titik_ukur WHERE id_titik='%1'",id_titik);
			strcpy(MYQ.Text,sTemp.c_str());
			MYQ.Query();
			
			sTemp=MYQ.ambil_string("id_group_titik_ukur");
			id_parent=atoi(sTemp.c_str());
			
			MYQ.Buang();
			//hapus titik ukurnya
			sTemp=Glib::ustring::compose("DELETE FROM titik_ukur WHERE id_titik='%1'",id_titik);
			printf(" |-- Query: %s\n",sTemp.c_str());
			strcpy(MYQ.Text,sTemp.c_str());
			
			MYQ.Delete();
			
			//hapus datanya
			//data jaman
			sTemp=Glib::ustring::compose("DELETE FROM data_jaman WHERE id_titik='%1",id_titik);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			MYQ.Delete();
			
			//data harian
			sTemp=Glib::ustring::compose("DELETE FROM data_harian WHERE id_titik='%1",id_titik);
			strcpy(MYQ.Text,sTemp.c_str());
			
			MYQ.Delete();
			
			//data tunggal
			sTemp=Glib::ustring::compose("DELETE FROM data_tunggal WHERE id_titik='%1",id_titik);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			MYQ.Delete();
			
			//tutup databasenya
			MYQ.Close();
			break;
		default:
			//Keluar dari fungsi
			printf("default");
			return 0;
	}
	
	UpdateTreeView (3,id_parent);
	return 0;
}

int main_window::hapus_group(int id_group,Glib::ustring valumenu)
{
	printf("[hapus_group]\n");
	Glib::ustring sTemp;
	int result;
	int titik[100],jumlah_titik;
	int id_titik,id_parent;
			
	sTemp="Hapus titik ukur [" + valumenu + "]?";
	Gtk::MessageDialog dialog(*this,sTemp,
	true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

	dialog.set_secondary_text("Peringatan: Menghapus group juga akan menghapus \nsemua data dari ukur ini");
	
	result=dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			printf(" |-- Hapus group\n");
			
			//konek database
			if(!MYQ.isConnected)
			{
				if(MYQ.init_lengkap()!=1)
				{
					printf(" |--|-- Gagal melakukan inisialisasi database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return false;
				}
			}
			//Cari parent
			sTemp=Glib::ustring::compose("SELECT * FROM group_titik_ukur WHERE id_group='%1'",id_group);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s",sTemp.c_str());
			
			MYQ.Query();
			sTemp=MYQ.ambil_string("id_equipment");
			id_parent=atoi(sTemp.c_str());
			
			MYQ.Buang();
			//Query titik-titik di group ini
			sTemp=Glib::ustring::compose("SELECT * FROM titik_ukur WHERE id_group_titik_ukur='%1'",id_group);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s",sTemp.c_str());
			
			MYQ.Query();
			
			if(MYQ.jum_row>0)
			{
				jumlah_titik=MYQ.jum_row;
				for(int i=0;i<jumlah_titik;i++)
				{
					sTemp=MYQ.ambil_string("id_titik");
					try
					{
						id_titik=atoi(sTemp.c_str());
					}
					catch(...)
					{
						id_titik=0;
					}
					titik[i]=id_titik;
					MYQ.Next();
				}
			}
			else
				jumlah_titik=0;
			
			MYQ.Buang();
			
			for(int i=0;i<jumlah_titik;i++)
			{
				id_titik=titik[i];
				
				if(id_titik==0)
					continue;
				//hapus titik ukurnya
				sTemp=Glib::ustring::compose("DELETE FROM titik_ukur WHERE id_titik='%1'",id_titik);
				printf(" |-- Query: %s\n",sTemp.c_str());
				strcpy(MYQ.Text,sTemp.c_str());
				
				MYQ.Delete();
				
				//hapus datanya
				//data jaman
				sTemp=Glib::ustring::compose("DELETE FROM data_jaman WHERE id_titik='%1",id_titik);
				strcpy(MYQ.Text,sTemp.c_str());
				printf(" |-- Query: %s\n",sTemp.c_str());
				//MYQ.Delete();
				
				//data harian
				sTemp=Glib::ustring::compose("DELETE FROM data_harian WHERE id_titik='%1",id_titik);
				strcpy(MYQ.Text,sTemp.c_str());
				
				MYQ.Delete();
				
				//data tunggal
				sTemp=Glib::ustring::compose("DELETE FROM data_tunggal WHERE id_titik='%1",id_titik);
				strcpy(MYQ.Text,sTemp.c_str());
				printf(" |-- Query: %s\n",sTemp.c_str());
				MYQ.Delete();
			}
			
			//Jika sudah selesai, baru hapus data groupnya
			sTemp=Glib::ustring::compose("DELETE FROM group_titik_ukur WHERE id_group='%1'",id_group);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			MYQ.Delete();
			
			//tutup databasenya
			MYQ.Close();
			break;
		default:
			//Keluar dari fungsi
			printf("default");
			return 0;
	}
	
	UpdateTreeView (2,id_parent);
	return 0;
}

int main_window::hapus_equipment(int id_equipment,Glib::ustring valumenu)
{
	printf("[hapus_group]\n");
	Glib::ustring sTemp;
	int result;
	
	//group
	int jumlah_group=MYQ.jum_row;
	int id_group,group[100];
	int g;
	//titik
	int titik[100],jumlah_titik;
	int id_titik,id_parent;
		
	sTemp="Hapus data peralatan [" + valumenu + "]?";
	Gtk::MessageDialog dialog(*this,sTemp,
	true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

	dialog.set_secondary_text("Peringatan: Menghapus data peralatan juga akan menghapus \nsemua semua data ukur");
	
	result=dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			printf(" |-- Hapus equipment\n");
			//konek database
			if(!MYQ.isConnected)
			{
				if(MYQ.init_lengkap()!=1)
				{
					printf(" |--|-- Gagal melakukan inisialisasi database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return false;
				}
			}
			//Cari parent
			sTemp=Glib::ustring::compose("SELECT * FROM equipment WHERE id_equipment='%1'",id_equipment);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			
			MYQ.Query();
			sTemp=MYQ.ambil_string("id_dept");
			id_parent=atoi(sTemp.c_str());
			MYQ.Buang();
			
			//Query group-group di bawah equipment ini
			sTemp=Glib::ustring::compose("SELECT * FROM group_titik_ukur WHERE id_equipment='%1'",id_equipment);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			
			MYQ.Query();
			jumlah_group=MYQ.jum_row;
			
			for(g=0;g<jumlah_group;g++)
			{
				sTemp=MYQ.ambil_string("id_group");
				try
				{
					id_group=atoi(sTemp.c_str());
				}
				catch(...)
				{
					id_group=0;
				}
				group[g]=id_group;
				MYQ.Next();
			}
			MYQ.Buang();
			printf(" |-- Mulai hapus group\n");
			for(g=0;g<jumlah_group;g++)
			{
				id_group=group[g];
				//Query titik-titik di group ini
				sTemp=Glib::ustring::compose("SELECT * FROM titik_ukur WHERE id_group_titik_ukur='%1'",id_group);
				strcpy(MYQ.Text,sTemp.c_str());
				printf(" |-- Query: %s\n",sTemp.c_str());
				
		
				MYQ.Query();
				
				if(MYQ.jum_row>0)
				{
					jumlah_titik=MYQ.jum_row;
					for(int i=0;i<jumlah_titik;i++)
					{
						sTemp=MYQ.ambil_string("id_titik");
						try
						{
							id_titik=atoi(sTemp.c_str());
						}
						catch(...)
						{
							id_titik=0;
						}
						titik[i]=id_titik;
						MYQ.Next();
					}
				}
				else
					jumlah_titik=0;
				
				MYQ.Buang();
					
				for(int i=0;i<jumlah_titik;i++)
				{
					id_titik=titik[i];
					
					if(id_titik==0)
						continue;
					//hapus titik ukurnya
					sTemp=Glib::ustring::compose("DELETE FROM titik_ukur WHERE id_titik='%1'",id_titik);
					printf(" |-- Query: %s\n",sTemp.c_str());
					strcpy(MYQ.Text,sTemp.c_str());
					
					MYQ.Delete();
					
					//hapus datanya
					//data jaman
					sTemp=Glib::ustring::compose("DELETE FROM data_jaman WHERE id_titik='%1",id_titik);
					strcpy(MYQ.Text,sTemp.c_str());
					printf(" |-- Query: %s\n",sTemp.c_str());
					//MYQ.Delete();
					
					//data harian
					sTemp=Glib::ustring::compose("DELETE FROM data_harian WHERE id_titik='%1",id_titik);
					strcpy(MYQ.Text,sTemp.c_str());
					
					MYQ.Delete();
					
					//data tunggal
					sTemp=Glib::ustring::compose("DELETE FROM data_tunggal WHERE id_titik='%1",id_titik);
					strcpy(MYQ.Text,sTemp.c_str());
					printf(" |-- Query: %s\n",sTemp.c_str());
					MYQ.Delete();
				}
				
				//Jika sudah selesai, baru hapus data groupnya
				sTemp=Glib::ustring::compose("DELETE FROM group_titik_ukur WHERE id_group='%1'",id_group);
				strcpy(MYQ.Text,sTemp.c_str());
				printf(" |-- Query: %s\n",sTemp.c_str());
				MYQ.Delete();
			}
			
			//jika sudah selesai, baru hapus data peralatannya
			sTemp=Glib::ustring::compose("DELETE FROM equipment WHERE id_equipment='%1'",id_equipment);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			MYQ.Delete();
			
			//tutup databasenya
			MYQ.Close();
			break;
		default:
			//Keluar dari fungsi
			printf("default");
			return 0;
	}
	
	UpdateTreeView (1,id_parent);
	return 0;
}


/*ah capek juga sebenarnya mengulang2, tapi demi integritas koneksi database, gak papalah
 
 */
int main_window::hapus_departemen(int id_dept,Glib::ustring valumenu)
{
	printf("[hapus_departemen]\n");
	Glib::ustring sTemp;
	int result;
	
	//equipment
	int jumlah_equipment;
	int id_equipment,equipment[100];
	int e;
	
	//group
	int jumlah_group;
	int id_group,group[100];
	int g;
	//titik
	int titik[100],jumlah_titik;
	int id_titik,id_parent;
		
	sTemp="Hapus data departemen [" + valumenu + "]?";
	Gtk::MessageDialog dialog(*this,sTemp,
	true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

	dialog.set_secondary_text("Peringatan: Menghapus data departemen juga akan menghapus \nsemua semua data ukur di bawahnya");
	
	result=dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			printf(" |-- Hapus departemen\n");
			//konek database
			if(!MYQ.isConnected)
			{
				if(MYQ.init_lengkap()!=1)
				{
					printf(" |--|-- Gagal melakukan inisialisasi database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return false;
				}
			}
			
			//Cari parent
			sTemp=Glib::ustring::compose("SELECT * FROM departemen WHERE id_dep='%1'",id_dept);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			
			MYQ.Query();
			sTemp=MYQ.ambil_string("id_pers");
			id_parent=atoi(sTemp.c_str());
			MYQ.Buang();
			//Query equipment di bawah departemen
			sTemp=Glib::ustring::compose("SELECT * FROM equipment WHERE id_dept='%1'",id_dept);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			
			MYQ.Query();
			jumlah_equipment=MYQ.jum_row;
			
			for(g=0;g<jumlah_group;g++)
			{
				sTemp=MYQ.ambil_string("id_equipment");
				try
				{
					id_equipment=atoi(sTemp.c_str());
				}
				catch(...)
				{
					id_equipment=0;
				}
				equipment[e]=id_equipment;
				MYQ.Next();
			}
			MYQ.Buang();
			printf(" |-- Mulai hapus equipment\n");
			
			for(e=0;e<jumlah_equipment;e++)
			{
				//Query group-group di bawah equipment ini
				sTemp=Glib::ustring::compose("SELECT * FROM group_titik_ukur WHERE id_equipment='%1'",id_equipment);
				strcpy(MYQ.Text,sTemp.c_str());
				printf(" |-- Query: %s\n",sTemp.c_str());
				
				MYQ.Query();
				jumlah_group=MYQ.jum_row;
				
				for(g=0;g<jumlah_group;g++)
				{
					sTemp=MYQ.ambil_string("id_group");
					try
					{
						id_group=atoi(sTemp.c_str());
					}
					catch(...)
					{
						id_group=0;
					}
					group[g]=id_group;
					MYQ.Next();
				}
				MYQ.Buang();
				printf(" |-- Mulai hapus group\n");
				for(g=0;g<jumlah_group;g++)
				{
					id_group=group[g];
					//Query titik-titik di group ini
					sTemp=Glib::ustring::compose("SELECT * FROM titik_ukur WHERE id_group_titik_ukur='%1'",id_group);
					strcpy(MYQ.Text,sTemp.c_str());
					printf(" |-- Query: %s\n",sTemp.c_str());
					
			
					MYQ.Query();
					
					if(MYQ.jum_row>0)
					{
						jumlah_titik=MYQ.jum_row;
						for(int i=0;i<jumlah_titik;i++)
						{
							sTemp=MYQ.ambil_string("id_titik");
							try
							{
								id_titik=atoi(sTemp.c_str());
							}
							catch(...)
							{
								id_titik=0;
							}
							titik[i]=id_titik;
							MYQ.Next();
						}
					}
					else
						jumlah_titik=0;
					
					MYQ.Buang();
						
					for(int i=0;i<jumlah_titik;i++)
					{
						id_titik=titik[i];
						
						if(id_titik==0)
							continue;
						//hapus titik ukurnya
						sTemp=Glib::ustring::compose("DELETE FROM titik_ukur WHERE id_titik='%1'",id_titik);
						printf(" |-- Query: %s\n",sTemp.c_str());
						strcpy(MYQ.Text,sTemp.c_str());
						
						MYQ.Delete();
						
						//hapus datanya
						//data jaman
						sTemp=Glib::ustring::compose("DELETE FROM data_jaman WHERE id_titik='%1",id_titik);
						strcpy(MYQ.Text,sTemp.c_str());
						printf(" |-- Query: %s\n",sTemp.c_str());
						//MYQ.Delete();
						
						//data harian
						sTemp=Glib::ustring::compose("DELETE FROM data_harian WHERE id_titik='%1",id_titik);
						strcpy(MYQ.Text,sTemp.c_str());
						
						MYQ.Delete();
						
						//data tunggal
						sTemp=Glib::ustring::compose("DELETE FROM data_tunggal WHERE id_titik='%1",id_titik);
						strcpy(MYQ.Text,sTemp.c_str());
						printf(" |-- Query: %s\n",sTemp.c_str());
						MYQ.Delete();
					}
					
					//Jika sudah selesai, baru hapus data groupnya
					sTemp=Glib::ustring::compose("DELETE FROM group_titik_ukur WHERE id_group='%1'",id_group);
					strcpy(MYQ.Text,sTemp.c_str());
					printf(" |-- Query: %s\n",sTemp.c_str());
					MYQ.Delete();
				}
				
				//jika sudah selesai, baru hapus data peralatannya
				sTemp=Glib::ustring::compose("DELETE FROM equipment WHERE id_equipment='%1'",id_equipment);
				strcpy(MYQ.Text,sTemp.c_str());
				printf(" |-- Query: %s\n",sTemp.c_str());
				MYQ.Delete();
			}
			
			//jika sudah selesai, baru hapus data departemen
			sTemp=Glib::ustring::compose("DELETE FROM departemen WHERE id_dep='%1'",id_dept);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			MYQ.Delete();
			
			//tutup databasenya
			MYQ.Close();
			break;
		default:
			//Keluar dari fungsi
			printf("default");
			return 0;
	}
	
	UpdateTreeView (0,id_parent);
	return 0;
}

/*ah capek juga sebenarnya mengulang2, tapi demi integritas koneksi database, gak papalah
 
 */
int main_window::hapus_perusahaan(int id_persh,Glib::ustring valumenu)
{
	printf("[hapus_departemen]\n");
	Glib::ustring sTemp;
	int result;
	
	//departemen
	int jumlah_departemen;
	int id_departemen,departemen[100];
	int d;
	
	//equipment
	int jumlah_equipment;
	int id_equipment,equipment[100];
	int e;
	
	//group
	int jumlah_group;
	int id_group,group[100];
	int g;
	//titik
	int titik[100],jumlah_titik;
	int id_titik;
		
	sTemp="Hapus data departemen [" + valumenu + "]?";
	Gtk::MessageDialog dialog(*this,sTemp,
	true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

	dialog.set_secondary_text("Peringatan: Menghapus data perusahaan juga akan menghapus \nsemua semua data ukur di bawahnya");
	
	result=dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			printf(" |-- Hapus departemen\n");
			//konek database
			if(!MYQ.isConnected)
			{
				if(MYQ.init_lengkap()==1)
				{
					printf(" |--|-- Gagal melakukan inisialisasi database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return false;
				}
			}
			//Query departemen di bawah perusahaan
			sTemp=Glib::ustring::compose("SELECT * FROM departemen WHERE id_pers='%1'",id_persh);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			
			MYQ.Query();
			jumlah_departemen=MYQ.jum_row;
			
			for(d=0;d<jumlah_departemen;d++)
			{
				sTemp=MYQ.ambil_string("id_dep");
				try
				{
					id_departemen=atoi(sTemp.c_str());
				}
				catch(...)
				{
					id_departemen=0;
				}
				departemen[d]=id_equipment;
				MYQ.Next();
			}
			MYQ.Buang();
			printf(" |-- Mulai hapus departemen\n");
			
			for(d=0;d<jumlah_departemen;d++)
			{
				id_departemen=departemen[d];	
				//Query equipment di bawah departemen
				sTemp=Glib::ustring::compose("SELECT * FROM equipment WHERE id_dept='%1'",id_departemen);
				strcpy(MYQ.Text,sTemp.c_str());
				printf(" |-- Query: %s\n",sTemp.c_str());
				
				MYQ.Query();
				jumlah_equipment=MYQ.jum_row;
				
				for(g=0;g<jumlah_equipment;g++)
				{
					sTemp=MYQ.ambil_string("id_equipment");
					try
					{
						id_equipment=atoi(sTemp.c_str());
					}
					catch(...)
					{
						id_equipment=0;
					}
					equipment[e]=id_equipment;
					MYQ.Next();
				}
				MYQ.Buang();
				printf(" |-- Mulai hapus equipment\n");
				
				for(e=0;e<jumlah_equipment;e++)
				{
					id_equipment=equipment[e];
					//Query group-group di bawah equipment ini
					sTemp=Glib::ustring::compose("SELECT * FROM group_titik_ukur WHERE id_equipment='%1'",id_equipment);
					strcpy(MYQ.Text,sTemp.c_str());
					printf(" |-- Query: %s\n",sTemp.c_str());
					
					MYQ.Query();
					jumlah_group=MYQ.jum_row;
					
					for(g=0;g<jumlah_group;g++)
					{
						sTemp=MYQ.ambil_string("id_group");
						try
						{
							id_group=atoi(sTemp.c_str());
						}
						catch(...)
						{
							id_group=0;
						}
						group[g]=id_group;
						MYQ.Next();
					}
					MYQ.Buang();
					printf(" |-- Mulai hapus group\n");
					for(g=0;g<jumlah_group;g++)
					{
						id_group=group[g];
						//Query titik-titik di group ini
						sTemp=Glib::ustring::compose("SELECT * FROM titik_ukur WHERE id_group_titik_ukur='%1'",id_group);
						strcpy(MYQ.Text,sTemp.c_str());
						printf(" |-- Query: %s\n",sTemp.c_str());
						
				
						MYQ.Query();
						
						if(MYQ.jum_row>0)
						{
							jumlah_titik=MYQ.jum_row;
							for(int i=0;i<jumlah_titik;i++)
							{
								sTemp=MYQ.ambil_string("id_titik");
								try
								{
									id_titik=atoi(sTemp.c_str());
								}
								catch(...)
								{
									id_titik=0;
								}
								titik[i]=id_titik;
								MYQ.Next();
							}
						}
						else
							jumlah_titik=0;
						
						MYQ.Buang();
							
						for(int i=0;i<jumlah_titik;i++)
						{
							id_titik=titik[i];
							
							if(id_titik==0)
								continue;
							//hapus titik ukurnya
							sTemp=Glib::ustring::compose("DELETE FROM titik_ukur WHERE id_titik='%1'",id_titik);
							printf(" |-- Query: %s\n",sTemp.c_str());
							strcpy(MYQ.Text,sTemp.c_str());
							
							MYQ.Delete();
							
							//hapus datanya
							//data jaman
							sTemp=Glib::ustring::compose("DELETE FROM data_jaman WHERE id_titik='%1",id_titik);
							strcpy(MYQ.Text,sTemp.c_str());
							printf(" |-- Query: %s\n",sTemp.c_str());
							//MYQ.Delete();
							
							//data harian
							sTemp=Glib::ustring::compose("DELETE FROM data_harian WHERE id_titik='%1",id_titik);
							strcpy(MYQ.Text,sTemp.c_str());
							
							MYQ.Delete();
							
							//data tunggal
							sTemp=Glib::ustring::compose("DELETE FROM data_tunggal WHERE id_titik='%1",id_titik);
							strcpy(MYQ.Text,sTemp.c_str());
							printf(" |-- Query: %s\n",sTemp.c_str());
							MYQ.Delete();
						}
						
						//Jika sudah selesai, baru hapus data groupnya
						sTemp=Glib::ustring::compose("DELETE FROM group_titik_ukur WHERE id_group='%1'",id_group);
						strcpy(MYQ.Text,sTemp.c_str());
						printf(" |-- Query: %s\n",sTemp.c_str());
						MYQ.Delete();
					}
					
					//jika sudah selesai, baru hapus data peralatannya
					sTemp=Glib::ustring::compose("DELETE FROM equipment WHERE id_equipment='%1'",id_equipment);
					strcpy(MYQ.Text,sTemp.c_str());
					printf(" |-- Query: %s\n",sTemp.c_str());
					MYQ.Delete();
				}
				
				//jika sudah selesai, baru hapus data departemen
				sTemp=Glib::ustring::compose("DELETE FROM departemen WHERE id_dep='%1'",id_departemen);
				strcpy(MYQ.Text,sTemp.c_str());
				printf(" |-- Query: %s\n",sTemp.c_str());
				MYQ.Delete();
				}
			
			//jika sudah selesai, baru hapus data perusahaan
			sTemp=Glib::ustring::compose("DELETE FROM perusahaan WHERE id_pers='%1'",id_persh);
			strcpy(MYQ.Text,sTemp.c_str());
			printf(" |-- Query: %s\n",sTemp.c_str());
			MYQ.Delete();
	
			//tutup databasenya
			MYQ.Close();
			break;
		default:
			//Keluar dari fungsi
			printf("default");
			return 0;
	}
	
	UpdateTreeView (4,id_persh);
	return 0;
}

/*Event handler klik mouse List View Data*/
bool main_window::on_tree_data_button_press_event(GdkEventButton *event)
{
	int tree_depth;
	
	printf("[main_window::on_tree_data_button_press_event]\n");
	printf(" |-- id_titik_tampil_sekarang: %d\n",id_titik_tampil_sekarang);
	if(depth_level_sekarang==5)
	{
	   	if(!id_titik_tampil_sekarang)
		{
			return false;
	   	}
	}
	else
		return false;
	
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = tree_data->get_selection();	
	Gtk::TreeModel::iterator iterx;
	Gtk::TreePath *tpath;
	
	if(refSelection)
	{
		iterx = refSelection->get_selected();
		tpath= new Gtk::TreePath(iterx);
		tree_depth=tpath->get_depth();
		delete tpath;
	}
	else
		return false;
	
	if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
	{
		printf("tree_data klik kanan\n");
		data_popup.popup(event->button, event->time);
		
	}
 
  return false;
}

void main_window::on_data_popup_info()
{
	printf("[on_data_popup_info]\n");
	
	char cTemp[512];
	Glib::ustring data_baru;
	float f_data_baru;
	int result2;
	
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = tree_data->get_selection();
	if(refSelection)
	{
		Gtk::TreeModel::iterator iterx = refSelection->get_selected();
		Gtk::TreePath *tpath= new Gtk::TreePath(iterx);
		
		int id = (*iterx)[m_kolom_list.m_col_id];
		int depth=tpath->get_depth();
		Glib::ustring valumenu=(*iterx)[m_kolom_list.m_col_data];
		
		
		printf("-Data: %s\n",valumenu.c_str());
		printf("-ID Data: %d\n",id);
		
		dlg_edit_data* dlg_data=new class dlg_edit_data();
		
		Glib::ustring waktu_data=(*iterx)[m_kolom_list.m_col_waktu];
		
		//dlg_data->isi_form();
		dlg_data->label_waktu->set_text(waktu_data);
		dlg_data->entry_data->set_text(valumenu);
		
		
		int result=dlg_data->run();
		switch(result)
		{
			case(Gtk::RESPONSE_OK):
			printf(" |-- Update data\n");
			
			data_baru=dlg_data->entry_data->get_text();
			//periksa dengan cara konvert ke float dan balikkan lagi
			
			if(data_baru==valumenu)
				break;
			
				
			Gtk::MessageDialog dialog(*this,"Update dengan data yang baru?",
			true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

			//dialog.set_secondary_text("");
			
			result2=dialog.run();
			switch(result2)
			{
			case(Gtk::RESPONSE_OK):
				printf(" |-- Hapus data titik\n");
			
				//konek database
				if(!MYQ.isConnected)
				{
					if(MYQ.init_lengkap()!=1)
					{
						printf(" |--|-- Gagal melakukan inisialisasi database\n");
						Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
						dialog.set_secondary_text("Periksa parameter koneksi database");

						dialog.run();
						return ;
					}
				}
				
					
				//Update datanya
				
				sprintf(cTemp,"UPDATE data_harian SET data_tunggal='%s' WHERE id_data='%d'",data_baru.c_str(),id);
				strcpy(MYQ.Text,cTemp);
				
				MYQ.Update();
				MYQ.Close();
			}
			this->UpdateListView(depth_level_sekarang,id_titik_tampil_sekarang);
			break;
		}
		
		delete dlg_data;
	}
}

void main_window::on_data_popup_hapus()
{
	printf("[on_data_popup_hapus]\n");

	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = tree_data->get_selection();
	if(!refSelection)
	{
		
		return;
	}
	
		Gtk::TreeModel::iterator iterx = refSelection->get_selected();
		Gtk::TreePath *tpath= new Gtk::TreePath(iterx);
		
		int id = (*iterx)[m_kolom_list.m_col_id];
		int depth=tpath->get_depth();
		Glib::ustring valumenu=(*iterx)[m_kolom_list.m_col_data];
		
		printf("-Data: %s\n",valumenu.c_str());
		printf("-ID Data: %d\n",id);
		
		Glib::ustring sTemp;
	int result;
			
	sTemp="Hapus data [" + valumenu + "]?";
	Gtk::MessageDialog dialog(*this,sTemp,
	true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

	//dialog.set_secondary_text("Peringatan: Tindakan ini tidak ");
	
	result=dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			printf(" |-- Hapus data titik\n");
			//konek database
			if(!MYQ.isConnected)
			{
				if(MYQ.init_lengkap()!=1)
				{
					printf(" |--|-- Gagal melakukan inisialisasi database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return ;
				}
			}
			
			//hapus datanya
			
			//data harian
			sTemp=Glib::ustring::compose("DELETE FROM data_harian WHERE id_data='%1'",id);
			strcpy(MYQ.Text,sTemp.c_str());
			
			MYQ.Delete();
			
			//tutup databasenya
			MYQ.Close();
			this->UpdateListView(depth_level_sekarang,id_titik_tampil_sekarang);
			break;
		default:
			//Keluar dari fungsi
			printf("default");
			return;
	}
}

bool main_window::on_main_window_delete_event(GdkEventAny *ev)
{
	printf("[main_window::on_main_window_delete_even]\n");
	
	Glib::ustring sTemp="Tutup Monita?";
	Gtk::MessageDialog dialog(*this,sTemp,
	true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

	dialog.set_secondary_text("Peringatan: Menutup aplikasi juga akan menghentikan\n proses pengambilan data yang sedang berlangsung");
	
	int result=dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			return false;
			break;
		default:
		return true;
	}
	
}

bool main_window::on_tree_status_button_press_event(GdkEventButton *event)
{
	//printf("[main_window::on_tree_status_button_press_event]\n");
	
	if( (event->type == GDK_2BUTTON_PRESS) && (event->button == 1) )
	{
		printf("tree_data double klik\n");
			
		int id_sumber;
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
		Gtk::TreeModel::iterator iter;
		Gtk::TreeModel::Row row;

		refTreeSelection= this->tree_status->get_selection();
		iter = refTreeSelection->get_selected();
		
		if(iter) //If anything is selected
		{
			Glib::ustring uNamaSumber,uKeterangan;
			int iTemp;
			
			row = *iter;
			//Do something with the row.
			uNamaSumber= row[m_status_list.m_col_nama_sumber];
			printf("-Column Name: %s\n",uNamaSumber.c_str());
			
			iTemp=row[m_status_list.m_col_id];
			printf("-ID Sumber: %d\n",iTemp);
			
			uKeterangan="Nama Sumber: " + uNamaSumber 
						+ "\nIP Address : " + row[m_status_list.m_col_alamat_ip];
			
			dlg_koneksi_sumber *dlg_koneksi=new dlg_koneksi_sumber();
			
			
			printf("-MYQ.server:%s\n",MYQ.server);
			memcpy(&(dlg_koneksi->MYQ),(void*)&MYQ,sizeof(MyQuery));
			
			
			dlg_koneksi->label_nama_sumber->set_text(uKeterangan);
			
			dlg_koneksi->id_sumber_data=row[m_status_list.m_col_id];
			if(dlg_koneksi->ReloadList(1))
			{
				dlg_koneksi->run();
			}	
			delete dlg_koneksi;
		}
		else
		{
			Gtk::MessageDialog dialog(*this,"<b>Pilih Sumber Data yang akan dilihat?</b>",
			true /*use markup*/, Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK);


			dialog.run();
			
		}
	}
	return false;
}

void main_window::on_buat_laporan_activate()
{
	printf("[main_window::on_buat_laporan_activate]\n");
	
	//Cek posisi treeview ada dimana
	
	//Jika di posisi group
	//cek dulu id-groupnya
	if(depth_level_sekarang==4)
	{
		dlg_report* dlg_rpt=new class dlg_report();
		
		memcpy(&dlg_rpt->MYQ,(void*)&MYQ,sizeof(MyQuery));
		memcpy(&dlg_rpt->MYQ1,(void*)&MYQ,sizeof(MyQuery));
		dlg_rpt->id_group_tree=id_titik_tampil_sekarang;
		dlg_rpt->isi_form();
		dlg_rpt->run();
		delete dlg_rpt;
	}
}

//switch buffer:
//saat awal, data baru dipasang dari nomer terakhir (30) baru ke depan
//saat sudah berjalan, data paling muda ada di nomer 0, data tertua di nomer 30 ini

void main_window::push_buffer_switch(float data)
{
	float ftemp;
	char ctemp[32];
	
	if(buffer_counter<=BUFFER_DELAY)
	{
		sprintf(ctemp,"Inisialisasi buffer alarm: %d",buffer_counter);
		add_log(ctemp,LOG_INFO,0);
		alarm_switch_buffer[BUFFER_DELAY-buffer_counter]=data;
		buffer_counter++;
	}
	else
	{
		//pindahkan nomer 0 ke nomer 1, artinya
		//pindahkan nomer i ke nomer i+1
		for(int i=(BUFFER_DELAY-1);i>0;i--)
		{
			//ftemp=alarm_switch_buffer[i+1];
			alarm_switch_buffer[i]=alarm_switch_buffer[i-1];
		}
		alarm_switch_buffer[0]=data;
	}
}

int main_window::cek_mail_dir(Glib::ustring direktori)
{
	DIR           *d;
	struct dirent *dir;
	d = opendir("/home/herry/mail-archive/");
	
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
			
			
		}
		closedir(d);
	}
	return(0);
}
