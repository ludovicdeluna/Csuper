/*!
 * \file    game_config.c
 * \brief   Game configuration
 * \author  Remi BERTHO
 * \date    29/04/14
 * \version 2.4.0
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
 * \param[in] nb_config the number of game configuration
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
 * \param[in] *ptr_list_config a pointer on a list of game configuration
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
 * \param[in] *home_path the path to the home directory
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int makeConfigListFile(char * home_path)
{
    char folder[SIZE_MAX_FILE_NAME]="";
    char file_name[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;

    sprintf(folder,"%s%s",home_path,PREFERENCES_FOLDER_NAME);

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
        return MY_FALSE;

    fprintf(ptr_file,"%d",0);

    closeFile(ptr_file);

    return MY_TRUE;
}

/*!
 * \fn list_game_config *readConfigListFile(char * home_path)
 *  Read the file which contain the list of game configuration.
 * \param[in] *home_path the path to the home directory
 * \return a list_game_config
 */
list_game_config *readConfigListFile(char * home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;
    list_game_config *ptr_config;
    int nb_config;
    int i;

    sprintf(file_name_config,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,CONFIGURATION_FILE_NAME);

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
 * \param[in] new_config_name the name of the new game configuration
 * \param[in] home_path the path to the home directory
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int addConfigListFile(char *new_config_name,char *home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;
    int i;
    list_game_config *ptr_list_config =readConfigListFile(home_path);

    for (i=0 ; i< ptr_list_config->nb_config ; i++)
    {
        if (strcmp(ptr_list_config->name_game_config[i],new_config_name) == 0)
        {
            printf(_("\nThe game configuration %s already exist.\n"),new_config_name);
            return MY_FALSE;
        }
    }


    sprintf(file_name_config,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,CONFIGURATION_FILE_NAME);

    ptr_file=openFile(file_name_config,"w");

    if(ptr_file == NULL)
        return MY_FALSE;

    fprintf(ptr_file,"%d\n",ptr_list_config->nb_config+1);

    for (i=0 ; i< ptr_list_config->nb_config ; i++)
        fprintf(ptr_file,"%s\n",ptr_list_config->name_game_config[i]);

    closeListGameConfig(ptr_list_config);


    fprintf(ptr_file,"%s",new_config_name);
    closeFile(ptr_file);
    return MY_TRUE;
}

/*!
 * \fn int removeConfigListFile(int index_delete, list_game_config, *ptr_list_config,char *home_path)
 *  Remove a game configuration in the file which contain the list of game configuration and remove the game configuration.
 * \param[in] index_delete the index pf the file which will be deleted
 * \param[in] list_game_config the list of game configuration
 * \param[in] home_path the path to the home directory
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int removeConfigListFile(int index_delete, list_game_config *ptr_list_config,char *home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;
    int i;

    ptr_list_config=readConfigListFile(home_path);

    sprintf(file_name_config,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,CONFIGURATION_FILE_NAME);

    ptr_file=openFile(file_name_config,"w+");

    if(ptr_file == NULL)
        return MY_FALSE;

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

    return MY_TRUE;
}

 /*!
 * \fn int newConfigFile(game_config config,char * home_path)
 *  Create a game configuration file and put it into the game configuration file list.
 * \param[in] config the gale configuration
 * \param[in] home_path the path to the home directory
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int newConfigFile(game_config config,char * home_path)
{
    char folder[SIZE_MAX_FILE_NAME]="";
    char file_name[SIZE_MAX_FILE_NAME]="";
    FILE *ptr_file;

    if(addConfigListFile(config.name,home_path) == MY_FALSE)
        return MY_FALSE;

    sprintf(folder,"%s%s",home_path,PREFERENCES_FOLDER_NAME);

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
        return MY_FALSE;

    #ifdef __unix__
    fprintf(ptr_file,"%f ",config.nb_max);
    #elif _WIN32
    if (config.nb_max == INFINITY)
        fprintf(ptr_file,"inf ");
    else
        fprintf(ptr_file,"%f ",config.nb_max);
    #endif

    fprintf(ptr_file,"%f %d %d %d %d %d",config.begin_score,config.decimal_place,config.first_way,config.max,config.turn_based,config.use_distributor);

    closeFile(ptr_file);

    return MY_TRUE;
}

 /*!
 * \fn int removeConfigFile(char *config_name,char * home_path)
 *  Delete a game configuration.
 * \param[in] config_name the name of the game configuration which will be deleted
 * \param[in] home_path the path to the home directory
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int removeConfigFile(char *config_name,char * home_path)
{
    char folder[SIZE_MAX_FILE_NAME]="";
    char file_name[SIZE_MAX_FILE_NAME]="";

    libcsuper_initialize();

    sprintf(folder,"%s%s",home_path,PREFERENCES_FOLDER_NAME);

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
        return MY_FALSE;
    }
    else
    {
        printf(_("\nThe file %s was well deleted.\n"),file_name);
        return MY_TRUE;
    }

    return MY_TRUE;
}

/*!
 * \fn int readConfigFile(int index_read, list_game_config *ptr_list_config, game_config *ptr_config,char * home_path)
 *  Read a game configuration file.
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
    int tmp;
    #ifdef _WIN32
    char buffer[5];
    #endif // _WIN32

    sprintf(file_name_config,"%s%s/%s/%s",home_path,PREFERENCES_FOLDER_NAME,CONFIGURATION_FOLDER_NAME,ptr_list_config->name_game_config[index_read]);

    ptr_file=openFile(file_name_config,"r");

    if(ptr_file == NULL)
        return MY_FALSE;

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
    fscanf(ptr_file,"%f",&(ptr_config->begin_score));
    fscanf(ptr_file,"%d",&tmp);
    ptr_config->decimal_place=tmp;
    fscanf(ptr_file,"%d",&tmp);
    ptr_config->first_way=tmp;
    fscanf(ptr_file,"%d",&tmp);
    ptr_config->max=tmp;
    fscanf(ptr_file,"%d",&tmp);
    ptr_config->turn_based=tmp;
    fscanf(ptr_file,"%d",&tmp);
    ptr_config->use_distributor=tmp;

    strcpy(ptr_config->name,ptr_list_config->name_game_config[index_read]);

    closeFile(ptr_file);

    return MY_TRUE;
}

/*!
 * \fn int exportConfigFile(char *home_path,char *file_name)
 *  Export all config file into a file.
 * \param[in] file_name the filename of the exported file.
 * \param[in] home_path the path to the home directory
 * \return a list_game_config
 */
int exportConfigFile(char *home_path,char *file_name)
{
    int i;
    list_game_config *ptr_list_config;
    game_config config;
    FILE *ptr_file_export;

    ptr_list_config = readConfigListFile(home_path);

    ptr_file_export=openFile(file_name,"w");

    if(ptr_file_export == NULL)
    {
        printf(_("\nError while exporting game configurations.\n"));
        return MY_FALSE;
    }

    fprintf(ptr_file_export,"%s\n%d\n",STRING_CHECK_GAME_CONFIG,ptr_list_config->nb_config);

    for(i=0 ; i<ptr_list_config->nb_config ; i++)
    {
        readConfigFile(i,ptr_list_config,&config,home_path);
        #ifdef __unix__
        fprintf(ptr_file_export,"%f ",config.nb_max);
        #elif _WIN32
        if (config.nb_max == INFINITY)
            fprintf(ptr_file_export,"inf ");
        else
            fprintf(ptr_file_export,"%f ",config.nb_max);
        #endif
        fprintf(ptr_file_export,"%f %s %d %d %d %d %d\n",config.begin_score,config.name,config.decimal_place,config.first_way,config.max,config.turn_based,config.use_distributor);
    }

    closeFile(ptr_file_export);
    closeListGameConfig(ptr_list_config);

    return MY_TRUE;
}

/*!
 * \fn int importConfigFile(char *home_path,char *file_name)
 *  Import all config file from a file.
 * \param[in] file_name the filename of the exported file.
 * \param[in] home_path the path to the home directory
 * \return a list_game_config
 */
int importConfigFile(char *home_path,char *file_name)
{
    int i;
    int tmp;
    int nb_config;
    game_config config;
    FILE *ptr_file_import;
    char check_file[sizeof(STRING_CHECK_GAME_CONFIG)+1];
    #ifdef _WIN32
    char buffer[5];
    #endif // _WIN32

    ptr_file_import=openFile(file_name,"r");

    if(ptr_file_import == NULL)
    {
        printf(_("\nError while importing game configurations.\n"));
        return MY_FALSE;
    }

    /* Check if there is a good file */
    fgets(check_file,strlen(STRING_CHECK_GAME_CONFIG)+1,ptr_file_import);
    if (strcmp(STRING_CHECK_GAME_CONFIG,check_file) != 0)
    {
        printf(_("\nError: File not compatible.\n"));
        closeFile(ptr_file_import);
        return MY_FALSE;
    }

    fscanf(ptr_file_import,"%d",&nb_config);

    for(i=0 ; i<nb_config ; i++)
    {
        #ifdef __unix__
        fscanf(ptr_file_import,"%f",&(config.nb_max));
        #elif _WIN32
        if (fscanf(ptr_file_import,"%f",&(config.nb_max))==0)
        {
            config.nb_max = INFINITY;
            fscanf(ptr_file_import,"%s",buffer);
        }
        #endif
        fscanf(ptr_file_import,"%f%s",&(config.begin_score),config.name);
        fscanf(ptr_file_import,"%d",&tmp);
        config.decimal_place=tmp;
        fscanf(ptr_file_import,"%d",&tmp);
        config.first_way=tmp;
        fscanf(ptr_file_import,"%d",&tmp);
        config.max=tmp;
        fscanf(ptr_file_import,"%d",&tmp);
        config.turn_based=tmp;
        fscanf(ptr_file_import,"%d",&tmp);
        config.use_distributor=tmp;

        newConfigFile(config,home_path);
    }

    closeFile(ptr_file_import);

    return MY_TRUE;
}
