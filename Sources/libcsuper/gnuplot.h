/*!
 * \file    gnuplot.h
 * \author  Remi BERTHO
 * \date    14/05/15
 * \version 4.2.0
 */

/*
 * gnuplot.h
 *
 * Copyright 2014-2015 dalan <remi.bertho@openmailbox.org>
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

#ifndef GNUPLOT_H_INCLUDED
#define GNUPLOT_H_INCLUDED

#include "share.h"
#include "csu_struct.h"
#include "csu_files.h"

bool exportToGnuplotFile(csuStruct *ptr_csu_struct, char *filename);
bool exportToGnuplotData(csuStruct *ptr_csu_struct, char *filename);
bool exportToGnuplotScript(csuStruct *ptr_csu_struct, char *filename);

#endif // GNUPLOT_H_INCLUDED
