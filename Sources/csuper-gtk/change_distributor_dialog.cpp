/*!
 * \file    change_distributor_dialog.cpp
 * \author  Remi BERTHO
 * \date    18/09/15
 * \version 4.3.0
 */

/*
 * change_distributor_dialog.cpp
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

#include "change_distributor_dialog.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace csuper;


//
// Constructor and destructor
//
ChangeDistributorDialog::ChangeDistributorDialog(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Dialog(cobject)
{
    refGlade->get_widget("change_distributor_dialog_button_validate", ok_button_);
    refGlade->get_widget("change_distributor_dialog_button_cancel", cancel_button_);
    refGlade->get_widget("change_distributor_dialog_label", title_);
    refGlade->get_widget("change_distributor_dialog_grid", main_grid_);
    refGlade->get_widget("change_distributor_dialog_scrolledwindow", window_);
    refGlade->get_widget("change_distributor_dialog_viewport", viewport_);

    ok_button_->set_image_from_icon_name("gtk-ok",ICON_SIZE_BUTTON);
    cancel_button_->set_image_from_icon_name("gtk-cancel",ICON_SIZE_BUTTON);
}

//
// Function
//
bool ChangeDistributorDialog::launch()
{
    bool res = false;

    Grid* grid = new Grid();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    grid->set_column_homogeneous(true);
    #if GTK_MINOR_VERSION >= 12
    grid->set_margin_end(10);
    grid->set_margin_start(10);
    #else
    grid->set_margin_right(10);
    grid->set_margin_left(10);
    #endif // GTK_MINOR_VERSION
    grid->set_margin_top(10);
    grid->set_margin_bottom(10);

    RadioButton* tmp_button = manage(new RadioButton(app()->game()->playerName(0)));
    RadioButtonGroup group = tmp_button->get_group();
    grid->attach(*tmp_button,0,0,1,1);
    for (unsigned int i=1 ; i<app()->game()->nbPlayer() ; i++)
    {
        tmp_button = manage(new RadioButton(group,app()->game()->playerName(i)));
        grid->attach(*tmp_button,0,i,1,1);
    }

    static_cast<RadioButton*>(grid->get_child_at(0,app()->game()->distributor()))->set_active(true);

    viewport_->add(*grid);

    show_all();
    switch(run())
    {
    case RESPONSE_ACCEPT:
        res= true;
        unsigned int i;
        for (i=0 ; i<app()->game()->nbPlayer() ; i++)
        {
            if (static_cast<RadioButton*>(grid->get_child_at(0,i))->get_active())
                break;
        }
        app()->game()->setDistributor(i);
        break;
    case RESPONSE_CANCEL:
        break;
    default:
        break;
    }
    hide();

    delete grid;

    return res;
}
