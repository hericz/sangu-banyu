// generated 2008/10/17 18:38:33 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to pm_server.cc_new

// This file is for your program, I won't touch it again!

#include <config.h>
#include <gtkmm/main.h>
#include <glib/gi18n.h>

#include "Monita PM Server.hh"

int main(int argc, char **argv)
{  
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS
   
   Gtk::Main m(&argc, &argv);

Monita_PM_Server *Monita_PM_Server = new class Monita_PM_Server();
   m.run(*Monita_PM_Server);
delete Monita_PM_Server;
   return 0;
}
