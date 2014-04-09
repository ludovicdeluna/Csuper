/*!
 * \file    share.h
 * \brief   Prototypes des fonctions essentielles au fonctionnement du programme
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * share.h
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

#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <libintl.h>

/*!
 * \def TRUE
 * Definit TRUE a 1
 */
#define TRUE 1

/*!
 * \def FALSE
 * Definit FALSE a 0
 */
#define FALSE 0

/*!
 * \def _(String)
 * Define the _ for gettext.
 */
#ifndef CSUPER
#define _(String) dgettext ("libcsuper", String)
#endif // CSUPER

void libcsuper_initialize();
void wrongChoice();
void clearScreen();
int compareFloatDescending(void const *a, void const *b);
int compareFloatAscending(void const *a, void const *b);
FILE *openFile(char nome[], char mode[]);
int closeFile(FILE *ptr_file);
int readFileSize(FILE *ptr_file);
void *myAlloc(int size_alloue);
void myRealloc(void **ptr,int size_alloue);
void addFileCsuExtension(char *file_name);

#endif
