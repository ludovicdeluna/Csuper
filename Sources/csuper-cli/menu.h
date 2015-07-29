/*!
 * \file    menu.h
 * \author  Remi BERTHO
 * \date    10/07/15
 * \version 4.3.0
 */

/*
 * menu.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper-cli is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-cli is distributed in the hope that it will be useful,
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

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../libcsuper/libcsuper.h"

/*! \class Menu
*   \brief This class is used for the main menu
*/
class Menu
{
private:
    csuper::Preferences* pref_;                         /*!< The preferences */
    csuper::ListGameConfiguration* list_game_config_;   /*!< The list of game configuration */

    enum Main{
        MENU_NEW = 1,
        MENU_LOAD = 2,
        MENU_PRINT = 3,
        MENU_DELETE = 4,
        MENU_LIST = 5,
        MENU_EXPORT = 6,
        MENU_PREF = 7,
        MENU_ABOUT = 8,
        MENU_QUIT = 9
    };

    enum Preferences{
        MENU_NEW_GAME_CONF = 1,
        MENU_REMOVE_GAME_CONF = 2,
        MENU_PRINT_LIST_GAME_CONF = 3,
        MENU_PRINT_GAME_CONF = 4,
        MENU_EXPORT_GAME_CONF = 5,
        MENU_IMPORT_GAME_CONF = 6,
        MENU_PDF_PREFERENCES = 7,
        MENU_CHANGE_OPEN_PATH = 8,
        MENU_READ_OPEN_PATH = 9,
        MENU_BACK_MAIN_MENU = 10
    };

    /*!
     *  Print that the user use a wrong choice
     */
    void wrongChoice() const;


    //
    // Menu function
    //
    /*!
     *  \brief List all files in the directory
     */
    void listFile() const;

    /*!
     *  \brief About
     */
    void about() const;

    /*!
     *  \brief Delete a CSU file
     */
    void deleteCsuFile() const;

    /*!
     *  Ask a filename and display it.
     */
    void displayFile() const;

    /*!
     *  Export a csu file
     */
    void exportCsu() const;

    /*!
     *  Preferences menu of csuper.
     */
    void preferencesMenu() const;

    /*!
     *  Change the open path
     */
    void changeOpenPath() const;

    /*!
     *  Read the open path and display it.
     */
    void readOpenPath() const;

    /*!
     *  Print the list of game configuration
     */
    void printListGameConfig() const;

    /*!
     *  Ask and print a game configuration
     */
    void printGameConfig() const;

    /*!
     *  Add a new game configuration
     */
    void newGameConfig() const;

    /*!
     *  Ask and remove a game configuration
     */
    void removeGameConfig() const;

    /*!
     *  Export game configuration in one file.
     */
    void exportListGameConfig() const;

    /*!
     *  Import game configuration in one file.
     */
    void importListGameConfig() const;

    /*!
     *  Change the export to pdf preferences
     */
    void changePdfPreferences() const;

    /*!
     *  Load a game from a file and run the play function.
     */
    void loadGame() const;

    /*!
     *  Initialize a new game and run the play function.
     */
    void newGame() const;


    //
    // Ask function
    //
    /*!
     *  \brief Ask and save the filename
     *  \return filename the filename
     */
    Glib::ustring askFilename() const;

public:
    //
    // Constructor and destructor
    //
    /*!
     *  \brief Constructor
     */
    Menu();

    /*!
     *  \brief Destructor
     */
    ~Menu();


    //
    // Menu function
    //
    /*!
     *  \brief Run the main menu
     */
    void main();
};



#endif // MENU_H_INCLUDED