// generated 2008/8/8 16:24:27 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dl_edit_titik.cc_new

// This file is for your program, I won't touch it again!

#include <config.h>
#include <gtkmm/main.h>
#include <glib/gi18n.h>

#include "dlg_edit_titik.hh"

int main(int argc, char **argv)
{  
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS
   
   Gtk::Main m(&argc, &argv);

dlg_edit_titik *dlg_edit_titik = new class dlg_edit_titik();
   m.run(*dlg_edit_titik);
delete dlg_edit_titik;
   return 0;
}
