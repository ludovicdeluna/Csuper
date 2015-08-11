/*!
 * \file    display_preferences.h
 * \author  Remi BERTHO
 * \date    10/08/15
 * \version 4.3.0
 */

/*
 * display_preferences.h
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

#ifndef DISPLAY_PREFERENCES_H_INCLUDED
#define DISPLAY_PREFERENCES_H_INCLUDED

#include <gtkmm.h>
#include "../libcsuper/libcsuper.h"


#include "csu_widget.h"


/*! \class DisplayPreferences
*   \brief This class represent the display preferences scrolled window
*/
class DisplayPreferences : public CsuWidget, public Gtk::ScrolledWindow
{
protected:
    Gtk::Grid* main_grid_;                  /*!< The main grid */
    Gtk::Viewport* viewport_;               /*!< The viewport */

    Gtk::Label* title_bar_label_;               /*!< The title bar label */
    Gtk::Label* title_bar_decoration_label_;    /*!< The title bar decoration label */
    Gtk::Switch* title_bar_decoration_switch_;  /*!< The title bar decoration switch */
    Gtk::Label* title_bar_title_label_;         /*!< The title bar title label */
    Gtk::Switch* title_bar_title_switch_;       /*!< The title bar title switch */




public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    DisplayPreferences(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);


    //
    // Function
    //
    /*!
     *  \brief Update the view
     */
    void update();


    /*!
     *  \brief Read the title bar preferences
     */
    csuper::MainWindowTitleBarPreferences readTitleBar();
};


#endif // DISPLAY_PREFERENCES_H_INCLUDED
