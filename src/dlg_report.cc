// generated 2008/9/23 9:54:47 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_report.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "dlg_report.hh"
#include "common.hh"

dlg_report::dlg_report()
{
	printf("[dlg_report::dlg_report]\n");
	kolom_pilih_ada=false;
}

dlg_report::~dlg_report()
{
	printf("[~dlg_report::dlg_report]\n");
}

int dlg_report::isi_form()
{
	printf("[dlg_report::isi_form()]\n");
	
	Glib::ustring usQuery,usTemp;
	Gtk::TreeModel::Row row;
	
	//Isi tanggal
	//Inisialisasi List view data dan tanggal
	int itanggal,ibulan,itahun;
	int ijam,imenit,idetik;
	
	char cwaktu[32];
	time_t the_timelist;
	
	(void) time(&the_timelist);
	tm_pointer = localtime(&the_timelist);
	
	printf("[Inisialisasi Waktu]\n");
	strftime(cwaktu,32,"%d",tm_pointer);
	itanggal=atoi(cwaktu);
	printf(" |-- tanggal: %d\n",itanggal);
	
	strftime(cwaktu,32,"%m",tm_pointer);
	ibulan=atoi(cwaktu);
	printf(" |-- bulan: %d\n",ibulan);
	
	strftime(cwaktu,32,"%Y",tm_pointer); //%H:%M:%S
	itahun=atoi(cwaktu);
	printf(" |-- tahun: %d\n",itahun);
	
	strftime(cwaktu,32,"%H",tm_pointer);//%H:%M:%S
	ijam=atoi(cwaktu);
	printf(" |-- jam: %d\n",ijam);
	
	strftime(cwaktu,32,"%M",tm_pointer);
	imenit=atoi(cwaktu);
	printf(" |-- menit: %d\n",imenit);
	
	strftime(cwaktu,32,"%S",tm_pointer);
	idetik=atoi(cwaktu);
	printf(" |-- detik: %d\n",idetik);
	
	
	spin_tanggal->set_value(itanggal);
	spin_bulan->set_value(ibulan);
	spin_tahun->set_value(itahun);
	
	//Isi formnya
	if(!MYQ.init_lengkap())
	{
		printf("ERROR: Gagal inisialisasi database\n");
		return -1;
	}
	
	//Buat query
	usQuery="SELECT * FROM titik_ukur";
	
	strcpy(MYQ.Text,usQuery.c_str());
	
	MYQ.Query();
	
	int jumlah_titik=MYQ.jum_row;
	
	
	//isikan ke list
	mRefPilihTitik = Gtk::ListStore::create(m_daftar_titik);
	tree_pilih_titik->set_model(mRefPilihTitik);
	
	for(int i=0;i<jumlah_titik;i++)
	{
		row=*(mRefPilihTitik->append());
		row[m_daftar_titik.nomer_titik]=i;
		
		usTemp=MYQ.ambil_string("nama_titik");
		row[m_daftar_titik.nama_titik]=Glib::ustring::compose(usTemp,i);
		
		usTemp=MYQ.ambil_string("kode_titik");
		row[m_daftar_titik.kode_titik]=Glib::ustring::compose(usTemp,i);
		
		usTemp=MYQ.ambil_string("id_titik");
		row[m_daftar_titik.id_titik]=atoi(usTemp.c_str());
		
		
		
		MYQ.Next();
	}
	MYQ.Buang();
	
	if(!kolom_pilih_ada)
	{
		//Dipilih atau tidak
		tree_pilih_titik->append_column_editable("Pilih", m_daftar_titik.is_dipilih);
		
		tree_pilih_titik->append_column("Kode", m_daftar_titik.kode_titik);
		
		Gtk::TreeView::Column* pColumn=Gtk::manage( new Gtk::TreeView::Column("Nama"));
		pColumn->pack_start(m_daftar_titik.nomer_titik,false);
		pColumn->pack_start(m_daftar_titik.nama_titik,true);

		tree_pilih_titik->append_column(*pColumn);
		
		kolom_pilih_ada=true;
	}
	
	MYQ.Close();
}

void dlg_report::on_button_cetak_clicked() 
{
	printf("[on_button_cetak_clicked]\n");
	Glib::ustring asTanggal;
	
	if(radio_csv->get_active())
	{
		printf(" |-- radio csv\n");
		//Cari id group yang dicetak
		
		//lihat tanggal yang dipilih
		char cwaktu[32];
		sprintf(cwaktu,"%04d%02d%02d",spin_tahun->get_value_as_int(),
								spin_bulan->get_value_as_int(),
								spin_tanggal->get_value_as_int());
		printf("Update List View(astanggal=%s)\n",cwaktu);
		asTanggal=cwaktu;
		
		//Minta nama file
		
		
		if(ExportCSV ("tes.csv",id_group_tree,asTanggal)==1)
			printlog ("Simpan report csv: OK",0);
		else
			printlog("Simpan report csv: gagal",0);
	}
	else if(radio_printer->get_active())
	{
		printf(" |-- printer\n");
	}
	
	printf("[/on_button_cetak_clicked]\n");
}

int dlg_report::ExportCSV(Glib::ustring nama_file,int id_group_tree,Glib::ustring asTanggal)
{
	printf("[ExportCSV] file:%s id_group: %d, asTanggal:%s\n",nama_file.c_str(),id_group_tree,asTanggal.c_str());
	int i;

	if(!MYQ.init_lengkap())
	{
		printf("ERROR: Gagal inisialisasi database\n");
		return -1;
	}
	
	if(!MYQ1.init_lengkap())
	{
		printf("ERROR: Gagal inisialisasi database\n");
		return -1;
	}
	
    Glib::ustring asQuery;
    Glib::ustring asTemp;
    Glib::ustring sid_titik;
    Glib::ustring asData,asWaktu;
    Glib::ustring id_equip,id_dept,id_persh;
    Glib::ustring stanggal,swaktu;

    Glib::ustring judul_data[13];
    char cTemp[512],cTemp2[32],cwaktu[16];
    Glib::ustring data_matrix[40][1440];
    float ftemp;

		
    float fdata_temp;
    Glib::ustring data_temp[24][60];    //Mau dicetak, tidak dihitung
    bool ada_data_temp[24][60];

    FILE *stream;
    //struct mystruct s;
    Glib::ustring nama_group,nama_equip,nama_dept,nama_persh;

    //Buka filenya dulu
	printf(" |-- buka file stream\n");
   if ((stream = fopen(nama_file.c_str(), "wb")) == NULL) 
   {
      fprintf(stderr, "Cannot open output file.\n");
	   printf("Tidak bisa membuka file : %s\n",nama_file.c_str());
      return 1;
   }
    int RecCount,jum_titik,j;
	
    //TCursor Save_Cursor = Screen->Cursor;	
	
    //Screen->Cursor = crHourGlass;    // Show hourglass cursor
    Glib::ustring id_group;
	id_group=Glib::ustring::compose("%1",id_group_tree);

    //Isi judul
    asQuery="SELECT * FROM group_titik_ukur WHERE id_group='" +  id_group +"'";
    strcpy(MYQ.Text,asQuery.c_str());
    MYQ.Query();

    if(MYQ.jum_row!=1)
    {
        //ShowMessage("Kesalahan pada database. Tidak ada/multiple entri untuk id_group=" + id_group);
        //Screen->Cursor = Save_Cursor;
		printf("Kesalahan pada database. Tidak ada/multiple entri untuk id_group=%d\n", id_group.c_str());
        return 1;
    }

    nama_group=MYQ.ambil_string("nama_group");
    id_equip=MYQ.ambil_string("id_equipment");
    id_dept=MYQ.ambil_string("id_dept");
    id_persh=MYQ.ambil_string("id_persh");
	MYQ.Buang();
	
    //Cari nama equipment
	printf(" |-- cari nama equipment(id=%s)\n",id_equip.c_str());
    asQuery="SELECT * FROM equipment WHERE id_equipment='" + id_equip+"'";
    strcpy(MYQ.Text,asQuery.c_str());
    
    MYQ.Query();
    if(MYQ.jum_row!=1)
    {
        //ShowMessage("Kesalahan pada database. Tidak ada/multiple entri untuk id_equipment=" + id_equip);
		printf("Kesalahan pada database. Tidak ada/multiple entri untuk id_equipment=%d\n", id_equip.c_str());
        //Screen->Cursor = Save_Cursor;
        return 1;
    }
    nama_equip=MYQ.ambil_string("nama_equipment");
    MYQ.Buang();
	/*
    //Cari nama Dept
	printf(" |-- cari nama dept (id:%s)\n",id_dept.c_str());
    asQuery="SELECT * FROM departemen WHERE id_dep='" + id_dept+"'";
    strcpy(MYQ.Text,asQuery.c_str());

    MYQ.Query();
    if(MYQ.jum_row!=1)
    {
        //ShowMessage("Kesalahan pada database. Tidak ada/multiple entri untuk id_dept=" + id_dept);
		printf("Kesalahan pada database. Tidak ada/multiple entri untuk id_dept=%d\n",id_dept.c_str());
        //Screen->Cursor = Save_Cursor;
       // printf("
		return 1;
    }
    nama_dept=MYQ.ambil_string("nama_dep");
	MYQ.Buang();
	
    //cari nama Persh
	printf(" |-- cari nama persh (id:%s)\n",id_persh.c_str());
	asQuery="SELECT * FROM perusahaan WHERE id_pers='" + id_persh+"'";
    strcpy(MYQ.Text,asQuery.c_str());
    

    MYQ.Query();
    if(MYQ.jum_row>1)
    {
        //ShowMessage("Kesalahan pada database. Multiple entri untuk perusahaan dengan id:" + id_persh);
		printf("Kesalahan pada database. Multiple entri untuk perusahaan dengan id:%d\n", id_persh.c_str());
        return -1;
    }
    else if(MYQ.jum_row<=0)
    {
        //ShowMessage("Kesalahan pada database: Tidak ditemukan entri untuk perusahaan dengan id:" + id_persh);
		printf("Kesalahan pada database: Tidak ditemukan entri untuk perusahaan dengan id:%d\n", id_persh.c_str());
    }
    nama_persh=MYQ.ambil_string("nama_pers");
     MYQ.Buang();
	
	
    //Bikin judul
    sprintf(cTemp,"%s\n",nama_persh.c_str());
    fputs(cTemp,stream);
    sprintf(cTemp,"%s\n\n",nama_dept.c_str());
    fputs(cTemp,stream);*/
	printf(" |-- Buat Judul\n");
    sprintf(cTemp,"Mesin:, %s\n",nama_equip.c_str());
    fputs(cTemp,stream);
	printf(" |--|-- nama mesin: %s",cTemp);
	
    sprintf(cTemp,"Group:, %s\n",nama_group.c_str());
    fputs(cTemp,stream);
	printf(" |--|-- nama group: %s",cTemp);
	

    Glib::ustring tanggal_cetak=asTanggal;//.substr(0,4) + asTanggal.substr(6,2) + asTanggal.substr(9,2);
    Glib::ustring waktu_awal,waktu_akhir;

    sprintf(cTemp,"Tanggal,%s,\n",tanggal_cetak.c_str());
    fputs(cTemp,stream);

    waktu_awal="00:00";
    waktu_akhir="23.59";
    
    asQuery="SELECT * FROM titik_ukur WHERE id_group_titik_ukur='" +  id_group +"'";
    strcpy(MYQ.Text,asQuery.c_str());
	printf(" |-- Query: %s\n",asQuery.c_str());
	MYQ.Query();

    if(MYQ.jum_row<1)
    {
        //ShowMessage("Kesalahan pada database. Tidak ada entri untuk titik ukur dengan group id =" + id_group);
        //Screen->Cursor = Save_Cursor;
		printf("Kesalahan pada database. Tidak ada entri untuk titik ukur dengan group id=%d\n", id_group.c_str());
        return 1;
    }

    fputs("\n\nNo., Waktu,, ",stream);
	
    jum_titik=MYQ.jum_row;
    int hitung_menit;
	printf(" |-- jum_titik: %d\n",jum_titik);
	if(jum_titik>0)
    {

        Glib::ustring asWaktuTemp,asDataTemp;
        int ijam,imenit,itemp;
        int jam_skr,menit_skr;
        printf(" |--|--* Traversing titik demi titik\n");
        for(i=0;i<jum_titik;i++)
        {
            sid_titik=MYQ.ambil_string("id_titik");
            asTemp=MYQ.ambil_string("nama_titik");
			printf(" |--|--|-- Titik: %d\n",i);
            sprintf(cTemp,"%s,",asTemp.c_str());
            fputs(cTemp,stream);

            //Bersihkan data temporary
            for(int jam=0;jam<24;jam++)
            for(int menit=0;menit<60;menit++)
            {
                data_temp[jam][menit]="0.0";
                ada_data_temp[jam][menit]=false;
            }

            asQuery="SELECT * FROM data_harian RIGHT JOIN waktu on waktu.id_waktu=data_harian.id_waktu ";
        	asQuery+="WHERE id_titik_ukur='" + sid_titik + "' AND waktu.waktu LIKE '" + tanggal_cetak + "%'";
        	asQuery+="ORDER BY waktu ASC LIMIT 1440";

            strcpy(MYQ1.Text,asQuery.c_str());
            printlog(asQuery,0);
			printf(" |--|--|-- Query: %s\n",asQuery.c_str());
            MYQ1.Query();
			
            //Lihat apakah tiap menit ada isinya, jika ada pindahkan ke data_temp
			printf(" |--|--|--* Cek data per menit. jum_row: %d\n",MYQ.jum_row);
			
			for(int j=0;j<MYQ1.jum_row;j++)
			{
				//FormPrintGroup->QRNo->Lines->Add(IntToStr(j));
				printf(" |--|--|--|-- j=%d:",j);
				swaktu=MYQ1.ambil_string("waktu"); //20080908-092345
				asWaktuTemp=swaktu.substr(9,2);
				ijam=atoi(asWaktuTemp.c_str());
				
				asWaktuTemp=swaktu.substr(11,2);
				imenit=atoi(asWaktuTemp.c_str());
				
				asDataTemp = MYQ1.ambil_string("data_tunggal");
				printf(" waktu: %s, data: %s. ijam:%d, imenit:%d",swaktu.c_str(),asDataTemp.c_str(),ijam,imenit);
				if (asDataTemp != "")
				{
					fdata_temp = strtod(asDataTemp.c_str(),NULL);
					printf(",fdata: %0.2f",fdata_temp);
					if(fdata_temp>100)
					{
						sprintf(cTemp,"%0.0f",fdata_temp);
						data_temp[ijam][imenit].assign(cTemp);// = Glib::ustring::format(std::fixed, std::setprecision(0), fdata_temp);//
						//FloatToStrF(fdata_temp, ffNumber, 9,0);
					}
					else
					{
						sprintf(cTemp,"%0.0f",fdata_temp);
						data_temp[ijam][imenit].assign(cTemp);// = Glib::ustring::format(std::fixed, std::setprecision(2), fdata_temp);
						//FloatToStrF(fdata_temp, ffNumber, 9,2);
					}
					printf(",data_temp[%d][%d]:%s",ijam,imenit,data_temp[ijam][imenit].c_str());
				}
				//data_temp[ijam][imenit]=MYQ.ambil_string("data_tunggal");
				ada_data_temp[ijam][imenit]=true;
				printf(".");
				MYQ1.Next();
				printf(".\n");
			}
			
            MYQ1.Buang();
			printf(" |-- isi data ke matrix\n");
            for(int jam=0;jam<24;jam++)
            {
                for(int menit=0;menit<60;menit++)
                {
                    //Tampilkan tiap 30 menit

                    //if((menit==0)||(menit==30))
                    //{
                        hitung_menit=jam*60+menit;
						sprintf(cTemp,"%02d:%02d",jam,menit);
						asWaktuTemp.assign(cTemp);
						
						//printf(" |-- Data temp: %s\n",data_temp[jam][menit].c_str());
                        if(ada_data_temp[jam][menit]==true)
                        {
                            data_matrix[i][hitung_menit]=data_temp[jam][menit];
                        }
                        else
                        {
                            data_matrix[i][hitung_menit]="-1";
                        }
                    //}
                }
            }
			
            MYQ.Next();
        }
    }
    else
    {
        //sgProp->Ce   
    }
    MYQ.Buang();
    //FormPrintGroup->LabelPeriodeData->Caption=waktu_awal + " - " + waktu_akhir;
	printf(" |-- Tulis data ke file. jumlah_titik: %d\n",jum_titik);
   fputs("\n\n",stream);
   for(int ijam=0;ijam<24;ijam++)
   {
	   printf("\ncetak: jam %d\n",ijam);
    for(int imenit=0;imenit<60;imenit++)
    {
		printf("%d ",imenit);
        hitung_menit=ijam*60+imenit;
        sprintf(cwaktu,"%d,%02d:%02d,",hitung_menit,ijam,imenit);
        strcpy(cTemp,"");
        asTemp="";
		
		//printf(" |-- menit: %d\t",imenit);
        for(int index_titik=0;index_titik<jum_titik;index_titik++)
        {
			//asTemp=data_matrix[index_titik][hitung_menit];
			//printf(" %d(%s)\t",index_titik,asTemp.c_str());
            if (data_matrix[index_titik][hitung_menit]!="-1")
			{
				sprintf(cTemp,"%s,\"%s\"",cTemp,data_matrix[index_titik][hitung_menit].c_str());
            	//asTemp.sprintf(",\"%s\"",data_matrix[index_titik][hitung_menit]);
				//asTemp.assign(cTemp);
			}
			else
			{
				sprintf(cTemp,"%s,\" \"",cTemp);
				//asTemp=asTemp+ ",\" \"";
			}
        }
		//printf("\n");
		asTemp.assign(cTemp);
        //printf("%s\n",cTemp);
        sprintf(cTemp,"%s%s\n",cwaktu,asTemp.c_str());
        fputs(cTemp,stream);
     }
   }

   	fclose(stream); /* close file */
   	//Screen->Cursor = Save_Cursor;
   	MYQ.Close();
	MYQ1.Close();
	
	//Tampilkan pesan bahwa report sudah dibuat dengan sukses
	Glib::ustring sTemp="Report berhasil disimpan dengan nama file [" + nama_file + "]";
	Gtk::MessageDialog dialog(*this,sTemp,
	true /*use markup*/, Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK);

	//dialog.set_secondary_text("Peringatan: Menghapus titik ukur juga akan menghapus \nsemua data dari titik ukur ini");
	
	int result=dialog.run();
	
	printf("[/ExportCSV]\n");
	return 0;
}

void dlg_report::on_button_open_kalender_clicked()
{
	printf("[button open kalender]\n");
	
	int result;
	Glib::Date date;
	struct tm tm_tanggal;
	int itanggal,ibulan,itahun;
	char cwaktu[32];
	
	dlg_kalender *dlg_kal = new class dlg_kalender();
	
	result=dlg_kal->run();
	
	switch(result)
	{
		case GTK_RESPONSE_OK:
			printf("+-- Set tanggal\n");
		
			dlg_kal->calendar1->get_date(date);
			date.to_struct_tm(tm_tanggal);
			
			printf("[Inisialisasi Waktu]\n");
			strftime(cwaktu,32,"%d",&tm_tanggal);
			itanggal=atoi(cwaktu);
			printf(" |-- tanggal: %d\n",itanggal);
			strftime(cwaktu,32,"%m",&tm_tanggal);
			ibulan=atoi(cwaktu);
			printf(" |-- bulan: %d\n",ibulan);
			strftime(cwaktu,32,"%Y",&tm_tanggal);
			itahun=atoi(cwaktu);
			printf(" |-- tahun: %d\n",itahun);
			
			spin_tanggal->set_value(itanggal);
			spin_bulan->set_value(ibulan);
			spin_tahun->set_value(itahun);
			
			
			dlg_kal->hide();
			
		break;
		default:
			dlg_kal->hide();
		break;
	}
	
	delete dlg_kal;
}

void dlg_report::on_button_tanggal_apply_clicked()
{
	
}
