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


    //
    // General
    //

    /*!
     *  Initialize libcsuper with gettext.
     *  \exception Glib::exception
     */
    void csuperInitialize(const bool portable);

    /*!
     *  Remove the file extension from a filename
     * \param[in] filename the filename
     */
    void removeFileExtension(Glib::ustring& filename);



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
    Glib::ustring doubleToUstring(const double d, const int decimals=-1, const unsigned int width = 0);

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
    int ustringToInt(const Glib::ustring& str);

    /*!
     *  Convert an int into a ustring
     *  \param i the int
     *  \return the ustring
     */
     Glib::ustring intToUstring(const double i, const unsigned int width =0);

    /*!
     *  Change the decimal place of a double in a ustring
     *  \param str the ustring
     *  \param old_character the old character
     *  \param new_character the new character
     *  \return the ustring
     */
     Glib::ustring replaceCharacterInUstring(const Glib::ustring& str, const char old_character, const char new_character);

    /*!
     *  Change the decimal place of a double in a ustring
     *  \param str the ustring
     *  \param old_character the character
     *  \param new_character the character
     *  \return the ustring
     */
     Glib::ustring &replaceCharacterInUstring(Glib::ustring& str, const char old_character, const char new_character);

    /*!
     *  Remove a character in a ustring
     *  \param str the ustring
     *  \param character
     *  \return the ustring
     */
     Glib::ustring removeCharacterInUstring(const Glib::ustring& str, const char character);

    /*!
     *  Remove a character in a ustring
     *  \param str the ustring
     *  \param character
     *  \return the ustring
     */
     Glib::ustring &removeCharacterInUstring(Glib::ustring& str, const char character);



    //
    // XML
    //
    /*!
     *  Change the node to the next element
     *  \param node the xmlpp node
     *  \return the node
     *  \exception csuper::XmlError if no next element
     */
    xmlpp::Element *nextXmlElement(xmlpp::Node*& node);

    /*!
     *  Change the node to the next child element
     *  \param node the xmlpp node
     *  \return the node
     *  \exception csuper::XmlError if no child element
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


    //
    // Sort
    //
    /*!
     *  Compare 2 double
     * \param[in] a a double
     * \param[in] b a double
     * \return the comparison
     */
    inline bool compareDoubleAscending(const int a, const int b)
    {
       return a<b;
    }

    /*!
     *  Compare 2 double
     * \param[in] a a double
     * \param[in] b a double
     * \return the comparison
     */
    inline bool compareDoubleDescending(const int a, const int b)
    {
       return a>b;
    }

}

#endif
