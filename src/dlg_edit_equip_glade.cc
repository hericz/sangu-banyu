// generated 2008/9/5 11:34:24 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/herry/Monita/src/monitaapp.glade
// for gtk 2.12.9 and gtkmm 2.12.5
//
// Please modify the corresponding derived classes in .//dlg_edit_equip.cc


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
#include "dlg_edit_equip_glade.hh"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/table.h>
#include <gtkmm/frame.h>
#include <gtkmm/combobox.h>

dlg_edit_equip_glade::dlg_edit_equip_glade(
)
{  
   
   Gtk::Dialog *dlg_edit_equip = this;
   gmm_data = new GlademmData(get_accel_group());
   
   Gtk::Button *cancelbutton5 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-cancel")));
   Gtk::Button *okbutton5 = Gtk::manage(new class Gtk::Button(Gtk::StockID("gtk-ok")));
   entry_nama = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label24 = Gtk::manage(new class Gtk::Label(_("Nama Alat")));
   Gtk::Label *label25 = Gtk::manage(new class Gtk::Label(_("Kode")));
   Gtk::Label *label26 = Gtk::manage(new class Gtk::Label(_("Keterangan")));
   textview_keterangan = Gtk::manage(new class Gtk::TextView());
   
   Gtk::ScrolledWindow *scrolledwindow12 = Gtk::manage(new class Gtk::ScrolledWindow());
   entry_gambar = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Label *label27 = Gtk::manage(new class Gtk::Label(_("Gambar")));
   Gtk::Image *image44 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-open"), Gtk::IconSize(4)));
   Gtk::Label *label28 = Gtk::manage(new class Gtk::Label(_("_Pilih Gambar"), true));
   Gtk::HBox *hbox8 = Gtk::manage(new class Gtk::HBox(false, 2));
   Gtk::Alignment *alignment11 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 0, 0));
   button4 = Gtk::manage(new class Gtk::Button());
   
   Gtk::Label *label29 = Gtk::manage(new class Gtk::Label(_("Jenis")));
   combo_jenis = Gtk::manage(new class Gtk::ComboBox());
   entry_kode = Gtk::manage(new class Gtk::Entry());
   
   Gtk::Table *table5 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::Alignment *alignment10 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   Gtk::Label *label23 = Gtk::manage(new class Gtk::Label(_("Informasi Peralatan")));
   Gtk::Frame *frame6 = Gtk::manage(new class Gtk::Frame());
   Gtk::Label *label31 = Gtk::manage(new class Gtk::Label(_("Parameter input")));
   Gtk::ComboBox *combo_input1 = Gtk::manage(new class Gtk::ComboBox());
   Gtk::Label *label32 = Gtk::manage(new class Gtk::Label(_("Parameter Input 2")));
   Gtk::Label *label33 = Gtk::manage(new class Gtk::Label(_("Parameter Output")));
   Gtk::ComboBox *combo_input2 = Gtk::manage(new class Gtk::ComboBox());
   Gtk::ComboBox *combo_output1 = Gtk::manage(new class Gtk::ComboBox());
   Gtk::Label *label35 = Gtk::manage(new class Gtk::Label(_("Parameter Output 2")));
   Gtk::ComboBox *combo_output2 = Gtk::manage(new class Gtk::ComboBox());
   Gtk::Table *table6 = Gtk::manage(new class Gtk::Table(2, 2, false));
   Gtk::Alignment *alignment12 = Gtk::manage(new class Gtk::Alignment(0.5, 0.5, 1, 1));
   Gtk::Label *label30 = Gtk::manage(new class Gtk::Label(_("Informasi Operasional")));
   Gtk::Frame *frame7 = Gtk::manage(new class Gtk::Frame());
   Gtk::VBox *vbox5 = Gtk::manage(new class Gtk::VBox(false, 0));
   cancelbutton5->set_flags(Gtk::CAN_FOCUS);
   cancelbutton5->set_flags(Gtk::CAN_DEFAULT);
   cancelbutton5->add_accelerator("clicked", gmm_data->getAccelGroup(), GDK_Escape, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
   cancelbutton5->set_relief(Gtk::RELIEF_NORMAL);
   okbutton5->set_flags(Gtk::CAN_FOCUS);
   okbutton5->set_flags(Gtk::CAN_DEFAULT);
   okbutton5->add_accelerator("clicked", gmm_data->getAccelGroup(), GDK_Return, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
   okbutton5->set_relief(Gtk::RELIEF_NORMAL);
   dlg_edit_equip->get_action_area()->property_layout_style().set_value(Gtk::BUTTONBOX_END);
   entry_nama->set_flags(Gtk::CAN_FOCUS);
   entry_nama->set_visibility(true);
   entry_nama->set_editable(true);
   entry_nama->set_max_length(0);
   entry_nama->set_text(_(""));
   entry_nama->set_has_frame(true);
   entry_nama->set_activates_default(false);
   label24->set_alignment(0,0.5);
   label24->set_padding(0,0);
   label24->set_justify(Gtk::JUSTIFY_LEFT);
   label24->set_line_wrap(false);
   label24->set_use_markup(false);
   label24->set_selectable(false);
   label25->set_alignment(0,0.5);
   label25->set_padding(0,0);
   label25->set_justify(Gtk::JUSTIFY_LEFT);
   label25->set_line_wrap(false);
   label25->set_use_markup(false);
   label25->set_selectable(false);
   label26->set_alignment(0,0.5);
   label26->set_padding(0,0);
   label26->set_justify(Gtk::JUSTIFY_LEFT);
   label26->set_line_wrap(false);
   label26->set_use_markup(false);
   label26->set_selectable(false);
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
   scrolledwindow12->set_flags(Gtk::CAN_FOCUS);
   scrolledwindow12->set_shadow_type(Gtk::SHADOW_IN);
   scrolledwindow12->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   scrolledwindow12->property_window_placement().set_value(Gtk::CORNER_TOP_LEFT);
   scrolledwindow12->add(*textview_keterangan);
   entry_gambar->set_flags(Gtk::CAN_FOCUS);
   entry_gambar->set_visibility(true);
   entry_gambar->set_editable(true);
   entry_gambar->set_max_length(0);
   entry_gambar->set_text(_(""));
   entry_gambar->set_has_frame(true);
   entry_gambar->set_activates_default(false);
   label27->set_alignment(0,0.5);
   label27->set_padding(0,0);
   label27->set_justify(Gtk::JUSTIFY_LEFT);
   label27->set_line_wrap(false);
   label27->set_use_markup(false);
   label27->set_selectable(false);
   image44->set_alignment(0.5,0.5);
   image44->set_padding(0,0);
   label28->set_alignment(0.5,0.5);
   label28->set_padding(0,0);
   label28->set_justify(Gtk::JUSTIFY_LEFT);
   label28->set_line_wrap(false);
   label28->set_use_markup(false);
   label28->set_selectable(false);
   hbox8->pack_start(*image44, Gtk::PACK_SHRINK, 0);
   hbox8->pack_start(*label28, Gtk::PACK_SHRINK, 0);
   alignment11->add(*hbox8);
   button4->set_flags(Gtk::CAN_FOCUS);
   button4->set_relief(Gtk::RELIEF_NORMAL);
   button4->add(*alignment11);
   label29->set_alignment(0,0.5);
   label29->set_padding(0,0);
   label29->set_justify(Gtk::JUSTIFY_LEFT);
   label29->set_line_wrap(false);
   label29->set_use_markup(false);
   label29->set_selectable(false);
   entry_kode->set_flags(Gtk::CAN_FOCUS);
   entry_kode->set_visibility(true);
   entry_kode->set_editable(true);
   entry_kode->set_max_length(0);
   entry_kode->set_text(_(""));
   entry_kode->set_has_frame(true);
   entry_kode->set_activates_default(false);
   table5->set_row_spacings(0);
   table5->set_col_spacings(0);
   table5->attach(*entry_nama, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table5->attach(*label24, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table5->attach(*label25, 0, 1, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table5->attach(*label26, 0, 1, 4, 5, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table5->attach(*scrolledwindow12, 1, 2, 4, 5, Gtk::FILL, Gtk::FILL, 0, 0);
   table5->attach(*entry_gambar, 1, 2, 3, 4, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table5->attach(*label27, 0, 1, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table5->attach(*button4, 2, 3, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table5->attach(*label29, 0, 1, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table5->attach(*combo_jenis, 1, 2, 2, 3, Gtk::FILL, Gtk::FILL, 0, 0);
   table5->attach(*entry_kode, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   alignment10->add(*table5);
   label23->set_alignment(0.5,0.5);
   label23->set_padding(0,0);
   label23->set_justify(Gtk::JUSTIFY_LEFT);
   label23->set_line_wrap(false);
   label23->set_use_markup(true);
   label23->set_selectable(false);
   frame6->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame6->set_label_align(0,0.5);
   frame6->add(*alignment10);
   frame6->set_label_widget(*label23);
   label31->set_alignment(0,0.5);
   label31->set_padding(0,0);
   label31->set_justify(Gtk::JUSTIFY_LEFT);
   label31->set_line_wrap(false);
   label31->set_use_markup(false);
   label31->set_selectable(false);
   label32->set_alignment(0,0.5);
   label32->set_padding(0,0);
   label32->set_justify(Gtk::JUSTIFY_LEFT);
   label32->set_line_wrap(false);
   label32->set_use_markup(false);
   label32->set_selectable(false);
   label33->set_alignment(0,0.5);
   label33->set_padding(0,0);
   label33->set_justify(Gtk::JUSTIFY_LEFT);
   label33->set_line_wrap(false);
   label33->set_use_markup(false);
   label33->set_selectable(false);
   label35->set_alignment(0,0.5);
   label35->set_padding(0,0);
   label35->set_justify(Gtk::JUSTIFY_LEFT);
   label35->set_line_wrap(false);
   label35->set_use_markup(false);
   label35->set_selectable(false);
   table6->set_row_spacings(0);
   table6->set_col_spacings(0);
   table6->attach(*label31, 0, 1, 0, 1, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table6->attach(*combo_input1, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::FILL, 0, 0);
   table6->attach(*label32, 0, 1, 1, 2, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table6->attach(*label33, 0, 1, 2, 3, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table6->attach(*combo_input2, 1, 2, 1, 2, Gtk::FILL, Gtk::FILL, 0, 0);
   table6->attach(*combo_output1, 1, 2, 2, 3, Gtk::FILL, Gtk::FILL, 0, 0);
   table6->attach(*label35, 0, 1, 3, 4, Gtk::FILL, Gtk::AttachOptions(), 0, 0);
   table6->attach(*combo_output2, 1, 2, 3, 4, Gtk::FILL, Gtk::FILL, 0, 0);
   alignment12->add(*table6);
   label30->set_alignment(0.5,0.5);
   label30->set_padding(0,0);
   label30->set_justify(Gtk::JUSTIFY_LEFT);
   label30->set_line_wrap(false);
   label30->set_use_markup(true);
   label30->set_selectable(false);
   frame7->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
   frame7->set_label_align(0,0.5);
   frame7->add(*alignment12);
   frame7->set_label_widget(*label30);
   vbox5->pack_start(*frame6);
   vbox5->pack_start(*frame7);
   dlg_edit_equip->get_vbox()->set_homogeneous(false);
   dlg_edit_equip->get_vbox()->set_spacing(0);
   dlg_edit_equip->get_vbox()->pack_start(*vbox5);
   dlg_edit_equip->set_title(_("Peralatan"));
   dlg_edit_equip->set_modal(true);
   dlg_edit_equip->property_window_position().set_value(Gtk::WIN_POS_NONE);
   dlg_edit_equip->set_resizable(true);
   dlg_edit_equip->property_destroy_with_parent().set_value(true);
   dlg_edit_equip->set_has_separator(true);
   dlg_edit_equip->add_action_widget(*cancelbutton5, -6);
   dlg_edit_equip->add_action_widget(*okbutton5, -5);
   cancelbutton5->show();
   okbutton5->show();
   entry_nama->show();
   label24->show();
   label25->show();
   label26->show();
   textview_keterangan->show();
   scrolledwindow12->show();
   entry_gambar->show();
   label27->show();
   image44->show();
   label28->show();
   hbox8->show();
   alignment11->show();
   button4->show();
   label29->show();
   combo_jenis->show();
   entry_kode->show();
   table5->show();
   alignment10->show();
   label23->show();
   frame6->show();
   label31->show();
   combo_input1->show();
   label32->show();
   label33->show();
   combo_input2->show();
   combo_output1->show();
   label35->show();
   combo_output2->show();
   table6->show();
   alignment12->show();
   label30->show();
   frame7->show();
   vbox5->show();
   dlg_edit_equip->show();
   okbutton5->signal_clicked().connect(SigC::slot(*this, &dlg_edit_equip_glade::on_okbutton5_clicked), false);
}

dlg_edit_equip_glade::~dlg_edit_equip_glade()
{  delete gmm_data;
}
