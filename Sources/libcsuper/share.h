/*!
 * \file    share.h
 * \brief   Header for the essential function of libcsuper
 * \author  Remi BERTHO
 * \date    25/01/15
 * \version 4.1.0
 */

/*
* share.h
*
* Copyright 2014-2015
 Remi BERTHO <remi.bertho@openmailbox.org>
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

#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <libintl.h>
#include <stdbool.h>
#include <hpdf.h>
#include <math.h>
#include <locale.h>


/*!
 * \def _(String)
 * Define the _ for gettext.
 */
#ifndef NOT_LIBCSUPER
#define _(String) dgettext ("libcsuper", String)
#endif // _

/*!
 * \def CSUPER_VERSION
 * Define the version of csuper
 */
#define CSUPER_VERSION "4.2.0"

void libcsuper_initialize();
void wrongChoice();
void clearScreen();
int compareFloatDescending(void const *a, void const *b);
int compareFloatAscending(void const *a, void const *b);
void *myAlloc(int size_alloue);
void myRealloc(void **ptr,int size_alloue);
char *integerToYesNo(int i, char *yes, char *no);
char *utf8ToLatin9(const char *const string);
void convertFloatString(char *output, float input,int decimal_place);
float convertStringFloat(char *str);
int convertStringInt(char *str);
bool convertStringBool(char *str);

#endif
