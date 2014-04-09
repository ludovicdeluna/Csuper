/*!
 * \file    game_config.h
 * \brief   Prototypes des fonction des fichiers lies a la configuration de jeu
 * \author  Remi BERTHO
 * \date    27/03/14
 * \version 2.2.0
 */

 /*
 * game_config.h
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

#ifndef GAME_CONFIG_H_INCLUDED
#define GAME_CONFIG_H_INCLUDED

#include <math.h>
#include "csu_struct.h"
#include "file_system_path.h"

/*!
 * \def CONFIGURATION_FOLDER_NAME
 * Definit CONFIGURATION_FOLDER_NAME a "config"
 */
#define CONFIGURATION_FOLDER_NAME "config"

/*!
 * \def CONFIGURATION_FILE_NAME
 * Definit CONFIGURATION_FILE_NAME a "configuratio"
 */
#define CONFIGURATION_FILE_NAME "configuration"

typedef struct
{
    int nb_config;
    char **name_game_config;
}list_game_config;

list_game_config *newListGameConfig(int nb_config);
void closeListGameConfig(list_game_config *ptr_list_config);
int makeConfigListFile();
list_game_config *readConfigListFile();
int addConfigListFile(char *new_config_name);
int removeConfigListFile(int index_delete, list_game_config *ptr_list_config);
int newConfigFile(game_config config);
int removeConfigFile(char *config_name);
int readConfigFile(int index_read, list_game_config *ptr_list_config, game_config *ptr_config);

#endif
