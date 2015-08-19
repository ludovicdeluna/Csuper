/*!
 * \file    new_file_assistant_page_1.h
 * \author  Remi BERTHO
 * \date    13/08/15
 * \version 4.3.0
 */

/*
 * new_file_assistant_page_1.h
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

#include "new_file_assistant_page_1.h"

using namespace Gtk;
using namespace Glib;

NewFileAssistantPage1::NewFileAssistantPage1(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :
    CsuWidget(), Grid(cobject)
{
    refGlade->get_widget("new_csu_file_assistant_page_1_name_label", name_label_);
    refGlade->get_widget("new_csu_file_assistant_page_1_name_entry", name_entry_);

    refGlade->get_widget("new_csu_file_assistant_page_1_folder_label", folder_label_);
    refGlade->get_widget("new_csu_file_assistant_page_1_folder_chooser", folder_chooser_);

    refGlade->get_widget("new_csu_file_assistant_page_1_nb_player_label", nb_player_label_);
    refGlade->get_widget("new_csu_file_assistant_page_1_nb_player_spinbutton", nb_player_spinbutton_);

    refGlade->get_widget("new_csu_file_assistant_page_1_game_config_label", game_config_label_);
}
