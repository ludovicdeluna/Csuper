/*!
 * \file    csu_application.h
 * \author  Remi BERTHO
 * \date    28/07/15
 * \version 4.3.0
 */

/*
 * csu_application.h
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

#ifndef CSU_APPLICATION_H_INCLUDED
#define CSU_APPLICATION_H_INCLUDED

#include <gtkmm.h>

#include "main_window.h"
#include "about.h"
#include "game_configuration_window.h"
#include "new_game_configuration_dialog.h"
#include "import_export_game_configuration_dialog.h"
#include "menu_file.h"
#include "menu_edit.h"
#include "menu_display.h"

#include "../libcsuper/libcsuper.h"


/*! \class CsuApplication
*   \brief This class represent the Application
*/
class CsuApplication : public Gtk::Application
{
private:
    Glib::RefPtr<Gtk::Builder> builder_;    /*!< The Gtk::Builder */

    csuper::Preferences* pref_;                         /*!< The preferences */
    csuper::ListGameConfiguration* list_game_config_;   /*!< The list of game configuration */

    MainWindow* main_window_;                                               /*!< The main window */
    About* about_;                                                          /*!< The about dialog */
    GameConfigurationWindow* game_config_window_;                           /*!< The game configuration window */
    NewGameConfigurationDialog* new_game_config_dialog_;                    /*!< The new game configuration dialog*/
    ImportExportGameConfigurationDialog* import_export_game_config_dialog_; /*!< The import export game configuration dialog*/
    MenuFile* menu_file_;                                                   /*!< The menu file */
    MenuEdit* menu_edit_;                                                   /*!< The menu edit */
    MenuDisplay* menu_display_;                                             /*!< The menu display */



    //
    // Signal
    //
    /*!
     *  \brief Function used on the startup signal. It create the menu
     */
    void onStartup();

public:
    //
    // Constructor and destructor
    //
    /*!
     *  \brief Constructor
     *  \param argc The parameter received by your main() function.
     *  \param argv The parameter received by your main() function.
     */
    CsuApplication(int& argc, char**& argv);


    /*!
     *  \brief Destructor
     */
    ~CsuApplication();



    //
    // Function
    //
    /*!
     *  \brief Initialize the CsuApplication with the builder
     *  \param builder the GTK::Builder
     */
    void init(Glib::RefPtr<Gtk::Builder>& builder);

    /*!
     *  \brief Launch the application
     */
    int launch();

    /*!
     *  \brief Quit Csuper
     */
    void onQuit();



    //
    // Getter
    //
    /*!
     *  \brief return the Preferences
     *  \return the Preferences
     */
     inline csuper::Preferences* pref()
     {
         return pref_;
     }

    /*!
     *  \brief return the ListGameConfiguration
     *  \return the ListGameConfiguration
     */
     inline csuper::ListGameConfiguration* listGameConfig()
     {
         return list_game_config_;
     }

    /*!
     *  \brief return the MainWindow
     *  \return the MainWindow
     */
     inline MainWindow* mainWindow()
     {
         return main_window_;
     }

    /*!
     *  \brief return the About
     *  \return the About
     */
     inline About* about()
     {
         return about_;
     }

    /*!
     *  \brief return the GameConfigurationWindow
     *  \return the GameConfigurationWindow
     */
     inline GameConfigurationWindow* gameConfigurationWindow()
     {
         return game_config_window_;
     }

    /*!
     *  \brief return the NewGameConfigurationDialog
     *  \return the NewGameConfigurationDialog
     */
     inline NewGameConfigurationDialog* newGameConfigurationDialog()
     {
         return new_game_config_dialog_;
     }

    /*!
     *  \brief return the ImportExportGameConfigurationDialog
     *  \return the ImportExportGameConfigurationDialog
     */
     inline ImportExportGameConfigurationDialog* importExportGameConfigurationDialog()
     {
         return import_export_game_config_dialog_;
     }

    /*!
     *  \brief return the MenuFile
     *  \return the MenuFile
     */
     inline MenuFile* menuFile()
     {
         return menu_file_;
     }

    /*!
     *  \brief return the MenuEdit
     *  \return the MenuEdit
     */
     inline MenuEdit* menuEdit()
     {
         return menu_edit_;
     }

    /*!
     *  \brief return the MenuDisplay
     *  \return the MenuDisplay
     */
     inline MenuDisplay* menuDisplay()
     {
         return menu_display_;
     }

};

#endif // CSU_APPLICATION_H_INCLUDED
