/*!
 * \file    game_config.c
 * \brief   Game configuration
 * \author  Remi BERTHO
 * \date    16/04/14
 * \version 2.2.0
 */

 /*
 * game_config.c
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

 #include "game_config.h"

/*!
 * \fn list_game_config *newListGameConfig(int nb_config)
 *  Create a list of game configuration.
 * \parma[in] nb_config the number of game configuration
 * \return une list_game_config
 */
list_game_config *newListGameConfig(int nb_config)
 {
     int i;
     list_game_config *config=(list_game_config *)myAlloc(sizeof(list_game_config));
     config->nb_config=nb_config;
     config->name_game_config = (char **)myAlloc(nb_config*sizeof(char*));
     for (i=0 ; i< nb_config ; i++)
        config->name_game_config[i]=(char *)myAlloc(sizeof(char)*SIZE_MAX_FILE_NAME);
    return config;
 }

/*!
 * \fn void closeListGameConfig(list_game_config *ptr_list_config)
 *  Free a list of game configuration
 * \parma[in] ptr_list_config a pointer on a list of game configuration
 */
void closeListGameConfig(list_game_config *ptr_list_config)
 {
     int i;
     for (i=0 ; i<ptr_list_config->nb_config ; i++)
        free(ptr_list_config->name_game_config[i]);
     free(ptr_list_config->name_game_config);
     free(ptr_list_config);
 }

 /*!
 * \fn int makeConfigListFile(char * home_path)
 *  Create the folder which contain the games configurations and the files which contain the list of games configurations
 * \param[in] home_path the path to the home directory
 * \return TRUE if everything is OK, FALSE otherwise
 */
int makeConfigListFile(char * home_path)
{
    char folder[SIZE_MAX_FILE_NAME]="";
    char file_name[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;

    sprintf(folder,"%s%s",home_path,MAIN_FOLDER_NAME);

    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(file_name,"%s/%s",folder,CONFIGURATION_FILE_NAME);

    sprintf(folder,"%s/%s",folder,CONFIGURATION_FOLDER_NAME);
    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif


    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return FALSE;

    fprintf(ptr_file,"%d",0);

    closeFile(ptr_file);

    return TRUE;
}

/*!
 * \fn list_game_config *readConfigListFile(char * home_path)
 *  Read the file which contain the list of game configuration.
 * \param[in] home_path the path to the home directory
 * \return a list_game_config
 */
list_game_config *readConfigListFile(char * home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;
    list_game_config *ptr_config;
    int nb_config;
    int i;

    sprintf(file_name_config,"%s%s/%s",home_path,MAIN_FOLDER_NAME,CONFIGURATION_FILE_NAME);

    ptr_file=openFile(file_name_config,"r");

    if(ptr_file == NULL)
    {
        makeConfigListFile(home_path);
        ptr_file=openFile(file_name_config,"r");
    }

    fscanf(ptr_file,"%d",&nb_config);

    ptr_config=newListGameConfig(nb_config);

    for (i=0 ; i< nb_config ; i++)
        fscanf(ptr_file,"%s",ptr_config->name_game_config[i]);

    closeFile(ptr_file);

    return ptr_config;
}

/*!
 * \fn int addConfigListFile(char *new_config_name,char *home_path)
 *  Add a new game configuration into the file which contain the list of game configuration.
 * \param[in] new_config_game the name of the new game configuration
 * \param[in] home_path the path to the home directory
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int addConfigListFile(char *new_config_name,char *home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;
    int i;
    list_game_config *ptr_list_config =readConfigListFile(home_path);

    sprintf(file_name_config,"%s%s/%s",home_path,MAIN_FOLDER_NAME,CONFIGURATION_FILE_NAME);

    ptr_file=openFile(file_name_config,"w");

    if(ptr_file == NULL)
        return FALSE;

    fprintf(ptr_file,"%d\n",ptr_list_config->nb_config+1);

    for (i=0 ; i< ptr_list_config->nb_config ; i++)
        fprintf(ptr_file,"%s\n",ptr_list_config->name_game_config[i]);

    fprintf(ptr_file,"%s",new_config_name);

    closeFile(ptr_file);
    closeListGameConfig(ptr_list_config);

    return TRUE;
}

/*!
 * \fn int removeConfigListFile(int index_delete, list_game_config *ptr_list_config,char *home_path)
 *  Remove a game configuration in the file which contain the list of game configuration and remove the game configuration.
 * \param[in] index_delete the index pf the file which will be deleted
 * \param[in] list_game_config the list of game configuration
 * \param[in] home_path the path to the home directory
 * \return TRUE if everything is OK, FALSE otherwise
 */
int removeConfigListFile(int index_delete, list_game_config *ptr_list_config,char *home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;
    int i;

    ptr_list_config=readConfigListFile(home_path);

    sprintf(file_name_config,"%s%s/%s",home_path,MAIN_FOLDER_NAME,CONFIGURATION_FILE_NAME);

    ptr_file=openFile(file_name_config,"w+");

    if(ptr_file == NULL)
        return FALSE;

    fprintf(ptr_file,"%d\n",ptr_list_config->nb_config-1);

    for (i=0 ; i< ptr_list_config->nb_config ; i++)
    {
        if (i!=index_delete)
            fprintf(ptr_file,"%s\n",ptr_list_config->name_game_config[i]);
        else
            removeConfigFile(ptr_list_config->name_game_config[i],home_path);
    }

    closeFile(ptr_file);
    closeListGameConfig(ptr_list_config);

    return TRUE;
}

 /*!
 * \fn int newConfigFile(game_config config,char * home_path)
 *  Create a game configuration file and put it into the game configuration file list.
 * \param[in] config the gale configuration
 * \param[in] home_path the path to the home directory
 * \return TRUE if everything is OK, FALSE otherwise
 */
int newConfigFile(game_config config,char * home_path)
{
    char folder[SIZE_MAX_FILE_NAME]="";
    char file_name[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;

    sprintf(folder,"%s%s",home_path,MAIN_FOLDER_NAME);

    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(folder,"%s/%s",folder,CONFIGURATION_FOLDER_NAME);
    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(file_name,"%s/%s",folder,config.name);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return FALSE;

    #ifdef __unix__
    fprintf(ptr_file,"%f ",config.nb_max);
    #elif _WIN32
    if (config.nb_max == INFINITY)
        fprintf(ptr_file,"inf ");
    else
        fprintf(ptr_file,"%f ",config.nb_max);
    #endif
    fprintf(ptr_file,"%d %d %d %d %d %f",config.first_way,config.turn_by_turn,config.use_distributor,config.number_after_comma,config.max,config.begin_score);

    closeFile(ptr_file);

    addConfigListFile(config.name,home_path);

    return TRUE;
}

 /*!
 * \fn int removeConfigFile(char *config_name,char * home_path)
 *  Delete a game configuration.
 * \param[in] config_name the name of the game configuration which will be deleted
 * \param[in] home_path the path to the home directory
 * \return TRUE if everything is OK, FALSE otherwise
 */
int removeConfigFile(char *config_name,char * home_path)
{
    char folder[SIZE_MAX_FILE_NAME]="";
    char file_name[SIZE_MAX_FILE_NAME]="";

    libcsuper_initialize();

    sprintf(folder,"%s%s",home_path,MAIN_FOLDER_NAME);

    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(folder,"%s/%s",folder,CONFIGURATION_FOLDER_NAME);
    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(file_name,"%s/%s",folder,config_name);

    if(remove(file_name))
    {
        printf(_("\nThe file %s cannot be deleted.\n"),file_name);
        perror("");
        return FALSE;
    }
    else
    {
        printf(_("\nThe file %s was well deleted.\n"),file_name);
        return TRUE;
    }

    return TRUE;
}

/*!
 * \fn int readConfigFile(int index_read, list_game_config *ptr_list_config, game_config *ptr_config,char * home_path)
 *  Read a game configuration file and close the list of game configuration
 * \param[in] index_read the index of the game configuration to be read
 * \param[in] ptr_list_config a pointer on the game configration list
 * \param[in] ptr_config a pointer on a game configuration
 * \param[in] home_path the path to the home directory
 * \return a list_game_config
 */
int readConfigFile(int index_read, list_game_config *ptr_list_config, game_config *ptr_config,char * home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;
    #ifdef _WIN32
    char buffer[5];
    #endif // _WIN32

    sprintf(file_name_config,"%s%s/%s/%s",home_path,MAIN_FOLDER_NAME,CONFIGURATION_FOLDER_NAME,ptr_list_config->name_game_config[index_read]);

    ptr_file=openFile(file_name_config,"r");

    if(ptr_file == NULL)
        return FALSE;

    /*Lis les differentes config*/
    #ifdef __unix__
    fscanf(ptr_file,"%f",&(ptr_config->nb_max));
    #elif _WIN32
    if (fscanf(ptr_file,"%f",&(ptr_config->nb_max))==0)
    {
        ptr_config->nb_max = INFINITY;
        fscanf(ptr_file,"%s",buffer);
    }
    #endif
    fscanf(ptr_file,"%d%d%d%d%d%f",(int *)&(ptr_config->first_way),(int *)&(ptr_config->turn_by_turn),(int *)&(ptr_config->use_distributor),(int *)&(ptr_config->number_after_comma),(int *)&(ptr_config->max),&(ptr_config->begin_score));

    strcpy(ptr_config->name,ptr_list_config->name_game_config[index_read]);

    closeFile(ptr_file);

    closeListGameConfig(ptr_list_config);

    return TRUE;
}
