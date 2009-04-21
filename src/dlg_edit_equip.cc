// generated 2008/8/26 18:12:38 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_equip.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "dlg_edit_equip.hh"

dlg_edit_equip::dlg_edit_equip()
{
	printf("[dlg_edit_equip]\n");
	id_equipment=0;
	id_dept=0;

}

dlg_edit_equip::~dlg_edit_equip()
{
	printf("[~dlg_edit_equip]\n");
}

//Event handler
void dlg_edit_equip::on_okbutton5_clicked()
{
	printf("[on_okbutton5_clicked]\n");
	char sTemp[512];
	Glib::ustring unama_equip,ukode_equip,uketerangan,ugambar;
	int param_input1,param_input2,param_output1,param_output2;
	int no_urut,jenis_equipment;
	
	if(id_equipment<0)
	{
		//Data error
		Gtk::MessageDialog dialog(*this, "ERROR: ID Alat tidak valid");
		
		dialog.run();
		return ;
	}
	
	//Ambil data dari dialog
	unama_equip=entry_nama->get_text();
	
	ukode_equip=entry_kode->get_text();
	no_urut=0;
	jenis_equipment=0;
	
	uketerangan="";
	
	//Parameter
	param_input1=0;
	param_input2=0;
	param_output1=0;
	param_output2=0;
	
	//Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
	//m_refTextBuffer= textview_keterangan->get_buffer();//Gtk::TextBuffer::create();
	//unote=m_refTextBuffer->get_text();
	
	//Cek entri form
	if(unama_equip=="")
	{
		Gtk::MessageDialog dialog(*this, "Nama Peralatan tidak boleh kosong");
		
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
	if((id_equipment==0)&&(id_dept>0))
	{//Dianggap data baru
		sprintf(sTemp,"INSERT INTO equipment(id_dept,nama_equipment,kode_equipment,jenis_equipment,ket_equipment,no_urut)");
		sprintf(sTemp,"%s VALUES('%d','%s','%s','%d','%s','%d')",sTemp,id_dept,
				unama_equip.c_str(),ukode_equip.c_str(),jenis_equipment,uketerangan.c_str(),no_urut);

		printf("Query: %s\n",sTemp);
		
		strcpy(MYQ.Text,sTemp);
		MYQ.Insert();
	}
	else if(id_equipment>0)
	{//Update data
		
		sprintf(sTemp,"UPDATE equipment SET nama_equipment='%s',kode_equipment='%s',jenis_equipment='%d',ket_equipment='%s',no_urut='%d'",
				unama_equip.c_str(),ukode_equip.c_str(),jenis_equipment,uketerangan.c_str(),no_urut);
		//sprintf(sTemp,
		sprintf(sTemp,"%s WHERE id_equipment='%d'",sTemp,id_equipment);
		
		printf("Query: %s\n",sTemp);
		
		strcpy(MYQ.Text,sTemp);
		MYQ.Update();
	}

	MYQ.Close();
}

void dlg_edit_equip::isi_form()
{
	this->isi_combo();
	Glib::ustring usQuery,usTemp;
	printf("[dlg_edit_equip::isi_form] id_equipment: %d\n",id_equipment);
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
	
	//Mulai isi form
	if(!id_equipment)
	{
		usQuery="SELECT MAX(id_equipment) as max FROM equipment";
		
		strcpy(MYQ.Text,usQuery.c_str());
		MYQ.Query();
		if(MYQ.jum_row==1)
		{
			usTemp=MYQ.ambil_string("max");
			this->entry_nama->set_text("Equipment " + usTemp);	
		}
		else
			this->entry_nama->set_text("Equipment 0");
		
		MYQ.Buang();
		return;
	}
	
	usQuery=Glib::ustring::compose("SELECT * FROM equipment WHERE id_equipment='%1'",id_equipment);	
	
	strcpy(MYQ.Text,usQuery.c_str());
	printf("Query: %s\n",usQuery.c_str());
	MYQ.Query();
	
	if(!MYQ.jum_row)
	{
		Gtk::MessageDialog dialog(*this, "Data Alat tidak ditemukan");

		dialog.run();
		MYQ.Close();
		return ;	
	}
	
	if(MYQ.jum_row==1)
	{
		//isi_combo ();
		usTemp="";
		usTemp=MYQ.ambil_string("nama_equipment"); 
		printf(" |- nama_equipment: %s\n",usTemp.c_str());
		this->entry_nama->set_text(usTemp);	
		
		//Glib::ustring ugambar=MYQ.ambil_string("gambar");
		//this->entry_gambar->set_text(ugambar); 
		//printf(" |- gambar: %s\n",ugambar.c_str());
		
		//usTemp="";
		//usTemp=MYQ.ambil_string("gambar"); printf(" |- gambar: %s\n",usTemp.c_str());
		//this->entry_gambar->set_text(usTemp);
		
		
		/*usTemp="";
		usTemp=MYQ.ambil_string("keterangan");  
		printf(" |- keterangan: %s\n",usTemp.c_str());
		Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
		m_refTextBuffer= Gtk::TextBuffer::create();
		
		m_refTextBuffer->set_text(usTemp);
		
		this->textview_keterangan->set_buffer(m_refTextBuffer);*/
	}
	MYQ.Buang();
	
	//Isi combo jenis 
	
	MYQ.Close();
}

int dlg_edit_equip::isi_combo()
{
	printf("[dlg_edit_equip::isi_combo]\n");
	Glib::ustring usTemp;
	Glib::ustring usQuery;
	int iTemp;
	
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
		return -1;
	}	
	//Isi combo jenis equipment
	usQuery="SELECT * FROM tipe_equipment";
	
	strcpy(MYQ.Text,usQuery.c_str());
	MYQ.Query();
	
	int jumlah_jenis=MYQ.jum_row;
	
	if(jumlah_jenis<=0)
	{
		MYQ.Close();
		return -1;
	}
	m_refTreeModel = Gtk::TreeStore::create(m_Columns);
	combo_jenis->set_model(m_refTreeModel);
	Gtk::TreeModel::Row row;
	
	for(int i=0;i<jumlah_jenis;i++)
	{
		usTemp=MYQ.ambil_string("id_tipe");
		try
		{
			iTemp=atoi(usTemp.c_str());
		}
		catch(...)
		{
			iTemp=0;
		}
		
		if(iTemp<=0)
			continue;
		
		row=*(m_refTreeModel->append());
		
		row[m_Columns.id_jenis]=iTemp;
		row[m_Columns.nama_jenis]=MYQ.ambil_string("nama_tipe");
		row[m_Columns.icon]=Gdk::Pixbuf::create_from_file("emblem-generic16.png");
		
		MYQ.Next();
	}
 	combo_jenis->pack_start(m_Columns.icon);
  	combo_jenis->pack_start(m_Columns.nama_jenis);
	
	MYQ.Close();
}
