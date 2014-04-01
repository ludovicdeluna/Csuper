/*!
 * \file    structure.h
 * \brief   Prototypes des fonction de gestion des fichiers de la struction contenant les informations
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * structure.h
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

#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#include "fonction.h"
#include <time.h>

/*!
 * \def TAILLE_MAX_NOM
 * Definit la taille max d'un nom a 30
 */
#define TAILLE_MAX_NOM 30

/*!
 * \def VERSION
 * Definit la version a 1.4
 */
#define VERSION 1.4

/*!
 * \struct game_config
 * Type representant une configuration de jeu
 */
typedef struct
{
    float nb_max;          /*!< Nombre maximum que peut prendre un joueur. */
    char sens_premier;     /*!< Vaut 1 si le premier est celui qui a le plus de points, -1 sinon */
    char tour_par_tour;    /*!< Vaut 1 si on joue en tour par tour, 0 sinon */
    char use_distributor;  /*!< Vaut 1 si on utilise un distributeur, 0 sinon */
    char number_after_comma;/*!< Le nombre de chiffres apres la virgule dans l'affichage */
    char name[TAILLE_MAX_NOM];/*!< Le nom de la configuration de jeu */
}game_config;


/*!
 * \struct Fichier_Jeu
 * Type representant un fichier .jeu
 */
typedef struct
{
    float version;         /*!< Version de la structure. */
    float taille_max_nom;  /*!< Taille maximum que peut prendre un nom de joueur. */
    float jour;            /*!< Jour de creation de la structure. */
    float mois;            /*!< Mois de creation de la structure. */
    float annee;           /*!< Annee de creation de la structure. */
    float nb_joueur;       /*!< Nombre de joueurs. */
    game_config config;    /*!< La configuration de la partie*/
    char **nom_joueur;     /*!< Tableau contenant tout les noms de joueurs. */
    float *point_tot;      /*!< Tableau contenant tout les points totaux des joueurs. */
    float *position;       /*!< Tableau contenant la position des joueurs. */
    float *nb_tour;        /*!< Nombre de tour dans le jeu par joueur. */
    float distribue;       /*!< Numero de la personne qui doit distribuer. */
    float **point;         /*!< Tableau contenat les points de chaque joueur a chaque tour. */
} Fichier_Jeu;

Fichier_Jeu *creerFichierStruct(float nb_joueur , game_config config);
void fermeeFichierStruct(Fichier_Jeu *ptr_struct_fichier);
void debNouvTour(Fichier_Jeu *ptr_struct_fichier, int num_joueur);
void finNouvTour(Fichier_Jeu *ptr_struct_fichier, int num_joueur);
void calculPosition(Fichier_Jeu *ptr_struct_fichier);
void ajoutDistribueStruct(Fichier_Jeu *ptr_struct_fichier, char *nom_distribue);
int depScoreMax(Fichier_Jeu *ptr_struct_fichier);
int maxNbTour(Fichier_Jeu *ptr_struct_fichier);
int rechercheNumJoueur(Fichier_Jeu *ptr_struct_fichier, char *nom_personne);

#endif
