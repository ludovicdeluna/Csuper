/*!
 * \file    csu_files.h
 * \brief   Files management
 * \author  Remi BERTHO
 * \date    16/04/14
 * \version 2.2.0
 */

 /*
 * csu_files.h
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

#ifndef FICHIER_JEU_H_INCLUDED
#define FICHIER_JEU_H_INCLUDED

#include "csu_struct.h"
#include "filename.h"
#include <unistd.h>


/*!
 * \def SIZE_MAX_FILE_NAME
 * Define the size maximum of a filename to 1024
 */
#define SIZE_MAX_FILE_NAME 1024

/*!
 * \def FILE_EXTENSION_CSU
 * Define the file extension to "csu"
 */
#define FILE_EXTENSION_CSU "csu"

/*!
 * \def STRING_CHECK_CSU_FILE
 * String for checking if the file is a csu file.
 */
#define STRING_CHECK_CSU_FILE "CompteurScoreUniversel"

FILE *openFileCsuExtension(char file_name[], char mode[]);
csuStruct *readCsuFile(char *file_name);
bool writeCsuFile(char *file_name, csuStruct *ptr_csu_struct);
bool writeFileNewTurn(char *file_name, csuStruct *ptr_csu_struct);

#endif
