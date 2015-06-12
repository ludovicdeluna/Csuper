/*!
 * \file    preferences_score_display.h
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_score_display.h
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

#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED

#include "share.h"

namespace csuper
{
    /*! \class DirectoryPreferences
    *   \brief This class indicate the directory preference
    */
    class DirectoryPreferences
    {
    private:
        Glib::ustring open_;   /*!< The directory for opening file */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        DirectoryPreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param directory
         */
        DirectoryPreferences(const Glib::ustring& open);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::xmlError if bad xmlpp node
         */
        DirectoryPreferences(xmlpp::Node* xml_node);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param dir another DirectoryPreferences
         */
        bool operator==(const DirectoryPreferences& dir) const;

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param dir the DirectoryPreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const DirectoryPreferences& dir);

        /*!
         *  \brief Add the DirectoryPreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the open directory
         *  \param the open directory
         */
         inline void setOpen(const Glib::ustring& open)
         {
             open_ = open;
         }




        //
        // Getter
        //
        /*!
         *  \brief Return the open directory
         *  \return the open directory
         */
         inline Glib::ustring open() const
         {
             return open_;
         }




        //
        // Getter ustring
        //
        /*!
         *  \brief Return the open directory in a ustring
         *  \return the ustring
         */
         inline Glib::ustring openUstring() const
         {
             return open_;
         }
    };
}


#endif // DIRECTORY_H_INCLUDED
