/*!
 * \file    csuper.h
 * \brief   Include of csuper
 * \author  Remi BERTHO
 * \date    17/04/14
 * \version 2.2.0
 */

 /*
 * csuper.h
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper is distributed in the hope that it will be useful,
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


#ifndef CSUPER_H_INCLUDED
#define CSUPER_H_INCLUDED


#include "../libcsuper/libcsuper.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <locale.h>
#include <libintl.h>


/*!
 * \def _(String)
 * Define the _ for gettext.
 */
#define _(STRING) gettext(STRING)



#endif // CSUPER_H_INCLUDED
