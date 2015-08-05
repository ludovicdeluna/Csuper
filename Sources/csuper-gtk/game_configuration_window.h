/*!
 * \file    game_configuration_window.h
 * \author  Remi BERTHO
 * \date    04/08/15
 * \version 4.3.0
 */

/*
 * game_configuration_window.h
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



#ifndef GAME_CONFIGURATION_WINDOW_H_INCLUDED
#define GAME_CONFIGURATION_WINDOW_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class GameConfigurationWindow
*   \brief This class represent the game configuration window
*/
class GameConfigurationWindow : public CsuWidget, public Gtk::ApplicationWindow
{
protected:
    Gtk::Grid* main_grid_;                  /*!< The main grid */
    Gtk::ScrolledWindow* scrolled_window_;  /*!< The scrolled window */
    Gtk::Viewport* viewport_;               /*!< The viewport */
    Gtk::ButtonBox* button_box_;            /*!< The buttonbox */
    Gtk::Button* add_button_;               /*!< The add button */
    Gtk::Button* import_button_;            /*!< The import button */
    Gtk::Button* export_button_;            /*!< The export button */
    Gtk::Button* close_button_;             /*!< The close button */
    Gtk::Label* list_label_;                /*!< The list label*/
    Gtk::Label* detail_label_;              /*!< The detail label*/
    Gtk::Label* selected_pref_label_;       /*!< The selected pref label*/
    Gtk::Label* config_name_label_;         /*!< The config name label*/

    Gtk::Grid* game_config_grid_=nullptr;                    /*!< The grid of game configuration*/

    unsigned int game_config_displayed_;    /*!< The current game configuration displayed */



    //
    // Function
    //
    /*!
     *  \brief Update the list of game configuration
     */
    void updateList();



public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    GameConfigurationWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);


    /*!
     *  \brief Destructor
     */
    ~GameConfigurationWindow();


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
    // Edit, delete, view
    //
    /*!
     *  \brief Delete a game configuration
     */
    void deleteGameConfig(const unsigned int id);

    /*!
     *  \brief View a game configuration
     */
    void viewGameConfig(const unsigned int id);

    /*!
     *  \brief Edit a game configuration
     */
    void editGameConfig(const unsigned int id);


    //
    // Add' export, import
    //
    /*!
     *  \brief Add a game configuration
     */
    void addGameConfig();

    /*!
     *  \brief Export a game configuration
     */
    void exportGameConfig();

    /*!
     *  \brief Import a game configuration
     */
    void importGameConfig();

};



#endif // GAME_CONFIGURATION_WINDOW_H_INCLUDED
