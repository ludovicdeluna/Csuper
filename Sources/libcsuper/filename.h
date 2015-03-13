/*!
 * \file    filename.h
 * \brief   Header for the essential function of libcsuper
 * \author  Remi BERTHO
 * \date    22/12/14
 * \version 4.1.0
 */

 /*
 * filename.h
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

#ifndef FILENAME_H_INCLUDED
#define FILENAME_H_INCLUDED

#include "preferences_files.h"

void addFileCsuExtension(char *file_name);
void addFilePdfExtension(char *file_name);
void addFileCsvExtension(char *file_name);
void removeFileExtension(char *file_name);
bool getFolderFromFilename(char *file_name_to_folder);
bool getSimpleFilenameFromFullFilename(char *full_filename,char *simple_filename);
bool checkPath(char *path);
bool checkFilename(char *filename,char * folder);
void readHomePath(char *path);
void readHomePathSlash(char *path);
bool removeFilenameExtension(char *filename);

#endif // FILENAME_H_INCLUDED
