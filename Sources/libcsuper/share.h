/*!
 * \file    share.h
 * \brief   Header for the essential function of libcsuper
 * \author  Remi BERTHO
 * \date    25/05/15
 * \version 4.3.0
 */

/*
* share.h
*
* Copyright 2014-2015
 Remi BERTHO <remi.bertho@openmailbox.org>
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

#ifndef SHARE_H_INCLUDED
#define SHARE_H_INCLUDED

#include <glibmm/i18n.h>
#include <glibmm.h>
#include <libxml++/libxml++.h>


/*! \namespace csuper
 *
 * Namespace of Csuper
 */
namespace csuper
{
    //
    // Macro
    //

    /*!
     * \def CSUPER_VERSION
     * Define the version of csuper
     */
    #define CSUPER_VERSION "4.3.0"

    /*!
     * \def CSUPER_DIRECTORY_NAME
     * Define the directory of csuper
     */
    #define CSUPER_DIRECTORY_NAME ".csuper"

    /*!
     * \def CSUPER_PREFERENCES_FILENAME
     * Define the filename of the preferences file of csuper
     */
    #define CSUPER_PREFERENCES_FILENAME "preferences.xml"

    /*!
     * \def CSUPER_GAME_CONFIGURATIONS_FILENAME
     * Define the filename of the game configuration file of csuper
     */
    #define CSUPER_GAME_CONFIGURATIONS_FILENAME "game_configuration.xml"

    /*!
     * \def CSUPER_SYSTEM_PATH_FILENAME
     * Define the filename of the system path file of csuper
     */
    #define CSUPER_SYSTEM_PATH_FILENAME "system_path.txt"


    //
    // General
    //

    /*!
     *  Initialize libcsuper with gettext.
     */
    void libcsuper_initialize(const bool portable);

    /*!
     *  Clear the terminal.
     */
    void clearScreen();



    // Conversion
    /*!
     *  Convert a Boolean into a ustring with yes or no which can be translated
     *  \param b
     *  \return the ustring
     */
    Glib::ustring boolToYesNo(const bool b);

    /*!
     *  Convert a Boolean into a ustring
     *  \param b
     *  \return the ustring
     */
    Glib::ustring boolToUstring(const bool b);

    /*!
     *  Convert a ustring to a bool
     *  \param str the ustring
     *  \return the bool
     */
    bool ustringToBool(const Glib::ustring& str);

    /*!
     *  Convert a double into a ustring
     *  \param d the double
     *  \param decimals the number of decimals
     *  \return the ustring
     */
    Glib::ustring doubleToUstring(const double d, const int decimals=0);

    /*!
     *  Convert a ustring into a double
     *  \param str the ustring
     *  \return the double
     */
    double ustringToDouble(const Glib::ustring& str);

    /*!
     *  Convert a int into a ustring
     *  \param str the ustring
     *  \return the int
     */
    inline int ustringToInt(const Glib::ustring& str)
    {
        return atoi(str.c_str());
    }


    //
    // XML
    //

    /*!
     *  Convert an int into a ustring
     *  \param i the int
     *  \return the ustring
     */
     Glib::ustring intToUstring(const double i);

    // xmlpp
    /*!
     *  Change the node to the next element
     *  \param node the xmlpp node
     *  \return the node
     *  \exception csuper::xmlError if no next element
     */
    xmlpp::Element *nextXmlElement(xmlpp::Node*& node);

    /*!
     *  Change the node to the next child element
     *  \param node the xmlpp node
     *  \return the node
     *  \exception csuper::xmlError if no child element
     */
    xmlpp::Element *firstChildXmlElement(xmlpp::Node*& node);




    //
    // Class
    //

    /*! \class Portable
    *   \brief This class define is we use Csuper as a portable application or not
    */
    class Portable
    {
    private:
        static bool portable_; /*!< Define if it is portable */

    public:
        /*!
         *  \brief Set the portable variable
         *  \param portable
         */
        inline static void setPortable(const bool portable)
        {
            portable_ = portable;
        }

        /*!
         *  \brief Get the portable variable
         *  \return the portable value
         */
        inline static bool getPortable()
        {
            return portable_;
        }
    };
}

#endif
