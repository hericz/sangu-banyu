## Process this file with automake to produce Makefile.in

## Created by Anjuta

gladedir = $(datadir)/pm_server/glade
glade_DATA = pm_server.glade

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(PM_SERVER_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = pm_server

pm_server_SOURCES = \
	main.cc    \
	main_window.cc    \
	main_window_glade.cc    \
	low_mod.c    \
	mbcrc.c    \
	ServerSocket.cpp    \
	Socket.cpp    

pm_server_LDFLAGS = 

pm_server_LDADD = $(PM_SERVER_LIBS)

EXTRA_DIST = $(glade_DATA)
