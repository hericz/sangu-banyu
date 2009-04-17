//SQL routine
//Di porting dari UnitCQuery (C++ Builder 4)

//---------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#pragma hdrstop

#define debug_query

#include "sql_routine.h"

#define blob_kirim   256



/*2008 Maret-11: Tambahi try/catch statement untuk masing fungsi */
//---------------------------------------------------------------------------
#pragma package(smart_init)
unsigned int error_count = 0;
unsigned int total_query_count;

void pesan_error(Glib::ustring  s)
{
     Glib::ustring s2;
     error_count++;
     //if (error_count > (1024 * 1024))
     //FormError->Memo1->Clear();
	printf(s.c_str());
    // s2 = Now();
     //s2 = IntToStr(error_count)+". "+s2 + " " + s;

     //if(!FormError)
     //   Application->CreateForm(__classid(TFormError), &FormError);
     //FormError->Memo1->Lines->Add(s2);
}

void MyQuery::Query(void)
{
   #ifdef debug_query
   //printlog(Text,1);
   #endif
   jum_row=0;
   //if ( ! mysql_query( myDB, Text ))
try
{
        nomer_error = mysql_query( &myDB, Text );

   if (!nomer_error)
   {
      myRES = mysql_store_result( &myDB);
      jum_row = (int) mysql_num_rows( myRES );
      jum_field = (int) mysql_num_fields( myRES );
      myFD = mysql_fetch_fields( myRES );

      //ambil row nya untuk yang pertama
      myROW = mysql_fetch_row( myRES );
      posisi_row = 0;
      query_count++;
	  total_query_count++;
      if(query_count>5)
      {
        //printlog("Query not clean: " + IntToStr(query_count),0);
        printf("Query not clean");
      }
#ifdef use_progress
      if (FormBarQuery != NULL)
      {
          if (jum_row > 100)
          {
               FormBarQuery->Bar1->Max = jum_row;
               FormBarQuery->Position = 0;
               FormBarQuery->Show();
               FormBarQuery->BringToFront();
          }
      }
    #endif

    #ifdef use_bar
     if (FormDatabase != NULL)
     {
          if (jum_row > 100)
          {
          FormDatabase->bar1->Position = 0;
          FormDatabase->bar1->Max = jum_row;
          FormDatabase->StatusBar1->Refresh();
          FormDatabase->bar1->Visible = true;
          }
     }
    #endif
      //pesan_error(IntToStr(query_count));
    }
    else
    {
        //sprintf(text_error, "Last query error %d :%s", nomer_error,  nomer_error, Text.c_str());
        //text_error="";
        //text_error.sprintf("Last query error %d :%s, query_count: %d", nomer_error,  nomer_error, Text,query_count);
        //text_error="ERROR saat query";
        //pesan_error(text_error);
        printf("Error saat query");
    }

}
catch(...)
{
        //sprintf(text_error, "Last query error %d :%s, query_count: %d", nomer_error,  nomer_error, Text,query_count);
        //text_error="";
        //text_error.sprintf("Last query error %d :%s, query_count: %d", nomer_error, nomer_error, Text,query_count);
        //printlog("ERROR saat melakukan query",0);
        printf("ERROR saat melakukan query");
        jum_row=0;
        return;
}
}

void MyQuery::Buang(void)
{
    try
    {
     mysql_free_result( myRES );
     query_count--;
	 total_query_count--;
    }
   catch(...)
   {
        //printlog("error saat mengosongkan SQL cache",0);
        printf("error saat mengosongkan SQL cache");
   }
     //pesan_error(IntToStr(query_count));
}

void MyQuery::Query_row(void)
{
     nomer_error = mysql_query( &myDB, Text );

     if (!nomer_error)
     {
          myRES = mysql_store_result( &myDB);
          jum_row = (int) mysql_num_rows( myRES );
          mysql_free_result( myRES );
     }
     else
     {
          //pesan_error("Last query ROW error !");
          printf("Last query ROW error !");
     }

}


int MyQuery::init(void)
{
  *if ( (myDB = mysql_init((MYSQL*) 0)) &&
       mysql_real_connect( myDB, server, user, psw, db, port_koneksi_SQL,
			   NULL, 0 ) )
   {//Sukses
	  query_count = 0;
      myDB->reconnect = 1;
      posisi_row = 0;
      return 1;
   }
   else
      return 0;
}

int MyQuery::init_lengkap(void)
{
	printf("\nInisialisasi MySQL...");
	int ret,res,res_ptr;
	unsigned int timeout = 7;
	
	
	mysql_init(&myDB);
  	
  	printf("Ganti setting timeout...");
  	ret = mysql_options(&myDB, MYSQL_OPT_CONNECT_TIMEOUT, (const char *)&timeout);	
  
  	if(ret!=0)
   		printf("Gagal\n\r");
   	else
   		printf("OK\n");
   	
	//if (mysql_real_connect(&my_connection, uhost.c_str(), 
	// 		uusername.c_str(),upassword.c_str(), unama_db.c_str(), 0, NULL, 0)) 

	if(mysql_real_connect( &myDB, server, user, psw, db, port_koneksi_SQL,
			   NULL, 0 ))
	{
      	printf("Connection success\n");
      	return 1;		 
		//mysql_close(&myDB);
	} 
   else 
   {
      fprintf(stderr, "Connection failed\n");
      if (mysql_errno(&myDB)) 
      {
      	fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&myDB),mysql_error(&myDB));
		sprintf(ctemp, "Connection error %d: %s\n", mysql_errno(&myDB),mysql_error(&myDB));
		//printf(ctemp);
		//catat_log(ctemp,0);
		return 0;
      }
   }/**/
}
void MyQuery::Close(void)
{
   //mysql_free_result(myRES);
   mysql_close(&myDB);
}

Glib::ustring MyQuery::ambil_string(const char *field)
{
   int i;

   try
   {
   //mysql_field_seek(myRES, 0);
   for (i=0; i<jum_field; i++)
   {
      if (strcmp(myFD[i].name, field)==0)
      {
         if ( (Glib::ustring) myROW[i] != "(null)")
            return myROW[i];
         else
            return "";
            //return 0;
      }
   }
   }
   catch(...)
   {
	   sprintf(text_error, "Error ambil data %d :%s", nomer_error, nomer_error, Text);
	   printf("Error ambil data %d :%s", nomer_error, nomer_error, Text);
	   Glib::ustring sText;
	   sText.assign(text_error);
	   return text_error; 
   }
}

void MyQuery::Next(void)
{
   myROW = mysql_fetch_row( myRES );
   posisi_row++;

#ifdef use_progress
      if (FormBarQuery != NULL)
      {
          FormBarQuery->Bar1->Position = posisi_row;
          if (posisi_row > (jum_row-1))
               FormBarQuery->Hide();
      }
#endif

#ifdef use_bar
     if (FormDatabase != NULL)
     {
          //FormDatabase->bar1->Max = jum_row;
          FormDatabase->bar1->Position = posisi_row;
          //if (posisi_row > (jum_row-1)) FormDatabase->bar1->Visible = false;
     }
#endif
}

void MyQuery::Prev(void)
{
   myROW = mysql_fetch_row( myRES );
   posisi_row--;
}

void MyQuery::First(void)
{
    myROW = mysql_fetch_row( myRES );
    posisi_row=0;
}

void MyQuery::Last(void)
{
    myROW = mysql_fetch_row( myRES );
    posisi_row=jum_row-1;
}


int MyQuery::Insert(void)     //Jika error return 1, jika sukses return 0
{
   // Glib::ustring asTemp;
   #ifdef debug_query
   //FormDebug->Memo1->Lines->Add(Text);
   //printlog(Text,1);
   #endif


   try
   {

        nomer_error = mysql_query( &myDB, Text );
        if ( nomer_error )
        {
            //sprintf(text_error, "Error insert data %d :%s", nomer_error, nomer_error, Text);
            //text_error="";
            //text_error.sprintf("Last query error %d :%s, query_count: %d", nomer_error,  nomer_error, Text,query_count);
            //printlog("Error saat melakukan entri data",0);//text_error);
            //ShowMessage("Gagal saat menginput data");
            return 1;
        }
   }
   catch(...)
   {
        //sprintf(text_error, "Error insert data %d :%s", nomer_error, nomer_error, Text);
        //text_error="";
        //text_error.sprintf("Last query error %d :%s, query_count: %d", nomer_error,  nomer_error, Text,query_count);
        //printlog("Error saat menginsert data (catch statement)",0);//text_error,0);
        //ShowMessage("Gagal saat menginput data");
        return 1;
   }
   return 0;
}

void MyQuery::Replace(void)
{
   #ifdef debug_query
   //FormDebug->Memo1->Lines->Add(Text);
   //printlog(Text,1);
   #endif

   if ( mysql_query( &myDB, Text ))
   {
      //pesan_error("Error replace data");
   }
}
void MyQuery::Update(void)
{
   #ifdef debug_query
   //printlog(Text,1);
   #endif
   try
   {
        if ( mysql_query( &myDB, Text ))
        {
            //pesan_error("Error update data");
            printf("Error update data");
        }
   }
   catch(...)
   {
        //sprintf(text_error, "Error insert data %d :%s", nomer_error, nomer_error, Text);
        //text_error="";
        //text_error.sprintf("Last query error %d :%s, query_count: %d", nomer_error,  nomer_error, Text,query_count);
        //printlog("Error saat mengupdate data",0);//text_error,0);
        printf("Error saat mengupdate data");
   }
}
void MyQuery::Delete(void)
{
   #ifdef debug_query
   //FormDebug->Memo1->Lines->Add(Text);
    //printlog(Text,1);
   #endif
   try
   {
    if ( mysql_query( &myDB, Text ))
    {
        //pesan_error("Error delete data");
        printf("error");
    }
      }
   catch(...)
   {
        //sprintf(text_error, "Error insert data %d :%s", nomer_error, nomer_error, Text);
        //text_error="";
        //text_error.sprintf("Last query error %d :%s, query_count: %d", nomer_error,  nomer_error, Text,query_count);
        //printlog("Error saat menghapus data",0);//text_error,0);
        printf("Error");
   }
}

/*
void MyQuery::BuatStream(TStream *st)
{
   buf_blob = new char[st->Size];
   st->ReadBuffer(buf_blob, st->Size);
} */

/*
void MyQuery::masukkan_blob(TStream *st)
{
   int rc;
   int i;
   int last;
   char s_debug[128];

   buf_blob = new char[st->Size+1];
   st->ReadBuffer(buf_blob, st->Size);


   #ifdef debug_query

   //FormDebug->Memo1->Lines->Add("Prepare ..");
   printlog("Prepare...",1);
   //FormDebug->Memo1->Lines->Add(Text);
   printlog(Text,1);
   #endif

   stmt = mysql_stmt_init(myDB);
   if (stmt && mysql_stmt_prepare(stmt, Text, strlen(Text)))
   {
      sprintf(s_debug, "Error prepare stmt %s", mysql_stmt_error(stmt));
      mysql_stmt_close(stmt);
      //FormDebug->Memo1->Lines->Add(s_debug);
      //printlog(s_debug,1);
      //ShowMessage("Prepare error !");
      return;
   }

   #ifdef debug_query
   //verify param count
   long param_count= mysql_stmt_param_count(stmt);
   //FormDebug->Memo1->Lines->Add(IntToStr((__int64)param_count));
   printlog(IntToStr((__int64)param_count),1);
   #endif

   //siapin BIND
   memset((char*) bind, 0, sizeof(bind));

   bind[0].buffer= buf_blob;            // string data
   bind[0].buffer_length = st->Size;
   bind[0].length= &length1;
   //bind[0].buffer_type= MYSQL_TYPE_BLOB;
   bind[0].buffer_type= MYSQL_TYPE_LONG_BLOB;
   length1= 0;

   rc = mysql_stmt_bind_param(stmt, bind);

   #ifdef debug_query

   sprintf(s_debug, "bind_param %d", rc);
   //FormDebug->Memo1->Lines->Add(s_debug);
   printlog(s_debug,1);
   sprintf(s_debug, "size of buf %d", st->Size);
   //FormDebug->Memo1->Lines->Add(s_debug);
   printlog(s_debug,1);
   #endif

   //dikirim satu persatu
   for (i=0; i<st->Size;)
   {
      rc= mysql_stmt_send_long_data(stmt, 0, &buf_blob[i], blob_kirim);

      i = i+blob_kirim;
      if ((i+blob_kirim)>st->Size)
      {
         last = st->Size - i;
         rc= mysql_stmt_send_long_data(stmt, 0, &buf_blob[i], last);
         break;
      }
   }

   if (rc == 0)
   {
      rc= mysql_stmt_execute(stmt);

      if (rc == 0)
      {
         sprintf(s_debug, "Sending & eksekusi ok %d blob_kirim = %d", i, bind[0].length);
         //FormDebug->Memo1->Lines->Add(s_debug);
         //printlog(s_debug,1);
      }
      else
      {
         sprintf(s_debug, "error eksekusi %d & i=%d, %s", rc, i, mysql_stmt_error(stmt));
         //FormDebug->Memo1->Lines->Add(s_debug);
         //printlog(s_debug,1);
      }

      mysql_stmt_close(stmt);
   }
   else
   pesan_error("send error");

   delete buf_blob;
}*/

//------------------------------------------------------------------------------
void MyQuery::cek_field(void)
{
   int i;
   char out[128];

   for (i=0; i<jum_field; i++)
   {
      sprintf(out, "field = %s, L = %d, type = %d, max = %d", myFD[i].name,  myFD[i].length, myFD[i].type, myFD[i].max_length);
      //FormDebug->Memo1->Lines->Add(out);
       //printlog(out,1);
   }
}

//------------------------------------------------------------------------------
//cek apakah blob ada isinya atau tidak
bool MyQuery::cek_blob(char *field)
{
   int i;
   for (i=0; i<jum_field; i++)
   {
      if (strcmp(myFD[i].name, field)==0 && myFD[i].type == MYSQL_TYPE_BLOB)
      {
         if (myROW[i] != NULL) return true;
         else
            return false;
      }
   }
}

//------------------------------------------------------------------------------
unsigned char * MyQuery::ambil_buf(char *field, int &jum)
{
   int i;
   int y;
   //TStream *st;

   for (i=0; i<jum_field; i++)
   {
      if (strcmp(myFD[i].name, field)==0)
      {
         jum = myFD[i].max_length;
         //buf_blob = new char[st->Size+1];

         //for (y=0; y<st->Size; y++)

         //st->WriteBuffer(myROW[i], st->Size);


         //besar = myFD[i].max_length;
         return (unsigned char*) myROW[i];
      }
   }
   
   return 0;
}
//------------------------------------------------------------------------------
/*TStream * MyQuery::ambil_buf2(char *field)
{
   int i;
   int y;
   TMemoryStream *st;

   st = new TMemoryStream;

   for (i=0; i<jum_field; i++)
   {
      if (strcmp(myFD[i].name, field)==0)
      {
         //st->Size = myFD[i].max_length;
         st->Write(myROW[i], myFD[i].max_length);
         st->Position = 0;
         return st;
         //return myROW[i];
      }
   }
}*/
//------------------------------------------------------------------------------
/*TStream * MyQuery::ambil_blob(char *field)
{
   TMemoryStream *ts;
   int i;
   int rc;
   bool true_value;

   ts = new TMemoryStream;


   #ifdef debug_query
   //FormDebug->Memo1->Lines->Add("Ambil blob ..");
   //printlog("Ambil blob ..",1);
   //FormDebug->Memo1->Lines->Add(Text);
   //printlog(Text,1);
   #endif

   stmt = mysql_stmt_init(myDB);
   if (stmt && mysql_stmt_prepare(stmt, Text, strlen(Text)))
   {
      mysql_stmt_close(stmt);
      //pesan_error("ambil error !");
      //printf("ambil error");
      return 0;
   }

   #ifdef debug_query
   //verify param count
   long param_count= mysql_stmt_param_count(stmt);
   //FormDebug->Memo1->Lines->Add(IntToStr((__int64)param_count));
   //printlog(IntToStr((__int64)param_count),1);
   #endif
	*/
   //siapin BIND
   /*
   memset((char*) bind, 0, sizeof(bind));

   bind[0].buffer_type= MYSQL_TYPE_LONG_BLOB;
   bind[0].buffer= (void *) &data; //* this buffer won't be altered
   bind[0].buffer_length= 16;
   bind[0].length= &blob_length;
   bind[0].error= &bind[0].error_value;
   rc= mysql_stmt_bind_result(stmt, bind);

   rc = mysql_stmt_bind_param(stmt, bind);
   */

/*
   true_value= 1;
   mysql_stmt_attr_set(stmt, STMT_ATTR_UPDATE_MAX_LENGTH, (void*) &true_value);

   rc= mysql_stmt_execute(stmt);
   if (rc != 0) 
   	pesan_error("errror");

   rc= mysql_stmt_store_result(stmt);
   if (rc != 0) pesan_error("errror");

   myRES = mysql_stmt_result_metadata(stmt);
   myFD  = mysql_fetch_fields(myRES);

   //FormDebug->Memo1->Lines->Add(IntToStr((__int64)myFD->max_length));
   //printlog(IntToStr((__int64)myFD->max_length),1);
   //siapin BIND
   memset((char*) bind, 0, sizeof(bind));

}*/

//------------------------------------------------------------------------------
// 24 juli 2007
// mendapatkan id terakhir yang baru diinsert
unsigned long MyQuery::last_id(void)
{
   return mysql_insert_id(&myDB);
}
//------------------------------------------------------------------------------


unsigned int MyQuery::Ping(void)
{
     return mysql_ping(&myDB);
}

unsigned int MyQuery::CekUnclean(void)
{
	return total_query_count;
}
