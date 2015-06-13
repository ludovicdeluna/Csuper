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

#include "../libcsuper/libcsuper.h"
#include <clocale>
#include <iostream>
#include <glibmm/i18n.h>

using namespace csuper;
using namespace std;
using namespace xmlpp;
using namespace Glib;

/*!
 * \fn int main(int argc, char *argv[])
 *  Begin csuper.
 * \param[in] argc the number of argument.
 * \param[in] argv the array of argument.
 * \return 0 if everything is OK
 */
int main(int argc, char *argv[])
{
    // Set locals
    locale::global(locale(""));
    setlocale(LC_ALL,"");
    cout.imbue(locale(""));
    cerr.imbue(locale(""));
    cin.imbue(locale(""));
    bindtextdomain("csuper-cli","Locales");
    bind_textdomain_codeset("csuper-cli","UTF-8");
    textdomain("csuper-cli");

    #ifdef PORTABLE
    csuperInitialize(true);
    #else
    csuperInitialize(false);
    #endif // PORTABLE




    return EXIT_SUCCESS;
}

