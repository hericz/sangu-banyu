// generated 2008/9/23 9:54:47 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Monita/src/monitaapp.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//dlg_splash.hh and.//dlg_splash.cc

#ifndef _DLG_SPLASH_GLADE_HH
#  define _DLG_SPLASH_GLADE_HH


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

class dlg_splash_glade : public Gtk::Dialog
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Dialog * dlg_splash;
protected:
        
        dlg_splash_glade();
        
        ~dlg_splash_glade();
};
#endif