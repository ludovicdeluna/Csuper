/*!
 * \file    version.h
 * \brief   Header for the essential function of libcsuper
 * \author  Remi BERTHO
 * \date    26/08/15
 * \version 4.3.0
 */

/*
* version.h
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

#ifndef VERSION_H_INCLUDED
#define VERSION_H_INCLUDED

#include <glibmm.h>

namespace csuper
{

    /*! \class Version
    *   \brief This class define a version of Csuper
    */
    class Version
    {
    private:
        unsigned int major_ = 4;    /*!< The major version */
        unsigned int minor_ = 3;    /*!< The minor version */
        unsigned int micro_ = 0;    /*!< The micro version */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        Version();


        /*!
         *  \brief Constructor with the version in string
         *  \param version the version
         */
        Version(const Glib::ustring& version);


        //
        // Function
        //
        /*!
         *  \brief Get the major version
         *  \return the major version
         */
         inline unsigned int major() const
         {
             return major_;
         }

        /*!
         *  \brief Get the minor version
         *  \return the minor version
         */
         inline unsigned int minor() const
         {
             return minor_;
         }

        /*!
         *  \brief Get the micro version
         *  \return the micro version
         */
         inline unsigned int micro() const
         {
             return micro_;
         }

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
         Glib::ustring toUstring() const;


         //
         // Operator
         //
        /*!
         *  \brief Operator ==
         *  \param version an other version
         *  \return true if equal, false otherwise
         */
         bool operator==(const Version& version);

        /*!
         *  \brief Operator !=
         *  \param version an other version
         *  \return true if different, false otherwise
         */
         bool operator!=(const Version& version);

        /*!
         *  \brief Operator >
         *  \param version an other version
         *  \return true if superior, false otherwise
         */
         bool operator>(const Version& version);

        /*!
         *  \brief Operator <
         *  \param version an other version
         *  \return true if inferior, false otherwise
         */
         bool operator<(const Version& version);

        /*!
         *  \brief Operator >=
         *  \param version an other version
         *  \return true if superior or equal, false otherwise
         */
         bool operator>=(const Version& version);

        /*!
         *  \brief Operator <=
         *  \param version an other version
         *  \return true if inferior or equal, false otherwise
         */
         bool operator<=(const Version& version);
    };
}


#endif // VERSION_H_INCLUDED
