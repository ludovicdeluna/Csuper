/*!
 * \file    new_file_assistant_page_3.cpp
 * \author  Remi BERTHO
 * \date    18/08/15
 * \version 4.3.0
 */

/*
 * new_file_assistant_page_3.cpp
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-gtk.
 *
 * Csuper-gtk is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-gtk is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include "new_file_assistant_page_3.h"

#include <glibmm/i18n.h>
#include "csu_application.h"


using namespace Gtk;
using namespace Glib;

NewFileAssistantPage3::NewFileAssistantPage3() : CsuWidget(), Grid()
{
    set_column_spacing(10);
    set_row_spacing(10);
    set_column_homogeneous(true);
    #if GTK_MINOR_VERSION >= 12
    set_margin_end(10);
    set_margin_start(10);
    #else
    set_margin_right(10);
    set_margin_left(10);
    #endif // GTK_MINOR_VERSION
    set_margin_top(10);
    set_margin_bottom(10);

    distributor_label_ = manage(new Label(_("Select the distributor")));
    attach(*distributor_label_,0,0,1,1);

    distributor_combobox_ = manage(new ComboBoxText());
    attach(*distributor_combobox_,1,0,1,1);
}
