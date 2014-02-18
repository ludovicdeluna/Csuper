/*!
 * \file    affichage.h
 * \brief   Prototypes des fonctions qui gerent l'affichage des scores du logiciel
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * affichage.h
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

#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include "structure.h"
#include <string.h>

void afficherNom(Fichier_Jeu *ptr_struct_fichier, int *ptr_taille_ligne);
void afficherLigne(int taille_ligne);
void afficherScoreTotal(Fichier_Jeu *ptr_struct_fichier);
void afficherDistribue(Fichier_Jeu *ptr_struct_fichier);
void afficherEnTete(Fichier_Jeu *ptr_struct_fichier);
void afficherScoreEntier(Fichier_Jeu *ptr_struct_fichier);
void afficherPosition(Fichier_Jeu *ptr_struct_fichier);
void afficherScore(Fichier_Jeu *ptr_struct_fichier);
void afficherStruct(Fichier_Jeu *ptr_struct_fichier);
void afficherPartieFinie(Fichier_Jeu *ptr_struct_fichier);
void afficherChaineTroisTab(char *chaine);
void afficherLicense();

#endif
