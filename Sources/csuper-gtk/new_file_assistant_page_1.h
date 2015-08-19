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

#ifndef NEW_FILE_ASSISTANT_PAGE_1_H_INCLUDED
#define NEW_FILE_ASSISTANT_PAGE_1_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class NewFileAssistantPage1
*   \brief This class represent the scrolled window of the first page of the new assistant
*/
class NewFileAssistantPage1 : public CsuWidget, public Gtk::Grid
{
protected:
    Gtk::Label* name_label_;    /*!< The name label */
    Gtk::Entry* name_entry_;    /*!< The name entry */

    Gtk::Label* folder_label_;                  /*!< The folder label */
    Gtk::FileChooserButton* folder_chooser_;    /*!< The folder file chooser */

    Gtk::Label* nb_player_label_;           /*!< The nb player label */
    Gtk::SpinButton* nb_player_spinbutton_; /*!< The nb player spinbutton */

    Gtk::Label* game_config_label_;                     /*!< The game configuration label */
    Gtk::ComboBoxText* game_config_combobox_ = nullptr; /*!< The game configuration combobox */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    NewFileAssistantPage1(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

    friend class NewFileAssistant;
};


#endif // NEW_FILE_ASSISTANT_PAGE_1_H_INCLUDED
