/*!
 * \file    config.h
 * \brief   Prototypes des fonction des fichiers lies a la config
 * \author  Remi BERTHO
 * \date    27/03/14
 * \version 2.2.0
 */

 /*
 * config.h
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

#include "fonction.h"
#include "structure.h"
#include "fichier.h"
#include "emplacement_fichier.h"

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

/*!
 * \def NOM_DOSSIER_CONFIG
 * Definit NOM_DOSSIER_CONFIG a "config"
 */
#define NOM_DOSSIER_CONFIG "config"

/*!
 * \def NOM_FICHIER_CONFIG
 * Definit NOM_FICHIER_CONFIG a "configuratio"
 */
#define NOM_FICHIER_CONFIG "configuration"

typedef struct
{
    int nb_config;
    char **name_game_config;
}list_game_config;

list_game_config *makeListGameConfig(int nb_config);
void freeListGameConfig(list_game_config *ptr_list_config);
int makeConfigListFile();
list_game_config *readConfigListFile();
int addConfigListFile(char *new_config_name);
int removeConfigListFile(int num_suppr, list_game_config *ptr_list_config);
int makeConfigFile(game_config config);
int removeConfigFile(char *config_name);
int readConfigFile(int num_read, list_game_config *ptr_list_config, game_config *ptr_config);

#endif
