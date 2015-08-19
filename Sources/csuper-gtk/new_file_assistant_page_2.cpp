/*!
 * \file    new_file_assistant_page_2.cpp
 * \author  Remi BERTHO
 * \date    17/08/15
 * \version 4.3.0
 */

/*
 * new_file_assistant_page_2.cpp
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

#include "new_file_assistant_page_2.h"

#include <glibmm/i18n.h>
#include "csu_application.h"


using namespace Gtk;
using namespace Glib;

NewFileAssistantPage2::NewFileAssistantPage2() : CsuWidget(), ScrolledWindow()
{
    viewport_ = manage(new Viewport(Adjustment::create(0,0,0),Adjustment::create(0,0,0)));
    add(*viewport_);

    grid_ = manage(new Grid());
    grid_->set_column_spacing(10);
    grid_->set_row_spacing(10);
    grid_->set_column_homogeneous(true);
    #if GTK_MINOR_VERSION >= 12
    grid_->set_margin_end(10);
    grid_->set_margin_start(10);
    #else
    grid_->set_margin_right(10);
    grid_->set_margin_left(10);
    #endif // GTK_MINOR_VERSION
    grid_->set_margin_top(10);
    grid_->set_margin_bottom(10);
    viewport_->add(*grid_);
}


void NewFileAssistantPage2::createLines(const unsigned int nb_player)
{
    // Add the missing lines
    for (unsigned int i=nb_ligne_ ; i < nb_player ; i++)
    {
        Entry* tmp_entry;
        grid_->attach(*manage(new Label(ustring::compose(_("Name of the %1th player"),i+1))),0,i,1,1);
        tmp_entry = manage(new Entry());
        grid_->attach(*tmp_entry,1,i,1,1);
        tmp_entry->set_placeholder_text(ustring::compose(_("Type here the name of the %1th player"),i+1));
        tmp_entry->set_alignment(0.5);
        tmp_entry->signal_changed().connect(mem_fun(*(app()->newFileAssistant()),&NewFileAssistant::validatePageTwo));
    }

    // Remove the unwanted lines
    for (unsigned int i = nb_ligne_ ; i > nb_player ; i--)
    {
        delete grid_->get_child_at(1,i-1);
        delete grid_->get_child_at(0,i-1);
    }
    grid_->show_all();
    nb_ligne_ = nb_player;
}


void NewFileAssistantPage2::deleteLines()
{
    for (unsigned int i = nb_ligne_ ; i > 0 ; i--)
    {
        delete grid_->get_child_at(1,i-1);
        delete grid_->get_child_at(0,i-1);
    }

    nb_ligne_ = 0;
}
