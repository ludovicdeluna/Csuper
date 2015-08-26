/*!
 * \file    version.cpp
 * \brief   Header for the essential function of libcsuper
 * \author  Remi BERTHO
 * \date    26/08/15
 * \version 4.3.0
 */

/*
* version.cpp
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

#include "version.h"
#include "config.h"
#include "share.h"

namespace csuper
{
    using namespace Glib;
    using namespace std;

    //
    // Constructor
    //
    Version::Version()
    {

    }

    Version::Version(const ustring& version)
    {
        stringstream ss(version);
        char tmp_1, tmp_2;
        ss >> major_ >> tmp_1 >> minor_ >> tmp_2 >> micro_;
    }

    //
    // Function
    //
    ustring Version::toUstring() const
    {
        return intToUstring(major()) + "." + intToUstring(minor()) + "." + intToUstring(micro());
    }


    //
    // operator
    //
    bool Version::operator==(const Version& version)
    {
        return major() == version.major()
                && minor() == version.minor()
                && micro() == version.micro();
    }


    bool Version::operator!=(const Version& version)
    {
        return major() != version.major()
                || minor() != version.minor()
                || micro() != version.micro();
    }


    bool Version::operator>(const Version& version)
    {
        return (major() > version.major()) ||
            (major() == version.major() && minor() > version.minor()) ||
            (major() == version.major() && minor() == version.minor() && micro() > version.micro());
    }


    bool Version::operator<(const Version& version)
    {
        return (major() < version.major()) ||
            (major() == version.major() && minor() < version.minor()) ||
            (major() == version.major() && minor() == version.minor() && micro() < version.micro());
    }


    bool Version::operator>=(const Version& version)
    {
        return (*this == version || *this > version);
    }


    bool Version::operator<=(const Version& version)
    {
        return (*this == version || *this < version);
    }
}
