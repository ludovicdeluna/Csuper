/*!
 * \file    game_config.h
 * \brief   Game configurations
 * \author  Remi BERTHO
 * \date    29/04/14
 * \version 2.4.0
 */

/*
* game_config.h
*
* Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
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

#ifndef GAME_CONFIG_H_INCLUDED
#define GAME_CONFIG_H_INCLUDED

#include <math.h>
#include "csu_struct.h"
#include "preferences_files.h"

/*!
 * \def CONFIGURATION_FOLDER_NAME
 * Define the name of the folder which contain the game configurations
 */
#define CONFIGURATION_FOLDER_NAME "config"

/*!
 * \def CONFIGURATION_FILE_NAME
 * Define the name of the file which contain the list of the game configurations
 */
#define CONFIGURATION_FILE_NAME "configuration"

/*!
 * \def CONFIGURATION_XML_FILENAME
 * Define the filename of the file which contain the game configuration
 */
#define CONFIGURATION_XML_FILENAME "game_configuration.xml"

/*!
 * \def STRING_CHECK_GAME_CONFIG
 * String for checking if the file is game configuration file.
 */
#define STRING_CHECK_GAME_CONFIG "Csuper_Game_Configuration"

/*!
 * \def GAME_CONFIG_FILE_XML_VERSION
 * Define the version of the XML game configuration file
 */
#define GAME_CONFIG_FILE_XML_VERSION 1.0

/*!
 * \struct list_game_config
 * Represent a list of game configuration
 */
typedef struct
{
    int nb_config;              /*!< Number of game configuration. */
    char **name_game_config;    /*!< The list of the game configuration. */
    game_config *game_configs;
} list_game_config;


list_game_config *newListGameConfig(int nb_config);
void closeListGameConfig(list_game_config *ptr_list_config);
void addConfigListGameConfig(list_game_config *ptr_list_config,game_config config);
void removeConfigListGameConfig(list_game_config *ptr_list_config,game_config config);

bool makeConfigListFile(char * home_path);
list_game_config *readConfigListFile(char * home_path);
bool addConfigListFile(char *new_config_name, char * home_path); // Depreciated
bool removeConfigListFile(int index_delete, list_game_config *ptr_list_config,char * home_path); //
bool newConfigFile(game_config config,char * home_path); //
bool removeConfigFile(char *config_name,char * home_path); // Depreciated
bool readConfigFile(int index_read, list_game_config *ptr_list_config, game_config *ptr_config,char * home_path);

bool exportConfigFile(char *home_path,char *file_name, int *id,int nb_id);
bool importConfigFile(char *home_path,char *file_name, int *id,int nb_id);
list_game_config *newListGameConfigFromImport(char *filename);

list_game_config *readXmlListGameConfig(char *filename);
bool writeXmlListGameConfig(char *filename,list_game_config *ptr_list_config);
list_game_config *readXmlListGameConfigWithId(char *filename,int *id,int nb_id);
bool writeXmlListGameConfigWithId(char *filename,list_game_config *ptr_list_config,int *id,int nb_id);

#endif
