// generated 2009/6/1 9:43:02 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Monita/src/monitaapp.glade
// for gtk 2.16.1 and gtkmm 2.16.0
//
// Please modify the corresponding derived classes in .//main_window.hh and.//main_window.cc

#ifndef _MAIN_WINDOW_GLADE_HH
#  define _MAIN_WINDOW_GLADE_HH


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
#include <gtkmm/tooltips.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#endif //
#include <gtkmm/button.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#endif //
#include <gtkmm/treeview.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/label.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/ruler.h>
#include <gtkmm/notebook.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/paned.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#include <gtkmm/expander.h>
#else //
#include <gtkmm/handlebox.h>
#endif //

class main_window_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
        Gtk::Tooltips _tooltips;
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#endif //
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#endif //
public:
        class Gtk::Button * button_logging_data;
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#endif //
        class Gtk::TreeView * treeview1;
        class Gtk::SpinButton * spin_tanggal;
        class Gtk::SpinButton * spin_bulan;
        class Gtk::SpinButton * spin_tahun;
        class Gtk::Label * label_info;
        class Gtk::Label * label_titik_ukur;
        class Gtk::Label * label_waktu;
        class Gtk::TreeView * tree_data;
        class Gtk::DrawingArea * drawingarea1;
        class Gtk::HRuler * hruler1;
        class Gtk::VRuler * vruler1;
        class Gtk::Label * label_status_waktu;
        class Gtk::ProgressBar * progress_koneksi;
        class Gtk::TreeView * tree_status;
        class Gtk::VPaned * vpaned_status;
        class Gtk::TreeView * tree_log;
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
        class Gtk::Expander * expander_log;
#else //
        class Gtk::HandleBox * expander_log;
#endif //
        class Gtk::VPaned * vpaned_log;
protected:
        
        main_window_glade();
        
        ~main_window_glade();
private:
        virtual void on_konfigurasi1_activate() = 0;
        virtual void on_database_login_setting1_activate() = 0;
        virtual void on_buat_laporan_activate() = 0;
        virtual void on_tambah_entri_perusahaan1_activate() = 0;
        virtual void on_quit1_activate() = 0;
        virtual void on_sumber_data1_activate() = 0;
        virtual void on_posting_pengiriman_data1_activate() = 0;
        virtual void on_mulai_baca_data1_activate() = 0;
        virtual void on_stop_baca_data1_activate() = 0;
        virtual void on_about1_activate() = 0;
        virtual void on_buttonbuka_clicked() = 0;
        virtual void on_button_sumber_clicked() = 0;
        virtual void on_button_logging_data_clicked() = 0;
        virtual void on_treeview1_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path) = 0;
        virtual void on_treeview1_cursor_changed() = 0;
        virtual bool on_treeview1_button_press_event(GdkEventButton *ev) = 0;
        virtual void on_button_open_kalender_clicked() = 0;
        virtual void on_button_tanggal_apply_clicked() = 0;
        virtual bool on_tree_data_button_press_event(GdkEventButton *ev) = 0;
        virtual void on_button_refresh_clicked() = 0;
        virtual bool on_drawingarea1_expose_event(GdkEventExpose *ev) = 0;
        virtual void on_notebook1_switch_page(GtkNotebookPage *p0, guint p1) = 0;
        virtual void on_tree_status_cursor_changed() = 0;
        virtual bool on_tree_status_button_press_event(GdkEventButton *ev) = 0;
        virtual bool on_main_window_delete_event(GdkEventAny *ev) = 0;
};
#endif
