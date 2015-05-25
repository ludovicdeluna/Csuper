/*!
 * \file    main.cpp
 * \brief   Begin csuper
 * \author  Remi BERTHO
 * \date    25/05/15
 * \version 4.3.0
 */

/*
 * main.cpp
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper is distributed in the hope that it will be useful,
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

#include "../libcsuper/libcsuper.h"
#include <clocale>
#include <iostream>

using namespace csuper;
using namespace std;

/*!
 * \fn int main(int argc, char *argv[])
 *  Begin csuper.
 * \param[in] argc the number of argument.
 * \param[in] argv the array of argument.
 * \return EXIT_SUCCESS if everything is OK
 */
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    bindtextdomain("csuper-cli","Locales");
    textdomain("csuper-cli");

    GameConfiguration game_config(500,false,true,true,0,true,"Uno",0);
    cout << game_config.name() << endl;

    return 0;
}

