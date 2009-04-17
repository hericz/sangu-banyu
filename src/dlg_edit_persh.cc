// generated 2008/8/26 17:54:30 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_persh.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "dlg_edit_persh.hh"

dlg_edit_persh::dlg_edit_persh()
{
	printf("[dlg_edit_persh]\n");
}

dlg_edit_persh::~dlg_edit_persh()
{
	printf("[~dlg_edit_persh]\n");
}

void dlg_edit_persh::on_okbutton3_clicked()
{  
	printf("[on_okbutton3_clicked]\n");
	
	char sTemp[512];
	Glib::ustring unama_persh,ualamat,unote,ugambar;
	
	if(id_persh<0)
	{
		//Data error
		Gtk::MessageDialog dialog(*this, "ERROR: ID Group tidak valid");
		
		dialog.run();
		return ;
	}
	
	//Ambil data dari dialog
	unama_persh=entry_nama->get_text();
	
	ualamat=entry_alamat->get_text();
	ugambar=entry_gambar->get_text();
	
	
	Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

	m_refTextBuffer= textview_keterangan->get_buffer();//Gtk::TextBuffer::create();
	unote=m_refTextBuffer->get_text();
	
	//Cek entri form
	if(unama_persh=="")
	{
		Gtk::MessageDialog dialog(*this, "Nama Perusahaan tidak boleh kosong");
		
		dialog.run();

		//Jangan nutup dialognya
		
		//this->set_modal(false);
		
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
	if(id_persh==0)
	{//Dianggap data baru
		sprintf(sTemp,"INSERT INTO perusahaan(nama_pers,alamat,note,gambar)");
		sprintf(sTemp,"%s VALUES('%s','%s','%s','%s')",sTemp,
				unama_persh.c_str(),ualamat.c_str(),unote.c_str(),ugambar.c_str());

		printf("Query: %s\n",sTemp);
		
		strcpy(MYQ.Text,sTemp);
		MYQ.Insert();	
	}
	else if(id_persh>0)
	{//Update data
		
		sprintf(sTemp,"UPDATE perusahaan SET nama_pers='%s',alamat='%s',note='%s',gambar='%s'",
				unama_persh.c_str(),ualamat.c_str(),unote.c_str(),ugambar.c_str());
		sprintf(sTemp,"%s WHERE id_pers='%d'",sTemp,id_persh);
		
		printf("Query: %s\n",sTemp);
		
		strcpy(MYQ.Text,sTemp);
		MYQ.Update();
	}

	MYQ.Close();
}

void dlg_edit_persh::isi_form()
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
	
	if(!id_persh)
	{
		usQuery="SELECT MAX(id_pers) as max FROM perusahaan";
		
		strcpy(MYQ.Text,usQuery.c_str());
		MYQ.Query();
		if(MYQ.jum_row==1)
		{
			usTemp=MYQ.ambil_string("max");
			this->entry_nama->set_text("Perusahaan " + usTemp);	
		}
		else
			this->entry_nama->set_text("Perusahaan 0");
		
		MYQ.Buang();
		return;
	}
	usQuery=Glib::ustring::compose("SELECT * FROM perusahaan WHERE id_pers='%1'",id_persh);	
	
	strcpy(MYQ.Text,usQuery.c_str());
	printf("Query: %s\n",usQuery.c_str());
	MYQ.Query();
	
	if(!MYQ.jum_row)
	{
		Gtk::MessageDialog dialog(*this, "Data Perusahaan tidak ditemukan");

		dialog.run();
		MYQ.Close();
		return ;	
	}
	
	if(MYQ.jum_row==1)
	{
		//isi_combo ();
		usTemp="";
		usTemp=MYQ.ambil_string("nama_pers"); 
		printf(" |- nama_pers: %s\n",usTemp.c_str());
		this->entry_nama->set_text(usTemp);	
		
		Glib::ustring uAlamat=MYQ.ambil_string("alamat");
		this->entry_alamat->set_text(uAlamat); 
		printf(" |- alamat: %s\n",uAlamat.c_str());
		
		//usTemp="";
		//usTemp=MYQ.ambil_string("gambar"); printf(" |- gambar: %s\n",usTemp.c_str());
		//this->entry_gambar->set_text(usTemp);
		
		
		usTemp="";
		usTemp=MYQ.ambil_string("note");  
		printf(" |- keterangan: %s\n",usTemp.c_str());
		Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
		m_refTextBuffer= Gtk::TextBuffer::create();
		
		m_refTextBuffer->set_text(usTemp);
		
		this->textview_keterangan->set_buffer(m_refTextBuffer);
	
	}
	
	MYQ.Close();
}
