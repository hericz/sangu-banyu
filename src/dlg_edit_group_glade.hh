// generated 2008/8/26 16:17:24 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Monita/src/monitaapp.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//dlg_edit_group.hh and.//dlg_edit_group.cc

#ifndef _DLG_EDIT_GROUP_GLADE_HH
#  define _DLG_EDIT_GROUP_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include <gtkmm/combobox.h>

class dlg_edit_group_glade : public Gtk::Dialog
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Entry * entry_nama;
        class Gtk::TextView * textview_keterangan;
        class Gtk::ComboBox * combo_jenis;
        class Gtk::Entry * entry_gambar;
protected:
        
        dlg_edit_group_glade();
        
        ~dlg_edit_group_glade();
private:
        virtual void on_okbutton2_clicked() = 0;
};
#endif
