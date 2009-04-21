// generated 2008/8/4 9:28:45 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_koneksi_sumber.cc_new

// This file is for your program, I won't touch it again!

#include <config.h>
#include <gtkmm/main.h>
#include <glib/gi18n.h>

#include "dlg_koneksi_sumber.hh"

dlg_koneksi_sumber::dlg_koneksi_sumber()
{
	
	no_port_sekarang=0;
	id_sumber_data=0;
	row_konek_sumber=false;
	//isikan ke list
	m_refCombo = Gtk::ListStore::create(m_combo_port);
	combo_port->set_model(m_refCombo);
	Gtk::TreeModel::Row row,row_tampil;
	
	for(int i=0;i<5;i++)
	{
			//Glib::ustring::compose("Sumber %1",i);
		row=*(m_refCombo->append());
		
		if(i==0)row_tampil=row; //simpan row pertama
		
		//Nomer urut di list
		row[m_combo_port.m_col_nomer]=i+1;	
		row[m_combo_port.m_col_port]=Glib::ustring::compose("Port/Board no %1",i+1);
	}
	
	combo_port->pack_start(m_combo_port.m_col_port);
	combo_port->set_active(row_tampil);
	
	
	//Buat timer refresh data
	//id_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this,
    //         &dlg_koneksi_sumber::on_refresh_data), 1000);
}

bool dlg_koneksi_sumber::ReloadList(int port)
{
	printf(" |--* dlg_koneksi_sumber->ReloadList(int port:%d) id_sumber:%d\n",port,this->id_sumber_data);	
	
	if(!(this->id_sumber_data))
		return false;
	
	if(!MYQ.isConnected)
	{
		if(MYQ.init_lengkap()==1)
		{
			printf("Gagal melakukan inisialisasi database\n");
			return false;
		}
	}
	//Sampai disini database harusnya sudah konek
	
	int id_titik,jumlah_kanal,ijumlah_titik,ikanal;
	bool ada_cocok;
	Glib::ustring nama_titik_temp[30],nama_mesin_temp[30],id_titik_temp[30];;
	
	Glib::ustring uNamaTitik,snomer_kanal,usTemp,usQuery;
	
	m_refSumberModel = Gtk::ListStore::create(m_konek_sumber);
	treeview2->set_model(m_refSumberModel);
	Gtk::TreeModel::Row row;
	bool ada_data_lho=false;
	
	//Query mencari jumlah kanal
	jumlah_kanal=10; //default
	
	//Query mengisi tabel
	usQuery=Glib::ustring::compose(
			"SELECT * FROM titik_ukur JOIN equipment on equipment.id_equipment=titik_ukur.id_equipment WHERE sumber_data='%1' AND no_port='%2'",
			this->id_sumber_data,port);					   
	
	strcpy(MYQ.Text,usQuery.c_str());
	printf(" |--* Query: %s\n",usQuery.c_str());
	if(MYQ.Query())
	{
		printf("error saat query\n");
		
		Gtk::MessageDialog dialog(*this, "Gagal koneksi ke database");
		dialog.set_secondary_text("Periksa parameter koneksi database");

		dialog.run();
		this->hide();
		return false;
	}
		
	ijumlah_titik=MYQ.jum_row;
	printf(" |--* Cari nama titik (jumlah_titik=%d)\n",ijumlah_titik);
	for(int i=0;i<ijumlah_titik;i++)
	{
		printf(" |  |--* %d\n",i);
		
		//cari titik ukur yang bersesuaian
		usTemp=Glib::ustring::compose("%1",i);
		snomer_kanal=MYQ.ambil_string("no_kanal");
		
		printf(" |  |--* no_kanal: %s\n",snomer_kanal.c_str());
		
		try
		{
			ikanal=atoi(snomer_kanal.c_str())-1;
		}
				catch(...)
		{
			ikanal=-1;
		}
		
		if(ikanal>=0)
		{
			nama_titik_temp[ikanal]=MYQ.ambil_string("nama_titik");
			nama_mesin_temp[ikanal]=MYQ.ambil_string("nama_equipment");
			id_titik_temp[ikanal]=MYQ.ambil_string("id_titik");
		}
		else 
			nama_titik_temp[i]="";	
		
		MYQ.Next();
	}	
	MYQ.Buang();
	
	//Init variabel, asumsi semua kosong
	printf(" |--* Isi list view. jumlah kanal=%d\n",jumlah_kanal);
	for(int i=0;i<jumlah_kanal;i++)
	{
		printf(" |  |--* kanal %d: %s\n",i,nama_titik_temp[i].c_str());
		row =*(m_refSumberModel->append());
		
		row[m_konek_sumber.m_col_nomer]=i+1;
		
		row[m_konek_sumber.m_col_nama_titik]=nama_titik_temp[i];
		row[m_konek_sumber.m_col_nama_mesin]=nama_mesin_temp[i];
		
		if(id_titik_temp[i]!="")
		{
			usQuery="SELECT * FROM data_jaman WHERE id_titik='" + id_titik_temp[i] 
				+ "' ORDER BY waktu DESC LIMIT 1";
			
			strcpy(MYQ.Text,usQuery.c_str());
			
			if(MYQ.Query())
			{
				printf("ERROR:\n");
				return false;
			}
			
			if(MYQ.jum_row==1)
			{
				row[m_konek_sumber.m_col_data_last]=MYQ.ambil_string("data");
				ada_data_lho=true;
			}
			MYQ.Buang();
		}
	}
	
	if(!row_konek_sumber)
	{
		treeview2->append_column("Kanal",m_konek_sumber.m_col_nomer);
		treeview2->append_column("Nama Titik",m_konek_sumber.m_col_nama_titik);
		treeview2->append_column("Mesin",m_konek_sumber.m_col_nama_mesin);
		
		if(ada_data_lho)
			treeview2->append_column("Data Terakhir",m_konek_sumber.m_col_data_last);
		row_konek_sumber=true;
	}	
	//treeview2->set_editable(false);
	printf(" |--* Selesai: bersihkan database\n");
	no_port_sekarang=port;
	//MYQ.Close();
	return true;
}

void dlg_koneksi_sumber::on_combo_port_changed()
{
	if(!MYQ.isConnected)
		return;
	
	printf("combo change\n");
	Gtk::TreeModel::iterator iter = combo_port->get_active();
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  
		if(row)
	  	{
		//Get the data for the selected row, using our knowledge of the tree
		int id = row[m_combo_port.m_col_nomer];
		Glib::ustring nama=row[m_combo_port.m_col_port];
		  
		printf("-m_col_id: %d\n-m_col_name: %s\n",id,nama.c_str());
		  
		no_port_sekarang=row[m_combo_port.m_col_nomer];  
		
		this->ReloadList(no_port_sekarang);
	  	} 
	}
}

void  dlg_koneksi_sumber::on_okbutton1_clicked()
{
	this->hide();
}

bool dlg_koneksi_sumber::on_refresh_data()
{
	this->ReloadList(no_port_sekarang);
	return true;
}

