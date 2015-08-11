/*!
 * \file    menu_file.h
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
 * menu_file.h
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

#ifndef MENU_FILE_H_INCLUDED
#define MENU_FILE_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class MenuFile
*   \brief This class represent the menu file
*/
class MenuFile : public CsuWidget, public Gtk::Menu
{
protected:
    Gtk::MenuItem* save_as_;        /*!< The save as button */
    Gtk::MenuItem* export_;         /*!< The export button */
    Gtk::SeparatorMenuItem* sep_1_; /*!< The separator 1 */
    Gtk::MenuItem* prop_;           /*!< The properties button */
    Gtk::SeparatorMenuItem* sep_2_; /*!< The separator 2 */
    Gtk::MenuItem* delete_;         /*!< The delete file button */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    MenuFile(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
};



#endif // MENU_FILE_H_INCLUDED
