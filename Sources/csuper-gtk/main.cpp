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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <clocale>
#include <gtkmm.h>
#include <glibmm/i18n.h>
#include "../libcsuper/libcsuper.h"
#include "csu_application.h"

using namespace csuper;
using namespace std;
using namespace Glib;
using namespace Gtk;

/*!
 *  Print an error message on error terminate
 *  \param log_domain the log domain of the message
 *  \param log_level the log level of the message (including the fatal and recursion flags)
 *  \param message the message to process
 *  \param user_data user data
 */
void terminateFunction(const gchar* log_domain, GLogLevelFlags log_level, const gchar* message, gpointer user_data)
{
    cerr << message << endl;

    MessageDialog error(message,false,MESSAGE_ERROR,BUTTONS_OK,true);
    error.run();
}

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

    set_prgname("csuper-gtk");
    set_application_name(_("Csuper"));

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


    // Set terminate function
    g_log_set_handler("glibmm",(GLogLevelFlags)(G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),terminateFunction,nullptr);
    g_log_set_handler("gtkmm",(GLogLevelFlags)(G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),terminateFunction,nullptr);

    // Create the application
    RefPtr<CsuApplication> app(new CsuApplication(argc,argv));

    //Load the Glade file
    RefPtr<Builder> builder = Builder::create();
    try
    {
        builder->add_from_file("UI/csuper-gtk.glade");
    }
    catch(Glib::Exception& e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    app->init(builder);

    return app->launch();
}
