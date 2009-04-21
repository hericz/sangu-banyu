// generated 2008/8/8 19:42:02 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_post.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "dlg_edit_post.hh"

dlg_edit_post::dlg_edit_post()
{
	printf("[Inisialisasi dlg_edit_post]\n");
	parameter_changed=false;
}

dlg_edit_post::~dlg_edit_post ()
{
	printf("[dekonstruktor dialog edit post]\n");
}

void dlg_edit_post::on_parameter_changed()
{
	parameter_changed=true;
}
