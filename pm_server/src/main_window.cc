// generated 2008/10/17 18:43:52 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to main_window.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "main_window.hh"


#include "common.h"
//#include "serial.h"
//#include "low_mod.h"
#include "mbcrc.c"

#ifdef GUNA_THREAD
#include "fungsi_soket.c"
#endif

extern struct d_pmod pmod;

unsigned char addr_PM710;
unsigned char addr_KTA;
unsigned short jum_balik;
unsigned int konting=0;
unsigned int urutan=0;
unsigned int lanjut;
unsigned int trm;
unsigned int pool_wait;
unsigned int loop_kirim=0;

//int server_counter;

Glib::ustring pm_parameter[33]={
	"KWh", //1
	"KVArh", //2
	"KVAh", //3
	"KW", //4
	"KVA", //5
	"KVAR", //6
	"PF", //7
	"Volt 1", //8
	"Volt 2", //9
	"Arus Rata-rata", //10
	"Frekuensi", //11
	"Arus L1", //12
	"Arus L2", //13
	"Arus L3", //14
	"Arus N", //15
	"Volt L1-L2", //16
	"Volt L2-L3", //17
	"Volt L1-L3", //18
	"Volt L1-N", //19
	"Volt L2-N", //20
	"Volt L3-N", //21
	"KW L1", //22
	"KW L2", //23
	"KW L3", //24
	"KVA L1", //25
	"KVA L2", //26
	"KVA L3", //27
	"KVAR L1", //28
	"KVAR L2", //29
	"KVAR L3", //30
	"PF L1",//31
	"PF L2",//32
	"PF L3" //33
	};
Glib::ustring pm_satuan[33]={
	"KWh", //1
	"KVArh", //2
	"KVAh", //3
	"KW", //4
	"KVA", //5
	"KVAR", //6
	"PF", //7
	"Volt", //8
	"Volt", //9
	"Ampere", //10
	"Hz", //11
	"Ampere", //12
	"Ampere", //13
	"Ampere", //14
	"Ampere", //15
	"Volt", //16
	"Volt", //17
	"Volt", //18
	"Volt", //19
	"Volt", //20
	"Volt", //21
	"KW", //22
	"KW", //23
	"KW", //24
	"KVA", //25
	"KVA", //26
	"KVA", //27
	"KVAR", //28
	"KVAR", //29
	"KVAR", //30
	"PF",//31
	"PF",//32
	"PF" //33
	};
static char status_teks[128];
char ctemp[256];
int t;

long server_counter, loop_counter;
struct f_PM710 asli_PM710[JUMLAH_PM];
//int wait_flag;                    /* TRUE while no signal received */	

char MODEMDEVICE[32] = {"/dev/ttyUSB0"};
int wait_flag_serial;                    /* TRUE while no signal received */

//buat thread server
pthread_t a_thread;
int result;
int no_pm;
bool server_aktif;
void *thread_server(void *arg)
{
	/*MULAINYA OF SERVER ETHERNET*/
	std::string data;
	printf("Buat socket baru\n");
	try
    {
		//Create the socket
		ServerSocket server (5001);
		server_counter=0;

		while ( true )
		{
			ServerSocket new_sock;
			printf("Terima koneksi\n");
			server.accept ( new_sock );
	
	  		try
			{
		  	while (server_aktif)
				{
			  	
				new_sock >> data;
					  	
				printf("\nData masuk: %s\n",data.c_str());
			  	
				if(!strncmp(data.c_str(),"stack_01",8))
					no_pm=1;
				else if(!strncmp(data.c_str(),"stack_02",8))
					no_pm=2;
				else if(!strncmp(data.c_str(),"stack_03",8))
					no_pm=3;
				else if(!strncmp(data.c_str(),"stack_04",8))
					no_pm=4;
				else if(!strncmp(data.c_str(),"stack_05",8))
					no_pm=5;
				//Yang baru yang bawah
				else if(!strncmp(data.c_str(),"sampurasun1",11))
					no_pm=1;
				else if(!strncmp(data.c_str(),"sampurasun2",11))
					no_pm=2;
				else if(!strncmp(data.c_str(),"sampurasun3",11))
					no_pm=3;
				else if(!strncmp(data.c_str(),"sampurasun4",11))
					no_pm=4;
				else if(!strncmp(data.c_str(),"sampurasun5",11))
					no_pm=5;
				else
					no_pm=0;
						
				//sprintf(ctemp,"%d",counter);
				printf("Nomer rekues: %d\n",no_pm);
				
				//DATA ASLI	
				bool data_asli=false;
				if(data_asli)
				{
					memcpy(pm_eth.buf, (char *) &asli_PM710[no_pm], sizeof (asli_PM710[1]));
					kontrol_PM[no_pm].alamat = no_pm;
					pm_eth.alamat = kontrol_PM[no_pm].alamat;
					strcpy(pm_eth.mon, "monita1");
				}
				else
				//DATA DUMMY
				{
					float data_dummy[31];
					//memcpy(pm_eth.buf, (char *) &asli_PM710[no_pm], sizeof (asli_PM710[1]));
					for(int i=0;i<31;i++)
					{
						data_dummy[i]=(float) no_pm*100+i;
					}
					memcpy(pm_eth.buf,(char*) &data_dummy,sizeof(asli_PM710[1]));
					kontrol_PM[no_pm].alamat = no_pm;
					pm_eth.alamat = no_pm;
					strcpy(pm_eth.mon, "monita1");
					
					printf("Dummy data: alamat: %d\n",no_pm);
				}	
					
				//Kirim data
				new_sock.send_buffer((char*)&pm_eth,sizeof(pm_eth));
				printf("\n |-- %d> kirim: %d bytes\n",server_counter, sizeof(pm_eth));
				server_counter++;
				  
				//printf(".");
				if(server_counter%50==0)
					printf("\n%d",server_counter);
				if(server_counter>1100)
				  	server_counter=0;
				}
			}
			catch ( SocketException& e) 
			{
				//printf("ERROR: %s\n",e.description().c_str());
			}
			

		}
	}  
	catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
	
	/*END OF pthread_t a_thread ETHERNET*/
	pthread_exit(NULL);
}

main_window::main_window()
{
	printf("[main_window]\n");
	
	wait_flag_serial=TRUE;
	serial_terbuka=FALSE;
	timer_on=false;
	jum_PM=3;
	server_counter=0;
	loop_counter=0;
	tree_ada_kolom=false;
	
	server_counter=0;
	m_context_id = statusbar1->get_context_id("Statusbar");
	//init font
	Glib::ustring font_desc;
	font_desc="Arial 20";
	
	label_kw->modify_font(Pango::FontDescription(font_desc));
	label_kva->modify_font(Pango::FontDescription(font_desc));
	label_kvar->modify_font(Pango::FontDescription(font_desc));
	
	label_kwh->modify_font(Pango::FontDescription(font_desc));
	label_kvah->modify_font(Pango::FontDescription(font_desc));
	label_kvarh->modify_font(Pango::FontDescription(font_desc));
	
	label_cospi->modify_font(Pango::FontDescription(font_desc));
	label_frek->modify_font(Pango::FontDescription(font_desc));
	
	label_vl1l2->modify_font(Pango::FontDescription(font_desc));
	label_vl2l3->modify_font(Pango::FontDescription(font_desc));
	label_vl1l3->modify_font(Pango::FontDescription(font_desc));
	
	label_voltl1n->modify_font(Pango::FontDescription(font_desc));
	label_voltl2n->modify_font(Pango::FontDescription(font_desc));
	label_voltl3n->modify_font(Pango::FontDescription(font_desc));
	
	label_ampl1->modify_font(Pango::FontDescription(font_desc));
	label_ampl2->modify_font(Pango::FontDescription(font_desc));
	label_ampl3->modify_font(Pango::FontDescription(font_desc));
	label_ampn->modify_font(Pango::FontDescription(font_desc));
	
	label_vll->modify_font(Pango::FontDescription(font_desc));
	label_vln->modify_font(Pango::FontDescription(font_desc));
	label_ampr->modify_font(Pango::FontDescription(font_desc));
	
	id_tampilkan=1;
	
	on_button_connect_clicked ();
}

void main_window::on_button_connect_clicked()
{
	printf("on_button_connect_clicked\n");
	
	//buka port serial dan aktifkan timer
	if(!serial_terbuka)
	{
	//#if 1	
	printf("Mencoba membuka serial port: %s\n",MODEMDEVICE);
	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd <0) {
		/* buat error message */
		//err = gtk_message_dialog_new((GtkWindow *)window1, GTK_DIALOG_MODAL , GTK_MESSAGE_ERROR, \
		//	GTK_BUTTONS_OK, "Open device %s gagal !", MODEMDEVICE); 
		printf("ERROR: Gagal membuka serial port: %s\n",MODEMDEVICE);
		
		//gtk_dialog_run(GTK_DIALOG(err));
		//gtk_widget_destroy(err);
		
		printf("Open dev %s gagal\n", MODEMDEVICE);
		perror(MODEMDEVICE); 
		//exit(-1); 	
	}
	else
	{
		printf("Berhasil membuka serial port [%s]\n",MODEMDEVICE);
		serial_terbuka=true;
		
		printf("set_awal_serial\n");
		set_awal_serial(fd);

		printf("Mulai timer\n");
		//#endif	
		lanjut = TRUE;
		trm = 0;

		//Hidupkan server socket
		//printf("Hidupkan server ethernet\n");
		//server =new ServerSocket(5002);
		//counter=0;
		int parameter_server=0;
		server_aktif=true;
		
		result = pthread_create(&a_thread, NULL, 
								thread_server, (void*)&parameter_server);
		if (result != 0)
		{
			perror(" -> Thread creation failed\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			
			printf("Server diaktifkan\n");
		}
		//t_saat = g_timeout_add(50, (GSourceFunc) saat_kerja, main_window);
		timer_on=true;
		
		t_saat = Glib::signal_timeout().connect(sigc::mem_fun(*this,&main_window::saat_kerja),50 );
		t_tampil= Glib::signal_timeout().connect(sigc::mem_fun(*this,&main_window::update_tampilan),1000 );	
		//t_tampil = g_timeout_add(300, (GSourceFunc) tampil, main_window);
		
		//ganti label button
		button_connect->set_label("STOP");
		
		}
	}
	else
	{
		//tutup serial_port
		printf("Matikan timer\n");
		timer_on=false;
		server_aktif=false;
		printf("Tutup serial port\n");
		
		serial_terbuka=false;
		button_connect->set_label("MULAI");
	}
}

void main_window::on_button_1_clicked()
{
	printf("on_button_1_clicked\n");
	
	id_tampilkan=1;
	update_tampilan();
	//button_2->set_active(false);	
}

void main_window::on_button_2_clicked()
{
	printf("on_button_2_clicked\n");
	id_tampilkan=2;
	update_tampilan();
	//button_1->set_active(false);
}

void main_window::on_button_3_clicked()
{
	printf("on_button_3_clicked\n");
	id_tampilkan=3;
	update_tampilan();
}

void main_window::on_button_4_clicked()
{
	printf("on_button_4_clicked\n");
	id_tampilkan=4;
	update_tampilan();
}

void main_window::on_button_5_clicked()
{
	printf("on_button_5_clicked\n");
	id_tampilkan=5;
	update_tampilan();
}

bool main_window::saat_kerja()//GtkWidget *wg)
{
	unsigned char *pc;
	static char tek[128];
	static char tek2[256];
	
	int i;
	int res;
	
	float *pFloat;
	float *pFloat2;
	
	//printf("[saat_kerja]wf: %d\n",wait_flag_serial);
	
	if (lanjut == TRUE)
	{
	#ifdef TIPE_PM710
		/* berikut ini request data 
		 * untuk power meter tipe 710 */

		if (urutan == 1)
		{
		   jum_balik = get_PM710(reg_satuan, 4);
		}
		else if (urutan == 2)
		{
		   jum_balik = get_PM710(reg_kva, 7);  //kVA, kVAR, PF, volt L-L, L-N, A, Hz
		}
		else if (urutan == 3)
		{
		   jum_balik = get_PM710(reg_ampA, 4); //ampA, B, C & N
		}
		else if (urutan == 4)
		{
		   jum_balik = get_PM710(reg_voltA_C, 6); //voltA_B, B_C, A_C, A_N, B_N & C_N
		}
		else if (urutan == 5)
		{
		   //jum_balik = get_PM710(reg_kva, 1);
		   jum_balik = get_PM710(reg_kwh, 6);  //kWh, kVAh, & kVArh
		   
		}
		else if (urutan == 6)
		{
			jum_balik = get_KTA(reg_KTA, 9);
		}
		else if (urutan == 7)
		{
			jum_balik = get_KTA(reg_satuan_KTA, 6);
		}
#endif

#ifdef TIPE_PM810
		if (urutan == 1)
   	    {
   	    	jum_balik = get_PM710(reg_satuan, 6);
   	          //urut_PM710 = 34;
   	    }
   		else if (urutan == 2)
   		{
     		jum_balik = get_PM710(meter_current, 6);  //Current A, B, C, N, - , & ave
   		}
   		else if (urutan == 3)
   		{
     	    jum_balik = get_PM710(meter_voltage, 9);  //Voltage A-B, B-C, C-A, L-L, A-N, B-N, C-N , L-N
   		}
   		else if (urutan == 4)
   		{
     	    jum_balik = get_PM710(meter_power, 12); // kwA, kwB, kwC, kW, kvarA, kvarB, kvarC, kvar, kvaA, kvaB, kvaC, kva
   		}
   		else if (urutan == 5)
   		{
     	    jum_balik = get_PM710(meter_faktor, 4);   //pfA, pfB, pfC, pf
   		}
   		else if (urutan == 6)
   		{
     	    jum_balik = get_PM710(reg_frek, 1); //Hz
     	    //jum_balik = get_PM710(meter_energi2, 4);
   		}
   		else if (urutan == 7)
   		{
   		   jum_balik = get_PM710(meter_energi2, 8);
   		}
     	 else if (urutan == 8)
   		{
   		   jum_balik = get_PM710(meter_energi_vah, 8);
   		}

#endif
		
     	// kirim lewat serial	
     	write(fd, (unsigned char *) &pmod, sizeof (pmod));
		
		pc = (unsigned char *) &pmod;
    	sprintf(tek2, "Send ke %2d [%2d] :", urutan, jum_balik);
		for (i=0; i<sizeof (pmod); i++)
    	{
    		sprintf(tek, "%2X ", (unsigned char) *pc++);
			strcat(tek2, tek);	
    	}
		//gtk_label_set_text((GtkLabel *) snd, tek2);
		//printf(tek2);
		//printf("\n");
		lanjut = FALSE;
	}
	
	//printf("pool_wait: %d, urutan: %d, addr_PM710:%d, jum_PM=%d, wait_flag_serial:%d\n",
	//	   	pool_wait, urutan,addr_PM710,jum_PM,wait_flag_serial);
	pool_wait++; 
	if (pool_wait > 5)
	{
		lanjut = TRUE;
		trm = 0;
		pool_wait = 0;
		
		sprintf(tek, "Timeout dari alamat = %d !", addr_PM710);
		//gtk_label_set_text((GtkLabel *) tout, tek);
			
		urutan++;
        //if (urutan > MAKS_URUT)
		if (urutan > 2) // supaya tidak terlalu lama pooling yang timeout 
		{
			urutan = 1;
			addr_PM710++;
				
			if (addr_PM710 > jum_PM)
			{
				addr_PM710 = 1;	
			}	
		}	
	}
//#if 1	
	/* 
	 * prosedur ini harusnya dipanggil saat timer
	 * yang akan datang, karena wait_flag sudah diset false
	 * oleh bagian atas (pengirim) 
	 */
	
	if (wait_flag_serial == FALSE)
	{
		//printf("wait_flag = FALSE\n");
		
		wait_flag_serial = TRUE;	
		
		res = read(fd, (char *) &buf[trm],255);
		
		//printf("Terima: %d\n",res);
		trm = trm + res;
		if (trm == jum_balik)
		{
			sprintf(tek2, "Recv ke %2d [%2d]:", urutan, pool_wait);
			for (i=0; i<jum_balik; i++)
			{
				sprintf(tek,"%2X ", (unsigned char) buf[i]);
				strcat(tek2, tek);
			}
			//printf(tek2);
			//printf("\n");
			//gtk_label_set_text((GtkLabel *) rcv, tek2);
			//gtk_label_set_text((GtkLabel *) tout, "");
			
			// ingat bahwa urutan menjadi masalah ketika = 0
			#ifdef TIPE_PM710
			taruh_data(addr_PM710, (urutan-1));
			#endif
			
			#ifdef TIPE_PM810
			taruh_data_PM810(addr_PM710, urutan);
			#endif
			
			lanjut = TRUE;
			trm = 0;
			pool_wait = 0;
			
			urutan++;
        	if (urutan > MAKS_URUT) 
			{
				urutan = 1;
				addr_PM710++;
				
				if (addr_PM710 > jum_PM)
				{
					addr_PM710 = 1;	
				}
			}	
		}
	}
	else
		//printf("wait_flag = TRUE\n");
	
//#endif
	
	//Restart server 
	//sprintf(tek2, "Recv ke %2d [%2d]:", urutan, pool_wait);
	

	//server_counter++;
	/*
	if(server_counter==1000)
	{
		server_aktif=false;
	}
	else if(server_counter>1005)
	{
		server_aktif=true;
		printf("server_counter mencapai %d. Reset ke 0\n",server_counter);
		server_counter=0;
	}
	*/
	loop_counter++;
	//if(loop_counter>1000)
	//{
		
	//	loop_counter=0;
	//}
	
	if(timer_on==false)
	{
		printf("Timer dimatikan\n");
		return false;
	}
}

/*
   query data dari register PM710 & juga dimasukkan ukuran data yang akan diquery
   di query secara periodik untuk mendapatkan data yang diinginkan

   return adalah jumlah byte yang seharusnya diterima
*/


unsigned short main_window::get_PM710(unsigned short reg, unsigned char uk)
{
   unsigned short dcrc;
   int i;

   reg_flag = reg;

   if (reg != reg_kwh)
   reg = reg - 1;

   pmod.addr = (unsigned char)   addr_PM710;
   pmod.command = (unsigned char) command_baca;
   pmod.reg_hi = (unsigned char) ((reg & 0xFF00) >> 8);
   pmod.reg_lo = (unsigned char) (reg & 0x00FF);
   pmod.jum_hi = (unsigned char) ((uk & 0xFF00) >> 8);
   pmod.jum_lo = (unsigned char) (uk & 0x00FF);;

   dcrc = usMBCRC16((unsigned char *) &pmod, sizeof (pmod)-2);
   pmod.crc_lo = (unsigned char) ((dcrc & 0xFF00) >> 8);
   pmod.crc_hi = (unsigned char) (dcrc & 0x00FF);;

   	return (1 + 1 + 1 + (uk * 2) + 2);
}

unsigned short main_window::cek_PM()
{
	unsigned short dcrc;
   	unsigned char *p;
   	int i;

	//reg_flag = reg;
	printf("cek_pm\n");
	pmod.addr = (unsigned char)   addr_PM710;
	pmod.command = (unsigned char) 0x03;		// command untuk cek ID
	pmod.reg_hi = (unsigned char) 0x40;
	pmod.reg_lo = (unsigned char) 0x00;
	pmod.jum_hi = (unsigned char) ((5 & 0xFF00) >> 8);
	pmod.jum_lo = (unsigned char) (5 & 0x00FF);;

	dcrc = usMBCRC16((unsigned char *) &pmod, sizeof (pmod)-2);
	pmod.crc_lo = (unsigned char) ((dcrc & 0xFF00) >> 8);
	pmod.crc_hi = (unsigned char) (dcrc & 0x00FF);;

	return 7;	// respon harusnya 7 byte
	//return (1 + 1 + 1 + (uk * 2) + 2);		
}

#ifdef TIPE_PM710
//void taruh_data(int no_slave, int urt, char *buf)
void taruh_data(int no_slave, int urt)
{
	short satuan_t;
	int i;
	
	if (urt == 0)     //satuan2
	{
		// amper
		satuan_t = buf[3];
		satuan_t = (satuan_t << 8) | buf[4];

		if (satuan_t == (short) -4) satuan_amp = 0.0001;
		else if (satuan_t == -3) satuan_amp = 0.001;
		else if (satuan_t == -2) satuan_amp = 0.01;
		else if (satuan_t == -1) satuan_amp = 0.1;
		else if (satuan_t == 0) satuan_amp = 1.0;
		else if (satuan_t == 1) satuan_amp = 10.0;
		else if (satuan_t == 2) satuan_amp = 100.0;
		else if (satuan_t == 3) satuan_amp = 1000.0;
		else if (satuan_t == 4) satuan_amp = 10000.0;
		
		//move_ke(80, 12);
        //printw("sat amp  : %d : %X", satuan_t, (short) satuan_t);

		//volt
		satuan_t = buf[5];
		satuan_t = (satuan_t << 8) | buf[6];

		if (satuan_t == -4) satuan_volt = 0.0001;
		else if (satuan_t == -3) satuan_volt = 0.001;
		else if (satuan_t == -2) satuan_volt = 0.01;
		else if (satuan_t == -1) satuan_volt = 0.1;
		else if (satuan_t == 0) satuan_volt = 1.0;
		else if (satuan_t == 1) satuan_volt = 10.0;
		else if (satuan_t == 2) satuan_volt = 100.0;
		else if (satuan_t == 3) satuan_volt = 1000.0;
		else if (satuan_t == 4) satuan_volt = 10000.0;

		//power
		satuan_t = buf[7];
		satuan_t = (satuan_t << 8) | buf[8];

		if (satuan_t == -4) satuan_kw = 0.0001;
		else if (satuan_t == -3) satuan_kw = 0.001;
		else if (satuan_t == -2) satuan_kw = 0.01;
		else if (satuan_t == -1) satuan_kw = 0.1;
		else if (satuan_t == 0) satuan_kw = 1.0;
		else if (satuan_t == 1) satuan_kw = 10.0;
		else if (satuan_t == 2) satuan_kw = 100.0;
		else if (satuan_t == 3) satuan_kw = 1000.0;
		else if (satuan_t == 4) satuan_kw = 10000.0;

		//energy
		satuan_t = buf[9];
		satuan_t = (satuan_t << 8) | buf[10];

		if (satuan_t == -4) satuan_kwh = 0.0001;
		else if (satuan_t == -3) satuan_kwh = 0.001;
		else if (satuan_t == -2) satuan_kwh = 0.01;
		else if (satuan_t == -1) satuan_kwh = 0.1;
		else if (satuan_t == 0) satuan_kwh = 1.0;
		else if (satuan_t == 1) satuan_kwh = 10.0;
		else if (satuan_t == 2) satuan_kwh = 100.0;
		else if (satuan_t == 3) satuan_kwh = 1000.0;
		else if (satuan_t == 4) satuan_kwh = 10000.0;

	}
	else if (urt == 1) // kva, kvar, PF, volt1, volt2, amper
	{
		data_PM710[no_slave].kva = buf[3];
		data_PM710[no_slave].kva = (data_PM710[no_slave].kva << 8) | buf[4];
		asli_PM710[no_slave].kva = data_PM710[no_slave].kva * satuan_kw;

		data_PM710[no_slave].kvar = buf[5];
		data_PM710[no_slave].kvar = (data_PM710[no_slave].kvar << 8) | buf[6];
		asli_PM710[no_slave].kvar = data_PM710[no_slave].kvar * satuan_kw;

		data_PM710[no_slave].pf = buf[7];
		data_PM710[no_slave].pf = (data_PM710[no_slave].pf << 8) | buf[8];
		asli_PM710[no_slave].pf = data_PM710[no_slave].pf * 0.0001;

		data_PM710[no_slave].volt1 = buf[9];
		data_PM710[no_slave].volt1 = (data_PM710[no_slave].volt1 << 8) | buf[10];
		if (data_PM710[no_slave].volt1 == 32768)
			asli_PM710[no_slave].volt1 = 0;
		else
			asli_PM710[no_slave].volt1 = data_PM710[no_slave].volt1 * satuan_volt;
		
		//move_ke(80, 20);
        //printw("9=%X, 10 = %X, jadi = %d", buf[9], (unsigned char) buf[10], data_PM710[no_slave].volt1);

		data_PM710[no_slave].volt2 = buf[11];
		data_PM710[no_slave].volt2 = (data_PM710[no_slave].volt2 << 8) | buf[12];
		if (data_PM710[no_slave].volt2 == 32768)
			asli_PM710[no_slave].volt2 = 0;
		else
			asli_PM710[no_slave].volt2 = data_PM710[no_slave].volt2 * satuan_volt;

		data_PM710[no_slave].amp = buf[13];
		data_PM710[no_slave].amp = (data_PM710[no_slave].amp << 8) | buf[14];
		if (data_PM710[no_slave].amp  == 32768)
			asli_PM710[no_slave].amp = 0;
		else
			asli_PM710[no_slave].amp = data_PM710[no_slave].amp * satuan_amp;

		data_PM710[no_slave].frek = buf[15];
		data_PM710[no_slave].frek = (data_PM710[no_slave].frek << 8) | buf[16];
		if (data_PM710[no_slave].frek == 32768)
			asli_PM710[no_slave].frek = 0;
		else
			asli_PM710[no_slave].frek = data_PM710[no_slave].frek * 0.01;

	}
	else if (urt == 2)
	{
		// ampA, B, C & N
		data_PM710[no_slave].ampA = buf[3];
		data_PM710[no_slave].ampA = (data_PM710[no_slave].ampA << 8) | buf[4];
		if (data_PM710[no_slave].ampA == 32768)
			asli_PM710[no_slave].ampA = 0;
		else
			asli_PM710[no_slave].ampA = data_PM710[no_slave].ampA * satuan_amp;

		data_PM710[no_slave].ampB = buf[5];
		data_PM710[no_slave].ampB = (data_PM710[no_slave].ampB << 8) | buf[6];
		if (data_PM710[no_slave].ampB == 32768)
			asli_PM710[no_slave].ampB = 0;
		else
			asli_PM710[no_slave].ampB = data_PM710[no_slave].ampB * satuan_amp;

		data_PM710[no_slave].ampC = buf[7];
		data_PM710[no_slave].ampC = (data_PM710[no_slave].ampC << 8) | buf[8];
		if (data_PM710[no_slave].ampC == 32768)
			asli_PM710[no_slave].ampC = 0;
		else
			asli_PM710[no_slave].ampC = data_PM710[no_slave].ampC * satuan_amp;

		data_PM710[no_slave].ampN = buf[9];
		data_PM710[no_slave].ampN = (data_PM710[no_slave].ampN << 8) | buf[10];
		if (data_PM710[no_slave].ampN == 32768)
			asli_PM710[no_slave].ampN = 0;
		else
			asli_PM710[no_slave].ampN = data_PM710[no_slave].ampN * satuan_amp;

	}
	else if (urt == 3)
	{
		//voltA_B, B_C, A_C, A_N, B_N & C_N
		data_PM710[no_slave].voltA_B = buf[3];
		data_PM710[no_slave].voltA_B = (data_PM710[no_slave].voltA_B << 8) | buf[4];
		if (data_PM710[no_slave].voltA_B == 32768)
			asli_PM710[no_slave].voltA_B = 0;
		else
			asli_PM710[no_slave].voltA_B = data_PM710[no_slave].voltA_B * satuan_volt;

		data_PM710[no_slave].voltB_C = buf[5];
		data_PM710[no_slave].voltB_C = (data_PM710[no_slave].voltB_C << 8) | buf[6];
		if (data_PM710[no_slave].voltB_C == 32768)
			asli_PM710[no_slave].voltB_C = 0;
		else
			asli_PM710[no_slave].voltB_C = data_PM710[no_slave].voltB_C * satuan_volt;

		data_PM710[no_slave].voltA_C = buf[7];
		data_PM710[no_slave].voltA_C = (data_PM710[no_slave].voltA_C << 8) | buf[8];
		if (data_PM710[no_slave].voltA_C == 32768)
			asli_PM710[no_slave].voltA_C = 0;
		else
			asli_PM710[no_slave].voltA_C = data_PM710[no_slave].voltA_C * satuan_volt;

		data_PM710[no_slave].voltA_N = buf[9];
		data_PM710[no_slave].voltA_N = (data_PM710[no_slave].voltA_N << 8) | buf[10];
		if (data_PM710[no_slave].voltA_N == 32768)
			asli_PM710[no_slave].voltA_N = 0;
		else
			asli_PM710[no_slave].voltA_N = data_PM710[no_slave].voltA_N * satuan_volt;

		data_PM710[no_slave].voltB_N = buf[11];
		data_PM710[no_slave].voltB_N = (data_PM710[no_slave].voltB_N << 8) | buf[12];
		if (data_PM710[no_slave].voltB_N == 32768)
			asli_PM710[no_slave].voltB_N = 0;
		else
			asli_PM710[no_slave].voltB_N = data_PM710[no_slave].voltB_N * satuan_volt;

		data_PM710[no_slave].voltC_N = buf[9];
		data_PM710[no_slave].voltC_N = (data_PM710[no_slave].voltC_N << 8) | buf[10];
		if (data_PM710[no_slave].voltC_N == 32768)
			asli_PM710[no_slave].voltC_N = 0;
		else
			asli_PM710[no_slave].voltC_N = data_PM710[no_slave].voltC_N * satuan_volt;

	}
	else if (urt == 4)
	{
		//memcpy((char *) &asli_PM710[no_slave].frek, &buf[2], 4);
		
		// kWh
		data_PM710[no_slave].kwh = buf[5];
		data_PM710[no_slave].kwh = (data_PM710[no_slave].kwh << 8) | buf[6];
		data_PM710[no_slave].kwh = (data_PM710[no_slave].kwh << 8) | buf[3];
		data_PM710[no_slave].kwh = (data_PM710[no_slave].kwh << 8) | buf[4];
		asli_PM710[no_slave].kwh = data_PM710[no_slave].kwh * satuan_kwh;

		// kVAh
		data_PM710[no_slave].kvah = buf[9];
		data_PM710[no_slave].kvah  = (data_PM710[no_slave].kvah  << 8) | buf[10];
		data_PM710[no_slave].kvah  = (data_PM710[no_slave].kvah  << 8) | buf[7];
		data_PM710[no_slave].kvah  = (data_PM710[no_slave].kvah  << 8) | buf[8];
		asli_PM710[no_slave].kvah = data_PM710[no_slave].kvah * satuan_kwh;

		// kVArh
		data_PM710[no_slave].kvarh = buf[11];
		data_PM710[no_slave].kvarh  = (data_PM710[no_slave].kvarh  << 8) | buf[12];
		asli_PM710[no_slave].kvarh = data_PM710[no_slave].kvarh * satuan_kwh;

		// kW, ini harusnya salah posisi
		data_PM710[no_slave].kw = buf[13];
		data_PM710[no_slave].kw  = (data_PM710[no_slave].kw  << 8) | buf[14];
		if (data_PM710[no_slave].kw  == 32768)
			asli_PM710[no_slave].kw = 0;
		else
			asli_PM710[no_slave].kw = data_PM710[no_slave].kw * satuan_kw;
	
	}
	else if (urt == 5)
	{
		// data angin
		wind_speed = buf[3];
		wind_speed = (wind_speed << 8) | buf[4];
		
		wind_dir = buf[5];
		wind_dir = (wind_dir << 8) | buf[6];	
		
		//asli_PM710[no_slave].ampB = wind_speed;
		//sli_PM710[no_slave].ampC = wind_dir;
	}
	else if (urt == 6)
	{
		// satuan angin
		wind_satuan = buf[3];
		wind_satuan = (wind_satuan << 8) | buf[4];
		
		// retransmision value
		wind_speed_tr = buf[9];
		wind_speed_tr = (wind_speed_tr << 8) | buf[10];
		
		wind_dir_tr = buf[11];
		wind_dir_tr = (wind_dir_tr << 8) | buf[12];
		
		//asli_PM710[no_slave].voltB_C = wind_satuan;
	}
	
}

// 22 Jan 09
unsigned short main_window::get_KTA(unsigned short reg, unsigned char uk)
{
   unsigned short dcrc;
   int i;

   reg_flag = reg;

   if (reg != reg_kwh)
   reg = reg - 1;

   pmod.addr = (unsigned char)   addr_KTA;
   pmod.command = (unsigned char) command_baca;
   pmod.reg_hi = (unsigned char) ((reg & 0xFF00) >> 8);
   pmod.reg_lo = (unsigned char) (reg & 0x00FF);
   pmod.jum_hi = (unsigned char) ((uk & 0xFF00) >> 8);
   pmod.jum_lo = (unsigned char) (uk & 0x00FF);;

   dcrc = usMBCRC16((unsigned char *) &pmod, sizeof (pmod)-2);
   pmod.crc_lo = (unsigned char) ((dcrc & 0xFF00) >> 8);
   pmod.crc_hi = (unsigned char) (dcrc & 0x00FF);;

   	return (1 + 1 + 1 + (uk * 2) + 2);
}
#endif

/* 
 * 24 Februari 2009
 * taruh data untuk PM810
 */


void main_window::taruh_data_PM810(int pm_dibaca, int urt)
{
 	short satuan_t;
	int i;
	unsigned int temp;
   	unsigned int temp2;
   
	printf("Taruh data pm810 [%d] urut[%d]\n",pm_dibaca,urt);
	if (urt == 1)
	{
		// amper
		satuan_t = buf[3];
		satuan_t = (satuan_t << 8) + buf[4];

		if (satuan_t == -4) satuan_amp[pm_dibaca] = 0.0001;
		else if (satuan_t == -3) satuan_amp[pm_dibaca] = 0.001;
		else if (satuan_t == -2) satuan_amp[pm_dibaca] = 0.01;
		else if (satuan_t == -1) satuan_amp[pm_dibaca] = 0.1;
		else if (satuan_t == 0) satuan_amp[pm_dibaca] = 1.0;
		else if (satuan_t == 1) satuan_amp[pm_dibaca] = 10.0;
		else if (satuan_t == 2) satuan_amp[pm_dibaca] = 100.0;
		else if (satuan_t == 3) satuan_amp[pm_dibaca] = 1000.0;
		else if (satuan_t == 4) satuan_amp[pm_dibaca] = 10000.0;

		//ampere2 (L-N)
		satuan_t = buf[5];
		satuan_t = (satuan_t << 8) + buf[6];

		if (satuan_t == -4) satuan_amp2[pm_dibaca] = 0.0001;
		else if (satuan_t == -3) satuan_amp2[pm_dibaca] = 0.001;
		else if (satuan_t == -2) satuan_amp2[pm_dibaca] = 0.01;
		else if (satuan_t == -1) satuan_amp2[pm_dibaca] = 0.1;
		else if (satuan_t == 0) satuan_amp2[pm_dibaca] = 1.0;
		else if (satuan_t == 1) satuan_amp2[pm_dibaca] = 10.0;
		else if (satuan_t == 2) satuan_amp2[pm_dibaca] = 100.0;
		else if (satuan_t == 3) satuan_amp2[pm_dibaca] = 1000.0;
		else if (satuan_t == 4) satuan_amp2[pm_dibaca] = 10000.0;
		// buf[7] & [8] kosong

		// volt (L - L)
		satuan_t = buf[9];
		satuan_t = (satuan_t << 8) + buf[10];

		if (satuan_t == -4) satuan_volt[pm_dibaca] = 0.0001;
		else if (satuan_t == -3) satuan_volt[pm_dibaca] = 0.001;
		else if (satuan_t == -2) satuan_volt[pm_dibaca] = 0.01;
		else if (satuan_t == -1) satuan_volt[pm_dibaca] = 0.1;
		else if (satuan_t == 0) satuan_volt[pm_dibaca] = 1.0;
		else if (satuan_t == 1) satuan_volt[pm_dibaca] = 10.0;
		else if (satuan_t == 2) satuan_volt[pm_dibaca] = 100.0;
		else if (satuan_t == 3) satuan_volt[pm_dibaca] = 1000.0;
		else if (satuan_t == 4) satuan_volt[pm_dibaca] = 10000.0;

		// volt2 (L - N)
		satuan_t = buf[11];
		satuan_t = (satuan_t << 8) + buf[12];

		if (satuan_t == -4) satuan_volt2[pm_dibaca] = 0.0001;
		else if (satuan_t == -3) satuan_volt2[pm_dibaca] = 0.001;
		else if (satuan_t == -2) satuan_volt2[pm_dibaca] = 0.01;
		else if (satuan_t == -1) satuan_volt2[pm_dibaca] = 0.1;
		else if (satuan_t == 0) satuan_volt2[pm_dibaca] = 1.0;
		else if (satuan_t == 1) satuan_volt2[pm_dibaca] = 10.0;
		else if (satuan_t == 2) satuan_volt2[pm_dibaca] = 100.0;
		else if (satuan_t == 3) satuan_volt2[pm_dibaca] = 1000.0;
		else if (satuan_t == 4) satuan_volt2[pm_dibaca] = 10000.0;

		//power
		satuan_t = buf[13];
		satuan_t = (satuan_t << 8) + buf[14];

		if (satuan_t == -4) satuan_kw[pm_dibaca] = 0.0001;
		else if (satuan_t == -3) satuan_kw[pm_dibaca] = 0.001;
		else if (satuan_t == -2) satuan_kw[pm_dibaca] = 0.01;
		else if (satuan_t == -1) satuan_kw[pm_dibaca] = 0.1;
		else if (satuan_t == 0) satuan_kw[pm_dibaca] = 1.0;
		else if (satuan_t == 1) satuan_kw[pm_dibaca] = 10.0;
		else if (satuan_t == 2) satuan_kw[pm_dibaca] = 100.0;
		else if (satuan_t == 3) satuan_kw[pm_dibaca] = 1000.0;
		else if (satuan_t == 4) satuan_kw[pm_dibaca] = 10000.0;

		//energy
		/*
		satuan_t = buf[9];
		satuan_t = (satuan_t << 8) + buf[10];

		if (satuan_t == -4) satuan_kwh = 0.0001;
		else if (satuan_t == -3) satuan_kwh = 0.001;
		else if (satuan_t == -2) satuan_kwh = 0.01;
		else if (satuan_t == -1) satuan_kwh = 0.1;
		else if (satuan_t == 0) satuan_kwh = 1.0;
		else if (satuan_t == 1) satuan_kwh = 10.0;
		else if (satuan_t == 2) satuan_kwh = 100.0;
		else if (satuan_t == 3) satuan_kwh = 1000.0;
		else if (satuan_t == 4) satuan_kwh = 10000.0;
		*/
		satuan_kwh[pm_dibaca] = 10;	
	}	
	else if (urt == 2)
	{
		// current_metering
		data_PM710[pm_dibaca].ampA = buf[3];
		data_PM710[pm_dibaca].ampA = (data_PM710[pm_dibaca].ampA << 8) + buf[4];

		asli_PM710[pm_dibaca].ampA = data_PM710[pm_dibaca].ampA * satuan_amp[pm_dibaca];

		#ifndef MOD_SERVER
		f = data_PM710[pm_dibaca].ampA * 10;
		//Label45->Caption = FloatToStrF(f, ffGeneral, 8, 2);
		#endif

		// ampere B
		data_PM710[pm_dibaca].ampB = buf[5];
		data_PM710[pm_dibaca].ampB  = (data_PM710[pm_dibaca].ampB  << 8) + buf[6];
		//asli_PM710[pm_dibaca].ampB = data_PM710[pm_dibaca].ampB * satuan_amp[pm_dibaca];
		if (data_PM710[pm_dibaca].ampB == 32768)
			asli_PM710[pm_dibaca].ampB = 0;
		else
			asli_PM710[pm_dibaca].ampB = data_PM710[pm_dibaca].ampB * satuan_amp[pm_dibaca];


		#ifndef MOD_SERVER
		f = data_PM710[pm_dibaca].ampB  * 10;
		//Label46->Caption = FloatToStrF(f, ffGeneral, 8, 2);
		#endif

		// ampere C
		data_PM710[pm_dibaca].ampC = buf[7];
		data_PM710[pm_dibaca].ampC = (data_PM710[pm_dibaca].ampC << 8) + buf[8];
		//asli_PM710[pm_dibaca].ampC = data_PM710[pm_dibaca].ampC * satuan_amp[pm_dibaca];
		if (data_PM710[pm_dibaca].ampC == 32768)
			asli_PM710[pm_dibaca].ampC = 0;
		else
			asli_PM710[pm_dibaca].ampC = data_PM710[pm_dibaca].ampC * satuan_amp[pm_dibaca];

		#ifndef MOD_SERVER
		f = data_PM710[pm_dibaca].ampC  * 10;
		//Label47->Caption = FloatToStrF(f, ffGeneral, 8, 2);
		#endif

		// ampere N
		data_PM710[pm_dibaca].ampN = buf[9];
		data_PM710[pm_dibaca].ampN = (data_PM710[pm_dibaca].ampN << 8) + buf[10];
		//asli_PM710[pm_dibaca].ampN = data_PM710[pm_dibaca].ampN * satuan_amp[pm_dibaca];
		if (data_PM710[pm_dibaca].ampN == 32768)
			asli_PM710[pm_dibaca].ampN = 0;
		else
			asli_PM710[pm_dibaca].ampN = data_PM710[pm_dibaca].ampN * satuan_amp[pm_dibaca];
		#ifndef MOD_SERVER
		f = data_PM710[pm_dibaca].ampN  * 10;
		//Label48->Caption = FloatToStrF(f, ffGeneral, 8, 2);
		#endif

		// ampere average
		data_PM710[pm_dibaca].amp = buf[13];
		data_PM710[pm_dibaca].amp = (data_PM710[pm_dibaca].amp << 8) + buf[14];
		asli_PM710[pm_dibaca].amp = data_PM710[pm_dibaca].amp * satuan_amp[pm_dibaca];

		#ifndef MOD_SERVER
		f = data_PM710[pm_dibaca].amp  * 10;
		//Label21->Caption = FloatToStrF(f, ffGeneral, 8, 2);
		#endif

	 }
	 else if (urt == 3)
	 {
		//voltA_B, B_C, A_C, A_N, B_N & C_N
		data_PM710[pm_dibaca].voltA_B = buf[3];
		data_PM710[pm_dibaca].voltA_B = (data_PM710[pm_dibaca].voltA_B << 8) + buf[4];
		//asli_PM710[pm_dibaca].voltA_B = data_PM710[pm_dibaca].voltA_B * satuan_volt[pm_dibaca];
		if (data_PM710[pm_dibaca].voltA_B == 32768)
			asli_PM710[pm_dibaca].voltA_B = 0;
		else
			asli_PM710[pm_dibaca].voltA_B = data_PM710[pm_dibaca].voltA_B * satuan_volt[pm_dibaca];


		data_PM710[pm_dibaca].voltB_C = buf[5];
		data_PM710[pm_dibaca].voltB_C = (data_PM710[pm_dibaca].voltB_C << 8) + buf[6];
		//asli_PM710[pm_dibaca].voltB_C = data_PM710[pm_dibaca].voltB_C * satuan_volt[pm_dibaca];
		if (data_PM710[pm_dibaca].voltB_C == 32768)
			asli_PM710[pm_dibaca].voltB_C = 0;
		else
			asli_PM710[pm_dibaca].voltB_C = data_PM710[pm_dibaca].voltB_C * satuan_volt[pm_dibaca];

		data_PM710[pm_dibaca].voltA_C = buf[7];
		data_PM710[pm_dibaca].voltA_C = (data_PM710[pm_dibaca].voltA_C << 8) + buf[8];
		//asli_PM710[pm_dibaca].voltA_C = data_PM710[pm_dibaca].voltA_C * satuan_volt[pm_dibaca];
		if (data_PM710[pm_dibaca].voltA_C == 32768)
			asli_PM710[pm_dibaca].voltA_C = 0;
		else
			asli_PM710[pm_dibaca].voltA_C = data_PM710[pm_dibaca].voltA_C * satuan_volt[pm_dibaca];

		// L-L average
		data_PM710[pm_dibaca].volt1 = buf[9];
		data_PM710[pm_dibaca].volt1 = (data_PM710[pm_dibaca].volt1 << 8) + buf[10];
		//asli_PM710[pm_dibaca].volt1 = data_PM710[pm_dibaca].volt1 * satuan_volt[pm_dibaca];
		if (data_PM710[pm_dibaca].volt1 == 32768)
			asli_PM710[pm_dibaca].volt1 = 0;
		else
			asli_PM710[pm_dibaca].volt1 = data_PM710[pm_dibaca].volt1 * satuan_volt[pm_dibaca];

		data_PM710[pm_dibaca].voltA_N = buf[11];
		data_PM710[pm_dibaca].voltA_N = (data_PM710[pm_dibaca].voltA_N << 8) + buf[12];
		//asli_PM710[pm_dibaca].voltA_N = data_PM710[pm_dibaca].voltA_N * satuan_volt[pm_dibaca];
		if (data_PM710[pm_dibaca].voltA_N == 32768)
			asli_PM710[pm_dibaca].voltA_N = 0;
		else
			asli_PM710[pm_dibaca].voltA_N = data_PM710[pm_dibaca].voltA_N * satuan_volt[pm_dibaca];


		data_PM710[pm_dibaca].voltB_N = buf[13];
		data_PM710[pm_dibaca].voltB_N = (data_PM710[pm_dibaca].voltB_N << 8) + buf[14];
		//asli_PM710[pm_dibaca].voltB_N = data_PM710[pm_dibaca].voltB_N * satuan_volt[pm_dibaca];
		if (data_PM710[pm_dibaca].voltB_N == 32768)
			asli_PM710[pm_dibaca].voltB_N = 0;
		else
			asli_PM710[pm_dibaca].voltB_N = data_PM710[pm_dibaca].voltB_N * satuan_volt[pm_dibaca];


		data_PM710[pm_dibaca].voltC_N = buf[15];
		data_PM710[pm_dibaca].voltC_N = (data_PM710[pm_dibaca].voltC_N << 8) + buf[16];
		//asli_PM710[pm_dibaca].voltC_N = data_PM710[pm_dibaca].voltC_N * satuan_volt[pm_dibaca];
		if (data_PM710[pm_dibaca].voltC_N == 32768)
			asli_PM710[pm_dibaca].voltC_N = 0;
		else
			asli_PM710[pm_dibaca].voltC_N = data_PM710[pm_dibaca].voltC_N * satuan_volt[pm_dibaca];


		// fasa - netral average
		data_PM710[pm_dibaca].volt2 = buf[19];
		data_PM710[pm_dibaca].volt2 = (data_PM710[pm_dibaca].volt2 << 8) + buf[20];
		//asli_PM710[pm_dibaca].volt2 = data_PM710[pm_dibaca].volt2 * satuan_volt[pm_dibaca];
		if (data_PM710[pm_dibaca].volt2 == 32768)
			asli_PM710[pm_dibaca].volt2 = 0;
		else
			asli_PM710[pm_dibaca].volt2 = data_PM710[pm_dibaca].volt2 * satuan_volt[pm_dibaca];

	 }
	 else if (urt == 4)
	 {
		// kwA, kwB, kwC, kw
		data_PM710[pm_dibaca].kwA = buf[3];
		data_PM710[pm_dibaca].kwA = (data_PM710[pm_dibaca].kwA << 8) + buf[4];
		asli_PM710[pm_dibaca].kwA = data_PM710[pm_dibaca].kwA * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kwB = buf[5];
		data_PM710[pm_dibaca].kwB = (data_PM710[pm_dibaca].kwB << 8) + buf[6];
		asli_PM710[pm_dibaca].kwB = data_PM710[pm_dibaca].kwB * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kwC = buf[7];
		data_PM710[pm_dibaca].kwC = (data_PM710[pm_dibaca].kwC << 8) + buf[8];
		asli_PM710[pm_dibaca].kwC = data_PM710[pm_dibaca].kwC * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kw = buf[9];
		data_PM710[pm_dibaca].kw = (data_PM710[pm_dibaca].kw << 8) + buf[10];
		asli_PM710[pm_dibaca].kw = data_PM710[pm_dibaca].kw * satuan_kw[pm_dibaca];

		// kvarA, kvarB, kvarC, kvar
		data_PM710[pm_dibaca].kvarA = buf[11];
		data_PM710[pm_dibaca].kvarA = (data_PM710[pm_dibaca].kvarA << 8) + buf[12];
		asli_PM710[pm_dibaca].kvarA = data_PM710[pm_dibaca].kvarA * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kvarB = buf[13];
		data_PM710[pm_dibaca].kvarB = (data_PM710[pm_dibaca].kvarB << 8) + buf[14];
		asli_PM710[pm_dibaca].kvarB = data_PM710[pm_dibaca].kvarB * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kvarC = buf[15];
		data_PM710[pm_dibaca].kvarC = (data_PM710[pm_dibaca].kvarC << 8) + buf[16];
		asli_PM710[pm_dibaca].kvarC = data_PM710[pm_dibaca].kvarC * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kvar = buf[17];
		data_PM710[pm_dibaca].kvar = (data_PM710[pm_dibaca].kvar << 8) + buf[18];
		asli_PM710[pm_dibaca].kvar = data_PM710[pm_dibaca].kvar * satuan_kw[pm_dibaca];

		// kvaA, kvaB, kvaC, kva
		data_PM710[pm_dibaca].kvaA = buf[19];
		data_PM710[pm_dibaca].kvaA = (data_PM710[pm_dibaca].kvaA << 8) + buf[20];
		asli_PM710[pm_dibaca].kvaA = data_PM710[pm_dibaca].kvaA * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kvaB = buf[21];
		data_PM710[pm_dibaca].kvaB = (data_PM710[pm_dibaca].kvaB << 8) + buf[22];
		asli_PM710[pm_dibaca].kvaB = data_PM710[pm_dibaca].kvaB * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kvaC = buf[23];
		data_PM710[pm_dibaca].kvaC = (data_PM710[pm_dibaca].kvaC << 8) + buf[24];
		asli_PM710[pm_dibaca].kvaC = data_PM710[pm_dibaca].kvaC * satuan_kw[pm_dibaca];

		data_PM710[pm_dibaca].kva = buf[25];
		data_PM710[pm_dibaca].kva = (data_PM710[pm_dibaca].kva << 8) + buf[26];
		asli_PM710[pm_dibaca].kva = data_PM710[pm_dibaca].kva * satuan_kw[pm_dibaca];

	 }
	 else if (urt == 5)
	 {
		//pfA, pfB, pfC, pf
		data_PM710[pm_dibaca].pfA = buf[3];
		data_PM710[pm_dibaca].pfA = (data_PM710[pm_dibaca].pfA << 8) + buf[4];
		if (data_PM710[pm_dibaca].pfA == 0x8000) asli_PM710[pm_dibaca].pfA = 1.00;
		else
		{
		   if (data_PM710[pm_dibaca].pfA > 0x8000)
				data_PM710[pm_dibaca].pfA = data_PM710[pm_dibaca].pfA + 0x8000;

		   asli_PM710[pm_dibaca].pfA = data_PM710[pm_dibaca].pfA * 0.001;
		}

		data_PM710[pm_dibaca].pfB = buf[5];
		data_PM710[pm_dibaca].pfB = (data_PM710[pm_dibaca].pfB << 8) + buf[6];
		if (data_PM710[pm_dibaca].pfB == 0x8000) asli_PM710[pm_dibaca].pfB = 1.00;
		else
		{
		   if (data_PM710[pm_dibaca].pfB > 0x8000)
				data_PM710[pm_dibaca].pfB = data_PM710[pm_dibaca].pfB + 0x8000;

		   asli_PM710[pm_dibaca].pfB = data_PM710[pm_dibaca].pfB * 0.001;
		}

		data_PM710[pm_dibaca].pfC = buf[7];
		data_PM710[pm_dibaca].pfC = (data_PM710[pm_dibaca].pfC << 8) + buf[8];
		//Memo1->Lines->Add(IntToStr( data_PM710[pm_dibaca].pfC));
		if (data_PM710[pm_dibaca].pfC == 0x8000) asli_PM710[pm_dibaca].pfC = 1.00;
		else
		{
		   if (data_PM710[pm_dibaca].pfC > 0x8000)
				data_PM710[pm_dibaca].pfC = data_PM710[pm_dibaca].pfC + 0x8000;
		   
		   asli_PM710[pm_dibaca].pfC = data_PM710[pm_dibaca].pfC * 0.001;
		}

		data_PM710[pm_dibaca].pf = buf[9];
		data_PM710[pm_dibaca].pf = (data_PM710[pm_dibaca].pf << 8) + buf[10];
		if (data_PM710[pm_dibaca].pf == 0x8000) asli_PM710[pm_dibaca].pf = 1.00;
		else
		{
		   if (data_PM710[pm_dibaca].pf > 0x8000)
				data_PM710[pm_dibaca].pf = data_PM710[pm_dibaca].pf + 0x8000;

		   asli_PM710[pm_dibaca].pf = data_PM710[pm_dibaca].pf * 0.001;
		}

	 }
	 else if (urt == 6)
	 {
		//frekuensi thok
		data_PM710[pm_dibaca].frek = buf[3];
		data_PM710[pm_dibaca].frek = (data_PM710[pm_dibaca].frek << 8) + buf[4];

		if (data_PM710[pm_dibaca].frek == 32768) data_PM710[pm_dibaca].frek = 0;
		asli_PM710[pm_dibaca].frek = data_PM710[pm_dibaca].frek * 0.01;

		#ifndef MOD_SERVER
		f = data_PM710[pm_dibaca].frek * 0.01;
		//Label22->Caption = FloatToStrF(f, ffGeneral, 4, 3);
		#endif

	 }
	 else if (urt == 7)
	 {
		//ENERGI
		// kwh, kvarh
		temp2 = buf[7];
		temp2 = (temp2 << 8) + buf[8];
		temp2 = temp2 * 10000;

		temp = buf[5];
		temp = (temp << 8) + buf[6];
		temp = (temp+temp2) * 10000;

		data_PM710[pm_dibaca].kwh = buf[3];
		data_PM710[pm_dibaca].kwh = (data_PM710[pm_dibaca].kwh << 8) + buf[4];
		data_PM710[pm_dibaca].kwh = data_PM710[pm_dibaca].kwh + temp;
		asli_PM710[pm_dibaca].kwh = data_PM710[pm_dibaca].kwh * satuan_kwh[pm_dibaca];

		//
		temp2 = buf[15];
		temp2 = (temp2 << 8) + buf[16];
		temp2 = temp2 * 10000;

		temp = buf[13];
		temp = (temp << 8) + buf[14];
		temp = (temp+temp2) * 10000;

		data_PM710[pm_dibaca].kvarh = buf[11];
		data_PM710[pm_dibaca].kvarh = (data_PM710[pm_dibaca].kvarh << 8) + buf[12];
		data_PM710[pm_dibaca].kvarh = data_PM710[pm_dibaca].kvarh + temp;
		asli_PM710[pm_dibaca].kvarh = data_PM710[pm_dibaca].kvarh * satuan_kwh[pm_dibaca];

	 }

	 else if (urt == 8)
	 {
		//ENERGI KVAH
		// kvah
		temp2 = buf[7];
		temp2 = (temp2 << 8) + buf[8];
		temp2 = temp2 * 10000;

		temp = buf[5];
		temp = (temp << 8) + buf[6];
		temp = (temp+temp2) * 10000;

		data_PM710[pm_dibaca].kvah = buf[3];
		data_PM710[pm_dibaca].kvah = (data_PM710[pm_dibaca].kvah << 8) + buf[4];
		data_PM710[pm_dibaca].kvah = data_PM710[pm_dibaca].kvah + temp;
		asli_PM710[pm_dibaca].kvah = data_PM710[pm_dibaca].kvah * satuan_kwh[pm_dibaca];

		kontrol_PM[pm_dibaca].alamat = addr_PM710;
		kontrol_PM[pm_dibaca].konek = 1;             // tersambung
		kontrol_PM[pm_dibaca].baru = 1;              // data baru

		//cek jika Volt = 0, maka mesin mati
		if (asli_PM710[pm_dibaca].volt1 == 0)
		{
		   kontrol_PM[pm_dibaca].baru = 0;           // supaya tidak dikirim ethernet
		}

		//NEXT PM
	 }
}

bool main_window::update_tampilan()
{
	printf("\nTAMPILAN\n");
	
	static char tek[128];	
	int i;
	int jumlah_titik=30;
	Glib::ustring usTemp;
	
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
	
	m_refTreeModel = Gtk::TreeStore::create(m_Columns);
	list_pm->set_model(m_refTreeModel);
	
	float *fTemp;
	
	fTemp=(float*) &asli_PM710[id_tampilkan].kwh;
	//asli_PM710[id_tampilkan].kwh=12;
	for(i=0;i<jumlah_titik;i++)
	{
		Gtk::TreeModel::Row row =*(m_refTreeModel->append());
		
		row[m_Columns.m_col_id]=i;
		row[m_Columns.m_nama]=pm_parameter[i];
		row[m_Columns.m_satuan]=pm_satuan[i];
		
		sprintf(tek, "%0.2f",*fTemp);	
		row[m_Columns.m_nilai]=tek;
		//printf("%d->%0.2f \t",i,*fTemp);
		fTemp++;
	}
	
	if(!tree_ada_kolom)
	{
		list_pm->append_column("No.",m_Columns.m_col_id);
		list_pm->append_column("Parameter",m_Columns.m_nama);
		list_pm->append_column("Nilai",m_Columns.m_nilai);
		list_pm->append_column("Satuan",m_Columns.m_satuan);
		//tree_data->append_column("Satuan",m_Columns.m_col_nomer);
		
		tree_ada_kolom=true;
	}
	
	sprintf(tek, "kWh   = %.2f", asli_PM710[id_tampilkan].kwh);	
	//printf(tek);
	//gtk_label_set_text((GtkLabel *) l_kwh, tek);
	label_kwh->set_text(tek);
		
	sprintf(tek, "kVAh  = %.2f", asli_PM710[id_tampilkan].kvah);	
	label_kvah->set_text(tek);
	//printf("%s\n",tek);
	//gtk_label_set_text((GtkLabel *) l_kvah, tek);
	
	//sprintf(tek, "<span foreground=\"blue\" size=\"20\">kVArh = %.2f</span>", asli_PM710[addr_PM710].kvarh);	
	sprintf(tek, "kVArh = %.2f", asli_PM710[id_tampilkan].kvarh);	
	
	//printf("%s\n",tek);
	label_kvarh->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_kvarh, tek);
	
	sprintf(tek, "kW    = %.2f", asli_PM710[id_tampilkan].kw);	
	//sprintf(tek, "kW    = %.2f", asli_PM710[addr_PM710].kw);	
	//printf("%s\n",tek);
	
	label_kw->set_text(tek);
	//
	//gtk_label_set_text((GtkLabel *) l_kw, tek);
	
	
	sprintf(tek, "kVA   = %.2f", asli_PM710[id_tampilkan].kva);		
	//printf("%s\n",tek);
	label_kva->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_kva, tek);
	
	sprintf(tek, "kVAr  = %.2f", asli_PM710[id_tampilkan].kvar);	
	label_kvar->set_text(tek);
	//printf("%s\n",tek);
	//gtk_label_set_text((GtkLabel *) l_kvar, tek);
	
	sprintf(tek, "pf    = %.2f", asli_PM710[id_tampilkan].pf);	
	//printf("%s\n",tek);
	label_cospi->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_pf, tek);
	
	sprintf(tek, "Volt1 = %.2f", asli_PM710[id_tampilkan].volt1);	
	//printf("%s\n",tek);
	label_vll->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_volt1, tek);
	
	sprintf(tek, "Volt2 = %.2f", asli_PM710[id_tampilkan].volt2);	
	//printf("%s\n",tek);
	label_vln->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_volt2, tek);
	
	sprintf(tek, "Ampere = %.2f", asli_PM710[id_tampilkan].amp);	
	//printf("%s\n",tek);
	label_ampr->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_volt2, tek);
	
	
	sprintf(tek, "frek  = %.2f", asli_PM710[id_tampilkan].frek);	
	//printf("%s\n",tek);
	label_frek->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_frek, tek);
	
	
	sprintf(tek, "amp_A = %.2f", asli_PM710[id_tampilkan].ampA);	
	//printf("%s\n",tek);
	label_ampl1->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_ampa, tek);
	
	sprintf(tek, "amp_B = %.2f", asli_PM710[id_tampilkan].ampB);	
	//printf("%s\n",tek);
	label_ampl2->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_ampb, tek);
	
	sprintf(tek, "amp_C = %.2f", asli_PM710[id_tampilkan].ampC);	
	//printf("%s\n",tek);
	label_ampl3->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_ampc, tek);
	
	sprintf(tek, "amp_N = %.2f", asli_PM710[id_tampilkan].ampN);	
	//printf("%s\n",tek);
	label_ampn->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_ampn, tek);
	
	
	sprintf(tek, "Volt_AB = %.2f", asli_PM710[id_tampilkan].voltA_B);	
	//printf("%s\n",tek);
	label_vl1l2->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_voltab, tek);

	sprintf(tek, "Volt_BC = %.2f", asli_PM710[id_tampilkan].voltB_C);	
	//printf("%s\n",tek);
	label_vl2l3->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_voltbc, tek);

	sprintf(tek, "Volt_AC = %.2f", asli_PM710[id_tampilkan].voltA_C);	
	//printf("%s\n",tek);
	label_vl1l3->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_voltac, tek);


	sprintf(tek, "Volt_AN = %.2f", asli_PM710[id_tampilkan].voltA_N);	
	//printf("%s\n",tek);
	label_voltl1n->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_voltan_piye, tek);
	
	sprintf(tek, "Volt_BN = %.2f", asli_PM710[id_tampilkan].voltB_N);	
	//printf("%s\n",tek);
	label_voltl2n->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_voltbn, tek);

	sprintf(tek, "Volt_CN = %.2f", asli_PM710[id_tampilkan].voltC_N);	
	//printf("%s\n",tek);
	label_voltl3n->set_text(tek);
	//gtk_label_set_text((GtkLabel *) l_voltcn, tek);
	/**/
	
	// alamat yang sedang diambil
	sprintf(tek, "Alamat = %2d\n", addr_PM710);	

	printf(tek);
	
	sprintf(tek,"server_counter: %d\n",server_counter);
	printf(tek);
	
	sprintf(status_teks,"address: %d |eth counter: %d | loop: %d",addr_PM710, server_counter,loop_counter);
	statusbar1->push(status_teks, 1);
	
	if(!timer_on)
		return false;
}
void set_awal_serial(int fd)
{
	struct termios oldtio,newtio;
    struct sigaction saio;           /* definition of signal action */
	
	printf("[set_awal_serial]\n");
	/* install the signal handler before making the device asynchronous */
    saio.sa_handler = signal_handler_IO;
    //saio.sa_mask = 0;
    saio.sa_flags = 0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO,&saio,NULL);
          
    /* allow the process to receive SIGIO */
    fcntl(fd, F_SETOWN, getpid());
    /* Make the file descriptor asynchronous (the manual page says only 
       O_APPEND and O_NONBLOCK, will work with F_SETFL...) */
    fcntl(fd, F_SETFL, FASYNC);
        
    tcgetattr(fd,&oldtio); /* save current port settings */
    /* set new port settings for canonical input processing */
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    
    //newtio.c_iflag = IGNPAR | ICRNL;
    newtio.c_iflag = IGNPAR;
    
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;		// non-canonical
    newtio.c_cc[VMIN]=1;	// wait 1 karakter
    newtio.c_cc[VTIME]=0;
    
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
	
	printf("[set_awal_serial]\n");
}


void signal_handler_IO (int status)
{
	//printf("received SIGIO signal.\n");
    //printf("r\n");
    wait_flag_serial = FALSE;
	//printf("wait_flag= %d\n",wait_flag_serial);
}

//---------------------------------------------------------------------------
bool main_window::on_main_window_delete_event(GdkEventAny *ev)
{
	Glib::ustring sTemp="Tutup Power Meter Server?";
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
//---------------------------------------------------------------------------

int main_window::isi_form()
{
	
	//m_refTreeModel = Gtk::ListStore::create(m_kolom);
	//combo_com->set_model(m_refTreeModel);
	m_refCombo=Gtk::TreeStore::create(m_kolom);
	
}
