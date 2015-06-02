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
#include "exceptions.h"
#include "list_game_configuration.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <clocale>
#include <cmath>
#include <sys/stat.h>

namespace csuper{

    using namespace std;
    using namespace xmlpp;
    using namespace Glib;

    bool Portable::portable_(false);

    void libcsuper_initialize(const bool portable)
    {
        static bool initialized=false;
        if (initialized == false)
        {
            bindtextdomain("libcsuper","./Locales");
            initialized = true;

            Portable::setPortable(portable);

            string folder;
            string home = get_home_dir();

            if (portable)
                folder = CSUPER_DIRECTORY_NAME;
            else
                folder = build_filename(home,CSUPER_DIRECTORY_NAME);
            #ifdef __unix__
            mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            #elif _WIN32
            mkdir(folder.c_str());
            #endif

            string pref = build_filename(folder,CSUPER_PREFERENCES_FILENAME);
            string game_config = build_filename(folder,CSUPER_GAME_CONFIGURATIONS_FILENAME);
            string path = build_filename(folder,CSUPER_SYSTEM_PATH_FILENAME);

            if (!file_test(pref,FILE_TEST_EXISTS))
                ; // To be completed

            if (!file_test(game_config,FILE_TEST_EXISTS))
            {
                ListGameConfiguration list_config;
                list_config.writeToFile(game_config);
            }

            if (!file_test(path,FILE_TEST_EXISTS))
                ; // To be completed
        }
    }

    void clearScreen()
    {
        int successful;

        // Lancement de la fonction d'effacage de l'ecran
        #ifdef __unix__
        successful=system("clear");
        #elif _WIN32
        successful=system("cls");
        #endif

        /*Verifie si l'ecran s'est bien efface*/
        if (successful != 0)
            cout << _("Error while clearing the screen.") << endl;
    }

    ustring boolToYesNo(bool b)
    {
        if (b)
            return _("yes");
        else
            return _("no");
    }

    ustring boolToUstring(bool b)
    {
        if (b)
            return "yes";
        else
            return "no";
    }

    bool ustringToBool(const ustring& str)
    {
        return str == "yes";
    }

    ustring doubleToUstring(const double d, const int decimals)
    {
        return ustring::format(fixed,setprecision(decimals), d);
    }

    ustring intToUstring(const double i)
    {
        return Glib::ustring::format(i);
    }

    double ustringToDouble(const ustring& str)
    {
        ustring copy_str(str);
        lconv *lc = localeconv();
        ustring::size_type pos;

        /*Change the decimals to a comma if needed*/
        if(*(lc->decimal_point) == ',')
        {
            if ((pos = copy_str.find('.')) != ustring::npos)
                copy_str.replace(pos,1,",");
        }
        else if(*(lc->decimal_point) == '.')
        {
            if ((pos = copy_str.find(',')) != ustring::npos)
                copy_str.replace(pos,1,".");
        }

        #ifdef _WIN32
        if (copy_str == "inf")
            return INFINITY;
        else
        #endif // _WIN32

        return atof(copy_str.c_str());
    }


    Element *nextXmlElement(Node*& node)
    {
        node = node->get_next_sibling();
        while (dynamic_cast<Element*>(node) == NULL)
        {
            if (node != nullptr)
                node = node->get_next_sibling();
            else
                throw xmlError("No next element");
        }
        return static_cast<Element*>(node) ;
    }

    Element *firstChildXmlElement(Node*& node)
    {
        #if LIBXMLXX_MINOR_VERSION < 36
        node = node->get_children().front();
        #else
        node = node->get_first_child();
        #endif
        while (dynamic_cast<Element*>(node) == NULL)
        {
            if (node != nullptr)
                node = node->get_next_sibling();
            else
                throw xmlError("No child element");
        }
        return static_cast<Element*>(node) ;
    }

}
