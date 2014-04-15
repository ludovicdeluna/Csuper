/*!
 * \file    main_argument.h
 * \brief   Lancement du programme
 * \author  Remi BERTHO
 * \date    21/03/14
 * \version 2.1.0
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
 * Definit l'appel a la lecture du fichier a "--read"
 */
#define STRING_READ_FILE "--read"

/*!
 * \def STRING_READ_FILE_RED
 * Definit l'appel a la lecture du fichier a "-r"
 */
#define STRING_READ_FILE_RED "-r"

/*!
 * \def READ_FILE
 * Definit l'appel a la lecture du fichier a 0
 */
#define READ_FILE 0

/*!
 * \def STRING_OPEN_FILE
 * Definit l'appel a l'ouverture du fichier a "--open"
 */
#define STRING_OPEN_FILE "--open"

/*!
 * \def STRING_OPEN_FILE_RED
 * Definit l'appel a l'ouverture du fichier a "-o"
 */
#define STRING_OPEN_FILE_RED "-o"

/*!
 * \def OPEN_FILE
 * Definit l'appel a l'ouverture du fichier a 1
 */
#define OPEN_FILE 1

/*!
 * \def STRING_HELP
 * Definit l'appel a l'aide a "--help"
 */
#define STRING_HELP "--help"

/*!
 * \def STRING_HELP_RED
 * Definit l'appel a l'aide a "-h"
 */
#define STRING_HELP_RED "-h"

/*!
 * \def HELP
 * Definit l'appel a l'aide a 2
 */
#define HELP 2

int searchArgument(int argc, char *argv[], int *fonction, int *file_place);
void displayHelp();

#endif
