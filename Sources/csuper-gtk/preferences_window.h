/*!
 * \file    preferences.h
 * \author  Remi BERTHO
 * \date    10/08/15
 * \version 4.3.0
 */

/*
 * preferences.h
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

#ifndef PREFERENCES_WINDOW_H_INCLUDED
#define PREFERENCES_WINDOW_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"
#include "exportation_preferences.h"
#include "display_preferences.h"

/*! \class PreferencesWindow
*   \brief This class represent the preferences window
*/
class PreferencesWindow : public CsuWidget, public Gtk::ApplicationWindow
{
protected:
    Gtk::Grid* main_grid_;                  /*!< The main grid */
    Gtk::Notebook* notebook_;               /*!< The notebook */
    Gtk::ButtonBox* button_box_;            /*!< The button box */
    Gtk::Button* apply_button_;             /*!< The apply button */
    Gtk::Button* ok_button_;                /*!< The OK button */
    Gtk::Button* close_button_;             /*!< The close button */
    Gtk::Label* exportation_label_;         /*!< The exportation label */
    Gtk::Label* display_label_;             /*!< The display label */



public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    PreferencesWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);



    //
    // Launch, stop
    //
    /*!
     *  \brief Show the game preferences window
     */
    void launch();


    /*!
     *  \brief Hide the game preferences window
     */
    void stop();


    //
    // Function
    //
    /*!
     *  \brief Check if the user change something in the preferences
     */
    void hasChange();

    /*!
     *  \brief Apply the new preferences
     */
    void apply();

    /*!
     *  \brief Validate the new preferences
     */
    void validate();
};



#endif // PREFERENCES_WINDOW_H_INCLUDED
