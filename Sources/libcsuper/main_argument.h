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
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
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
 * \def READ_FILE
 * Define the call to read a file to 0
 */
#define READ_FILE 0

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
 * \def OPEN_FILE
 * Define the call to read a file to 1
 */
#define OPEN_FILE 1

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
 * \def HELP
 * Define the call help to 2
 */
#define HELP 2

bool searchArgument(int argc, char *argv[], int *function, int *file_place);
void displayHelp();

#endif
