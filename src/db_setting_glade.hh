// generated 2008/7/17 14:37:24 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Documents/Program/MonitaApp/src/db_setting.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//db_setting.hh and.//db_setting.cc

#ifndef _DB_SETTING_GLADE_HH
#  define _DB_SETTING_GLADE_HH

// Since all your widgets were private I made them all public.
// To differentiate between accessable (e.g. entries, output labels)
// and unaccessible widgets (e.g. static labels, containers)
// you should use the 'visibility' property (only visible in C++ mode)


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

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/fixed.h>
#include <gtkmm/alignment.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>

class db_setting_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Window * db_setting;
        class Gtk::Entry * entry1;
        class Gtk::Entry * entry2;
        class Gtk::Entry * entry3;
        class Gtk::Entry * entry4;
        class Gtk::Entry * entry5;
        class Gtk::Fixed * fixed2;
        class Gtk::Alignment * alignment2;
        class Gtk::Label * label1;
        class Gtk::Frame * frame1;
        class Gtk::Button * buttonOK;
        class Gtk::Button * buttonBatal;
        class Gtk::Fixed * fixed1;
        class Gtk::VBox * vbox2;
protected:
        
        db_setting_glade();
        
        ~db_setting_glade();
private:
        virtual void on_buttonOK_clicked() = 0;
};
#endif