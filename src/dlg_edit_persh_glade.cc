// generated 2008/9/5 11:35:14 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Monita/src/monitaapp.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//dlg_edit_persh.cc


#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (GETTEXT_PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif
#include <gtkmmconfig.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //
#include "dlg_edit_persh_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/table.h>
#include <gtkmm/alignment.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>

dlg_edit_persh_glade::dlg_edit_persh_glade(
)
{  
   
   Gtk::Dialog *dlg_edit_persh = this;
   gmm_data = new GlademmData(get_accel_group());
   
   Gtk::Button *cancelbutton3 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-cancel")));
   Gtk::Button *okbutton3 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-ok")));
   entry_nama = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label15 = Gtk::manage(new class Gtk::Label(_("Nama Perusahaan")));
   textview_keterangan = Gtk::manage(new class Gtk::TextView());
   
   Gtk::ScrolledWindow *scrolledwindow10 = Gtk::manage(new class Gtk::ScrolledWindow());
   Gtk::Label *label16 = Gtk::manage(new class Gtk::Label(_("Alamat")));
   Gtk::Label *label17 = Gtk::manage(new class Gtk::Label(_("Keterangan")));
   entry_alamat = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label18 = Gtk::manage(new class Gtk::Label(_("Gambar")));
   entry_gambar = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Button *button_browse = Gtk::manage(new class Gtk::Button(_("_Pilih Gambar"), true));
   Gtk::Table *table3 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::Alignment *alignment8 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   Gtk::Label *label14 = Gtk::manage(new class Gtk::Label(_("Informasi Perusahaan")));
   Gtk::Frame *frame4 = Gtk::manage(new class Gtk::Frame());
   cancelbutton3->set_flags(Gtk::CAN_FOCUS);
   cancelbutton3->set_flags(Gtk::CAN_DEFAULT);
   cancelbutton3->add_accelerator("clicked", gmm_data->getAccelGroup(), GDK_Escape, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
   cancelbutton3->set_relief(Gtk::RELIEF_NORMAL);
   okbutton3->set_flags(Gtk::CAN_FOCUS);
   okbutton3->set_flags(Gtk::CAN_DEFAULT);
   okbutton3->add_accelerator("clicked", gmm_data->getAccelGroup(), GDK_Return, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
   okbutton3->set_relief(Gtk::RELIEF_NORMAL);
   dlg_edit_persh->get_action_area()->property_layout_style().set_value(Gtk::BUTTONBOX_END);
   entry_nama->set_flags(Gtk::CAN_FOCUS);
   entry_nama->set_visibility(true);
   entry_nama->set_editable(true);
   entry_nama->set_max_length(0);
   entry_nama->set_text(_(""));
   entry_nama->set_has_frame(true);
   entry_nama->set_activates_default(false);
   label15->set_alignment(0,0.5);
   label15->set_padding(0,0);
   label15->set_justify(Gtk::JUSTIFY_LEFT);
   label15->set_line_wrap(false);
   label15->set_use_markup(false);
   label15->set_selectable(false);
   textview_keterangan->set_flags(Gtk::CAN_FOCUS);
   textview_keterangan->set_editable(true);
   textview_keterangan->set_cursor_visible(true);
   textview_keterangan->set_pixels_above_lines(0);
   textview_keterangan->set_pixels_below_lines(0);
   textview_keterangan->set_pixels_inside_wrap(0);
   textview_keterangan->set_left_margin(0);
   textview_keterangan->set_right_margin(0);
   textview_keterangan->set_indent(0);
   textview_keterangan->set_wrap_mode(Gtk::WRAP_NONE);
   textview_keterangan->set_justification(Gtk::JUSTIFY_LEFT);
   scrolledwindow10->set_flags(Gtk::CAN_FOCUS);
   scrolledwindow10->set_shadow_type(Gtk::SHADOW_IN);
   scrolledwindow10->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow10->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow10->add(*textview_keterangan);
   label16->set_alignment(0,0.5);
   label16->set_padding(0,0);
   label16->set_justify(Gtk::JUSTIFY_LEFT);
   label16->set_line_wrap(false);
   label16->set_use_markup(false);
   label16->set_selectable(false);
   label17->set_alignment(0,0.5);
   label17->set_padding(0,0);
   label17->set_justify(Gtk::JUSTIFY_LEFT);
   label17->set_line_wrap(false);
   label17->set_use_markup(false);
   label17->set_selectable(false);
   entry_alamat->set_flags(Gtk::CAN_FOCUS);
   entry_alamat->set_visibility(true);
   entry_alamat->set_editable(true);
   entry_alamat->set_max_length(0);
   entry_alamat->set_text(_(""));
   entry_alamat->set_has_frame(true);
   entry_alamat->set_activates_default(false);
   label18->set_alignment(0,0.5);
   label18->set_padding(0,0);
   label18->set_justify(Gtk::JUSTIFY_LEFT);
   label18->set_line_wrap(false);
   label18->set_use_markup(false);
   label18->set_selectable(false);
   entry_gambar->set_flags(Gtk::CAN_FOCUS);
   entry_gambar->set_visibility(true);
   entry_gambar->set_editable(true);
   entry_gambar->set_max_length(0);
   entry_gambar->set_text(_(""));
   entry_gambar->set_has_frame(true);
   entry_gambar->set_activates_default(false);
   button_browse->set_flags(Gtk::CAN_FOCUS);
   button_browse->set_relief(Gtk::RELIEF_NORMAL);
   table3->set_row_spacings(0);
   table3->set_col_spacings(0);
   table3->attach(*entry_nama, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table3->attach(*label15, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table3->attach(*scrolledwindow10, 1, 2, 3, 4, Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 0);
   table3->attach(*label16, 0, 1, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table3->attach(*label17, 0, 1, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table3->attach(*entry_alamat, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table3->attach(*label18, 0, 1, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table3->attach(*entry_gambar, 1, 2, 2, 3, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table3->attach(*button_browse, 2, 3, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   alignment8->add(*table3);
   label14->set_alignment(0.5,0.5);
   label14->set_padding(0,0);
   label14->set_justify(Gtk::JUSTIFY_LEFT);
   label14->set_line_wrap(false);
   label14->set_use_markup(true);
   label14->set_selectable(false);
   frame4->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame4->set_label_align(0,0.5);
   frame4->add(*alignment8);
   frame4->set_label_widget(*label14);
   dlg_edit_persh->get_vbox()->set_homogeneous(false);
   dlg_edit_persh->get_vbox()->set_spacing(0);
   dlg_edit_persh->get_vbox()->pack_start(*frame4);
   dlg_edit_persh->set_title(_("Perusahaan"));
   dlg_edit_persh->set_modal(true);
   dlg_edit_persh->property_window_position().set_value(Gtk::WIN_POS_NONE);
   dlg_edit_persh->set_resizable(true);
   dlg_edit_persh->property_destroy_with_parent().set_value(false);
   dlg_edit_persh->set_has_separator(true);
   dlg_edit_persh->add_action_widget(*cancelbutton3, -6);
   dlg_edit_persh->add_action_widget(*okbutton3, -5);
   cancelbutton3->show();
   okbutton3->show();
   entry_nama->show();
   label15->show();
   textview_keterangan->show();
   scrolledwindow10->show();
   label16->show();
   label17->show();
   entry_alamat->show();
   label18->show();
   entry_gambar->show();
   button_browse->show();
   table3->show();
   alignment8->show();
   label14->show();
   frame4->show();
   dlg_edit_persh->show();
   okbutton3->signal_clicked().connect(SigC::slot(*this, &dlg_edit_persh_glade::on_okbutton3_clicked), false);
}

dlg_edit_persh_glade::~dlg_edit_persh_glade()
{  delete gmm_data;
}
