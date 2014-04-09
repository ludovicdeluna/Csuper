/*!
 * \file    csu_files.h
 * \brief   Prototypes des fonction de gestion des fichiers
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * csu_files.h
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of Csuper.
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

#ifndef FICHIER_JEU_H_INCLUDED
#define FICHIER_JEU_H_INCLUDED

#include "csu_struct.h"
#include <unistd.h>


/*!
 * \def SIZE_MAX_FILE_NAME
 * Definit la size max d'un nom a 250
 */
#define SIZE_MAX_FILE_NAME 250

/*!
 * \def FILE_EXTENSION
 * Definit l'extension du fichier a "csu"
 */
#define FILE_EXTENSION "csu"

/*!
 * \def STRING_CHECK_CSU_FILE
 * Definit la chaine de caractere permettant de verifier le type de fichier a "CompteurScoreUniversel"
 */
#define STRING_CHECK_CSU_FILE "CompteurScoreUniversel"

FILE *openFileCsuExtension(char file_name[], char mode[]);
csuStruct *readCsuFile(char *file_name);
int writeCsuFile(char *file_name, csuStruct *ptr_csu_struct);
int writeFileNewTurn(char *file_name, csuStruct *ptr_csu_struct);
int deleteCsuFile(char *file_name);
int renameCsuFile(char *old_name, char *new_name);

#endif
