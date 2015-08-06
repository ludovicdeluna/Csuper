/*!
 * \file    menu_file.cpp
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
 * menu_file.cpp
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


#include "menu_file.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;

MenuFile::MenuFile(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Menu(cobject)
{
    refGlade->get_widget("menu_save_as", save_as_);
    refGlade->get_widget("menu_export", export_);
    refGlade->get_widget("menuitem_separator5", sep_1_);
    refGlade->get_widget("menu_properties", prop_);
    refGlade->get_widget("menuitem_separator6", sep_2_);
    refGlade->get_widget("menu_delete_file", delete_);
}
