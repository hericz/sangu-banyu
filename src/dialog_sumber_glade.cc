// generated 2008/8/3 23:21:06 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Monita/src/db_dialog.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//dialog_sumber.cc


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
#include "dialog_sumber_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>

dialog_sumber_glade::dialog_sumber_glade(
)
{  dialog_sumber = this;
   gmm_data = new GlademmData(get_accel_group());
   cancelbutton2 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-cancel")));
   okbutton2 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-ok")));
   treeview2 = Gtk::manage(new class Gtk::TreeView());
   scrolledwindow1 = Gtk::manage(new class Gtk::ScrolledWindow());
   button_tambah = Gtk::manage(new class Gtk::Button(_("_Tambah"), true));
   button_hapus = Gtk::manage(new class Gtk::Button(_("_Hapus"), true));
   button_edit = Gtk::manage(new class Gtk::Button(_("_Edit"), true));
   vbuttonbox1 = Gtk::manage(new class Gtk::VButtonBox(Gtk::BUTTONBOX_START, 7));
   button_koneksi = Gtk::manage(new class Gtk::Button(_("_Lihat Koneksi"), true));
   vbuttonbox2 = Gtk::manage(new class Gtk::VButtonBox(Gtk::BUTTONBOX_DEFAULT_STYLE, 0));
   label_info = Gtk::manage(new class Gtk::Label(_("Info")));
   alignment2 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   label11 = Gtk::manage(new class Gtk::Label(_("Info")));
   frame3 = Gtk::manage(new class Gtk::Frame());
   vbox1 = Gtk::manage(new class Gtk::VBox(false, 0));
   hbox2 = Gtk::manage(new class Gtk::HBox(false, 0));
   alignment1 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   label10 = Gtk::manage(new class Gtk::Label(_("<b>Setting Sumber Data</b>")));
   frame2 = Gtk::manage(new class Gtk::Frame());
   hbox1 = Gtk::manage(new class Gtk::HBox(false, 0));
   cancelbutton2->set_flags(Gtk::CAN_FOCUS);
   cancelbutton2->set_flags(Gtk::CAN_DEFAULT);
   cancelbutton2->set_relief(Gtk::RELIEF_NORMAL);
   okbutton2->set_flags(Gtk::CAN_FOCUS);
   okbutton2->set_flags(Gtk::CAN_DEFAULT);
   okbutton2->set_relief(Gtk::RELIEF_NORMAL);
   dialog_sumber->get_action_area()->property_layout_style().set_value(Gtk::BUTTONBOX_END);
   treeview2->set_flags(Gtk::CAN_FOCUS);
   treeview2->set_headers_visible(true);
   treeview2->set_rules_hint(false);
   treeview2->set_reorderable(false);
   treeview2->set_enable_search(true);
   scrolledwindow1->set_flags(Gtk::CAN_FOCUS);
   scrolledwindow1->set_shadow_type(Gtk::SHADOW_IN);
   scrolledwindow1->set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
   scrolledwindow1->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow1->add(*treeview2);
   button_tambah->set_flags(Gtk::CAN_FOCUS);
   button_tambah->set_flags(Gtk::CAN_DEFAULT);
   button_tambah->set_relief(Gtk::RELIEF_NORMAL);
   button_hapus->set_flags(Gtk::CAN_FOCUS);
   button_hapus->set_flags(Gtk::CAN_DEFAULT);
   button_hapus->set_relief(Gtk::RELIEF_NORMAL);
   button_edit->set_flags(Gtk::CAN_FOCUS);
   button_edit->set_flags(Gtk::CAN_DEFAULT);
   button_edit->set_relief(Gtk::RELIEF_NORMAL);
   vbuttonbox1->pack_start(*button_tambah);
   vbuttonbox1->pack_start(*button_hapus);
   vbuttonbox1->pack_start(*button_edit);
   button_koneksi->set_flags(Gtk::CAN_FOCUS);
   button_koneksi->set_flags(Gtk::CAN_DEFAULT);
   button_koneksi->set_relief(Gtk::RELIEF_NORMAL);
   vbuttonbox2->pack_start(*button_koneksi);
   label_info->set_alignment(0.1,0.1);
   label_info->set_padding(0,0);
   label_info->set_justify(Gtk::JUSTIFY_LEFT);
   label_info->set_line_wrap(true);
   label_info->set_use_markup(true);
   label_info->set_selectable(false);
   alignment2->add(*label_info);
   label11->set_alignment(0.5,0.5);
   label11->set_padding(0,0);
   label11->set_justify(Gtk::JUSTIFY_LEFT);
   label11->set_line_wrap(false);
   label11->set_use_markup(true);
   label11->set_selectable(false);
   frame3->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame3->set_label_align(0,0.5);
   frame3->add(*alignment2);
   frame3->set_label_widget(*label11);
   vbox1->pack_start(*vbuttonbox1);
   vbox1->pack_start(*vbuttonbox2);
   vbox1->pack_start(*frame3);
   hbox2->pack_start(*scrolledwindow1);
   hbox2->pack_start(*vbox1, Gtk::PACK_SHRINK, 5);
   alignment1->add(*hbox2);
   label10->set_alignment(0.5,0.5);
   label10->set_padding(0,0);
   label10->set_justify(Gtk::JUSTIFY_LEFT);
   label10->set_line_wrap(false);
   label10->set_use_markup(true);
   label10->set_selectable(false);
   frame2->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame2->set_label_align(0,0.5);
   frame2->add(*alignment1);
   frame2->set_label_widget(*label10);
   hbox1->pack_start(*frame2);
   dialog_sumber->get_vbox()->set_homogeneous(false);
   dialog_sumber->get_vbox()->set_spacing(0);
   dialog_sumber->get_vbox()->pack_start(*hbox1);
   dialog_sumber->set_size_request(600,400);
   dialog_sumber->set_title(_("Sumber Data"));
   dialog_sumber->set_default_size(600,400);
   dialog_sumber->set_modal(true);
   dialog_sumber->property_window_position().set_value(Gtk::WIN_POS_CENTER_ON_PARENT);
   dialog_sumber->set_resizable(true);
   dialog_sumber->property_destroy_with_parent().set_value(false);
   dialog_sumber->set_has_separator(true);
   dialog_sumber->add_action_widget(*cancelbutton2, -6);
   dialog_sumber->add_action_widget(*okbutton2, -5);
   cancelbutton2->show();
   okbutton2->show();
   treeview2->show();
   scrolledwindow1->show();
   button_tambah->show();
   button_hapus->show();
   button_edit->show();
   vbuttonbox1->show();
   button_koneksi->show();
   vbuttonbox2->show();
   label_info->show();
   alignment2->show();
   label11->show();
   frame3->show();
   vbox1->show();
   hbox2->show();
   alignment1->show();
   label10->show();
   frame2->show();
   hbox1->show();
   dialog_sumber->show();
   button_tambah->signal_clicked().connect(SigC::slot(*this, &dialog_sumber_glade::on_button_tambah_clicked), false);
   button_hapus->signal_clicked().connect(SigC::slot(*this, &dialog_sumber_glade::on_button_hapus_clicked), false);
   button_edit->signal_clicked().connect(SigC::slot(*this, &dialog_sumber_glade::on_button_edit_clicked), false);
   button_koneksi->signal_clicked().connect(SigC::slot(*this, &dialog_sumber_glade::on_button_koneksi_clicked), false);
}

dialog_sumber_glade::~dialog_sumber_glade()
{  delete gmm_data;
}