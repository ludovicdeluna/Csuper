/*!
 * \file    csu_struct.h
 * \brief   Management of the csu files header
 * \author  Remi BERTHO
 * \date    16/06/14
 * \version 4.0.0
 */

/*
* csu_struct.h
*
* Copyright 2014-2015 Remi BERTHO <remi.bertho@gmail.com>
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
#include "file.h"

/*!
 * \def SIZE_MAX_NAME
 * Define size max of name to 30
 */
#define SIZE_MAX_NAME 30

/*!
 * \def VERSION
 * Define the version to 1.4
 */
#define VERSION 1.4

/*!
 * \struct game_config
 * Represent a game configuration
 */
typedef struct
{
    float nb_max;               /*!< Number maximum or minimum that can reach a player. */
    char first_way;             /*!< Is 1 if the first those has the maximum of points, -1 otherwise */
    char turn_based;          /*!< Is 1 if this is a turn-based game, 0 otherwise */
    char use_distributor;       /*!< Is 1 if the game use a distributor, 0 otherwise */
    char decimal_place;         /*!< The number of decimal place which are display */
    char max;                   /*!< Is 1 if the game use a maximum, 0 if it's a minimum */
    char name[SIZE_MAX_NAME];   /*!< The name of the game configuration */
    float begin_score;          /*!< The score of all players in the beginning of the game */
} game_config;


/*!
 * \struct csuStruct
 * Represent a csu file
 */
typedef struct
{
    float version;              /*!< Version of the structure. */
    float size_max_name;        /*!< Maximum size that can reach a player name. */
    float day;                  /*!< Day of the structure creation. */
    float month;                /*!< Month of the structure creation. */
    float year;                 /*!< Year of the structure creation. */
    float nb_player;            /*!< Number of player. */
    game_config config;         /*!< The game configuration.*/
    char **player_names;        /*!< Array containing the name of all players. */
    float *total_points;        /*!< Array containing the total score of all players. */
    float *rank;                /*!< Array containing the rank of all players. */
    float *nb_turn;             /*!< Array containing the number of turn of all players. */
    float distributor;          /*!< Index of the distributor. */
    float **point;              /*!< Array containing the points of all players in each turn. */
} csuStruct;

csuStruct *newCsuStruct(float nb_player , game_config config);
void closeCsuStruct(csuStruct *ptr_csu_struct);
void startNewTurn(csuStruct *ptr_csu_struct, int index_player);
void endNewTurn(csuStruct *ptr_csu_struct, int index_player);
void rankCalculation(csuStruct *ptr_csu_struct);
int searchIndexFromPosition(csuStruct *ptr_csu_struct, int position,int *nb);
void addDistributorCsuStruct(csuStruct *ptr_csu_struct, char *distributor_name);
bool exceedMaxNumber(csuStruct *ptr_csu_struct);
int maxNbTurn(csuStruct *ptr_csu_struct);
int searchPlayerIndex(csuStruct *ptr_csu_struct, char *player_name);
bool differentsPlayerName(csuStruct *ptr_csu_struct);
csuStruct *copyCsuStruct(csuStruct *ptr_csu_struct);
bool changeDistributor(csuStruct *ptr_csu_struct, int index);
float pointsAtTurn(csuStruct *ptr_csu_struct, int player_index, int turn);

#endif
