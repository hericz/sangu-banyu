/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) herry 2008 <herry@daunbiru.com>
 * 
 */
	
#include "main.hh"
//#include "common.hh"

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

/* For testing propose use the local (not installed) glade file */
/* #define GLADE_FILE PACKAGE_DATA_DIR"/monitaapp/glade/monitaapp.glade" */
#define GLADE_FILE "monitaapp.glade"

int main(int argc, char **argv)
{  
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS
   
   	Gtk::Main m(&argc, &argv);
	
	main_win=new class main_window(); 
	
	m.run(*main_win);
	printf("Hapus Main Window\n");
	delete main_win;
	printf("[/Tutup aplikasi]\n");
	return 0;
}
