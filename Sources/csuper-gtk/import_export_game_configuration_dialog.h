/*!
 * \file    import_export_game_configuration_dialog.h
 * \author  Remi BERTHO
 * \date    05/08/15
 * \version 4.3.0
 */

/*
 * import_export_game_configuration_dialog.h
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

#ifndef IMPORT_EXPORT_GAME_CONFIGURATION_DIALOG_H_INCLUDED
#define IMPORT_EXPORT_GAME_CONFIGURATION_DIALOG_H_INCLUDED

#include <gtkmm.h>

#include "../libcsuper/libcsuper.h"

#include "csu_widget.h"

/*! \class ImportExportGameConfigurationDialog
*   \brief This class represent the game configuration window
*/
class ImportExportGameConfigurationDialog : public CsuWidget, public Gtk::Dialog
{
protected:
    Gtk::Grid* main_grid_ = nullptr;                /*!< The main grid */
    Gtk::ScrolledWindow* scrolled_window_ ;         /*!< The scrolled window */
    Gtk::Viewport* viewport_ ;                      /*!< The viewport */
    std::vector<Gtk::CheckButton*> check_buttons_;  /*!< The checkbutton */


    //
    // Select function
    //
    /*!
     *  \brief Select all game configuration
     */
    void selectAll();

    /*!
     *  \brief Deselect all game configuration
     */
    void deselectAll();


public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor
     */
    ImportExportGameConfigurationDialog();


    /*!
     *  \brief Destructor
     */
    ~ImportExportGameConfigurationDialog();


    //
    // Launch, stop
    //
    /*!
     *  \brief Show the import/export game configuration dialog
     *  \param list_game_config the ListGameConfiguration
     *  \param import if true use import, otherwise export
     *  \return the vector of index of game configuration to be import or export
     */
    std::vector<unsigned int> launch(const csuper::ListGameConfiguration& list_game_config, bool import);

};



#endif // IMPORT_EXPORT_GAME_CONFIGURATION_DIALOG_H_INCLUDED
