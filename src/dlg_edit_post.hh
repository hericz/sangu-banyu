// generated 2008/8/8 19:42:02 WIT by herry@LancarJaya.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to dlg_edit_post.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _DLG_EDIT_POST_HH
#  include "dlg_edit_post_glade.hh"
#  define _DLG_EDIT_POST_HH
class dlg_edit_post : public dlg_edit_post_glade
{
	public:
	//konstruktor
		dlg_edit_post();
	//destruktor
		~dlg_edit_post();
		
	void on_parameter_changed();
	bool parameter_changed;
};
#endif
