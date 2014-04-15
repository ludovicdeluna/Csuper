/*!
 * \file    file_system_path.h
 * \brief   Prototypes des fonctions qui l'emrankment des fichiers sauvegardes
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * file_system_path.h
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef FILE_SYSTEM_PATH_H_INCLUDED
#define FILE_SYSTEM_PATH_H_INCLUDED

#include <sys/stat.h>
#include <sys/types.h>
#include "csu_struct.h"
#include "csu_files.h"


/*!
 * \def FILE_NAME_SYSTEM_PATH
 * Definit FILE_NAME_SYSTEM_PATH a "preferences.txt"
 */
#define FILE_NAME_SYSTEM_PATH "system_path.txt"

/*!
 * \def MAIN_FOLDER_NAME
 * Definit MAIN_FOLDER_NAME
 */
#ifndef PORTABLE
#define MAIN_FOLDER_NAME ".csuper"
#else
#define MAIN_FOLDER_NAME "csuper_config_files"
#endif // PORTABLE

int createFileSystemPath();
int readFileSystemPath(char *file_name);
int readSystemPath(char *file_name);
int changeSystemPath(char *new_path);

#endif
