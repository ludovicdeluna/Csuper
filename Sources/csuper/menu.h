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

#include "keyboarding.h"
#include "main.h"
#include "csuper.h"


char *menuFileName(char file_name[SIZE_MAX_FILE_NAME]);
void menuStartGame(float *ptr_nb_player, game_config *ptr_config);
void menuGameConfig(game_config *ptr_config);
void menuDistributor(char *distributor_name);
void menuPlayersName(csuStruct *ptr_csu_struct);
void menuPlayersPoints(csuStruct *ptr_csu_struct);
int menuPlayerIndex(csuStruct *ptr_csu_struct);
int menuContinue();
int menuDelete();
void menuNewPath(char *new_path);

#endif
