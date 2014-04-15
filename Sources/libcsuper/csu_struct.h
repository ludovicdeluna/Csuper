/*!
 * \file    csu_struct.h
 * \brief   Prototypes des fonction de gestion des fichiers de la struction contenant les informations
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * csu_struct.h
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
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

#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#include <time.h>
#include <float.h>
#include "share.h"

/*!
 * \def SIZE_MAX_NAME
 * Definit la size max d'un nom a 30
 */
#define SIZE_MAX_NAME 30

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
    float nb_max;               /*!< Nombre maximum que peut prendre un joueur. */
    char first_way;          /*!< Vaut 1 si le premier est celui qui a le plus de points, -1 sinon */
    char turn_by_turn;         /*!< Vaut 1 si on joue en tour par tour, 0 sinon */
    char use_distributor;       /*!< Vaut 1 si on utilise un distributeur, 0 sinon */
    char number_after_comma;    /*!< Le nombre de chiffres apres la virgule dans l'affichage */
    char max;                   /*!< Vaut 1 si on utilise un maximum, 0 si c'est un minimum */
    char name[SIZE_MAX_NAME];  /*!< Le nom de la configuration de jeu */
    float begin_score;          /*!< L score de chacun des joueurs au debut de la partie */
}game_config;


/*!
 * \struct csuStruct
 * Type representant un fichier .jeu
 */
typedef struct
{
    float version;         /*!< Version de la structure. */
    float size_max_name;  /*!< Taille maximum que peut prendre un nom de joueur. */
    float day;            /*!< Jour de creation de la structure. */
    float month;            /*!< Mois de creation de la structure. */
    float year;           /*!< Annee de creation de la structure. */
    float nb_player;       /*!< Nombre de joueurs. */
    game_config config;    /*!< La configuration de la partie*/
    char **player_names;     /*!< Tableau contenant tout les noms de joueurs. */
    float *total_points;      /*!< Tableau contenant tout les points totaux des joueurs. */
    float *rank;       /*!< Tableau contenant la rank des joueurs. */
    float *nb_turn;        /*!< Nombre de tour dans le jeu par joueur. */
    float distributor;       /*!< Numero de la personne qui doit distributorr. */
    float **point;         /*!< Tableau contenat les points de chaque joueur a chaque tour. */
} csuStruct;

csuStruct *newCsuStruct(float nb_player , game_config config);
void closeCsuStruct(csuStruct *ptr_csu_struct);
void startNewTurn(csuStruct *ptr_csu_struct, int index_player);
void endNewTurn(csuStruct *ptr_csu_struct, int index_player);
void rankCalculation(csuStruct *ptr_csu_struct);
void addDistributorCsuStruct(csuStruct *ptr_csu_struct, char *distributor_name);
int exceedMaxNumber(csuStruct *ptr_csu_struct);
int maxNbTurn(csuStruct *ptr_csu_struct);
int searchPlayerIndex(csuStruct *ptr_csu_struct, char *player_name);

#endif
