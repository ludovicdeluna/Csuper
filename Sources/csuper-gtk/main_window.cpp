/*!
 * \file    main_window.cpp
 * \author  Remi BERTHO
 * \date    28/07/15
 * \version 4.3.0
 */

/*
 * main_window.cpp
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "main_window.h"

#include <glibmm/i18n.h>


using namespace Gtk;
using namespace Glib;

MainWindow::MainWindow(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), ApplicationWindow(cobject)
{
    refGlade->get_widget("main_window_headerbar", header_bar_);

    refGlade->get_widget("menubutton_display", display_menu_button_);
    display_menu_button_->add_label(_("Display"));

    refGlade->get_widget("menubutton_edit", edit_menu_button_);
    edit_menu_button_->add_label(_("Edit"));

    refGlade->get_widget("menubutton_file", file_menu_button_);
    file_menu_button_->add_label(_("File"));
}
