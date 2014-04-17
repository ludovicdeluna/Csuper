/*!
 * \file    keyboarding.h
 * \brief   Function of keyboarding
 * \author  Remi BERTHO
 * \date    17/04/14
 * \version 2.2.0
 */

 /*
 * keyboarding.h
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

#ifndef SAISIE_CLAVIER_H_INCLUDED
#define SAISIE_CLAVIER_H_INCLUDED

#include "csuper.h"
#include <locale.h>
#include <string.h>
#include <math.h>
#include "main.h"
/*!
 * \def NB_CARACT_INT
 * Define the number of characters that need an int.
 */
#define NB_CARACT_INT 12

/*!
 * \def NB_CARACT_FLOAT
 *  Define the number of characters that need a float.
 */
#define NB_CARACT_FLOAT 39

/*!
 * \def NB_CARACT_DOUB
 * Define the number of characters that need a double
 */
#define NB_CARACT_DOUB 309

void clean_stdin(void);
char *stringKey(char *string, int nb_char_plus_one);
void intKey(int *nb);
void floatKey(float *nb);
void floatKeyNoComma(float *nb);
void doubleKey(double *nb);
char *charKey(char *c);
void systemPause();

#endif
