/*!
 * \file    main_argument.h
 * \brief   Begin csuper
 * \author  Remi BERTHO
 * \date    16/04/14
 * \version 2.2.0
 */

/*
 * main_argument.h
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef ARGUMENT_MAIN_H_INCLUDED
#define ARGUMENT_MAIN_H_INCLUDED

#include "share.h"

typedef enum
{
    read_file,
    open_file,
    help,
    export_to_pdf,
    export_to_gnuplot,
    export_to_m,
    export_to_csv
} main_argument_function;

/*!
 * \def STRING_READ_FILE
 * Define the argument which call to read a file to "--read"
 */
#define STRING_READ_FILE "--read"

/*!
 * \def STRING_READ_FILE_RED
 * Define the reduce argument which call to read a file to "-r"
 */
#define STRING_READ_FILE_RED "-r"

/*!
 * \def STRING_OPEN_FILE
 * Define the argument which call to open a file to  "--open"
 */
#define STRING_OPEN_FILE "--open"

/*!
 * \def STRING_OPEN_FILE_RED
 * Define the reduce argument which call to open a file to "-o"
 */
#define STRING_OPEN_FILE_RED "-o"

/*!
 * \def STRING_HELP
 * Define the argument which call help to "--help"
 */
#define STRING_HELP "--help"

/*!
 * \def STRING_HELP_RED
 * Define the reduce argument which call help to "-h"
 */
#define STRING_HELP_RED "-h"

/*!
 * \def STRING_EXPORT_TO_PDF
 * Define the argument which call to export to pdf to "--to-pdf"
 */
#define STRING_EXPORT_TO_PDF "--to-pdf"

/*!
 * \def STRING_EXPORT_TO_PDF_RED
 * Define the reduce argument which call to export to pdf to "-p"
 */
#define STRING_EXPORT_TO_PDF_RED "-p"


/*!
 * \def STRING_EXPORT_TO_CSV
 * Define the argument which call to export to csv to "--to-csv"
 */
#define STRING_EXPORT_TO_CSV "--to-csv"

/*!
 * \def STRING_EXPORT_TO_CSV_RED
 * Define the reduce argument which call to export to csv to "-c"
 */
#define STRING_EXPORT_TO_CSV_RED "-c"

/*!
 * \def STRING_EXPORT_TO_GNUPLOT
 * Define the argument which call to export to gnuplot
 */
#define STRING_EXPORT_TO_GNUPLOT "--to-gnuplot"

/*!
 * \def STRING_EXPORT_TO_GNUPLOT_RED
 * Define the reduce argument which call to export to gnuplot
 */
#define STRING_EXPORT_TO_GNUPLOT_RED "-g"

/*!
 * \def STRING_EXPORT_TO_M
 * Define the argument which call to export to matlab/octave file
 */
#define STRING_EXPORT_TO_M "--to-matlab"

/*!
 * \def STRING_EXPORT_TO_M_RED
 * Define the reduce argument which call to export to matlab/octave file
 */
#define STRING_EXPORT_TO_M_RED "-m"

bool searchArgument(int argc, char *argv[], main_argument_function *function, int *file_place);
void displayHelp();

#endif
