/*!
 * \file    interface.h
 * \brief   Prototypes des fonctions qui gerent l'interface graphique du logiciel
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * interface.h
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

#ifndef INTERFACE_INCLUDED
#define INTERFACE_INCLUDED

#include <dirent.h>

#include "menu.h"
#include "affichage.h"
#include "../System/emplacement_fichier.h"

typedef enum {nouvPart=1 , charPart=2 , affFich=3 , supprFich=4 , listFich=5 , pref=6, quit=7 , easterEggs = 42} MenuPrincipal;
#ifndef PORTABLE
typedef enum {nouvChem=1, lireChem=2 , newGameConf=3, removeGameConf=4, printListGameConf=5 , printGameConf=6 ,menuPrinc=7 , easterEggs2 = 42} MenuPreferences;
#else
typedef enum {newGameConf=1,removeGameConf=2,printListGameConf=3 , printGameConf=4 ,menuPrinc=5, easterEggs2 = 42} MenuPreferences;
#endif


void afficheFichier();
void supprimerFichierNom();
void listerFichier();
void jouer(Fichier_Jeu *ptr_struct_fichier, char *nom_fichier);
void nouvellePartie();
void chargerPartie();
void menuPrincipal();
void menuPreferences();
void nouveauCheminFichier();
void lireCheminFichier();
void chargerPartieLocale(char *nom_fichier);
void afficheFichierLocale(char *nom_fichier);
void newGameConfig();
void removeGameConfig();
void printListGameConfig();
void printGameConfigFile();

#endif
