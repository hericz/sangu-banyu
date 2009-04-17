// generated 2008/8/26 10:11:35 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_group.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "dlg_edit_group.hh"

dlg_edit_group::dlg_edit_group()
{
	printf("[dlg_edit_group]\n");
	kolom_jenis_ada=false;
	
	id_group=0;
	id_equipment=0;
}

dlg_edit_group::~dlg_edit_group()
{
	printf("[~dlg_edit_group]\n");
}

void dlg_edit_group::isi_form()
{
	printf("[dlg_edit_group::isi_form]\n");
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
	
	//Jika tidak ada id_group
	if(!id_group)
	{
		usQuery="SELECT MAX(id_group) as max FROM group_titik_ukur";
		
		strcpy(MYQ.Text,usQuery.c_str());
		MYQ.Query();
		if(MYQ.jum_row==1)
		{
			usTemp=MYQ.ambil_string("max");
			this->entry_nama->set_text("Group " + usTemp);	
		}
		else
			this->entry_nama->set_text("Group 0");
		
		MYQ.Buang();
		return;
	}
	
	//Jika ada id_group
	usQuery=Glib::ustring::compose("SELECT * FROM group_titik_ukur WHERE id_group='%1'",id_group);	
	
	strcpy(MYQ.Text,usQuery.c_str());
	printf("Query: %s\n",usQuery.c_str());
	MYQ.Query();
	
	if(!MYQ.jum_row)
	{
		Gtk::MessageDialog dialog(*this, "Data Group tidak ditemukan");
		//dialog.set_secondary_text("Periksa parameter koneksi database");

		dialog.run();
		return ;	
	}
	
	if(MYQ.jum_row==1)
	{
		isi_combo ();
		usTemp=MYQ.ambil_string("nama_group");
		
		this->entry_nama->set_text(usTemp);	
		
		usTemp=MYQ.ambil_string("keterangan");
		Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
		m_refTextBuffer= Gtk::TextBuffer::create();
		
		m_refTextBuffer->set_text(usTemp);
		
		this->textview_keterangan->set_buffer(m_refTextBuffer);
	}
	MYQ.Buang();
	MYQ.Close();
	printf("[/dlg_edit_group::isi_form]\n");
}

void dlg_edit_group::isi_combo()
{
	Glib::ustring usTemp;
	
	m_refJenisGroup = Gtk::TreeStore::create(m_jenis);
	combo_jenis->set_model(m_refJenisGroup);
	
	Gtk::TreeModel::Row row;// =*(m_refJenisGroup->append());
	
	for(int i=0;i<7;i++)
	{
		row =*(m_refJenisGroup->append());
		
		row[m_jenis.id_jenis]=i;
		row[m_jenis.icon]=Gdk::Pixbuf::create_from_file("emblem-generic16.png");
		usTemp=Glib::ustring::compose("Jenis %1",i);
		row[m_jenis.nama_jenis]=usTemp;
	}
	
	//Tambahan row
	if(!kolom_jenis_ada)
	{
		combo_jenis->pack_start(m_jenis.icon);
		combo_jenis->pack_start(m_jenis.nama_jenis);
	
		kolom_jenis_ada=true;
	}
}

void dlg_edit_group:: on_okbutton2_clicked()
{
	printf("[on_okbutton2_clicked]\n");
	
	Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
	Glib::ustring usQuery,unama_group,ugambar,uketerangan,ujenis_group;
	int jenis_group;
	char sQuery[512];
	
	unama_group=entry_nama->get_text();
	ugambar=entry_gambar->get_text();
	jenis_group=0; //undefined
	
	m_refTextBuffer=textview_keterangan->get_buffer();
	uketerangan=m_refTextBuffer->get_text();
	
	//Cek entri form
	if(unama_group=="")
	{
		Gtk::MessageDialog dialog(*this, "Nama Group tidak boleh kosong");
		
		dialog.run();
		return;
	}
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
	
	//simpan disini
	if(id_group) //Update data
	{
		
		sprintf(sQuery,
				"UPDATE group_titik_ukur SET nama_group='%s',gambar='%s',jenis_group='%d',keterangan='%s'",
				unama_group.c_str(),ugambar.c_str(),jenis_group,uketerangan.c_str());
		sprintf(sQuery,"%s WHERE id_group='%d'",sQuery,id_group);
		
		printf("Query: %s\n",sQuery);
		strcpy(MYQ.Text,sQuery);
		MYQ.Update();
	}
	else if((id_group==0)&&(id_equipment>0)) //data baru
	{
		sprintf(sQuery,"INSERT INTO group_titik_ukur(id_equipment,nama_group,gambar,jenis_group,keterangan)");
		sprintf(sQuery,"%s VALUES('%d','%s','%s','%d','%s')",sQuery,id_equipment,unama_group.c_str(),ugambar.c_str(),
				jenis_group,uketerangan.c_str());
		
		printf("Query: %s\n",sQuery);
		strcpy(MYQ.Text,sQuery);
		MYQ.Insert();
	}
	
	MYQ.Close();
}
