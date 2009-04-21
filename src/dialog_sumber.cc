// generated 2008/7/17 16:11:24 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dialog_sumber.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "dialog_sumber.hh"

dialog_sumber::dialog_sumber()
{
	printf("Inisiasi dialog sumber\n");
	printf("Isi data sumber dari database\n");
	list_ada_kolom=false;
}

void dialog_sumber::on_button_tambah_clicked()
{
	Glib::ustring uNamaSumber,uAlamatIP,uPort,usTemp,uDirectory; //kondisi sesudah
	Glib::ustring uFlag,uNoGSM,uKeterangan,uTipePM;
	int result;
	int istatus,flag_sumber;
	
	double djumlah_kanal,dno_stack;
	char sTemp[512];
	
	printf("button tambah clicked\n");
	dlg_edit_sumber *dlg_edit=new dlg_edit_sumber();
	
	dlg_edit->entry_ip_address->set_text("192.168.1.");
	dlg_edit->entry_port->set_text("5001");
	dlg_edit->spinbutton1->set_value(10);
	dlg_edit->spin_no_stack->set_value(1);
	
	//Combo stack
	
	result=dlg_edit->run();
	
	switch(result)
	{
		case GTK_RESPONSE_OK:
		printf("dialog response OK\n");
			
			//Jenis Sumber data
			
			if(dlg_edit->radio_modul->get_active())
				flag_sumber=21;
			else if(dlg_edit->radio_pm_server->get_active())
				flag_sumber=22;
			else if(dlg_edit->radio_gsm->get_active())
				flag_sumber=23;
			else if(dlg_edit->radio_server->get_active())
				flag_sumber=24;
			else if(dlg_edit->radio_file->get_active())
				flag_sumber=25; //MONITOR DIREKTORI DARI EMAIL
			
			uNamaSumber=dlg_edit->entry_nama_sumber->get_text();
			printf("-Nama sumber: %s\n",uNamaSumber.c_str());
			//,alamat,ip,port,jum_kanal,status)";
			
			uAlamatIP=dlg_edit->entry_ip_address->get_text();
			printf("-IP Address: %s\n",uAlamatIP.c_str());
			
			uPort=dlg_edit->entry_port->get_text();	
			printf("-Port: %s\n",uPort.c_str());
			
			djumlah_kanal=dlg_edit->spinbutton1->get_value();
			printf("-jumlah_kanal: %0.2f\n",djumlah_kanal);
			
			dno_stack=dlg_edit->spin_no_stack->get_value();
			printf("-default stack: %0.2f\n",dno_stack);
			
			uDirectory=dlg_edit->entry_directory->get_text();
			printf("-Directory: %s\n",uDirectory.c_str());
			
			if(dlg_edit->check_sumber_aktif->get_active())
				istatus=1;
			else
				istatus=0;
			
			//Masih dummy
			uNoGSM="0";
			uKeterangan="Keterangan";
			uTipePM="0";
			
			printf("-Aktif : %d\n",istatus);
			printf("-dno_stack: %0.1f\n",dno_stack);	
			printf("-flag_sumber: %d\n",flag_sumber);
			
			//Buat query string
			sprintf(sTemp,
					"INSERT INTO sumber_data (nama_sumber,flag,no_gsm,tipe_pm,alamat_ip,port,jum_kanal,status,keterangan,default_stack,directory)");
			
			
			sprintf(sTemp,"%s VALUES('%s','%d','%s','%s','%s','%s','%0.1f','%d','%s','%0.1f','%s')",sTemp,
					uNamaSumber.c_str(),flag_sumber,uNoGSM.c_str(),uTipePM.c_str(),uAlamatIP.c_str(),
					uPort.c_str(),djumlah_kanal,istatus,uKeterangan.c_str(),dno_stack,uDirectory.c_str());
			
			printf("Query: %s\n",sTemp);
			
			if(MYQ.init_lengkap()==1)
			{
				strcpy(MYQ.Text,sTemp);
				printf("Update Database...");
				if(!MYQ.Insert())
				{
					printf("OK\n");
					
					MYQ.Close();
					this->reload_list();
				}
			}
			else
			{
				printf("Gagal melakukan koneksi ke database\n");
			}
					
		break;
		default:
		printf("Default\n");
	}
	
	printf(" |-- Selesai tambah sumber\n");
}

void dialog_sumber::on_button_hapus_clicked()
{
	printf("Button hapus clicked\n");
	//Cari tau data mana yang sedang dipilih
	Glib::ustring strText,strQuery;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;
	
	int id_sumber_hapus;
	
	refTreeSelection= this->treeview2->get_selection();
	iter = refTreeSelection->get_selected();
	
	if(iter) //If anything is selected
	{
		row = *iter;
	  	//Do something with the row.
		strText= row[m_sumber.m_col_nama_sumber];
		id_sumber_hapus=row[m_sumber.m_col_id];
		printf("-Column Name: %s\n",strText.c_str());
		
		Gtk::MessageDialog dialog(*this,"<b>Hapus Sumber Data: <i>" + strText + "</i>?</b>",
        		true /*use markup*/, Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);

		dialog.set_secondary_text("Peringatan: Semua koneksi ke sumber data\n" +
								  strText+ " akan ikut dihapus");

		int result=dialog.run();
		
		switch(result)
		{
			case(Gtk::RESPONSE_OK):
				std::cout << "OK clicked." << std::endl;
				//Hapus koneksi ke sumber data ini
				//UPDATE titik_ukur
				strQuery=Glib::ustring::compose(
						"UPDATE titik_ukur SET sumber_data='0', no_port='0', no_kanal='0' WHERE sumber_data='%1'",
						id_sumber_hapus);
				
				if(MYQ.init_lengkap()==1)
				{
					printf(" - Query: %s\n",strQuery.c_str());
					strcpy(MYQ.Text,strQuery.c_str());
					printf(" - Update Database Titik ukur...");
					if(!MYQ.Update())
					{
						printf("OK\n");			
					}
					else
					{
						printf("Gagal\n");
						MYQ.Close();
						return;
					}
				}
				else
				{
					printf("Gagal melakukan koneksi ke database\n");
					return;
				}
				
				//Hapus sumber data ybs
				strQuery=Glib::ustring::compose("DELETE FROM sumber_data WHERE id_sumber='%1'",id_sumber_hapus);
				strcpy(MYQ.Text,strQuery.c_str());
				printf("Hapus Sumber data.\nQuery: %s\n",strQuery.c_str());
				
				printf("Update Database Sumber Data ");
				if(MYQ.Delete())
				{
					printf("->OK\n");			
				}
				else
				{
					printf("->Gagal\n");
					MYQ.Close();
					return;
				}
				
				this->reload_list();
				MYQ.Close();
				break;

			case(Gtk::RESPONSE_CANCEL):
				std::cout << "Cancel clicked." << std::endl;
				break;
			default:
				std::cout << "Default" << std::endl;
				break;
		}
	}
	else
	{
		printf("-Tidak ada kolom yang dipilih\n");
	}
}

void dialog_sumber::on_button_edit_clicked()
{
	printf("Button Edit clicked\n");
	//Cari tau data mana yang sedang dipilih
	char sTemp[512];
	int iTemp,id_sumber;
	int radio_jenis_sumber,flag_sumber,flag_sumber1;
	double djumlah_kanal,djumlah_kanal1;  //karena spinbutton get_value bernilai doublue
	
	Glib::ustring strText, strQuery;
	
	Glib::ustring uNamaSumber1,uAlamatIP1,uPort1,uDirectory1; //kondisi sebelum 
	Glib::ustring uNamaSumber,uAlamatIP,uPort,uDirectory; //kondisi sesudah
	
	double dno_stack,dno_stack1;
	int istatus,istatus1;
	int result;
	
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;
	
	refTreeSelection= this->treeview2->get_selection();
	iter = refTreeSelection->get_selected();
	
	if(iter) //If anything is selected
	{
		row = *iter;
	  	//Do something with the row.
		uNamaSumber1= row[m_sumber.m_col_nama_sumber];
		printf("-Column Name: %s\n",uNamaSumber1.c_str());
		
		iTemp=row[m_sumber.m_col_id];
		printf("-ID Sumber: %d\n",iTemp);
		id_sumber=iTemp;
		
		//Tampilkan dialog edit sumber

		dlg_edit_sumber *dlg_edit=new dlg_edit_sumber();
		
		//Isi dengan parameter tersimpan
		flag_sumber1=row[m_sumber.m_col_flag];
		
		if(flag_sumber1==21)
			dlg_edit->radio_modul->set_active();
		else if(flag_sumber1==22)
			dlg_edit->radio_pm_server->set_active();
		else if(flag_sumber1==23)
			dlg_edit->radio_gsm->set_active();
		else if(flag_sumber1==24)
			dlg_edit->radio_server->set_active();
		else if(flag_sumber1==25)
			dlg_edit->radio_file->set_active();
		
		uNamaSumber1= row[m_sumber.m_col_nama_sumber];
		dlg_edit->entry_nama_sumber->set_text(uNamaSumber1);
		printf("- flag: %d\n",flag_sumber1);
		
		strText=row[m_sumber.m_col_alamat_ip];
		printf("- Alamat IP: %s\n",strText.c_str());
		
		if(flag_sumber1==21)
		{
			uAlamatIP1= row[m_sumber.m_col_alamat_ip];
			
			dlg_edit->entry_ip_address->set_text(uAlamatIP1);			
		}
		else if(flag_sumber1==22)
		{
			uAlamatIP1= row[m_sumber.m_col_alamat_ip];
			dlg_edit->entry_ip_address->set_text(uAlamatIP1);
		}
		else if(flag_sumber1==25)
		{
			uDirectory1= row[m_sumber.m_col_alamat_ip];
			dlg_edit->entry_directory->set_text(uDirectory1);
			printf(" - Directory: %s\n ",uDirectory1.c_str());	
		}
		uPort1= row[m_sumber.m_col_port];
		dlg_edit->entry_port->set_text(uPort1);	
		
			
		djumlah_kanal1= row[m_sumber.m_col_jum_kanal];
		
		dlg_edit->spinbutton1->set_value(djumlah_kanal1);
		
		dno_stack1=(double) row[m_sumber.m_col_default_stack];
		dlg_edit->spin_no_stack->set_value(dno_stack1);
		
		strText= row[m_sumber.m_col_status];
		
		if(strText=="aktif")
		{
			dlg_edit->check_sumber_aktif->set_active(true);
			istatus1=1;
		}
		else if(strText=="non-aktif")
		{
			dlg_edit->check_sumber_aktif->set_active(false);
			istatus1=0;
		}
		
		result=dlg_edit->run();
		switch(result)
		{
			case GTK_RESPONSE_OK:
				
			printf("dialog response OK\n");
			//Jenis Sumber data
			
			if(dlg_edit->radio_modul->get_active())
			{
				radio_jenis_sumber=1;
				flag_sumber=21;
			}
			else if(dlg_edit->radio_pm_server->get_active())
			{	
				radio_jenis_sumber=2;
				flag_sumber=22;
			}
			else if(dlg_edit->radio_gsm->get_active())
			{
				radio_jenis_sumber=3;
				flag_sumber=23;
			}
			else if(dlg_edit->radio_server->get_active())
			{
				radio_jenis_sumber=4;
				flag_sumber=24;
			}
			else if(dlg_edit->radio_file->get_active())
			{
				radio_jenis_sumber=5;
				flag_sumber=25;
			}
			else
				flag_sumber=21;
			
			printf("-Radio jenis: %d\n",radio_jenis_sumber);
				
			//Nama Sumber	
			uNamaSumber=dlg_edit->entry_nama_sumber->get_text();
			printf("-Nama sumber: %s\n",uNamaSumber.c_str());
			//,alamat,ip,port,jum_kanal,status)";
			printf("- Flag = %d\n",flag_sumber);
			if(flag_sumber==21)
			{	
				uAlamatIP=dlg_edit->entry_ip_address->get_text(); //dlg_edit->entry_ip_address->get_text()
				printf("-IP Address: %s\n",uAlamatIP.c_str());
			}
			else if(flag_sumber==22)
			{
				uAlamatIP=dlg_edit->entry_ip_address->get_text();
				printf("-IP Address: %s\n",uAlamatIP.c_str());
			}
			else if(flag_sumber==25)
			{
				uDirectory=dlg_edit->entry_directory->get_text();
				printf("-IP Address: %s\n",uDirectory.c_str());
			}
			
			uPort=dlg_edit->entry_port->get_text();	
			printf("-Port: %s\n",uPort.c_str());
			
			djumlah_kanal=dlg_edit->spinbutton1->get_value();					
			printf("-jumlah_kanal: %0.2f\n",djumlah_kanal);						
																				
			if(dlg_edit->check_sumber_aktif->get_active())
				istatus=1;
			else
				istatus=0;
			
			//
			dno_stack=dlg_edit->spin_no_stack->get_value();
			printf(" |--* dno_stack:%0.1f\n",dno_stack);	
				
			printf("-Aktif : %d\n",istatus);
				
			//Cek apakah ada perubahan
			if((uNamaSumber!=uNamaSumber1)||
			   (uAlamatIP!=uAlamatIP1)||
			   (uPort!=uPort1)||
			   (istatus!=istatus1)||
			   (djumlah_kanal!=djumlah_kanal1)||
			   (istatus!=istatus1)||
			   (flag_sumber!=flag_sumber1)||
			   (dno_stack!=dno_stack1)||
			   (uDirectory!=uDirectory1))
			{
				printf("Ada perubahan, update database\n");
			}
			else
			{
				printf("Tidak ada perubahan\n");
				break;
			}
				
			//Buat query string
			sprintf(sTemp,
					"UPDATE sumber_data SET nama_sumber='%s',alamat_ip='%s',port='%s',jum_kanal='%0.1f',status='%d',flag='%d',default_stack='%0.1f',directory='%s'",
					uNamaSumber.c_str(),uAlamatIP.c_str(),uPort.c_str(),djumlah_kanal,istatus,flag_sumber,dno_stack,uDirectory.c_str());
			sprintf(sTemp,"%s WHERE id_sumber='%d'",sTemp,id_sumber);
			
			printf("Query: %s\n",sTemp);
			
			if(MYQ.init_lengkap()==1)
			{
				strcpy(MYQ.Text,sTemp);
				printf("Update Database...");
				if(!MYQ.Update())
				{
					printf("OK\n");
					
					MYQ.Close();
					this->reload_list();
				}
			}
			else
			{
				printf("Gagal melakukan koneksi ke database\n");
			}
					
			break;
				
			default:
				printf("Default\n");
			break;
		}
	}
	else
	{
		printf("-Tidak ada kolom yang dipilih\n");
	}
}


int dialog_sumber::reload_list()
{
	Glib::ustring sQuery,sTemp;
	int jumlah_sumber,iTemp, jumlah_aktif=0;
	int jenis_sumber;
	printf("dialog_sumber reload_list\n");
	
	m_refTreeModel = Gtk::TreeStore::create(m_sumber);
	
	treeview2->set_model(m_refTreeModel);
	
	printf("MYQ.server:%s\n",MYQ.server);
	
	if(MYQ.init_lengkap()==1)
	{
		printf("init db sukses\n");		
		
		sQuery="SELECT * FROM sumber_data";
		
		strcpy(MYQ.Text,sQuery.c_str());
		
		MYQ.Query();
		
		jumlah_sumber=MYQ.jum_row;
		if(jumlah_sumber>0)
		{
			for(int i=0;i<jumlah_sumber;i++)
			{
				Gtk::TreeModel::Row row =*(m_refTreeModel->append());
				
				row[m_sumber.m_col_nomer]=i;
				
				
				sTemp=MYQ.ambil_string("nama_sumber");
				printf("--Nama sumber %d: %s\n",i,sTemp.c_str());
				row[m_sumber.m_col_nama_sumber] = sTemp;
				
				sTemp=MYQ.ambil_string("flag");
				iTemp=atoi(sTemp.c_str());
				row[m_sumber.m_col_flag]=iTemp;
				jenis_sumber=iTemp;
				printf("--Flag : %d\n",iTemp);
				
				sTemp=MYQ.ambil_string("id_sumber");
				iTemp=atoi(sTemp.c_str());
				row[m_sumber.m_col_id] = iTemp;
				
				if(jenis_sumber==21)
				{
					sTemp=MYQ.ambil_string("alamat_ip");
					row[m_sumber.m_col_alamat_ip] = sTemp;
				}
				else if(jenis_sumber==22)
				{
					sTemp=MYQ.ambil_string("alamat_ip");
					row[m_sumber.m_col_alamat_ip] = sTemp;
				}
				else if(jenis_sumber==25)
				{
					sTemp=MYQ.ambil_string("directory");
					row[m_sumber.m_col_alamat_ip]=sTemp;
				}
				
				sTemp=MYQ.ambil_string("no_gsm");
				row[m_sumber.m_col_no_gsm] = sTemp;
				
				sTemp=MYQ.ambil_string("port");
				row[m_sumber.m_col_port] = sTemp;
				
				sTemp=MYQ.ambil_string("jum_kanal");
				iTemp=atoi(sTemp.c_str());
				row[m_sumber.m_col_jum_kanal]= iTemp;
				
				sTemp=MYQ.ambil_string("default_stack");
				iTemp=atoi(sTemp.c_str());
				row[m_sumber.m_col_default_stack]=iTemp;
				
				sTemp=MYQ.ambil_string("status");
				if(sTemp=="0")
				{
					row[m_sumber.m_col_status]= "non-aktif";
				}
				else if(sTemp=="1")
				{
					row[m_sumber.m_col_status]= "aktif";
					jumlah_aktif++;
				}
				else if(sTemp=="2")
					row[m_sumber.m_col_status]="not-responding";

				
				sTemp=MYQ.ambil_string("keterangan");
				row[m_sumber.m_col_keterangan] = sTemp;
				
				MYQ.Next();
			}
			
			if(list_ada_kolom==false)
			{
				treeview2->append_column("No.",m_sumber.m_col_nomer);
				treeview2->append_column("Nama Sumber", m_sumber.m_col_nama_sumber);
				treeview2->append_column("Alamat/Nomer/Folder", m_sumber.m_col_alamat_ip);
				treeview2->append_column("IP Port",m_sumber.m_col_port);
				treeview2->append_column("ID", m_sumber.m_col_id);	
				treeview2->append_column("Status",m_sumber.m_col_status);
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
		return 1;
	}
	
	//Update informasi di label info
	sTemp=Glib::ustring::compose("Jumlah: %1\nAktif: %2",jumlah_sumber,jumlah_aktif);
	this->label_info->set_text(sTemp);
	printf(" |--Selesai ReloadList ()\n");
	return 0;
}

void dialog_sumber::on_button_koneksi_clicked()
{
	
	printf("Button koneksi\n");
	
	int id_sumber;
	
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;

	refTreeSelection= this->treeview2->get_selection();
	iter = refTreeSelection->get_selected();
	
	if(iter) //If anything is selected
	{
		Glib::ustring uNamaSumber,uKeterangan;
		int iTemp;
		
		row = *iter;
	  	//Do something with the row.
		uNamaSumber= row[m_sumber.m_col_nama_sumber];
		printf("-Column Name: %s\n",uNamaSumber.c_str());
		
		iTemp=row[m_sumber.m_col_id];
		printf("-ID Sumber: %d\n",iTemp);
		
		uKeterangan="Nama Sumber: " + uNamaSumber 
					+ "\nIP Address : " + row[m_sumber.m_col_alamat_ip];
		
		dlg_koneksi_sumber *dlg_koneksi=new dlg_koneksi_sumber();
		
		
		printf("-MYQ.server:%s\n",MYQ.server);
		memcpy(&(dlg_koneksi->MYQ),(void*)&MYQ,sizeof(MyQuery));
		
		
		dlg_koneksi->label_nama_sumber->set_text(uKeterangan);
		
		dlg_koneksi->id_sumber_data=row[m_sumber.m_col_id];
		if(dlg_koneksi->ReloadList(1))
		{
			dlg_koneksi->run();
		}	
		//delete dlg_koneksi;
	}
	else
	{
		Gtk::MessageDialog dialog(*this,"<b>Pilih Sumber Data yang akan dilihat?</b>",
		true /*use markup*/, Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK);


		int result=dialog.run();
		
	}
}
