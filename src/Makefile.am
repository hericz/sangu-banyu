## Process this file with automake to produce Makefile.in

## Created by Anjuta

gladedir = $(datadir)/monitaapp/glade
glade_DATA = monitaapp.glade \
	db_setting.glade\
	db_dialog.glade

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(MONITAAPP_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = monitaapp

monitaapp_SOURCES = \
	main.cc    \
	main_window_glade.cc    \
	main_window.cc    \
	sql_routine.cc    \
	db_dialog.cc    \
	db_dialog_glade.cc    \
	dialog_sumber.cc    \
	dialog_sumber_glade.cc    \
	common.cc    \
	main_client.cc    \
	ClientSocket.cc    \
	Socket.cc    \
	dlg_edit_sumber_glade.cc    \
	dlg_edit_sumber.cc    \
	dlg_edit_titik.cc    \
	dlg_edit_titik_glade.cc    \
	dlg_koneksi_sumber.cc    \
	dlg_koneksi_sumber_glade.cc    \
	dlg_konfigurasi.cc    \
	dlg_konfigurasi_glade.cc    \
	dlg_posting_data.cc    \
	dlg_posting_data_glade.cc    \
	dlg_edit_post.cc    \
	dlg_edit_post_glade.cc    \
	dlg_kalender_glade.cc    \
	dlg_edit_group_glade.cc    \
	dlg_edit_group.cc    \
	dlg_edit_persh_glade.cc    \
	dlg_edit_persh.cc    \
	dlg_edit_dept.cc    \
	dlg_edit_dept_glade.cc    \
	dlg_edit_equip.cc    \
	dlg_edit_equip_glade.cc    \
	dlg_edit_data.cc    \
	dlg_edit_data_glade.cc    \
	dlg_report.cc    \
	dlg_report_glade.cc

monitaapp_CXXFLAGS = \
	-lmysqlclient \
	-I/usr/include/mysql

monitaapp_LDFLAGS = 

monitaapp_LDADD = $(MONITAAPP_LIBS)

EXTRA_DIST = $(glade_DATA)

INCLUDES = /usr/include/mysql

