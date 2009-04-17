// generated 2008/8/8 16:42:57 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_posting_data.cc_new

// This file is for your program, I won't touch it again!

#include <config.h>
#include <gtkmm/main.h>
#include <glib/gi18n.h>

#include "dlg_posting_data.hh"

dlg_posting_data::dlg_posting_data ()
{
	printf("[Inisialisasi dlg_posting_data]\n");
	list_ada_kolom=false;
	jumlah_aktif=0;
}

void dlg_posting_data::ReloadList()
{
	Glib::ustring sQuery,sTemp;
	int jumlah_post,iTemp, jumlah_aktif=0;
	
	printf("[dlg_posting data reload_list]\n");
	
	m_refTreeModel = Gtk::TreeStore::create(m_posting);
	
	tree_posting->set_model(m_refTreeModel);
	
	printf("MYQ.server:%s\n",MYQ.server);
	
	
	if(MYQ.init_lengkap()==1)
	{
		printf("init db sukses\n");		
		
		sQuery="SELECT * FROM posting_data";
		
		strcpy(MYQ.Text,sQuery.c_str());
		
		MYQ.Query();
		
		jumlah_post=MYQ.jum_row;
		if(jumlah_post>0)
		{
			jumlah_aktif=0;
			for(int i=0;i<jumlah_post;i++)
			{
				Gtk::TreeModel::Row row =*(m_refTreeModel->append());
				
				row[m_posting.m_col_nomer]=i;			
				
				sTemp=MYQ.ambil_string("nama_post");
				row[m_posting.m_col_nama_post] = sTemp;
				printf("--Nama sumber %d: %s\n",i,sTemp.c_str());
				
				sTemp=MYQ.ambil_string("flag");
				iTemp=atoi(sTemp.c_str());
				row[m_posting.m_col_flag]=iTemp;
				printf("--Flag : %d\n",iTemp);
				
				sTemp=MYQ.ambil_string("id_post");
				iTemp=atoi(sTemp.c_str());
				row[m_posting.m_col_id] = iTemp;
				printf("--id_post: %d\n",iTemp);
				
				sTemp=MYQ.ambil_string("alamat_ip");
				row[m_posting.m_col_alamat_ip] = sTemp;
				printf("--alamat ip: %s\n",sTemp.c_str());
				
				sTemp=MYQ.ambil_string("no_gsm");
				row[m_posting.m_col_no_gsm] = sTemp;
				printf("--no_gsm: %s\n",sTemp.c_str());
				
				sTemp=MYQ.ambil_string("port");
				row[m_posting.m_col_port] = sTemp;
				printf("--ip_port: %s\n",sTemp.c_str());
				
				sTemp=MYQ.ambil_string("periode");
				iTemp=atoi(sTemp.c_str());
				row[m_posting.m_col_periode]= iTemp;
				printf("--periode: %d\n",iTemp);
				
				sTemp=MYQ.ambil_string("status");
				printf("--status: %s\n",sTemp.c_str());
				if(sTemp=="1")
				{
					row[m_posting.m_col_status]= "aktif";
				}
				else
				{
					row[m_posting.m_col_status]= "non-aktif";
					jumlah_aktif++;
				}

				
				sTemp=MYQ.ambil_string("keterangan");
				row[m_posting.m_col_keterangan] = sTemp;
				printf("--keterangan: %d\n",sTemp.c_str());
				
				MYQ.Next();
			}
			
			if(list_ada_kolom==false)
			{
				tree_posting->append_column("No.",m_posting.m_col_nomer);
				tree_posting->append_column("Nama Post", m_posting.m_col_nama_post);
				tree_posting->append_column("Alamat/Nomer", m_posting.m_col_alamat_ip);
				tree_posting->append_column("ID", m_posting.m_col_id);	
				tree_posting->append_column("Status",m_posting.m_col_status);
				list_ada_kolom=true;
			}
		}
		
		MYQ.Buang();
	}
	else
	{
		printf("init db gagal\n");
		//catat_log("init db gagal",0);
		Gtk::MessageDialog dialog(*this, "Database belum terkoneksi");
  		dialog.set_secondary_text("Periksa parameter koneksi database");

  		dialog.run();
		return;
	}
	
	//Update informasi di label info
	//sTemp=Glib::ustring::compose("Jumlah: %1\nAktif: %2",jumlah_sumber,jumlah_aktif);
	//this->label_info->set_text(sTemp);*/
	printf(" |--Selesai ReloadList ()\n");
	MYQ.Close();
	return;
}

void dlg_posting_data::on_button_tambah_clicked()
{
	printf("[dlg_posting_data::on_button_tambah_clicked]\n");
	
	int result,iTemp;;
	int id_post=0;
	Glib::ustring usQuery,usTemp;
	char sTemp[512];

	
	//Sudah bisa inisialisasi dlg edit post
	dlg_edit_post* edit_post=new dlg_edit_post();
	
	//ambil datanya dan isi variabelnya
	usTemp="Post";//row[m_posting.m_col_nama_post];
	edit_post->entry_nama_post->set_text(usTemp);
	printf(" |-- Nama_post:%s\n",usTemp.c_str());
	
	//IP Address"
	usTemp="192.168.1.";//row[m_posting.m_col_alamat_ip];
	edit_post->entry_ip_address->set_text(usTemp);
	
	//IP Port
	usTemp="5001";//Glib::ustring::compose("%1",row[m_posting.m_col_port]);
	edit_post->entry_ip_port->set_text(usTemp);
	
	//Periode
	iTemp=30;//row[m_posting.m_col_periode];
	
	double dperiode=(double) iTemp;
	edit_post->spin_periode->set_value(dperiode);
	
	//flag (jenis post)
	usTemp="51";//Glib::ustring::compose("%1",row[m_posting.m_col_flag]);
	int flag=atoi(usTemp.c_str());
	
	if(flag==51)
		edit_post->radio_post_localdisplay->set_active(true);
	else if(flag==52)
		edit_post->radio_post_gsm->set_active(true);
	else
		edit_post->radio_post_localdisplay->set_active(true);
	
	//Status
	usTemp="aktif";//row[m_posting.m_col_status];
	if(usTemp=="aktif")
	{
		edit_post->check_post_aktif->set_active(true);
	}
	else 
	{
		edit_post->check_post_aktif->set_active(false);
	}
	
	//keterangan
	usTemp="Keterangan";//row[m_posting.m_col_keterangan];
	edit_post->entry_keterangan->set_text(usTemp);
	printf(" |-- Keterangan:%s\n",usTemp.c_str());
	
	//Bersihkan database setelah tidak dipakai
	
	
	//Tampilkan dialog
	result=edit_post->run();

	switch(result)
	{
		case GTK_RESPONSE_OK:
			printf(" |-- GTK Response OK\n");
			if(edit_post->parameter_changed)
			{
				printf(" +-- Parameter changed, update data\n");
				
				Glib::ustring uNama,uAlamatIP,uNoGSM,uKeterangan,usIpPort;
				int istatus,flag,iPeriode;
				//ambil data-data dari dialog ybs
				uNama=edit_post->entry_nama_post->get_text();
				printf(" |--nama: %s\n",uNama.c_str());
				
				uAlamatIP=edit_post->entry_ip_address->get_text();
				printf(" |--IP: %s\n",uAlamatIP.c_str());
				
				uNoGSM="0";
				uKeterangan=edit_post->entry_keterangan->get_text();
				printf(" |--Ket: %s\n",uKeterangan.c_str());
				
				usIpPort=edit_post->entry_ip_port->get_text();
				printf(" |--Port: %s\n",usIpPort.c_str());
				
				//jenis (flag)
				flag=51;
				printf(" |--Flag: %d\n",flag);
				
				//Periode-
				dperiode=edit_post->spin_periode->get_value();
				iPeriode=(int)dperiode;
				printf(" |--Periode: %d\n",iPeriode);
				
				//status
				if(edit_post->check_post_aktif->get_active())
				{
					istatus=1;
				}
				else
					istatus=0;
				
				printf(" |-- status: %d\n",istatus);
				
				printf(" |--* Buat query\n");
				
				sprintf(sTemp,"INSERT INTO posting_data(nama_post,flag,alamat_ip,port,status,periode,keterangan)");
				//printf("%s VALUES('%s','%d','%s','%s','%d','%d','%s')\n",
				//		sTemp,uNama.c_str(),flag,uAlamatIP.c_str(),usIpPort.c_str(),istatus,iPeriode,uKeterangan.c_str());
				
				sprintf(sTemp,"%s VALUES('%s','%d','%s','%s','%d','%d','%s')",sTemp,
						uNama.c_str(),flag,uAlamatIP.c_str(),usIpPort.c_str(),istatus,iPeriode,uKeterangan.c_str());
				printf(" |-- Query: %s\n",sTemp);
				
				if(!MYQ.isConnected)
				{
					if(!MYQ.init_lengkap())
					{
						printf("Gagal melakukan inisialisasi database\n");
						Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
						dialog.set_secondary_text("Periksa parameter koneksi database");

						dialog.run();
						edit_post->hide();
						return;
					}
				}
				
				strcpy(MYQ.Text,sTemp);
	
				if(MYQ.Insert()!=0)
				{
					printf("Gagal melakukan Insert database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan Insert database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					edit_post->hide();
					return;
				}
				
				MYQ.Close();
				this->ReloadList();
			}
			else
			{
				printf(" +-- Parameter tetap\n");
			}
			
			
		break;
			
		default:
			printf(" |-- GTK Response default\n");
		break;
	}
	edit_post->hide();
	//delete edit_post;
}

void dlg_posting_data::on_button_hapus_clicked()
{
	printf("[dlg_posting_data::on_button_hapus_clicked]\n");
	int result,iTemp;;
	int id_post=0;
	Glib::ustring usQuery,usTemp;
	char sTemp[512];
		
	//Cari tau data mana yang sedang dipilih
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;
	
	int id_sumber_hapus;
	
	refTreeSelection= this->tree_posting->get_selection();
	iter = refTreeSelection->get_selected();
	
	if(!iter) //If nothing is selected
		return;

	row = *iter;

	id_post=row[m_posting.m_col_id];
	
	usTemp= row[m_posting.m_col_nama_post];
	printf(" +-- Hapus posting:  id: %d, nama: %s\n",id_post,usTemp.c_str());
	
	usTemp="Hapus Post Data[" + usTemp + "]?";
	Gtk::MessageDialog dialog(*this,usTemp,
	true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

	dialog.set_secondary_text("Peringatan: Menghapus titik posting data akan \nmenghentikan pengiriman data ke titik ini");
	
	result=dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			printf(" |-- Hapus titik ukur\n");
			//konek database
			if(!MYQ.isConnected)
			{
				if(MYQ.init_lengkap()!=1)
				{
					printf(" |--|-- Gagal melakukan inisialisasi database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					return ;
				}
			}
			
			//hapus titik ukurnya
			sprintf(sTemp,"DELETE FROM posting_data WHERE id_post='%d'",id_post);
			printf(" |-- Query: %s\n",sTemp);
			strcpy(MYQ.Text,sTemp);
			
			MYQ.Delete();
			MYQ.Close();
			this->ReloadList();
	}
}

void dlg_posting_data::on_button_edit_clicked()
{
	int result,iTemp;;
	int id_post=0;
	Glib::ustring usQuery,usTemp;
	char sTemp[512];
	
	printf("[dlg_posting_data::on_button_edit_clicked]\n");
	//Cek apakah ada yang terpilih
	
	//Cari tau data mana yang sedang dipilih
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;
	
	int id_sumber_hapus;
	
	refTreeSelection= this->tree_posting->get_selection();
	iter = refTreeSelection->get_selected();
	
	if(iter) //If anything is selected
	{
		row = *iter;
	  	//Do something with the row.
		id_post=row[m_posting.m_col_id];
		
		usTemp= row[m_posting.m_col_nama_post];
		printf(" +-- Edit posting:  id:%d, nama: %s\n",id_post,usTemp.c_str());	
	}
	else
		return;
	
	//Kalau gak ada keluar saja
	if(!id_post)
		return;
	
	//ambil data dari 
	
	
	//Sampai disini harusnya jum_row==1;
	//Sudah bisa inisialisasi dlg edit post
	dlg_edit_post* edit_post=new dlg_edit_post();
	
	//ambil datanya dan isi variabelnya
	usTemp=row[m_posting.m_col_nama_post];
	edit_post->entry_nama_post->set_text(usTemp);
	printf(" |-- Nama_post:%s\n",usTemp.c_str());
	
	//IP Address"
	usTemp=row[m_posting.m_col_alamat_ip];
	edit_post->entry_ip_address->set_text(usTemp);
	
	//IP Port
	usTemp=Glib::ustring::compose("%1",row[m_posting.m_col_port]);
	edit_post->entry_ip_port->set_text(usTemp);
	
	//Periode
	iTemp=row[m_posting.m_col_periode];
	
	double dperiode=(double) iTemp;
	edit_post->spin_periode->set_value(dperiode);
	
	//flag (jenis post)
	usTemp=Glib::ustring::compose("%1",row[m_posting.m_col_flag]);
	int flag=atoi(usTemp.c_str());
	
	if(flag==51)
		edit_post->radio_post_localdisplay->set_active(true);
	else if(flag==52)
		edit_post->radio_post_gsm->set_active(true);
	else
		edit_post->radio_post_localdisplay->set_active(true);
	
	//Status
	usTemp=row[m_posting.m_col_status];
	if(usTemp=="aktif")
	{
		edit_post->check_post_aktif->set_active(true);
	}
	else 
	{
		edit_post->check_post_aktif->set_active(false);
	}
	
	//keterangan
	usTemp=row[m_posting.m_col_keterangan];
	edit_post->entry_keterangan->set_text(usTemp);
	printf(" |-- Keterangan:%s\n",usTemp.c_str());
	
	//Bersihkan database setelah tidak dipakai
	
	
	//Tampilkan dialog
	result=edit_post->run();

	switch(result)
	{
		case GTK_RESPONSE_OK:
			printf(" |-- GTK Response OK\n");
			if(edit_post->parameter_changed)
			{
				printf(" +-- Parameter changed, update data\n");
				
				Glib::ustring uNama,uAlamatIP,uNoGSM,uKeterangan,usIpPort;
				int istatus,flag,iPeriode;
				//ambil data-data dari dialog ybs
				uNama=edit_post->entry_nama_post->get_text();
				uAlamatIP=edit_post->entry_ip_address->get_text();
				uNoGSM="0";
				uKeterangan=edit_post->entry_keterangan->get_text();
				
				usIpPort=edit_post->entry_ip_port->get_text();
				
				//jenis
				flag=51;
				
				//Periode
				dperiode=edit_post->spin_periode->get_value();
				iPeriode=(int)dperiode;
				
				//status
				if(edit_post->check_post_aktif->get_active())
				{
					istatus=1;
				}
				else
					istatus=0;
				
				sprintf(sTemp,"UPDATE posting_data SET nama_post='%s',flag='%d',alamat_ip='%s',port='%s'",
						uNama.c_str(),flag,uAlamatIP.c_str(),usIpPort.c_str());
				sprintf(sTemp,"%s,status='%d',periode='%d',keterangan='%s' ",sTemp,istatus,iPeriode,uKeterangan.c_str()); 			
				sprintf(sTemp,"%s WHERE id_post='%d'",sTemp,id_post);
				printf(" |-- Query: %s\n",sTemp);
				
				if(!MYQ.isConnected)
				{
					if(!MYQ.init_lengkap())
					{
						printf("Gagal melakukan inisialisasi database\n");
						Gtk::MessageDialog dialog(*this, "Gagal melakukan koneksi database");
						dialog.set_secondary_text("Periksa parameter koneksi database");

						dialog.run();
						edit_post->hide();
						return;
					}
				}
				
				strcpy(MYQ.Text,sTemp);
	
				if(MYQ.Update()!=0)
				{
					printf("Gagal melakukan Update database\n");
					Gtk::MessageDialog dialog(*this, "Gagal melakukan Update database");
					dialog.set_secondary_text("Periksa parameter koneksi database");

					dialog.run();
					edit_post->hide();
					return;
				}
				MYQ.Close();
				this->ReloadList();
			}
			else
			{
				printf(" +-- Parameter tetap\n");
			}
			
			
		break;
			
		default:
			printf(" |-- GTK Respones default\n");
		break;
	}
	edit_post->hide();
	//delete edit_post;
}
