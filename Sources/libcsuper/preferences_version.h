/*!
 * \file    preferences_version.h
 * \author  Remi BERTHO
 * \date    26/08/15
 * \version 4.3.0
 */

/*
* preferences_version.h
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

#ifndef PREFERENCES_VERSION_H_INCLUDED
#define PREFERENCES_VERSION_H_INCLUDED

#include "share.h"
#include "version.h"

namespace csuper
{
    /*! \class VersionPreferences
    *   \brief This class indicate the version preference
    */
    class VersionPreferences
    {
    private:
        Version last_version_check_;    /*!< The last version checked version */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        VersionPreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param directory
         */
        VersionPreferences(const Version& version);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::XmlError if bad xmlpp node
         */
        VersionPreferences(xmlpp::Node* xml_node);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param pref another VersionPreferences
         */
        bool operator==(const VersionPreferences& pref) const;

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param pref the VersionPreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const VersionPreferences& pref);

        /*!
         *  \brief Add the VersionPreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the last check version
         *  \param version the Version
         */
         inline void setLastCheckVersion(const Version& version)
         {
             last_version_check_ = version;
         }




        //
        // Getter
        //
        /*!
         *  \brief Return the last check version
         *  \return the last check version
         */
         inline Version lastCheckVersion() const
         {
             return last_version_check_;
         }




        //
        // Getter ustring
        //
        /*!
         *  \brief Return the last check version in a ustring
         *  \return the ustring
         */
         inline Glib::ustring lastCheckVersionUstring() const
         {
             return last_version_check_.toUstring();
         }
    };
}

#endif // PREFERENCES_VERSION_H_INCLUDED
