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


class Menu
{
private:
    csuper::Preferences* pref_;                         /*!< The preferences */
    csuper::ListGameConfiguration* list_game_config_;   /*!< The list of game configuration */

    enum Main{
        NEW=1,
        LOAD=2,
        PRINT=3,
        DELETE=4,
        LIST=5,
        EXPORT=6,
        PREF=7,
        QUIT=8
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
