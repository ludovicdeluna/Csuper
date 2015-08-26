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
 * along with this program; if not, write to the Free Software
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
    Gtk::Grid* main_grid_;                  /*!< The main grid */
    Gtk::HeaderBar* header_bar_;            /*!< The HeaderBar */

    Gtk::MenuButton* menu_display_button_;  /*!< The display MenuButton */
    Gtk::MenuButton* menu_edit_button_;     /*!< The edit MenuButton */
    Gtk::MenuButton* menu_file_button_;     /*!< The file MenuButton */

    Gtk::Button* new_button_;               /*!< The new Button */

    Gtk::MenuButton* open_recent_button_;                   /*!< The open recent MenuButton */
    Gtk::RecentChooserMenu* open_recent_menu_;              /*!< The open recent Menu */
    Glib::RefPtr<Gtk::RecentFilter> open_recent_filter_;    /*!< The open recent filter */
    Gtk::Button* open_button_;                              /*!< The open button */

    // Use only if the user use window manager decoration
    Gtk::MenuButton* csuper_menu_button_;   /*!< The csuper MenuButton */
    Gtk::Menu* csuper_menu_;                /*!< The csuper menu */
    Gtk::MenuItem* game_config_menu_item_;  /*!< The game config menuitem */
    Gtk::MenuItem* pref_menu_item_;         /*!< The preferences menuitem */
    Gtk::MenuItem* about_menu_item_;        /*!< The about menuitem */
    Gtk::MenuItem* update_menu_item_;       /*!< The update menuitem */
    Gtk::MenuItem* quit_menu_item_;         /*!< The quit menuitem */


    //
    // Function
    //
    /*!
     *  \brief Open a file
     */
     void openFile();

    /*!
     *  \brief Open a recent file
     */
     void openRecentFile();


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



    //
    // Function
    //
    /*!
     *  \brief Save the window size when changing size
     */
     void saveSize();


    /*!
     *  \brief Set the filename as subtitle
     */
     void setFilename();
};



#endif // MAIN_WINDOW_H_INCLUDED
