/*!
 * \file    preferences_main_window_size.h
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_main_window_size.h
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

#ifndef MAIN_WINDOW_SIZE_H_INCLUDED
#define MAIN_WINDOW_SIZE_H_INCLUDED

#include "share.h"

namespace csuper
{
    /*! \class MainWindowSizePreferences
    *   \brief This class represent a the preferences for the size of_the main window
    */
    class MainWindowSizePreferences
    {
    private:
        unsigned int width_;     /*!< The width of the main window */
        unsigned int height_;    /*!< The height of the main window */
        bool is_maximize_;       /*!< Said if the main window is maximize or not */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        MainWindowSizePreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param width
         *  \param height
         *  \param is_maximize
         */
        MainWindowSizePreferences(const unsigned int width, const unsigned int height, const bool is_maximize);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::xmlError if bad xmlpp node
         */
        MainWindowSizePreferences(xmlpp::Node* xml_node);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param size another MainWindowSizePreferences
         */
        bool operator==(const MainWindowSizePreferences& size) const;

        /*!
         *  \brief Convert the main window size to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param size the MainWindowSizePreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const MainWindowSizePreferences& size);

        /*!
         *  \brief Add the MainWindowSizePreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the width
         *  \param the width
         */
         inline void setWidth(const unsigned int width)
         {
             width_ = width;
         }

        /*!
         *  \brief Set the height
         *  \param the height
         */
         inline void setHeight(const unsigned int height)
         {
             height_ = height;
         }

        /*!
         *  \brief Set the is_maximize
         *  \param the is_maximize
         */
         inline void setIsMaximize(const bool is_maximize)
         {
             is_maximize_ = is_maximize;
         }





        //
        // Getter
        //
        /*!
         *  \brief return the width
         *  \return the width
         */
         inline unsigned int width() const
         {
             return width_;
         }

        /*!
         *  \brief return the height
         *  \return the height
         */
         inline unsigned int height() const
         {
             return height_;
         }

        /*!
         *  \brief return the width
         *  \return the width
         */
         inline bool isMaximize() const
         {
             return is_maximize_;
         }



        //
        // Getter ustring
        //
        /*!
         *  \brief return the width in a ustring
         *  \return the ustring
         */
         inline Glib::ustring widthUstring() const
         {
             return intToUstring(width_);
         }

        /*!
         *  \brief return the height in a ustring
         *  \return the ustring
         */
         inline Glib::ustring heightUstring() const
         {
             return intToUstring(height_);
         }

        /*!
         *  \brief return the width in a ustring
         *  \return the ustring
         */
         inline Glib::ustring isMaximizeUstring() const
         {
             return boolToUstring(is_maximize_);
         }
    };
}


#endif // MAIN_WINDOW_SIZE_H_INCLUDED
