/*
* common.hh
* herry - Juli 2008
*/

#ifndef _COMMON_HH_
#define _COMMON_HH_

#include <iostream>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <string.h>

#include "config.h"

//DEFINISI STRUCT
typedef struct konfig_file
{
     int version;
     char db_host[25];
     char db_port[25];
     char db_username[25];
     char db_pass[25];
     char nama_db[25];
     char monita_aktif[25]; //untuk referensi saja. yang penting ID_nya
     int id_monita_aktif;

     unsigned int data_ditampilkan;     // jumlah data ditampilkan pada grid, default = 2000
     unsigned long warna[20];
     unsigned int set[10];              // setting tampilan char, copy clipboard dll

     unsigned int port_server;          // port untuk komunikasi dengan simple monitor
     unsigned int allowable_koneksi;    // jumlah koneksi yang boleh dengan simple monitor
     unsigned char aktifkan;            // aktifkan server simple monitor
     unsigned char mode;                // mode server 10/browsing & analysis 20
	//19 Februari
	unsigned char auto_start; 	//0: auto start disable. 1: autostart enable
	
     //12 Februari, configurasi Modem
     char COMPort[5];
     char COMBaudRate[7];
     char COMDatabits[5];
     char COMParity[2];
     char COMStopBits[2];
     char COMFlowControl[9];
	
	//Timing pengambilan dan refresh data
	 int siklus_ambil_data;
	 int waktu_simpan_data;
	 int waktu_refresh_tabel_utama;
	 int waktu_refresh_grafik_utama;
	 
	//Timing database
	int  waktu_simpan_data_harian;
		
	unsigned long cek_konf; //isinya harus AA55AA55
};

//VARIABEL
//int jumlah_kucing;
//konfig_file kf;

//DEKLARASI FUNGSI
int LoadConfig_global();
int SimpanKonfig (konfig_file* kf);
void printlog(Glib::ustring asLog,int mode);

#endif //_COMMON_HH_
