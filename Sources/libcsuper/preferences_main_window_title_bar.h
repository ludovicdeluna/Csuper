/*!
 * \file    preferences_main_window_title_bar.h
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
* preferences_main_window_title_bar.h
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

#ifndef PREFERENCES_MAIN_WINDOW_TITLE_BAR_H_INCLUDED
#define PREFERENCES_MAIN_WINDOW_TITLE_BAR_H_INCLUDED

#include "share.h"

namespace csuper
{
    /*! \class MainWindowTitleBarPreferences
    *   \brief This class indicate where and how then title bar will be set
    */
    class MainWindowTitleBarPreferences
    {
    private:
        bool disable_window_manager_decoration_;    /*!< Ask the window manager to not decorated the main window */
        bool print_title_;                          /*!< Print the file is the title bar ? */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        MainWindowTitleBarPreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param disable_window_manager_decoration
         *  \param print_title
         */
        MainWindowTitleBarPreferences(const bool disable_window_manager_decoration, const bool print_title);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::XmlError if bad xmlpp node
         */
        MainWindowTitleBarPreferences(xmlpp::Node* xml_node);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param pref another MainWindowTitleBarPreferences
         */
        bool operator==(const MainWindowTitleBarPreferences& pref) const;

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param pref the MainWindowTitleBarPreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const MainWindowTitleBarPreferences& pref);

        /*!
         *  \brief Add the MainWindowTitleBarPreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the disable_window_manager_decoration
         *  \param the disable_window_manager_decoration
         */
         inline void setDisableWindowManagerDecoration(const bool disable_window_manager_decoration)
         {
             disable_window_manager_decoration_ = disable_window_manager_decoration;
         }

        /*!
         *  \brief Set the print_title
         *  \param the print_title
         */
         inline void setPrintTitle(const bool print_title)
         {
             print_title_ = print_title;
         }





        //
        // Getter
        //
        /*!
         *  \brief Return the disable_window_manager_decoration
         *  \return the disable_window_manager_decoration
         */
         inline bool disableWindowManagerDecoration() const
         {
             return disable_window_manager_decoration_;
         }

        /*!
         *  \brief Return the print_title
         *  \return the print_title
         */
         inline bool printTitle() const
         {
             return print_title_;
         }



        //
        // Getter ustring
        //
        /*!
         *  \brief Return the disable_window_manager_decoration in a ustring
         *  \return the ustring
         */
         inline Glib::ustring disableWindowManagerDecorationUstring() const
         {
             return boolToUstring(disable_window_manager_decoration_);
         }

        /*!
         *  \brief Return the print_title in a ustring
         *  \return the ustring
         */
         inline Glib::ustring printTitleUstring() const
         {
             return boolToUstring(print_title_);
         }
    };
}



#endif // PREFERENCES_MAIN_WINDOW_TITLE_BAR_H_INCLUDED
