/*!
 * \file    emplacement_fichier.h
 * \brief   Prototypes des fonctions qui l'emplacement des fichiers sauvegardes
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * emplacement_fichier.h
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

#ifndef EMPLACEMENT_FICHIER_H_INCLUDED
#define EMPLACEMENT_FICHIER_H_INCLUDED

#include <sys/stat.h>
#include <sys/types.h>
#include "fichier.h"

/*!
 * \def PORTABLE
 * Definit PORTABLE
 */
/*#define PORTABLE*/

/*!
 * \def NOM_FICHIER
 * Definit NOM_FICHIER a "preferences.txt"
 */
#define NOM_FICHIER "preferences.txt"

/*!
 * \def NOM_DOSSIER
 * Definit NOM_DOSSIER a ".csuper"
 */
#define NOM_DOSSIER ".csuper"

int creationPreferences();
int lecturePreferences(char *nom_fichier);
int lectureCheminFichier(char *nom_fichier);
int changerCheminFichier(char *nouveauChemin);

#endif
