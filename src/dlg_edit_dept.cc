// generated 2008/8/26 18:01:18 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_dept.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "dlg_edit_dept.hh"

dlg_edit_dept::dlg_edit_dept()
{
	printf("[dlg_edit_dept]\n");
	id_dept=0;
	id_persh=0;
}

dlg_edit_dept::~dlg_edit_dept()
{
	printf("[~dlg_edit_dept]\n");	
}


void dlg_edit_dept::on_okbutton4_clicked()
{  
	printf("[~on_okbutton4_clicked]\n");	
	
	char sTemp[512];
	Glib::ustring unama_dept,unote,ugambar;
	
	if(id_dept<0)
	{
		//Data error
		Gtk::MessageDialog dialog(*this, "ERROR: ID Departemen tidak valid");
		
		dialog.run();
		return ;
	}
	
	//Ambil data dari dialog
	unama_dept=entry_nama->get_text();
	
	ugambar=entry_gambar->get_text();
	
	Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

	m_refTextBuffer= textview_keterangan->get_buffer();//Gtk::TextBuffer::create();
	unote=m_refTextBuffer->get_text();
	
	//Cek entri form
	if(unama_dept=="")
	{
		Gtk::MessageDialog dialog(*this, "Nama Departemen tidak boleh kosong");
		
		dialog.run();
		return ;
	}
	
	//Simpan data
	//Init mysql
	if(!MYQ.init_lengkap())
	{
		printf("Gagal melakukan inisialisasi database\n");
		Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
		dialog.set_secondary_text("Periksa parameter koneksi database");
		
		printf("[Init MySQL]\n");
		printf(" |- host: %s\n |- user: %s\n |- pass: %s\n |- db: %s\n",
			   MYQ.server,MYQ.user,MYQ.psw,MYQ.db);
		
		dialog.run();
		return ;
	}
	

	printf("Simpan data\n");
	if((id_dept==0)&&(id_persh>0))
	{//Dianggap data baru
		sprintf(sTemp,"INSERT INTO departemen(id_pers, nama_dep,keterangan,gambar)");
		sprintf(sTemp,"%s VALUES('%d','%s','%s','%s')",sTemp,id_persh,
				unama_dept.c_str(),unote.c_str(),ugambar.c_str());

		printf("Query: %s\n",sTemp);
		
		strcpy(MYQ.Text,sTemp);
		MYQ.Insert();	
	}
	else if(id_dept>0)
	{//Update data
		
		sprintf(sTemp,"UPDATE departemen SET nama_dep='%s',keterangan='%s',gambar='%s'",
				unama_dept.c_str(),unote.c_str(),ugambar.c_str());
		sprintf(sTemp,"%s WHERE id_dep='%d'",sTemp,id_dept);
		
		printf("Query: %s\n",sTemp);
		
		strcpy(MYQ.Text,sTemp);
		MYQ.Update();
	}

	MYQ.Close();
}

void dlg_edit_dept::isi_form()
{
	Glib::ustring usQuery,usTemp;
	
	//Init mysql
	if(!MYQ.init_lengkap())
	{
		printf("Gagal melakukan inisialisasi database\n");
		Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
		dialog.set_secondary_text("Periksa parameter koneksi database");
		
		printf("[Init MySQL]\n");
		printf(" |- host: %s\n |- user: %s\n |- pass: %s\n |- db: %s\n",
			   MYQ.server,MYQ.user,MYQ.psw,MYQ.db);
		
		dialog.run();
		return ;
	}
	
		
	if(!id_dept)
	{
		usQuery="SELECT MAX(id_dep) as max FROM departemen";
		
		strcpy(MYQ.Text,usQuery.c_str());
		MYQ.Query();
		if(MYQ.jum_row==1)
		{
			usTemp=MYQ.ambil_string("max");
			this->entry_nama->set_text("Departemen " + usTemp);	
		}
		else
			this->entry_nama->set_text("Departemen 0");
		
		MYQ.Buang();
		return;
	}
	
	usQuery=Glib::ustring::compose("SELECT * FROM departemen WHERE id_dep='%1'",id_dept);	
	
	strcpy(MYQ.Text,usQuery.c_str());
	printf("Query: %s\n",usQuery.c_str());
	MYQ.Query();
	
	if(!MYQ.jum_row)
	{
		Gtk::MessageDialog dialog(*this, "Data Departemen tidak ditemukan");

		dialog.run();
		MYQ.Close();
		return ;	
	}
	
	if(MYQ.jum_row==1)
	{
		//isi_combo ();
		usTemp="";
		usTemp=MYQ.ambil_string("nama_dep"); 
		printf(" |- nama_dep: %s\n",usTemp.c_str());
		this->entry_nama->set_text(usTemp);	
		
		Glib::ustring ugambar=MYQ.ambil_string("gambar");
		this->entry_gambar->set_text(ugambar); 
		printf(" |- gambar: %s\n",ugambar.c_str());
		
		//usTemp="";
		//usTemp=MYQ.ambil_string("gambar"); printf(" |- gambar: %s\n",usTemp.c_str());
		//this->entry_gambar->set_text(usTemp);
		
		
		usTemp="";
		usTemp=MYQ.ambil_string("keterangan");  
		printf(" |- keterangan: %s\n",usTemp.c_str());
		Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
		m_refTextBuffer= Gtk::TextBuffer::create();
		
		m_refTextBuffer->set_text(usTemp);
		
		this->textview_keterangan->set_buffer(m_refTextBuffer);
	
	}
	MYQ.Buang();
	MYQ.Close();
}
