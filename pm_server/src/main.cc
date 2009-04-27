/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Herry Susanto 2008 <herry@daunbiru.com>
 * 
 */

#include <libglademm/xml.h>
#include <gtkmm.h>
#include <iostream>

#include "main_window.hh"

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif


/* For testing propose use the local (not installed) glade file */
/* #define GLADE_FILE PACKAGE_DATA_DIR"/pm_server/glade/pm_server.glade" */
#define GLADE_FILE "pm_server.glade"


int main(int argc, char **argv)
{  
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS
   
   	Gtk::Main m(&argc, &argv);

	main_window *main_win=new class main_window(); 
	
	m.run(*main_win);
	printf("Hapus Main Window\n");
	delete main_win;
	printf("[/Tutup aplikasi]\n");
	return 0;
}
/*
int
main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	
	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gnome::Glade::Xml> refXml;
	try
	{
		refXml = Gnome::Glade::Xml::create(GLADE_FILE);
	}
	catch(const Gnome::Glade::XmlError& ex)
    {
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	Gtk::Window* main_win = 0;
	refXml->get_widget("main_window", main_win);
	if (main_win)
	{
		kit.run(*main_win);
	}
	return 0;
}
*/
