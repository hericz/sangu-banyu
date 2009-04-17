/*
* Common.cc untuk fungsi2 yang dipakai bersama
*
*
*/ 
#ifndef _COMMON_CC_
#define _COMMON_CC_

#include "common.hh"

//namespace std;
//konfig_file kf;
//log
Glib::ustring tanggal_log,tanggal_temp;
Glib::ustring nama_file;
Glib::ustring waktu_start;
Glib::ustring time_start;
FILE *fLog;
struct tm *log_tm_pointer;
int monita_log_count;
int monita_file_count;

#define DEBUG_LOG

void printlog(Glib::ustring asLog,int mode)
{

#ifdef DEBUG_LOG
   Glib::ustring  asTime;
   Glib::ustring  asTemp;

	
	//Inisialisasi tanggal
	int itanggal,ibulan,itahun;
	int ijam,imenit,idetik;

	char cwaktu[32];
	time_t the_timelist;

	(void) time(&the_timelist);
	log_tm_pointer = localtime(&the_timelist);

   if(nama_file=="")
   {
       strftime(cwaktu,32,"%Y-%m-%d",log_tm_pointer);
	   tanggal_log.assign(cwaktu);
	   	
	   strftime(cwaktu,32,"%H:%M:%S",log_tm_pointer);
       waktu_start.assign(cwaktu); 
	   
	   nama_file="./log/" + tanggal_log+ " " + waktu_start + Glib::ustring::compose("-%1.log",monita_file_count);
   }
   //asTime=TimeToStr(Time());
	strftime(cwaktu,32,"%H:%M:%S",log_tm_pointer);
	asTime.assign(cwaktu);
	//printf(" |--* Buka file log: %s\n",nama_file.c_str());
    if ((fLog = fopen(nama_file.c_str(), "a+t")) == NULL)
    {
	   printf(" |-- Gagal membuka file log: %s\n",nama_file.c_str());
   }
   else
   {
    asTemp="";
	asTemp=Glib::ustring::compose("\n[%1]",monita_log_count);
    asTemp+="(" + asTime + ")" + asLog;
    fprintf(fLog,asTemp.c_str());
    
    monita_log_count++;

    //Ganti hari-ganti log
	strftime(cwaktu,32,"%Y-%m-%d",log_tm_pointer);
	tanggal_temp.assign(cwaktu);

    if(tanggal_log!=tanggal_temp)
    {
       strftime(cwaktu,32,"%Y-%m-%d",log_tm_pointer); 
	   tanggal_log.assign(cwaktu);
	   	
	   	strftime(cwaktu,32,"%H:%M:%S",log_tm_pointer); 
       	waktu_start.assign(cwaktu); 
		
		nama_file="./log/" + tanggal_log+ " " + waktu_start + Glib::ustring::compose("-%1.log",monita_file_count);
		
        monita_log_count=0;
        monita_file_count=0;
    }

    if(monita_log_count>1000)
    {
        monita_file_count++;
        nama_file="./log/" + tanggal_log+ Glib::ustring::compose("-%1.log",monita_file_count);

        monita_log_count=0;
    }

    fclose(fLog);
   }
#endif

}
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
    /*if(!(strcmp(kfg.db_host,"")))
        strcpy(kfg->db_host,"localhost");
    if(!(strcmp(&kfg_file.db_port,"")))
        strcpy(kfg_file.db_port,"3306");
    if(!(strcmp(kfg_file.db_username,"")))
        strcpy(&kfg_file.db_username[0],"herry");            
    if(!(strcmp(kfg_file.db_pass,"")))
        strcpy(&kfg_file.db_pass[0],"");
    if(!(strcmp(kfg_file.nama_db,"")))
        strcpy(&kfg_file.nama_db[0],"monita_db");

    if (kfg_file.data_ditampilkan == NULL) kfg_file.data_ditampilkan = 2000;

    //cek jika mode tidak sama dengan nol atau 1 maka default adalah 1 (browsing & analisis)

    //if (kf.mode != 0 || kf.mode != 1)
    if (kfg_file.mode == 0)
          kfg_file.mode = 20;       //browsing, 10 server, 20 browsing
    //else if (kf.mode == 1) kf.mode = 1;
    //else kf.mode = 1;
	

	printf("OK\n");
    return 0;
}*/

/*int SimpanKonfig1(konfig_file* kf)
{
	FILE *stream;
	Glib::ustring asFilePath;
	
	printf("Simpan konfigurasi...");
	asFilePath="konfigurasi.kfg";
    
	if ((stream = fopen(asFilePath.c_str(), "wb"))== NULL)
    {
        fprintf(stderr, "Cannot open output file.\n");
        printf("Gagal membuka file\n");
		return 1;
    }

    fwrite(kf, sizeof(konfig_file), 1, stream);
	
    fclose(stream);
	
	printf("OK\n");
	return 0;
}*/
#endif //_COMMON_CC
