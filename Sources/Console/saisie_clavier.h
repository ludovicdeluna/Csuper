/*!
 * \file    saisie_clavier.h
 * \brief   Prototypes des fonctions de saisie clavier
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * saisie_clavier.h
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

#include "../System/fonction.h"
#include <locale.h>
#include <string.h>
#include <math.h>

/*!
 * \def NB_CARACT_INT
 * Definit NB_CARACT_INT a 12
 */
#define NB_CARACT_INT 12

/*!
 * \def NB_CARACT_FLOT
 * Definit NB_CARACT_FLOT a 39
 */
#define NB_CARACT_FLOT 39

/*!
 * \def NB_CARACT_DOUB
 * Definit NB_CARACT_DOUB a 309
 */
#define NB_CARACT_DOUB 309

void clean_stdin(void);
char *saisieClavierChaine(char *chaine, int nb_caract_plus_un);
void saisieClavierEntier(int *nb);
void saisieClavierFlottant(float *nb);
void saisieClavierFlottantSansVirgule(float *nb);
void saisieClavierDouble(double *nb);
char *saisieClavierCaractere(char *c);
void systemPause();

#endif
