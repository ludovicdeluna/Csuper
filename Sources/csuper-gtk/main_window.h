/*!
 * \file    main_window.h
 * \author  Remi BERTHO
 * \date    28/07/15
 * \version 4.3.0
 */

/*
 * main_window.h
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


#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class MainWindow
*   \brief This class represent the main window
*/
class MainWindow : public CsuWidget, public Gtk::ApplicationWindow
{
protected:
    Gtk::HeaderBar* header_bar_;            /*!< The HeaderBar */
    Gtk::MenuButton* display_menu_button_;  /*!< The display MenuButton */
    Gtk::MenuButton* edit_menu_button_;     /*!< The edit MenuButton */
    Gtk::MenuButton* file_menu_button_;     /*!< The file MenuButton */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
};



#endif // MAIN_WINDOW_H_INCLUDED
