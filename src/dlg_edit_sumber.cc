// generated 2008/7/30 8:32:14 WIT by herry@LancarJaya.(none) m hyyddddddddx cwi .k]iyi'k/[/k/
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_sumber.cc_new

// This file is for your program, I won't touch it again!

#include <config.h>
#include <gtkmm/main.h>
#include <glib/gi18n.h>
#include <gtkmm.h>

#include "dlg_edit_sumber.hh"

dlg_edit_sumber::dlg_edit_sumber()
{
	printf("create instance dlg_edit_sumber\n");
	
	notebook_parameter->set_current_page(0);
	notebook_parameter->set_show_tabs(FALSE);
}

void dlg_edit_sumber::on_button_ok_clicked ()
{
	//printf("button OK clicked\n");
	//cek dulu apakah parameter yang dimasukkan sudah benar
	
	this->hide();
}

void dlg_edit_sumber::on_button_cancel_clicked()
{
	this->hide();
}

void dlg_edit_sumber::on_radio_file_group_changed() 
{
	printf("[dlg_edit::radio_group_changed]\n");
}	

void dlg_edit_sumber::on_radio_file_toggled()
{
	printf("[dlg_edit::on_radio_toggled]\n");
	
	if(radio_file->get_active()==true)
	{
		notebook_parameter->set_current_page(1);
	}
}

void dlg_edit_sumber::on_radio_modul_toggled()
{
	if(radio_modul->get_active()==true)
	{
		notebook_parameter->set_current_page(0);
	}
}
void dlg_edit_sumber::on_radio_pm_server_toggled()
{
	if(radio_pm_server->get_active()==true)
	{
		notebook_parameter->set_current_page(0);
	}
}

void dlg_edit_sumber::on_button1_clicked ()
{
	printf("[dlg_edit_sumber::Browse direktori]\n");
	
	Gtk::FileChooserDialog dialog("Pilih folder/direktori",
    			Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	
	dialog.set_transient_for(*this);
	Glib::ustring usTemp; 
		
	//Kasih respons button
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button("Select", Gtk::RESPONSE_OK);
	
	usTemp=entry_directory->get_text();
	if(usTemp!="")
	{
		dialog.set_filename(usTemp);
	}
	
	int result = dialog.run();
	
	//Handle the response:
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
		{
			usTemp=dialog.get_filename();
			printf(" * Folder terpilih: %s\n",usTemp.c_str());
			entry_directory->set_text(usTemp);
		  	break;
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			printf(" * Cancel\n");
			//std::cout << "Cancel clicked." << std::endl;
		  	break;
		}
		default:
		{
			printf(" * ERROR\n");
		  break;
		}
	}
}
