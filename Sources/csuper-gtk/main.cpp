/*!
 * \file    main.cpp
 * \brief   Begin csuper
 * \author  Remi BERTHO
 * \date    28/07/15
 * \version 4.3.0
 */

/*
 * main.cpp
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

#include <clocale>
#include <glibmm/i18n.h>
#include "../libcsuper/libcsuper.h"

using namespace csuper;
using namespace std;
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
    bindtextdomain("csuper-gtk","Locales");
    bind_textdomain_codeset("csuper-gtk","UTF-8");
    textdomain("csuper-gtk");

    // Initialization of csuper
    try
    {
        #ifdef PORTABLE
        csuperInitialize(true);
        #else
        csuperInitialize(false);
        #endif // PORTABLE
    }
    catch (std::exception& e)
    {
        cerr << e.what() << endl;
        cerr << _("Error when initializing csuper.") << endl;
        exit(EXIT_FAILURE);
    }
    catch (Glib::Exception& e)
    {
        cerr << e.what() << endl;
        cerr << _("Error when initializing csuper.") << endl;
        exit(EXIT_FAILURE);
    }



    return EXIT_SUCCESS;
}
