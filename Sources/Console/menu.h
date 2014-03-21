/*!
 * \file    menu.h
 * \brief   Prototypes des fonctions qui gerent les menus demandant de rentrer des valeurs du logiciel
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * menu.h
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

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../System/saisie_clavier.h"
#include "../System/fichier.h"


char *menuNomFichier(char nom_fichier[TAILLE_MAX_NOM_FICHIER]);
void menuDebutPartie(float *ptr_nb_joueur, float *ptr_nb_max , char *ptr_sens_premier);
void menuDistribue(char *nom_distribue);
void menuNomJoueur(Fichier_Jeu *ptr_struct_fichier);
void menuPointsJoueur(Fichier_Jeu *ptr_struct_fichier);
int menuContinuer();
int menuSupprimer();
void menuNouveauChemin(char *nouveauChemin);

#endif
