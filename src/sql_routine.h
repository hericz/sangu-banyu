//---------------------------------------------------------------------------
#ifndef SQL_ROUTINE_H
#define SQL_ROUTINE_H

#include <libglademm.h>
#include <gtkmm.h>
//#include "Unit1.h"
//#include "UnitLog.h"
#include "mysql.h"

#define port_koneksi_SQL   3306

//void pesan_error(Glib::ustring s);

//---------------------------------------------------------------------------

class MyQuery
{
   private:
   MYSQL		myDB ;
   MYSQL_RES	* myRES ;
   MYSQL_FIELD	* myFD ;
   MYSQL_ROW	myROW ;

   MYSQL_STMT *stmt;
   MYSQL_BIND bind[2];

   int posisi_row;

   public:
	~MyQuery();
	
   char server[25];
   char user[25];
   char psw[25];
   char port[25];
   char db[25];
   //char Text[1024];
   char Text[2048];
   unsigned int  jum_row;
   unsigned int  jum_field;
   int init(void);
   int init_lengkap(void);
   char *buf_blob;
   unsigned long length1;
   int nomer_error;
   //char text_error[1024];
   char pesan_error[128];
   char ctemp[256];
   //Glib::ustring text_error;

   //fungsi2
   void Close(void);
   void Open(void);
   int Query(void);
   void Query_row(void);
   void Buang(void);          //free myRes, biar tidak numpuk2
   Glib::ustring ambil_string(const char *field);
   //float ambil_float(char *field);
   void Next(void);
   void Prev(void);
   void First(void);
   void Last(void);
   //void Buang(void);
   int Insert(void);
   void Replace(void);
   bool Delete(void);
   int Update(void);
   //void masukkan_blob(TStream *st);
   //TStream * ambil_blob(char *field);

   void cek_field(void);
   bool cek_blob(char *field);
   unsigned char * ambil_buf(char *field, int &jum);
   //TStream * ambil_buf2(char *field);
   unsigned int CekUnclean (void);
		
   unsigned long last_id(void);
   unsigned int Ping(void);
   bool isConnected;
		
   unsigned int query_count;	
};

#endif //SQL_ROUTINE_H
