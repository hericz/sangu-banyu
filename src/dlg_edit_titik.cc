// generated 2008/8/1 0:11:57 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_titik.cc_new

// This file is for your program, I won't touch it again!

#include <config.h>
#include <gtkmm/main.h>
#include <glib/gi18n.h>

#include "dlg_edit_titik.hh"



dlg_edit_titik::dlg_edit_titik()
{
	item_index_combo_sumber=0;
	item_index_combo_nomer_board=0;
	item_index_combo_kanal=0;
	
	id_sumber=0;
	id_port=0;
	id_kanal=0;
	
	id_equipment=0;
	id_group=0;
	jumlah_kanal=10;
	//this->ReloadCombo (COMBO_SEMUA);
	
	//combo_sumber->set_sensitive(false);
}

void dlg_edit_titik::on_combo_sumber_changed()
{
	printf("combo change\n");
	if(id_titik==0)
		return;
	
	Gtk::TreeModel::iterator iter = combo_sumber->get_active();
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  if(row)
	  {
		//Get the data for the selected row, using our knowledge of the tree
		int id = row[m_Columns.m_col_id];
		Glib::ustring nama=row[m_Columns.m_col_name];
		  
		printf("-m_col_id: %d\n-m_col_name: %s\n",id,nama.c_str());
		  
		item_index_combo_sumber=row[m_Columns.m_index];  
	  }
	}
	MYQ.Close();
}

void dlg_edit_titik::ReloadCombo(int id_combo)
{	
	Glib::ustring uTemp,usQuery,unama_sumber;
	Gtk::TreeModel::Row row,row_tampil;
	Gtk::TreeModel::iterator iter;
	
	int array_ijumlah_kanal[30];
	int iTemp;
	
	printf("[Reload Combo]\n");
	if(!MYQ.init_lengkap()) //gagal inisialisasi database
	{
		printf("Gagal inisialisasi database\n");
		return;
	}
	
	
	if((id_combo==COMBO_SUMBER)||(id_combo==COMBO_SEMUA))
	{
		printf(" |--* Combo Sumber. id_sumber: %d\n",id_sumber);
		//Combo Nama Sumber
		//database
		usQuery="SELECT * FROM sumber_data";
		strcpy(MYQ.Text,usQuery.c_str());
		
		if(MYQ.Query())
		{
			//ERROR
			printf("Gagal saat melakukan query ke database\n");
			return;
		}
		
		int jumlah_sumber=MYQ.jum_row;
		
		//isikan ke list
		m_refTreeModel = Gtk::ListStore::create(m_Columns);
		combo_sumber->set_model(m_refTreeModel);
		
		//baris pertama adalah: "<pilih sumber data>"
		row=*(m_refTreeModel->append());
		row[m_Columns.m_index]=0;
		row[m_Columns.m_col_name]="<pilih sumber data>";
		row[m_Columns.m_col_id]=0;
		row_tampil=row;	
		
		for(int i=0;i<jumlah_sumber;i++)
		{
				//Glib::ustring::compose("Sumber %1",i);
			row=*(m_refTreeModel->append());
			
			//Nomer urut di list
			row[m_Columns.m_index]=i+1;	
			//Data
			unama_sumber=MYQ.ambil_string("nama_sumber");
			row[m_Columns.m_col_name] = unama_sumber ;
			uTemp=MYQ.ambil_string("id_sumber");
			iTemp=atoi(uTemp.c_str());
			row[m_Columns.m_col_id]=iTemp;
			
			uTemp=MYQ.ambil_string("jum_kanal");
			array_ijumlah_kanal[i]=atoi(uTemp.c_str());
			
			
			printf(" |--* [%d](%s)jumlah_kanal: %d\n",i,unama_sumber.c_str(),jumlah_kanal);
			
			if((iTemp==id_sumber)&&(iTemp>0)) //item_index_combo_sumber)
			{
				row_tampil=row;
				printf(" |--|-- id_sumber=%d, iTemp=%d\n",id_sumber,iTemp);
			}
			MYQ.Next();//row = *iter;
		}

		//combo_sumber->set_text_column(m_Columns.m_col_name);
		combo_sumber->pack_start(m_Columns.m_col_name);
		iter=row_tampil;
		
		combo_sumber->set_active(iter);
	}
	//SELESAI ISI Combo Sumber
	
	printf(" |--* Combo no Board\n");
	//ISI Combo_nomer_board
	if((id_combo==COMBO_NOMER_BOARD)||(id_combo==COMBO_SEMUA))
	{
		//Isikan datanya
		m_refTreeModel2 = Gtk::ListStore::create(m_Columns);
		combo_nomer_board->set_model(m_refTreeModel2);
		
		//isi combo_nomer_board 
		row=*(m_refTreeModel2->append());
		row[m_Columns.m_index]=0;
		row[m_Columns.m_col_name] ="<pilih nomer board>" ;
		row[m_Columns.m_col_id]=0;
		row_tampil=row;
		
		for(int i=1;i<=5;i++) //JUMLAH BOARD/PORT maksimum 5
		{
			uTemp=Glib::ustring::compose("Board %1",i);
			row=*(m_refTreeModel2->append());
			
			//Nomer urut di list
			row[m_Columns.m_index]=i;
			
			//Data
			row[m_Columns.m_col_name] = uTemp ;
			row[m_Columns.m_col_id]=i;
			
			if(i==id_port)
			{
				row_tampil=row;
			}
		}

		combo_nomer_board->pack_start(m_Columns.m_col_name);

		iter=row_tampil;
		
		combo_nomer_board->set_active(iter);
	}//Selesai isi kombo nomer board
	
	printf(" |--* Combo no kanal\n");
	//Combo Nomer Kanal
	if((id_combo==COMBO_NO_KANAL)||(id_combo==COMBO_SEMUA))
	{
		//jumlah_kanal=array_ijumlah_kanal[i];
		jumlah_kanal=30;
		//combo nomer kanal
		m_refTreeModel3 = Gtk::ListStore::create(m_Columns);
		combo_kanal->set_model(m_refTreeModel3);
		
		row=*(m_refTreeModel3->append());
		row[m_Columns.m_index]=0;
		row[m_Columns.m_col_name] ="<pilih nomer kanal>" ;
		row[m_Columns.m_col_id]=0;
		row_tampil=row;
		
		for(int i=0;i<jumlah_kanal;i++)
		{
			uTemp=Glib::ustring::compose("Kanal %1",i+1);
			row=*(m_refTreeModel3->append());
			//if(i==0)row_tampil=row; //simpan row pertama
			//Nomer urut di list
			row[m_Columns.m_index]=i+1;
			
			//Data
			row[m_Columns.m_col_name] = uTemp ;
			row[m_Columns.m_col_id]=i+1;
			
			if(id_kanal==i+1)
			{
				row_tampil=row;
			}
		}

		combo_kanal->pack_start(m_Columns.m_col_name);

		iter=row_tampil;
		
		combo_kanal->set_active(iter);
	}
	
	
	
	show_all_children();
	
	MYQ.Buang();
	MYQ.Close();
}

void dlg_edit_titik::isi_form()
{
	printf("Reload Data\n");
	Glib::ustring usQuery,usTemp;
	
	
	if(!MYQ.init_lengkap())
	{
		printf("ERROR: Gagal inisialisasi database\n");
		return;
	}
	
	//Cek apakah sudah ada id_titik
	if(!id_titik)
	{
		//printf("ERROR: Identitas titik belum ditentukan!\n");
		//Isi dengan data baru (generate nama titik)
		usQuery="SELECT MAX(id_titik) as max FROM monita_db.titik_ukur";
		strcpy(MYQ.Text,usQuery.c_str());
		
		MYQ.Query();
		if(MYQ.jum_row==1)
		{
			usTemp=MYQ.ambil_string("max");
			this->entry_nama_titik->set_text("Titik " + usTemp);
			
			this->entry_kode_titik->set_text("TTK_"+usTemp);
		}
		else
		{
			this->entry_nama_titik->set_text("Titik 0");
			this->entry_kode_titik->set_text("TTK_0");
		}
		
		MYQ.Buang();
		return;
	}
	
	//Sampai disini berarti titik sudah ada
	printf("Buat Query:");
	usQuery=Glib::ustring::compose("SELECT * FROM titik_ukur WHERE id_titik ='%1'",id_titik);
	strcpy(MYQ.Text,usQuery.c_str());
	
	printf(" %s\n",usQuery.c_str());
	MYQ.Query();
	
	//Cek duplicate
	if(MYQ.jum_row>1)
	{
		printf("ERROR: Duplikat entry untuk id_titik = %d",id_titik);
		return;
	}
	
	if(MYQ.jum_row<1)
	{
		printf("ERROR: Tidak ditemukan entry untuk id_titik = %d",id_titik);
		return;
	}	
	
	printf("Mulai isikan data\n");
	//Sampai sini berarti OK
	
	/*Tab 1: Informasi Titik*/
	usTemp=MYQ.ambil_string("nama_titik");
	printf(" - nama titik: %s\n",usTemp.c_str());
	this->entry_nama_titik->set_text(usTemp);
	
	usTemp=MYQ.ambil_string("kode_titik");
	printf(" - kode titik: %s\n",usTemp.c_str());
	this->entry_kode_titik->set_text(usTemp);
	
	usTemp=MYQ.ambil_string("satuan");
	printf(" - satuan: %s\n",usTemp.c_str());
	this->entry_satuan->set_text(usTemp);
	
	//usTemp=MYQ.ambil_string("keterangan");
	//printf(" - keterangan %s\n",usTemp.c_str());
	//this->entry_informasi->set_text(usTemp);
	
	/*Tab 2: Sumber Data*/
	//Dilakukan dari ReloadCombo
	
	/*Tab : Kalibrasi*/
	usTemp=MYQ.ambil_string("kalibrasi_a");
	entry_kalib_a->set_text(usTemp);
	kalibrasi_a=strtod(usTemp.c_str(),NULL);
	
	usTemp=MYQ.ambil_string("kalibrasi_b");
	entry_kalib_b->set_text(usTemp);
	kalibrasi_b=strtod(usTemp.c_str(),NULL);
	
	/*--------------------- ALARM SETTING ---------------------------------*/
	/*Tab 3: Range dan Alarm*/
	double d_range_min,d_range_maks;
	int i_range_min,i_range_maks;
	int alarm_setting;
	bool b_min_enabled,b_min_min_enabled,b_max_enabled,b_max_max_enabled;
	
	// ISI KOMBO ALARM
	usTemp=MYQ.ambil_string("alarm_setting");
	alarm_setting=atoi(usTemp.c_str());
	
	b_min_min_enabled=alarm_setting&&0x01;
	b_min_enabled= alarm_setting&&0x02;
	b_min_enabled=alarm_setting && 0x04;
	b_min_enabled=alarm_setting &&0x10;
	
	printf(" |-- Alarm setting:\n");
	printf(" |--|-- alarm_min_min: %d\n",b_min_min_enabled);
	printf(" |--|-- alarm_min: %d\n",b_min_min_enabled);
	printf(" |--|-- alarm_max: %d\n",b_max_enabled);
	printf(" |--|-- alarm_max_max: %d\n",b_max_max_enabled);
	
	printf(" |-- Isikan ke combo \n");
	
	//Alarm min 
	m_refAlarm_min = Gtk::ListStore::create(m_alarm);
	
	combo_alarm_min->set_model(m_refAlarm_min);
	combo_alarm_min->pack_start(m_alarm.nama_alarm);

	combo_alarm_min_min->set_model(m_refAlarm_min); 
	combo_alarm_min_min->pack_start(m_alarm.nama_alarm);
	
	combo_alarm_max->set_model(m_refAlarm_min); 
	combo_alarm_max->pack_start(m_alarm.nama_alarm);

	combo_alarm_max_max->set_model(m_refAlarm_min); 
	combo_alarm_max_max->pack_start(m_alarm.nama_alarm);
	
	printf(" |-- Isi combo action alarm\n");
	//isi 	
	Gtk::TreeModel::Row row,row_tampil;
	Gtk::TreeModel::iterator iter;
	
	//0: <none>
	row=*(m_refAlarm_min->append());
	
	row[m_alarm.id_action]=0;
	
	row[m_alarm.nama_alarm]="<pilih alarm>";
	row[m_alarm.kode_alarm]="none";
	row[m_alarm.jenis_alarm]=0;
	row_tampil=row;
	
	//1: <sms>
	row=*(m_refAlarm_min->append());
	row[m_alarm.id_action]=1; 
	row[m_alarm.nama_alarm]="SMS";
	row[m_alarm.kode_alarm]="sms";
	row[m_alarm.jenis_alarm]=0;
	
	
	//2: <email>
	row=*(m_refAlarm_min->append());
	row[m_alarm.id_action]=2;
	row[m_alarm.nama_alarm]="E-mail";
	row[m_alarm.kode_alarm]="email";
	row[m_alarm.jenis_alarm]=0;
	
	//3: <aplikasi>
	row=*(m_refAlarm_min->append());
	row[m_alarm.id_action]=3;
	row[m_alarm.nama_alarm]="Aplikasi";
	row[m_alarm.kode_alarm]="app_alarm";
	row[m_alarm.jenis_alarm]=0;
	
	printf(" |-- Set nilai yang aktif\n");
	//combo_alarm_min->pack_start(m_alarm.nama_alarm);
	iter=row_tampil;
	combo_alarm_min->set_active(iter);
	combo_alarm_min_min->set_active(iter);
	combo_alarm_max->set_active(iter);
	combo_alarm_max_max->set_active(iter);
	//}
	
	printf(" |-- Set min alarm\n");
	usTemp=MYQ.ambil_string("range_min");
	printf(" - range min: %s\n",usTemp.c_str());
	i_range_min=atoi(usTemp.c_str());
	this->spin_range_min->set_value(i_range_min);
	
	usTemp=MYQ.ambil_string("range_max");
	printf(" - range max: %s\n",usTemp.c_str());
	i_range_maks=atoi(usTemp.c_str());
	this->spin_range_maks->set_value(i_range_maks);
	
	usTemp=MYQ.ambil_string("alarm_low2");
	printf(" - alarm min min: %s\n",usTemp.c_str());
	this->spin_alarm_min_min->set_range(i_range_min,i_range_maks);
	this->spin_alarm_min_min->set_value(atoi(usTemp.c_str()));
	
	usTemp=MYQ.ambil_string("alarm_low1");
	printf(" - alarm min: %s\n",usTemp.c_str());
	this->spin_alarm_min->set_range(i_range_min,i_range_maks);
	this->spin_alarm_min->set_value(atoi(usTemp.c_str()));
	
	usTemp=MYQ.ambil_string("alarm_high1");
	printf(" - alarm maks : %s\n",usTemp.c_str());
	this->spin_alarm_maks->set_range(i_range_min,i_range_maks);
	this->spin_alarm_maks->set_value(atoi(usTemp.c_str()));
	
	usTemp=MYQ.ambil_string("alarm_high2");
	printf(" - range maks maks: %s\n",usTemp.c_str());
	this->spin_alarm_maks_maks->set_range(i_range_min,i_range_maks);
	this->spin_alarm_maks_maks->set_value(atoi(usTemp.c_str()));
	
	/*---------------------EOF ALARM SETTING ---------------------------------*/
	
	//Sumber data
	printf("-Ambil id sumber data\n");
	usTemp=MYQ.ambil_string("sumber_data");
	try{
		id_sumber=atoi(usTemp.c_str());
		printf("--id_port:%d\n",id_sumber);
	}
	catch(...)
	{
		id_sumber=0;
	}
	
	printf("-Ambil id no_port\n");
	usTemp=MYQ.ambil_string("no_port");
	try{
		id_port=atoi(usTemp.c_str());
		printf("--id_port=%d\n",id_port);
	}
	catch(...)
	{
		id_port=0;
	}
	
	printf("-Ambil id no_kanal\n");
	usTemp=MYQ.ambil_string("no_kanal");
	try{
		id_kanal=atoi(usTemp.c_str());
		printf(" --id_kanal=%d\n",id_kanal);
	}
	catch(...)
	{
		id_kanal=0;
	}
	
	MYQ.Buang();
	
	MYQ.Close();
	printf("Selesai Reload Data\n");
	//ReloadCombo(COMBO_SEMUA);
}

//Simpan Data
void dlg_edit_titik::UpdateData()
{
	printf(" |--* Update Data\n");
	
	char sTemp[512];
	
	Glib::ustring usQuery,usTemp;
	Glib::ustring uNamaTitik,uKodeTitik,uSatuan;
	int iSumberData,iNoPort,iNoKanal;
	double dTemp;
	//tes apakah sudah ada id-titik
	if(!id_titik)
	{
		printf(" |--|--* ERROR: Identitas titik belum ditentukan!\n");
		return;
	}
	
	//Ambil data dari dialog
	uNamaTitik=this->entry_nama_titik->get_text();
	uKodeTitik=this->entry_kode_titik->get_text();
	uSatuan=this->entry_satuan->get_text();
	
	//Ambil data informasi sumber data
	//ID Sumber data
	Gtk::TreeModel::iterator iter = combo_sumber->get_active();
	iSumberData=0;
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  if(row)
	  {
		//Get the data for the selected row, using our knowledge of the tree
		iSumberData= row[m_Columns.m_col_id];
		//Glib::ustring nama=row[m_combo_port.m_col_port];
	  }
	}
	
	//ID Port
	iter = combo_nomer_board->get_active();
	iNoPort=0;
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  if(row)
	  {
		//Get the data for the selected row, using our knowledge of the tree
		iNoPort= row[m_Columns.m_col_id];
		//Glib::ustring nama=row[m_combo_port.m_col_port];
	  }
	}
	
	//ID No kanal
	iter = combo_kanal->get_active();
	iNoKanal=0;
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  if(row)
	  {
		//Get the data for the selected row, using our knowledge of the tree
		iNoKanal= row[m_Columns.m_col_id];
		//Glib::ustring nama=row[m_combo_port.m_col_port];
	  }
	}
	
	/*Tab 3: Range dan Alarm*/
	double d_range_min,d_range_maks,d_alarm_min,d_alarm_min_min,d_alarm_maks,d_alarm_maks_maks;
	int id_action,jenis_alarm;
	bool alarm_aktif=false;
	
	d_range_maks=spin_range_maks->get_value();
	d_range_min=spin_range_min->get_value();
	d_alarm_min_min=spin_alarm_min_min->get_value();	
	//actionnya
	//0. cek apakah enable?
	if(check_alarm_min_min->get_active())
	{
		alarm_aktif=true;	
		printf(" |-- Alarm enabled\n");
		//1. cek waktunya
		double d_waktu_min_min=spin_alarm_time_min_min->get_value();
		printf(" |--|-- waktu: %0.2f\n",d_waktu_min_min);
		
		//2. cek jenis action
		iter = combo_alarm_min_min->get_active();
		iNoKanal=0;
		if(iter)
		{
		  Gtk::TreeModel::Row row = *iter;
		  if(row)
		  {
			//Get the data for the selected row, using our knowledge of the tree
			jenis_alarm= row[m_alarm.jenis_alarm];
			printf(" |--|-- jenis alarm: %d\n",jenis_alarm);
			//Glib::ustring nama=row[m_combo_port.m_col_port];
			id_action=row[m_alarm.id_action];
		  }
		}
		
		//3. cek tujuan actionnya
		Glib::ustring usAction=entry_action_min_min->get_text();
		printf(" |--|-- Action : %s\n", usAction.c_str());
	}
	else
		printf(" |-- Alarm disabled\n");
	
	
	// Alarm yang lainnya
	d_alarm_min=spin_alarm_min->get_value();
	d_alarm_maks=spin_alarm_maks->get_value();
	d_alarm_maks_maks=spin_alarm_maks_maks->get_value();
	

	//Cek entri form
	if(uNamaTitik=="")
	{
		Gtk::MessageDialog dialog(*this, "Nama Titik tidak boleh kosong");
		
		dialog.run();
		return ;
	}
	
	//Cek entri kalibrasi
	//harus angka beneran, kalau tidak set ke nilai sebelumnya
	try{
		usTemp=this->entry_kalib_a->get_text();
		dTemp=strtod(usTemp.c_str(),NULL);
		kalibrasi_a_baru=dTemp;
	}
	catch(...)
	{
		kalibrasi_a_baru=kalibrasi_a;
	}
	
	try{
		usTemp=this->entry_kalib_b->get_text();
		dTemp=strtod(usTemp.c_str(),NULL);
		kalibrasi_b_baru=dTemp;
	}
	catch(...)
	{
		kalibrasi_b_baru=kalibrasi_b;
	}
	
	//Buat query string
	sprintf(sTemp,
				"UPDATE titik_ukur SET nama_titik='%s',kode_titik='%s',satuan='%s',sumber_data='%d',no_port='%d',no_kanal='%d'",
				uNamaTitik.c_str(),uKodeTitik.c_str(),uSatuan.c_str(),iSumberData,iNoPort,iNoKanal);
	sprintf(sTemp,"%s,range_min='%0.2f',range_max='%0.2f',alarm_low1='%0.2f',alarm_low2='%0.2f',alarm_high1='%0.2f',alarm_high2='%0.2f'",
			sTemp,d_range_min,d_range_maks,d_alarm_min,d_alarm_min_min,d_alarm_maks,d_alarm_maks_maks);
	sprintf(sTemp,"%s ,kalibrasi_a='%0.2f',kalibrasi_b='%0.2f'",
			sTemp,kalibrasi_a_baru,kalibrasi_b_baru);
	sprintf(sTemp,"%s WHERE id_titik='%d'",sTemp,id_titik);
	printf(" |--|--* Query: %s\n",sTemp);
	if(MYQ.init_lengkap())
	{
		printf("|--|--|--* Update Database...");
		strcpy(MYQ.Text,sTemp);
		
		if(!MYQ.Update())
		{
			printf("OK\n");
			
			MYQ.Close();
		}
	}
	else
	{
		printf("|--|--|--* Gagal melakukan koneksi ke database\n");
	}
}

void dlg_edit_titik::TambahData()
{
	printf("[Tambah Data]\n");
	char sTemp[512];
	
	Glib::ustring usQuery,usTemp;
	Glib::ustring uNamaTitik,uKodeTitik,uSatuan;
	int iSumberData,iNoPort,iNoKanal;
	double dTemp;
	//Pastikan belum ada id_titik
	if(id_titik)
	{
		printf(" |--* ERROR: Identitas titik sudah ditentukan!\n");
		return;
	}
	
	//Ambil data dari dialog
	uNamaTitik=this->entry_nama_titik->get_text();
	uKodeTitik=this->entry_kode_titik->get_text();
	uSatuan=this->entry_satuan->get_text();
	
	//Ambil data informasi sumber data
	//ID Sumber data
	Gtk::TreeModel::iterator iter = combo_sumber->get_active();
	iSumberData=0;
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  if(row)
	  {
		//Get the data for the selected row, using our knowledge of the tree
		iSumberData= row[m_Columns.m_col_id];
		//Glib::ustring nama=row[m_combo_port.m_col_port];
	  }
	}
	
	//ID Port
	iter = combo_nomer_board->get_active();
	iNoPort=0;
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  if(row)
	  {
		//Get the data for the selected row, using our knowledge of the tree
		iNoPort= row[m_Columns.m_col_id];
		//Glib::ustring nama=row[m_combo_port.m_col_port];
	  }
	}
	
	//ID No kanal
	iter = combo_kanal->get_active();
	iNoKanal=0;
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  if(row)
	  {
		//Get the data for the selected row, using our knowledge of the tree
		iNoKanal= row[m_Columns.m_col_id];
		//Glib::ustring nama=row[m_combo_port.m_col_port];
	  }
	}
	
		try{
		usTemp=this->entry_kalib_a->get_text();
		dTemp=strtod(usTemp.c_str(),NULL);
		kalibrasi_a_baru=dTemp;
	}
	catch(...)
	{
		kalibrasi_a_baru=1;
	}
	
	try{
		usTemp=this->entry_kalib_b->get_text();
		dTemp=strtod(usTemp.c_str(),NULL);
		kalibrasi_b_baru=dTemp;
	}
	catch(...)
	{
		kalibrasi_b_baru=0;
	}
	
	//Buat query string
	sprintf(sTemp,
				"INSERT INTO titik_ukur (id_equipment,id_group_titik_ukur,nama_titik,kode_titik,satuan,sumber_data,no_port,no_kanal,kalibrasi_a,kalibrasi_b)");
	sprintf(sTemp,"%s VALUES('%d','%d','%s','%s','%s','%d','%d','%d','%0.2f','%0.2f')",sTemp,id_equipment,id_group,
				uNamaTitik.c_str(),uKodeTitik.c_str(),uSatuan.c_str(),iSumberData,iNoPort,iNoKanal,kalibrasi_a_baru,kalibrasi_b_baru);
	//sprintf(sTemp,"%s WHERE id_titik='%d'",sTemp,id_titik);
	printf(" |--* Query: %s\n",sTemp);
	if(MYQ.init_lengkap())
	{
		printf("|--|--* Tambah titik ukur ke Database...");
		strcpy(MYQ.Text,sTemp);
		
		if(!MYQ.Insert())
		{
			printf("OK\n");
			
			MYQ.Close();
		}
	}
	else
	{
		printf("|--|--|--* Gagal melakukan koneksi ke database\n");
	}
	MYQ.Close();
}

void dlg_edit_titik::on_okbutton1_clicked()
{
	printf("[on_okbutton1_clicked]\n");		
	
	//Cek entri form
	Glib::ustring uNamaTitik=this->entry_nama_titik->get_text();
	if(uNamaTitik=="")
	{
		Gtk::MessageDialog dialog(*this, "Nama Titik tidak boleh kosong");
		
		dialog.run();
		return ;
	}
	
	if((id_titik==0)&&(id_equipment>0))
	{
		this->TambahData ();	
	}
	else if(id_titik>0)
	{
		this->UpdateData();
	}
	printf("[/on_okbutton1_clicked]\n");	
}
