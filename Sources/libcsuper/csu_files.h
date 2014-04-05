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
 * \def TAILLE_MAX_NOM_FICHIER
 * Definit la taille max d'un nom a 250
 */
#define TAILLE_MAX_NOM_FICHIER 250

/*!
 * \def EXTENSION_FICHIER
 * Definit l'extension du fichier a "csu"
 */
#define EXTENSION_FICHIER "csu"

/*!
 * \def TYPE_FICHIER
 * Definit la chaine de caractere permettant de verifier le type de fichier a "CompteurScoreUniversel"
 */
#define TYPE_FICHIER "CompteurScoreUniversel"

FILE *ouvrirFichierExtension(char nome[], char mode[]);
Fichier_Jeu *lireFichier(char *nom);
int ecrireFichier(char *nom, Fichier_Jeu *ptr_struct_fichier);
int nouveauScore(char *nom, Fichier_Jeu *ptr_struct_fichier);
int supprimerFichier(char *nom);
int renommerFichier(char *nom_ancien, char *nom_nouveau);

#endif
