// generated 2008/10/28 17:27:44 CIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Monita/src/dlg_edit_titik.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//dlg_edit_titik.hh and.//dlg_edit_titik.cc

#ifndef _DLG_EDIT_TITIK_GLADE_HH
#  define _DLG_EDIT_TITIK_GLADE_HH


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
#include <gtkmm/radiobutton.h>
#include <gtkmm/combobox.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>

class dlg_edit_titik_glade : public Gtk::Dialog
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Entry * entry_kode_titik;
        class Gtk::Entry * entry_satuan;
        class Gtk::Entry * entry_nama_titik;
        class Gtk::RadioButton * radio_ukur;
        class Gtk::RadioButton * radio_hitung;
        class Gtk::ComboBox * combo_sumber;
        class Gtk::ComboBox * combo_nomer_board;
        class Gtk::ComboBox * combo_kanal;
        class Gtk::Entry * entry_kalib_a;
        class Gtk::Entry * entry_kalib_b;
        class Gtk::Label * label_satuan1;
        class Gtk::Label * label_satuan2;
        class Gtk::SpinButton * spin_range_maks;
        class Gtk::SpinButton * spin_range_min;
        class Gtk::Label * label_satuan4;
        class Gtk::Label * label_satuan5;
        class Gtk::Label * label_satuan6;
        class Gtk::SpinButton * spin_alarm_min_min;
        class Gtk::SpinButton * spin_alarm_min;
        class Gtk::SpinButton * spin_alarm_maks;
        class Gtk::SpinButton * spin_alarm_maks_maks;
        class Gtk::Label * label_satuan3;
        class Gtk::ComboBox * combo_alarm_min_min;
        class Gtk::ComboBox * combo_alarm_max;
        class Gtk::ComboBox * combo_alarm_max_max;
        class Gtk::ComboBox * combo_alarm_min;
        class Gtk::Entry * entry_action_min_min;
        class Gtk::Entry * entry_action_max;
        class Gtk::Entry * entry_action_max_max;
        class Gtk::Entry * entry_action_min;
        class Gtk::SpinButton * spin_alarm_time_min_min;
        class Gtk::SpinButton * spin_alarm_time_min;
        class Gtk::SpinButton * spin_alarm_time_max;
        class Gtk::SpinButton * spin_alarm_time_max_max;
        class Gtk::CheckButton * check_alarm_min_min;
        class Gtk::CheckButton * check_alarm_min;
        class Gtk::CheckButton * check_max;
        class Gtk::CheckButton * check_alarm_max_max;
protected:
        
        dlg_edit_titik_glade();
        
        ~dlg_edit_titik_glade();
private:
        virtual void on_okbutton1_clicked() = 0;
};
#endif
