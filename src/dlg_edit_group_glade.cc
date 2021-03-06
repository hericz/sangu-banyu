// generated 2008/9/5 13:32:45 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Monita/src/monitaapp.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//dlg_edit_group.cc


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
#include "dlg_edit_group_glade.hh"
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

dlg_edit_group_glade::dlg_edit_group_glade(
)
{  
   
   Gtk::Dialog *dlg_edit_group = this;
   gmm_data = new GlademmData(get_accel_group());
   
   Gtk::Button *cancelbutton2 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-cancel")));
   Gtk::Button *okbutton2 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-ok")));
   Gtk::Label *label10 = Gtk::manage(new class Gtk::Label(_("Jenis Group")));
   entry_nama = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label11 = Gtk::manage(new class Gtk::Label(_("Nama Group")));
   Gtk::Label *label12 = Gtk::manage(new class Gtk::Label(_("Logo")));
   textview_keterangan = Gtk::manage(new class Gtk::TextView());
   
   Gtk::ScrolledWindow *scrolledwindow9 = Gtk::manage(new class Gtk::ScrolledWindow());
   Gtk::Label *label13 = Gtk::manage(new class Gtk::Label(_("Keterangan")));
   combo_jenis = Gtk::manage(new class Gtk::ComboBox());
   entry_gambar = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Button *button1 = Gtk::manage(new class Gtk::Button(_("_Pilih Gambar"), true));
   Gtk::Table *table2 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::Alignment *alignment7 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   Gtk::Label *label9 = Gtk::manage(new class Gtk::Label(_("Group Titik Ukur")));
   Gtk::Frame *frame3 = Gtk::manage(new class Gtk::Frame());
   cancelbutton2->set_flags(Gtk::CAN_FOCUS);
   cancelbutton2->set_flags(Gtk::CAN_DEFAULT);
   cancelbutton2->add_accelerator("clicked", gmm_data->getAccelGroup(), GDK_Escape, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
   cancelbutton2->set_relief(Gtk::RELIEF_NORMAL);
   okbutton2->set_flags(Gtk::CAN_FOCUS);
   okbutton2->set_flags(Gtk::CAN_DEFAULT);
   okbutton2->add_accelerator("clicked", gmm_data->getAccelGroup(), GDK_Return, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
   okbutton2->set_relief(Gtk::RELIEF_NORMAL);
   dlg_edit_group->get_action_area()->property_layout_style().set_value(Gtk::BUTTONBOX_END);
   label10->set_alignment(0,0.5);
   label10->set_padding(0,0);
   label10->set_justify(Gtk::JUSTIFY_LEFT);
   label10->set_line_wrap(false);
   label10->set_use_markup(false);
   label10->set_selectable(false);
   entry_nama->set_flags(Gtk::CAN_FOCUS);
   entry_nama->set_visibility(true);
   entry_nama->set_editable(true);
   entry_nama->set_max_length(0);
   entry_nama->set_text(_(""));
   entry_nama->set_has_frame(true);
   entry_nama->set_activates_default(false);
   label11->set_alignment(0,0.5);
   label11->set_padding(0,0);
   label11->set_justify(Gtk::JUSTIFY_LEFT);
   label11->set_line_wrap(false);
   label11->set_use_markup(false);
   label11->set_selectable(false);
   label12->set_alignment(0,0.5);
   label12->set_padding(0,0);
   label12->set_justify(Gtk::JUSTIFY_LEFT);
   label12->set_line_wrap(false);
   label12->set_use_markup(false);
   label12->set_selectable(false);
   textview_keterangan->set_size_request(50,50);
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
   scrolledwindow9->set_flags(Gtk::CAN_FOCUS);
   scrolledwindow9->set_shadow_type(Gtk::SHADOW_IN);
   scrolledwindow9->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow9->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow9->add(*textview_keterangan);
   label13->set_alignment(0,0.5);
   label13->set_padding(0,0);
   label13->set_justify(Gtk::JUSTIFY_LEFT);
   label13->set_line_wrap(false);
   label13->set_use_markup(false);
   label13->set_selectable(false);
   entry_gambar->set_flags(Gtk::CAN_FOCUS);
   entry_gambar->set_visibility(true);
   entry_gambar->set_editable(true);
   entry_gambar->set_max_length(0);
   entry_gambar->set_text(_(""));
   entry_gambar->set_has_frame(true);
   entry_gambar->set_activates_default(false);
   button1->set_flags(Gtk::CAN_FOCUS);
   button1->set_relief(Gtk::RELIEF_NORMAL);
   table2->set_row_spacings(0);
   table2->set_col_spacings(0);
   table2->attach(*label10, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table2->attach(*entry_nama, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table2->attach(*label11, 0, 1, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table2->attach(*label12, 0, 1, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table2->attach(*scrolledwindow9, 1, 2, 3, 4, Gtk::FILL, Gtk::EXPAND|Gtk::FILL, 0, 0);
   table2->attach(*label13, 0, 1, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table2->attach(*combo_jenis, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::FILL, 0, 0);
   table2->attach(*entry_gambar, 1, 2, 2, 3, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table2->attach(*button1, 2, 3, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   alignment7->add(*table2);
   label9->set_alignment(0.5,0.5);
   label9->set_padding(0,0);
   label9->set_justify(Gtk::JUSTIFY_LEFT);
   label9->set_line_wrap(false);
   label9->set_use_markup(true);
   label9->set_selectable(false);
   frame3->set_shadow_type(Gtk::SHADOW_OUT);
   frame3->set_label_align(0,0.5);
   frame3->add(*alignment7);
   frame3->set_label_widget(*label9);
   dlg_edit_group->get_vbox()->set_homogeneous(false);
   dlg_edit_group->get_vbox()->set_spacing(0);
   dlg_edit_group->get_vbox()->pack_start(*frame3);
   dlg_edit_group->set_title(_("Group Titik Ukur"));
   dlg_edit_group->set_modal(false);
   dlg_edit_group->property_window_position().set_value(Gtk::WIN_POS_NONE);
   dlg_edit_group->set_resizable(true);
   dlg_edit_group->property_destroy_with_parent().set_value(false);
   dlg_edit_group->set_has_separator(true);
   dlg_edit_group->add_action_widget(*cancelbutton2, -6);
   dlg_edit_group->add_action_widget(*okbutton2, -5);
   cancelbutton2->show();
   okbutton2->show();
   label10->show();
   entry_nama->show();
   label11->show();
   label12->show();
   textview_keterangan->show();
   scrolledwindow9->show();
   label13->show();
   combo_jenis->show();
   entry_gambar->show();
   button1->show();
   table2->show();
   alignment7->show();
   label9->show();
   frame3->show();
   dlg_edit_group->show();
   okbutton2->signal_clicked().connect(SigC::slot(*this, &dlg_edit_group_glade::on_okbutton2_clicked), false);
}

dlg_edit_group_glade::~dlg_edit_group_glade()
{  delete gmm_data;
}
