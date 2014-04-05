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

/*!
 * \def VRAI
 * Definit VRAI a 1
 */
#define VRAI 1

/*!
 * \def FAUX
 * Definit FAUX a 0
 */
#define FAUX 0


void mauvais_choix();
void systemEfface();
int compareFlottantDecroissant(void const *a, void const *b);
int compareFlottantCroissant(void const *a, void const *b);
FILE *ouvrirFichier(char nome[], char mode[]);
int fermerFichier(FILE *ptr_fichier);
int lireTailleFichier(FILE *ptr_fichier);
void *myAlloc(int taille_alloue);
void myRealloc(void **ptr,int taille_alloue);
void ajoutExtension(char *nom_fichier);

#endif
