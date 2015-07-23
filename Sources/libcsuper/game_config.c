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
    config->game_configs = (game_config *)myAlloc(nb_config*sizeof(game_config));
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
    free(ptr_list_config->game_configs);
    free(ptr_list_config);
}


/*!
 * \fn void addConfigListGameConfig(list_game_config *ptr_list_config,game_config config)
 *  Add a config to the config list
 * \param[in] *ptr_list_config a pointer on a list of game configuration
 * \param[in] config a game configuration
 */
void addConfigListGameConfig(list_game_config *ptr_list_config,game_config config)
{
    int i;
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
    {
        if (strcmp(ptr_list_config->game_configs[i].name,config.name) == 0)
        {
            printf(_("\nThe game configuration %s already exists.\n"),config.name);
            return;
        }
    }

    (ptr_list_config->nb_config) += 1;

    myRealloc((void **)&(ptr_list_config->name_game_config),ptr_list_config->nb_config*sizeof(char*));
    ptr_list_config->name_game_config[ptr_list_config->nb_config-1]=(char *)myAlloc(sizeof(char)*SIZE_MAX_FILE_NAME);
    strncpy(ptr_list_config->name_game_config[ptr_list_config->nb_config-1],config.name,SIZE_MAX_FILE_NAME);

    myRealloc((void **)&(ptr_list_config->game_configs),ptr_list_config->nb_config*sizeof(game_config));
    ptr_list_config->game_configs[ptr_list_config->nb_config-1] = config;
}


/*!
 * \fn void removeConfigListGameConfig(list_game_config *ptr_list_config,game_config config)
 *  Remove a config to the config list
 * \param[in] *ptr_list_config a pointer on a list of game configuration
 * \param[in] config a game configuration
 */
void removeConfigListGameConfig(list_game_config *ptr_list_config,game_config config)
{
    int i;
    bool config_found = false;

    for (i=0 ; i < ptr_list_config->nb_config ; i++)
    {
        if (config_found)
        {
            ptr_list_config->game_configs[i-1] = ptr_list_config->game_configs[i];
            strncpy(ptr_list_config->name_game_config[i-1],ptr_list_config->name_game_config[i],SIZE_MAX_FILE_NAME);
        }
        if (!config_found && strcmp(ptr_list_config->game_configs[i].name,config.name) == 0)
            config_found = true;
    }

    (ptr_list_config->nb_config) -= 1;

    free(ptr_list_config->name_game_config[ptr_list_config->nb_config]);
    myRealloc((void **)&(ptr_list_config->name_game_config),ptr_list_config->nb_config*sizeof(char*));
    myRealloc((void **)&(ptr_list_config->game_configs),ptr_list_config->nb_config*sizeof(game_config));
}

/*!
* \fn bool makeConfigListFile(char * home_path)
*  Create the files which contain the list of games configurations
* \param[in] *home_path the path to the home directory
* \return true if everything is OK, false otherwise
*/
bool makeConfigListFile(char * home_path)
{
    char folder[SIZE_MAX_FILE_NAME]="";
    char file_name[SIZE_MAX_FILE_NAME]="";
    //FILE *ptr_file;
    list_game_config *list;

    sprintf(folder,"%s%s",home_path,PREFERENCES_FOLDER_NAME);

    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(file_name,"%s/%s",folder,CONFIGURATION_XML_FILENAME);
    list = newListGameConfig(0);
    return writeXmlListGameConfig(file_name,list);
}

/*!
 * \fn list_game_config *readConfigListFile(char * home_path)
 *  Read the file which contain the list of game configuration
 * \param[in] *home_path the path to the home directory
 * \return a list_game_config
 */
list_game_config *readConfigListFile(char * home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    list_game_config *ptr_config;

    sprintf(file_name_config,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,CONFIGURATION_XML_FILENAME);

    ptr_config = readXmlListGameConfig(file_name_config);
    if (ptr_config->nb_config == 0)
        makeConfigListFile(home_path);
    return ptr_config;
}

/*!
 * \fn bool addConfigListFile(char *new_config_name,char *home_path)
 *  Depreciated, do nothing
 * \param[in] new_config_name the name of the new game configuration
 * \param[in] home_path the path to the home directory
 * \return true
 */
bool addConfigListFile(char *new_config_name,char *home_path)
{
    return true;
}

/*!
 * \fn bool removeConfigListFile(int index_delete, list_game_config, *ptr_list_config,char *home_path)
 *  Remove the game configuration.
 * \param[in] index_delete the index pf the file which will be deleted
 * \param[in] list_game_config the list of game configuration
 * \param[in] home_path the path to the home directory
 * \return true if everything is OK, false otherwise
 */
bool removeConfigListFile(int index_delete, list_game_config *ptr_list_config,char *home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";

    ptr_list_config=readConfigListFile(home_path);

    sprintf(file_name_config,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,CONFIGURATION_XML_FILENAME);
    removeConfigListGameConfig(ptr_list_config,ptr_list_config->game_configs[index_delete]);
    return writeXmlListGameConfig(file_name_config,ptr_list_config);
}

/*!
* \fn bool newConfigFile(game_config config,char * home_path)
*  Save a new game configuration file
* \param[in] config the gale configuration
* \param[in] home_path the path to the home directory
* \return true if everything is OK, false otherwise
*/
bool newConfigFile(game_config config,char * home_path)
{
    char file_name_config[SIZE_MAX_FILE_NAME]="";
    list_game_config *ptr_list_config=NULL;

    ptr_list_config=readConfigListFile(home_path);

    sprintf(file_name_config,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,CONFIGURATION_XML_FILENAME);
    addConfigListGameConfig(ptr_list_config,config);
    return writeXmlListGameConfig(file_name_config,ptr_list_config);
}

/*!
* \fn bool removeConfigFile(char *config_name,char * home_path)
*  Depreciated, do nothing
* \param[in] config_name the name of the game configuration which will be deleted
* \param[in] home_path the path to the home directory
* \return true
*/
bool removeConfigFile(char *config_name,char * home_path)
{
    return true;
}

/*!
 * \fn bool readConfigFile(int index_read, list_game_config *ptr_list_config, game_config *ptr_config,char * home_path)
 *  Read a game configuration file.
 * \param[in] index_read the index of the game configuration to be read
 * \param[in] ptr_list_config a pointer on the game configration list
 * \param[in] ptr_config a pointer on a game configuration
 * \param[in] home_path the path to the home directory
 * \return a list_game_config
 */
bool readConfigFile(int index_read, list_game_config *ptr_list_config, game_config *ptr_config,char * home_path)
{
    *ptr_config = ptr_list_config->game_configs[index_read];

    return true;
}

/*!
 * \fn bool exportConfigFile(char *home_path,char *file_name, int *id,int nb_id)
 *  Export all config file into a file.
 * \param[in] file_name the filename of the exported file.
 * \param[in] home_path the path to the home directory
 * \param[in] id the ids of the game configuration which will be exported
 * \param[in] nb_id the number of game configuration which will be exported
 * \return true if there is no problem, false otherwise
 */
bool exportConfigFile(char *home_path,char *file_name, int *id,int nb_id)
{
    bool res;

    list_game_config *ptr_list_config;
    ptr_list_config = readConfigListFile(home_path);
    res=writeXmlListGameConfigWithId(file_name,ptr_list_config,id,nb_id);
    closeListGameConfig(ptr_list_config);
    return res;
}

/*!
 * \fn bool importConfigFile(char *home_path,char *file_name, int *id,int nb_id)
 *  Import all config file from a file.
 * \param[in] file_name the filename of the imported file.
 * \param[in] home_path the path to the home directory
 * \param[in] id the id of the game configuration which will be imported
 * \param[in] nb_id the number of game configuration which will be imported
 * \return true if there is no problem, false otherwise
 */
bool importConfigFile(char *home_path,char *file_name, int *id,int nb_id)
{
    int i,j;
    int tmp;
    int nb_config;
    game_config config;
    FILE *ptr_file_import;
    char check_file[sizeof(STRING_CHECK_GAME_CONFIG)+1];
    #ifdef _WIN32
    char buffer[5];
    #endif // _WIN32
    list_game_config* ptr_list_game_config;

    // Test XML file
    ptr_list_game_config=readXmlListGameConfigWithId(file_name,id,nb_id);
    if(ptr_list_game_config->nb_config != 0)
    {
        for (i=0 ; i<ptr_list_game_config->nb_config ; i++)
        {
            newConfigFile(ptr_list_game_config->game_configs[i],home_path);
        }
        return true;
    }
    closeListGameConfig(ptr_list_game_config);

    ptr_file_import=openFile(file_name,"r");

    if(ptr_file_import == NULL)
    {
        printf(_("\nError while importing game configurations.\n"));
        return false;
    }

    /* Check if there is a good file */
    fgets(check_file,strlen(STRING_CHECK_GAME_CONFIG)+1,ptr_file_import);
    if (strcmp(STRING_CHECK_GAME_CONFIG,check_file) != 0)
    {
        printf(_("\nError: File not compatible.\n"));
        closeFile(ptr_file_import);
        return false;
    }

    fscanf(ptr_file_import,"%d",&nb_config);
    if(nb_id > nb_config)
    {
        printf(_("\nError while importing game configurations.\n"));
        return false;
    }

    for(i=0,j=0 ; i<nb_config && j<nb_id ; i++)
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

        if (i == id[j])
        {
            newConfigFile(config,home_path);
            j++;
        }
    }

    closeFile(ptr_file_import);

    return true;
}

/*!
 * \fn list_game_config *newListGameConfigFromImport(char *filename)
 *  Create a list_game_config with a import file
 * \param[in] filename the filename of the exported file.
 * \return a list_game_config
 */
list_game_config *newListGameConfigFromImport(char *filename)
{
    int i;
    int tmp;
    float buf;
    int nb_config;
    FILE *ptr_file_import;
    char check_file[sizeof(STRING_CHECK_GAME_CONFIG)+1];
    #ifdef _WIN32
    char buffer[5];
    #endif // _WIN32
    char config_name[SIZE_MAX_FILE_NAME];
    list_game_config* list_config;


    // Test XML file
    list_config = readXmlListGameConfig(filename);
    if (list_config->nb_config != 0)
        return list_config;

    ptr_file_import=openFile(filename,"r");

    if(ptr_file_import == NULL)
    {
        printf(_("\nError while importing game configurations.\n"));
        return NULL;
    }

    // Check if there is a good file
    fgets(check_file,strlen(STRING_CHECK_GAME_CONFIG)+1,ptr_file_import);
    if (strcmp(STRING_CHECK_GAME_CONFIG,check_file) != 0)
    {
        printf(_("\nError: File not compatible.\n"));
        closeFile(ptr_file_import);
        return NULL;
    }

    fscanf(ptr_file_import,"%d",&nb_config);

    list_config = newListGameConfig(nb_config);

    for(i=0 ; i<nb_config ; i++)
    {
        #ifdef __unix__
        fscanf(ptr_file_import,"%f",&buf);
        #elif _WIN32
        if (fscanf(ptr_file_import,"%f",&buf)==0)
            fscanf(ptr_file_import,"%s",buffer);
        #endif
        fscanf(ptr_file_import,"%f%s",&buf,config_name);
        fscanf(ptr_file_import,"%d",&tmp);
        fscanf(ptr_file_import,"%d",&tmp);
        fscanf(ptr_file_import,"%d",&tmp);
        fscanf(ptr_file_import,"%d",&tmp);
        fscanf(ptr_file_import,"%d",&tmp);

        strcpy(list_config->name_game_config[i],config_name);
    }

    closeFile(ptr_file_import);

    return list_config;
}


bool writeXmlListGameConfig(char *filename,list_game_config *ptr_list_config)
{
    bool res=true;
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr racine,tmp_node;
    int i;

    // Set root
    racine = xmlNewNode(NULL, BAD_CAST "csu_game_configuration");
    xmlDocSetRootElement(doc,racine);

    // Version
    addXmlFloatNode(racine,"version",GAME_CONFIG_FILE_XML_VERSION,1);

    // Number of game configuration
    addXmlIntNode(racine,"nb_game_config",ptr_list_config->nb_config);

    // Games configurations
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
    {
        tmp_node = xmlNewNode(NULL, BAD_CAST "game_configuration");
        addXmlFloatNode(tmp_node,"nb_max_min",ptr_list_config->game_configs[i].nb_max,ptr_list_config->game_configs[i].decimal_place);
        addXmlBoolNode(tmp_node,"max_winner",ptr_list_config->game_configs[i].first_way);
        addXmlBoolNode(tmp_node,"turn_by_turn",ptr_list_config->game_configs[i].turn_based);
        addXmlBoolNode(tmp_node,"use_distributor",ptr_list_config->game_configs[i].use_distributor);
        addXmlFloatNode(tmp_node,"decimal_place",ptr_list_config->game_configs[i].decimal_place,0);
        addXmlBoolNode(tmp_node,"use_maximum",ptr_list_config->game_configs[i].max);
        addXmlStringNode(tmp_node,"name",ptr_list_config->game_configs[i].name);
        addXmlFloatNode(tmp_node,"begin_score",ptr_list_config->game_configs[i].begin_score,ptr_list_config->game_configs[i].decimal_place);
        xmlAddChild(racine, tmp_node);
    }


    if(xmlSaveFormatFileEnc(filename,doc,"UTF-8",1) == -1)
        res = false;
    xmlFreeDoc(doc);

    return res;
}


list_game_config *readXmlListGameConfig(char *filename)
{
    list_game_config* list_config;
    xmlDocPtr doc;
    xmlNodePtr root,tmp_node;
    int i,nb_game_config;
    float version;

    doc = xmlParseFile(filename);
    if (doc == NULL)
        return newListGameConfig(0);

    // Check root
    root = xmlDocGetRootElement(doc);
    if (!xmlStrEqual(root->name,xmlCharStrdup("csu_game_configuration")))
    {
        printf(_("Not a csu game configuration file\n"));
        xmlFreeDoc(doc);
    }

    // Version
    tmp_node = xmlFirstElementChild(root);
    version = convertStringFloat((char *)xmlNodeGetContent(tmp_node));
    if (version > GAME_CONFIG_FILE_XML_VERSION)
    {
        printf(_("This version of Csuper only support game configuration file version of %.1f.\n")
               ,GAME_CONFIG_FILE_XML_VERSION);
        xmlFreeDoc(doc);
        return newListGameConfig(0);
    }

    // Number of game configuration
    tmp_node = xmlNextElementSibling(tmp_node);
    nb_game_config = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    list_config = newListGameConfig(nb_game_config);

    // Game configuration
    for (i=0 ; i< nb_game_config ; i++)
    {
        // Nb max
        tmp_node=xmlFirstElementChild(xmlNextElementSibling(tmp_node));
        list_config->game_configs[i].nb_max = convertStringFloat((char *)xmlNodeGetContent(tmp_node));

        // Nb max min
        tmp_node = xmlNextElementSibling(tmp_node);
        if (convertStringBool((char *)xmlNodeGetContent(tmp_node)))
            list_config->game_configs[i].first_way=1;
        else
            list_config->game_configs[i].first_way=-1;

        // Turn by turn
        tmp_node = xmlNextElementSibling(tmp_node);
        list_config->game_configs[i].turn_based=convertStringBool((char *)xmlNodeGetContent(tmp_node));

        // Use distributor
        tmp_node = xmlNextElementSibling(tmp_node);
        list_config->game_configs[i].use_distributor=convertStringBool((char *)xmlNodeGetContent(tmp_node));

        // Decimal place
        tmp_node = xmlNextElementSibling(tmp_node);
        list_config->game_configs[i].decimal_place = convertStringInt((char *)xmlNodeGetContent(tmp_node));

        // Use maximum
        tmp_node = xmlNextElementSibling(tmp_node);
        list_config->game_configs[i].max=convertStringBool((char *)xmlNodeGetContent(tmp_node));

        // Name
        tmp_node = xmlNextElementSibling(tmp_node);
        strncpy(list_config->game_configs[i].name,(char *)xmlNodeGetContent(tmp_node),SIZE_MAX_NAME+1);
        strncpy(list_config->name_game_config[i],(char *)xmlNodeGetContent(tmp_node),SIZE_MAX_NAME+1);

        // Begin score
        tmp_node = xmlNextElementSibling(tmp_node);
        list_config->game_configs[i].begin_score=convertStringFloat((char *)xmlNodeGetContent(tmp_node));

        tmp_node = tmp_node->parent;
    }

    xmlFreeDoc(doc);

    return list_config;
}

bool writeXmlListGameConfigWithId(char *filename,list_game_config *ptr_list_config,int *id,int nb_id)
{
    list_game_config* reduce_list_config = newListGameConfig(nb_id);
    int i,j;
    bool res;

    for(i=0,j=0 ; i<ptr_list_config->nb_config && j<nb_id ; i++)
    {
        if (i == id[j])
        {
            strcpy(reduce_list_config->name_game_config[j],ptr_list_config->name_game_config[i]);
            reduce_list_config->game_configs[j]=ptr_list_config->game_configs[i];
            j++;
        }
    }

    res = writeXmlListGameConfig(filename,reduce_list_config);

    closeListGameConfig(reduce_list_config);
    return res;
}


list_game_config *readXmlListGameConfigWithId(char *filename,int *id,int nb_id)
{
    list_game_config* full_list_config,*list_config;
    int i,j;

    full_list_config = readXmlListGameConfig(filename);
    if (full_list_config->nb_config == 0)
        return full_list_config;
    list_config = newListGameConfig(nb_id);

    for(i=0,j=0 ; i<full_list_config->nb_config && j<nb_id ; i++)
    {
        if (i == id[j])
        {
            strcpy(list_config->name_game_config[j],full_list_config->name_game_config[i]);
            list_config->game_configs[j]=full_list_config->game_configs[i];
            j++;
        }
    }

    closeListGameConfig(full_list_config);

    return list_config;
}
