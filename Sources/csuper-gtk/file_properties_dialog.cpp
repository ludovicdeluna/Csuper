/*!
 * \file    file_properties_dialog.cpp
 * \author  Remi BERTHO
 * \date    25/08/15
 * \version 4.3.0
 */

/*
 * file_properties_dialog.cpp
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

#include "file_properties_dialog.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace csuper;


//
// Constructor and destructor
//
FilePropertiesDialog::FilePropertiesDialog(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Dialog(cobject)
{
    refGlade->get_widget("button_validate_properties", ok_button_);
    refGlade->get_widget("file_properties_main_grid", main_grid_);
    refGlade->get_widget("file_properties_label", prop_label_);

    ok_button_->set_image_from_icon_name("gtk-ok",ICON_SIZE_BUTTON);
}

//
// Function
//
void FilePropertiesDialog::launch()
{
    prop_label_->set_text(app()->game()->toUstringProperties());
    run();
    hide();
}
