/*!
 * \file    exceptions.h
 * \brief   Exceptions of Csuper
 * \author  Remi BERTHO
 * \date    25/05/14
 * \version 4.3.0
 */

/*
* exceptions.h
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

#include "exceptions.h"
#include <glibmm/i18n.h>

using namespace std;

namespace csuper
{
    xmlError::xmlError(const string& what_arg) : runtime_error(_("XML Error: ")+what_arg)
    {

    }


    alreadyExist::alreadyExist(const string& what_arg) : runtime_error(_("Already exist: ")+what_arg)
    {

    }


    notFound::notFound(const string& what_arg) : runtime_error(_("Not found: ")+what_arg)
    {

    }


    fileError::fileError(const string& what_arg) : runtime_error(_("File error: ")+what_arg)
    {

    }


    wrongUse::wrongUse(const string& what_arg) : logic_error(_("Wrong use: ")+what_arg)
    {

    }
}
