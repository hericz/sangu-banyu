// generated 2008/7/17 14:47:00 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Documents/Program/MonitaApp/src/db_dialog.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//dialog1.hh and.//dialog1.cc

#ifndef _DIALOG1_GLADE_HH
#  define _DIALOG1_GLADE_HH

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

#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/table.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>

class dialog1_glade : public Gtk::Dialog
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Dialog * dialog1;
        class Gtk::Button * cancelbutton1;
        class Gtk::Button * okbutton1;
        class Gtk::Entry * entry4;
        class Gtk::Entry * entry5;
        class Gtk::Entry * entry6;
        class Gtk::Label * label4;
        class Gtk::Label * label5;
        class Gtk::Label * label6;
        class Gtk::Table * table1;
        class Gtk::Label * label1;
        class Gtk::Frame * frame1;
protected:
        
        dialog1_glade();
        
        ~dialog1_glade();
};
#endif
