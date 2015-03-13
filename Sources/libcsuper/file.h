/*!
 * \file    file.h
 * \brief   Header for the files function of libcsuper
 * \author  Remi BERTHO
 * \date    05/07/14
 * \version 4.0.1
 */

 /*
 * file.h
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

#include "share.h"

#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

FILE *openFile(char nome[], char mode[]);
int closeFile(FILE *ptr_file);
int readFileSize(FILE *ptr_file);
bool deleteFile(char *file_name);
bool renameFile(char *old_name, char *new_name);


#endif // FILE_H_INCLUDED
