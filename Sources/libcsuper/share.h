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

namespace csuper
{

    /*!
     * \def CSUPER_VERSION
     * Define the version of csuper
     */
    #define CSUPER_VERSION "4.3.0"

    void libcsuper_initialize();
    void clearScreen();

}

#endif
