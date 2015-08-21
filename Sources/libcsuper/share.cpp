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
#include "preferences.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <clocale>
#include <cmath>
#include <fstream>
#include <sys/stat.h>
#include <glib/gstdio.h>
#include "config.h"

namespace csuper{

    using namespace std;
    using namespace xmlpp;
    using namespace Glib;

    bool Portable::portable_(false);

    void csuperInitialize(const bool portable)
    {
        static bool initialized=false;
        if (initialized == false)
        {
            bindtextdomain("libcsuper","Locales");
            bind_textdomain_codeset("libcsuper","UTF-8");
            initialized = true;

            Portable::setPortable(portable);

            ustring folder;
            ustring home = locale_to_utf8(get_home_dir());

            if (portable)
                folder = CSUPER_DIRECTORY_NAME;
            else
                folder = build_filename(home,CSUPER_DIRECTORY_NAME);
            #ifdef __unix__
            g_mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            #elif _WIN32
            g_mkdir(folder.c_str(),0);
            #endif

            string pref = build_filename(folder,CSUPER_PREFERENCES_FILENAME);
            string game_config = build_filename(folder,CSUPER_GAME_CONFIGURATIONS_FILENAME);

            if (!file_test(pref,FILE_TEST_EXISTS))
            {
                Preferences pref;
                pref.writeToFile();
                cerr << ustring(_("Creation of the preferences file.")) << endl;
            }

            if (!file_test(game_config,FILE_TEST_EXISTS))
            {
                ListGameConfiguration list_config;
                list_config.writeToFile(game_config);
                cerr << ustring(_("Creation of the game configuration file.")) << endl;
            }
        }
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

    ustring intToUstring(const int i, const unsigned int width)
    {
        return ustring::format(setw(width),i);
    }

    int ustringToInt(const ustring& str)
    {
        lconv *lc = localeconv();
        removeCharacterInUstring(str,*(lc->thousands_sep));
        return atoi(str.c_str());
    }


    ustring doubleToUstring(const double d, const int decimals, const unsigned int width)
    {
        if (decimals < 0)
        {
            if (width == 0)
                return ustring::format(d);
            else
                return ustring::format(fixed,setw(width), d);
        }
        else
        {
            if (width == 0)
                return ustring::format(fixed,setprecision(decimals), d);
            else
                return ustring::format(fixed,setprecision(decimals),setw(width), d);
        }
    }


    double ustringToDouble(const ustring& str)
    {
        ustring copy_str(str);
        lconv *lc = localeconv();

        // Remove the thousands separator
        removeCharacterInUstring(copy_str,*(lc->thousands_sep));
        replaceCharacterInUstring(copy_str,*(lc->decimal_point),'.');

        #ifdef _WIN32
        if (copy_str == "inf")
            return INFINITY;
        else
        #endif // _WIN32

        return Ascii::strtod(copy_str);
    }

    Glib::ustring replaceCharacterInUstring(const Glib::ustring& str, const char old_character, const char new_character)
    {
        ustring::size_type pos;
        ustring ret(str);
        while ((pos = ret.find(old_character)) != ustring::npos)
            ret.replace(pos,1,ustring(1,new_character));
        return ret;
    }

    Glib::ustring &replaceCharacterInUstring(Glib::ustring& str, const char old_character, const char new_character)
    {
        ustring::size_type pos;
        while ((pos = str.find(old_character)) != ustring::npos)
            str.replace(pos,1,ustring(1,new_character));
        return str;
    }

    Glib::ustring removeCharacterInUstring(const Glib::ustring& str, const char character)
    {
        ustring::size_type pos;
        ustring ret(str);
        while ((pos = ret.find(character)) != ustring::npos)
            ret.erase(pos,1);
        return ret;
    }

    Glib::ustring &removeCharacterInUstring(Glib::ustring& str, const char character)
    {
        ustring::size_type pos;
        while ((pos = str.find(character)) != ustring::npos)
            str.erase(pos,1);
        return str;
    }


    Element *nextXmlElement(Node*& node)
    {
        node = node->get_next_sibling();
        while (dynamic_cast<Element*>(node) == nullptr)
        {
            if (node != nullptr)
                node = node->get_next_sibling();
            else
                throw XmlError("No next element");
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
                throw XmlError("No child element");
        }
        return static_cast<Element*>(node) ;
    }



    void removeFileExtension(Glib::ustring& filename)
    {
        for (int i=filename.size()-2 ; i>0 ; i--)
        {
            if (filename[i] == '.')
            {
                filename.resize(i);
                break;
            }
        }
    }

    //
    // File
    //
    bool checkFilename(const ustring& filename)
    {
        string full_filename = build_filename(get_tmp_dir(),locale_from_utf8(filename));

        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit );
        try
        {
            file.open(full_filename,ofstream::out);
            file.close();
            remove(full_filename.c_str());
            return true;
        }
        catch (std::exception& e)
        {
            return false;
        }
    }


    bool checkFolder(const ustring& folder)
    {
        string filename = build_filename(locale_from_utf8(folder),"test_csu_tmp");

        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit );
        try
        {
            file.open(filename,ofstream::out);
            file.close();
            remove(filename.c_str());
            return true;
        }
        catch (ios_base::failure& e)
        {
            return false;
        }
    }



    //
    // Extension
    //
    ustring addFileExtension(const ustring& filename, const ustring& file_extension)
    {
        if (filename.substr(filename.size() - file_extension.size()) == file_extension)
            return filename;
        else
            return filename + file_extension;
    }


    ustring& addFileExtension(ustring& filename, const ustring& file_extension)
    {
        if (filename.substr(filename.size() - file_extension.size()) != file_extension)
            filename += ("." + file_extension);

        return filename;
    }
}
