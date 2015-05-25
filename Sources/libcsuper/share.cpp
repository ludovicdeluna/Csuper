/*!
 * \file    share.cpp
 * \brief   Essential function of libcsuper
 * \author  Remi BERTHO
 * \date    25/05/15
 * \version 4.3.0
 */

 /*
 * share.cpp
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of LibCsuper.
 *
 * LibCsuper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibCsuper is distributed in the hope that it will be useful,
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

#include "share.h"
#include <iostream>
#include <cstdlib>

namespace csuper{

    using namespace std;

    /*!
     * \fn void libcsuper_initialize()
     *  Initialize libcsuper with gettext.
     */
    void libcsuper_initialize()
    {
        static bool initialized=false;
        if (initialized == false)
        {
            bindtextdomain("libcsuper","./Locales");
            initialized = true;
        }
    }

    /*!
     * \fn void clearScreen()
     *  Clear the terminal.
     */
    void clearScreen()
    {
        int successful;

        libcsuper_initialize();

        /*Lancement de la fonction d'effacage de l'ecran*/
        #ifdef __unix__
        successful=system("clear");
        #elif _WIN32
        successful=system("cls");
        #endif

        /*Verifie si l'ecran s'est bien efface*/
        if (successful != 0)
            cout << _("Error while clearing the screen.") << endl;
    }

}
