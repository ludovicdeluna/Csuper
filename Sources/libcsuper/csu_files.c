/*!
 * \file    csu_files.c
 * \brief   Files management
 * \author  Remi BERTHO
 * \date    31/08/14
 * \version 4.2.0
 */

/*
* csu_files.c
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

#include "csu_files.h"



/*!
 * \fn FILE *openFileCsuExtension(char file_name[], char mode[])
 *  Open a file with his name and with a specific mode and add the file extension if necessary.
 * \param[in] file_name[] the filename
 * \param[in] mode[] the mode
 * \return a pointer on the open file, NULL if there is a problem
 */
FILE *openFileCsuExtension(char file_name[], char mode[])
{
    FILE *ptr_file=openFile(file_name,mode);
    if (ptr_file != NULL)
        return ptr_file;

    addFileCsuExtension(file_name);

    return openFile(file_name,mode);
}


/*!
 * \fn csuStruct *readCsuFile(char *file_name)
 *  Read the file with the name file_name and copy the result in a new csu structure.
 * \param[in] file_name[] the filename
 * \return a pointer on the new csu structure, NULL if there is a problem
 */
csuStruct *readCsuFile(char *file_name)
{
    csuStruct *ptr_csu_struct=readCsuXmlFile(file_name);
    if (ptr_csu_struct != NULL)
        return ptr_csu_struct;

    int i;
    char *player_name_temp;
    FILE *ptr_file;
    char check_file[sizeof(STRING_CHECK_CSU_FILE)];
    int file_size;
    int check_file_size=0;

    libcsuper_initialize();

    ptr_file=openFileCsuExtension(file_name,"rb");
    if (ptr_file == NULL)
    {
        printf(_("\nError: The file could not be read.\n"));
        return ptr_csu_struct;
    }

    fseek(ptr_file,0,SEEK_SET);
    file_size=readFileSize(ptr_file);

    /*Check if it's a csu file*/
    check_file_size+=fread(check_file,sizeof(char),sizeof(STRING_CHECK_CSU_FILE),ptr_file);
    if (strcmp(STRING_CHECK_CSU_FILE,check_file) != 0)
    {
        printf(_("\nError: File not compatible.\n"));
        closeFile(ptr_file);
        return ptr_csu_struct;
    }

    ptr_csu_struct=(csuStruct *)myAlloc(sizeof(csuStruct));

    /*Check the version of the file*/
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->version),sizeof(float),1,ptr_file));
    if (ptr_csu_struct->version + 0.01 < VERSION && ptr_csu_struct->version - 0.01 > VERSION)
    {
        printf(_("\nError: the file's version is the %1.1f whereas the software only supports files "
                 "with versions higher than the %1.1f.\n"),ptr_csu_struct->version,VERSION);
        closeFile(ptr_file);
        free(ptr_csu_struct);
        return NULL;
    }

    /*Read different data*/
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->size_max_name),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->day),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->month),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->year),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->nb_player),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(game_config)*fread(&(ptr_csu_struct->config),sizeof(game_config),1,ptr_file));

    /*Read the players names*/
    ptr_csu_struct->player_names=(char **)myAlloc(ptr_csu_struct->nb_player*sizeof(char*));
    player_name_temp=(char *)myAlloc(sizeof(char)*ptr_csu_struct->size_max_name);
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        ptr_csu_struct->player_names[i]=(char *)myAlloc(ptr_csu_struct->size_max_name*sizeof(char));
        check_file_size+=fread(player_name_temp,sizeof(char),ptr_csu_struct->size_max_name,ptr_file);
        strcpy(ptr_csu_struct->player_names[i],player_name_temp);
    }
    free(player_name_temp);

    /*Read the total points*/
    ptr_csu_struct->total_points=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    check_file_size+=(sizeof(float)*fread(ptr_csu_struct->total_points,sizeof(float),ptr_csu_struct->nb_player,ptr_file));

    /*Read the rank*/
    ptr_csu_struct->rank=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    check_file_size+=(sizeof(float)*fread(ptr_csu_struct->rank,sizeof(float),ptr_csu_struct->nb_player,ptr_file));

    /*Read the number of turn*/
    ptr_csu_struct->nb_turn=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    check_file_size+=(sizeof(float)*fread(ptr_csu_struct->nb_turn,sizeof(float),ptr_csu_struct->nb_player,ptr_file));

    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->distributor),sizeof(float),1,ptr_file));

    /*Read the points*/
    ptr_csu_struct->point=(float **)myAlloc(ptr_csu_struct->nb_player*sizeof(float*));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        ptr_csu_struct->point[i]=(float *)myAlloc(ptr_csu_struct->nb_turn[i]*sizeof(float));
        check_file_size+=(sizeof(float)*fread(ptr_csu_struct->point[i],sizeof(float),ptr_csu_struct->nb_turn[i],ptr_file));
    }


    closeFile(ptr_file);

    /*Check the size of the file*/
    if (file_size != check_file_size)
    {
        printf(_("\nError: corrupted file.\n"));
        return NULL;
    }

    return ptr_csu_struct;
}

/*!
 * \fn bool writeCsuFile(char *file_name, csuStruct *ptr_csu_struct)
 *  Write a csu file
 * \param[in] *file_name the filename
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return true if everything is OK, false otherwise
 */
bool writeCsuFile(char *file_name, csuStruct *ptr_csu_struct)
{
    return writeCsuXmlFile(file_name,ptr_csu_struct);
    /*int i;
    FILE *ptr_file;

    libcsuper_initialize();

    ptr_file=openFileCsuExtension(file_name,"w+");

    if (ptr_file == NULL)
    {
        printf(_("\nError while writing the file.\n"));
        return false;
    }

    fseek(ptr_file,0,SEEK_SET);

    fwrite(STRING_CHECK_CSU_FILE,sizeof(char),sizeof(STRING_CHECK_CSU_FILE),ptr_file);
    fwrite(&(ptr_csu_struct->version),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->size_max_name),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->day),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->month),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->year),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->nb_player),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->config),sizeof(game_config),1,ptr_file);

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fwrite(ptr_csu_struct->player_names[i],sizeof(char),ptr_csu_struct->size_max_name,ptr_file);

    fwrite(ptr_csu_struct->total_points,sizeof(float),ptr_csu_struct->nb_player,ptr_file);
    fwrite(ptr_csu_struct->rank,sizeof(float),ptr_csu_struct->nb_player,ptr_file);
    fwrite(ptr_csu_struct->nb_turn,sizeof(float),ptr_csu_struct->nb_player,ptr_file);
    fwrite(&(ptr_csu_struct->distributor),sizeof(float),1,ptr_file);

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fwrite(ptr_csu_struct->point[i],sizeof(float),ptr_csu_struct->nb_turn[i],ptr_file);

    closeFile(ptr_file);

    return true;*/
}

/*!
 * \fn bool writeFileNewTurn(char *file_name, csuStruct *ptr_csu_struct)
 *  Update the file with the new scores
 * \param[in] *file_name the filename
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return true if everything is OK, false otherwise
 */
bool writeFileNewTurn(char *file_name, csuStruct *ptr_csu_struct)
{
    char filename_2[SIZE_MAX_FILE_NAME+4];

    sprintf(filename_2,"%s_tmp",file_name);


    if (writeCsuFile(filename_2,ptr_csu_struct))
    {
        if(deleteFile(file_name))
        {
            if(renameFile(filename_2,file_name))
                return true;
            else
                deleteFile(filename_2);
        }
        else
            deleteFile(filename_2);
    }

    return false;
}


/*!
 * \fn bool writeCsuXmlFile(char *filename, csuStruct *ptr_csu_struct)
 *  Write a csu file in the new XML format
 * \param[in] filename the filename
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \return true if everything is OK, false otherwise
 */
bool writeCsuXmlFile(char *filename, csuStruct *ptr_csu_struct)
{
    bool res=true;
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr racine,tmp_node1,tmp_node2;
    int i,j;


    // Set root
    racine = xmlNewNode(NULL, BAD_CAST "csu");
    xmlDocSetRootElement(doc,racine);

    // Version
    addXmlFloatNode(racine,"version",ptr_csu_struct->version,1);

    //Size max name
    addXmlFloatNode(racine,"size_max_name",ptr_csu_struct->size_max_name,0);


    //Date
    tmp_node1 = xmlNewNode(NULL, BAD_CAST "date");
    addXmlFloatNode(tmp_node1,"year",ptr_csu_struct->year,0);
    addXmlFloatNode(tmp_node1,"month",ptr_csu_struct->month,0);
    addXmlFloatNode(tmp_node1,"day",ptr_csu_struct->day,0);
    xmlAddChild(racine, tmp_node1);


    // Nb player + Distributor
    addXmlFloatNode(racine,"nb_player",ptr_csu_struct->nb_player,0);
    addXmlFloatNode(racine,"distributor",ptr_csu_struct->distributor,0);

    //Game configuration
    tmp_node1 = xmlNewNode(NULL, BAD_CAST "game_configuration");
    addXmlFloatNode(tmp_node1,"nb_max_min",ptr_csu_struct->config.nb_max,ptr_csu_struct->config.decimal_place);
    addXmlBoolNode(tmp_node1,"max_winner",ptr_csu_struct->config.first_way);
    addXmlBoolNode(tmp_node1,"turn_by_turn",ptr_csu_struct->config.turn_based);
    addXmlBoolNode(tmp_node1,"use_distributor",ptr_csu_struct->config.use_distributor);
    addXmlFloatNode(tmp_node1,"decimal_place",ptr_csu_struct->config.decimal_place,0);
    addXmlBoolNode(tmp_node1,"use_maximum",ptr_csu_struct->config.max);
    addXmlStringNode(tmp_node1,"name",ptr_csu_struct->config.name);
    addXmlFloatNode(tmp_node1,"begin_score",ptr_csu_struct->config.begin_score,ptr_csu_struct->config.decimal_place);
    xmlAddChild(racine, tmp_node1);

    // Players
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        tmp_node1 = xmlNewNode(NULL, BAD_CAST "player");
        addXmlStringNode(tmp_node1,"player_name",ptr_csu_struct->player_names[i]);
        addXmlFloatNode(tmp_node1,"total_points",ptr_csu_struct->total_points[i],ptr_csu_struct->config.decimal_place);
        addXmlFloatNode(tmp_node1,"rank",ptr_csu_struct->rank[i],0);
        addXmlFloatNode(tmp_node1,"number_of_turn",ptr_csu_struct->nb_turn[i],0);
        tmp_node2 = xmlNewNode(NULL, BAD_CAST "points");
        for (j=0 ; j < ptr_csu_struct->nb_turn[i] ; j++)
            addXmlFloatNodeIntProp(tmp_node2,"turn",ptr_csu_struct->point[i][j],ptr_csu_struct->config.decimal_place,"num",j);
        xmlAddChild(tmp_node1, tmp_node2);
        xmlAddChild(racine, tmp_node1);
    }


    if(xmlSaveFormatFileEnc(filename,doc,"UTF-8",1) == -1)
        res = false;
    xmlFreeDoc(doc);

    return res;
}


/*!
 * \fn void addXmlFloatNode(xmlNodePtr parent, char *name, float value, int decimal_place)
 *  Add a XML node to the parent with a float value and a number of decimal places
 * \param[in] parent the parent node
 * \param[in] name the name of the new node
 * \param[in] value the value of the new node
 * \param[in] decimal_place the number of decimal place
 */
void addXmlFloatNode(xmlNodePtr parent, char *name, float value, int decimal_place)
{
    xmlNodePtr tmp_node;
    char char_buffer[40]="";

    tmp_node = xmlNewNode(NULL, BAD_CAST name);
    convertFloatString(char_buffer,value,decimal_place);
    xmlNodeSetContent(tmp_node,BAD_CAST char_buffer);
    xmlAddChild(parent, tmp_node);
}

/*!
 * \fn void addXmlBoolNode(xmlNodePtr parent, char *name, int value)
 *  Add a XML node to the parent with a Boolean value
 * \param[in] parent the parent node
 * \param[in] name the name of the new node
 * \param[in] value the value of the new node
 */
void addXmlBoolNode(xmlNodePtr parent, char *name, int value)
{
    char *yes="yes";
    char *no="no";
    xmlNodePtr tmp_node;

    tmp_node = xmlNewNode(NULL, BAD_CAST name);
    xmlNodeSetContent(tmp_node,BAD_CAST integerToYesNo(value,yes,no));
    xmlAddChild(parent, tmp_node);
}


/*!
 * \fn void addXmlIntNode(xmlNodePtr parent, char *name, int value)
 *  Add a XML node to the parent with a integer value
 * \param[in] parent the parent node
 * \param[in] name the name of the new node
 * \param[in] value the value of the new node
 */
void addXmlIntNode(xmlNodePtr parent, char *name, int value)
{
    xmlNodePtr tmp_node;
    char char_buffer[40]="";
    sprintf(char_buffer,"%d",value);

    tmp_node = xmlNewNode(NULL, BAD_CAST name);
    xmlNodeSetContent(tmp_node,BAD_CAST char_buffer);
    xmlAddChild(parent, tmp_node);
}


/*!
 * \fn void addXmlStringNode(xmlNodePtr parent, char *name, char *value)
 *  Add a XML node to the parent with a string value
 * \param[in] parent the parent node
 * \param[in] name the name of the new node
 * \param[in] value the value of the new node
 */
void addXmlStringNode(xmlNodePtr parent, char *name, char *value)
{
    xmlNodePtr tmp_node;

    tmp_node = xmlNewNode(NULL, BAD_CAST name);
    xmlNodeSetContent(tmp_node,BAD_CAST value);
    xmlAddChild(parent, tmp_node);
}


/*!
 * \fn void addXmlFloatNodeIntProp(xmlNodePtr parent, char *name, float value, int decimal_place,char *prop_name, int prop_value)
 *  Add a XML node to the parent with a float value and a number of decimal places and a integer property
 * \param[in] parent the parent node
 * \param[in] name the name of the new node
 * \param[in] value the value of the new node
 * \param[in] decimal_place the number of decimal place
 * \param[in] prop_name the property's name
 * \param[in] prop_value the property's value
 */
void addXmlFloatNodeIntProp(xmlNodePtr parent, char *name, float value, int decimal_place,char *prop_name, int prop_value)
{
    xmlNodePtr tmp_node;
    char char_buffer[40]="";

    tmp_node = xmlNewNode(NULL, BAD_CAST name);
    convertFloatString(char_buffer,value,decimal_place);
    xmlNodeSetContent(tmp_node,BAD_CAST char_buffer);
    sprintf(char_buffer,"%d",prop_value);
    xmlSetProp(tmp_node, BAD_CAST prop_name, BAD_CAST char_buffer);
    xmlAddChild(parent, tmp_node);
}


/*!
 * \fn csuStruct *readCsuXmlFile(char *filename)
 *  Read the xml file with the name file_name and copy the result in a new csu structure.
 * \param[in] filename the filename
 * \return a pointer on the new csu structure, NULL if there is a problem
 */
csuStruct *readCsuXmlFile(char *filename)
{
    xmlDocPtr doc;
    xmlNodePtr root,tmp_node;
    csuStruct *ptr_csu_struct=NULL;
    int i,j;
    char new_filename[SIZE_MAX_FILE_NAME];

    strncpy(new_filename,filename,SIZE_MAX_FILE_NAME)
,

    // Parse file
    doc = xmlParseFile(new_filename);
    if (doc == NULL)
    {
        addFileCsuExtension(new_filename);
        doc = xmlParseFile(new_filename);
        if (doc == NULL)
        {
            printf(_("Invalid XML Document\n"));
            return NULL;
        }
    }

    // Check root
    root = xmlDocGetRootElement(doc);
    if (!xmlStrEqual(root->name,xmlCharStrdup("csu")))
    {
        printf(_("Document non csu\n"));
        xmlFreeDoc(doc);
        return NULL;
    }

    ptr_csu_struct=(csuStruct *)myAlloc(sizeof(csuStruct));

    // Version
    tmp_node = xmlFirstElementChild(root);
    ptr_csu_struct->version = convertStringFloat((char *)xmlNodeGetContent(tmp_node));
    if (ptr_csu_struct->version + 0.01 < VERSION && ptr_csu_struct->version - 0.01 > VERSION)
    {
        printf(_("\nError: the file's version is the %1.1f whereas the software only supports files "
                 "with versions %1.1f.\n"),ptr_csu_struct->version,VERSION);
        free(ptr_csu_struct);
        return NULL;
    }

    //size max name
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->size_max_name = convertStringFloat((char *)xmlNodeGetContent(tmp_node));

    // Date
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node));
    ptr_csu_struct->year = convertStringFloat((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->month = convertStringFloat((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->day = convertStringFloat((char *)xmlNodeGetContent(tmp_node));

    // Number of player + distributor
    tmp_node = xmlNextElementSibling(tmp_node->parent);
    ptr_csu_struct->nb_player = convertStringFloat((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->distributor = convertStringFloat((char *)xmlNodeGetContent(tmp_node));


    // Game configuration

    // Nb max
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node));
    ptr_csu_struct->config.nb_max = convertStringFloat((char *)xmlNodeGetContent(tmp_node));

    // Nb max min
    tmp_node = xmlNextElementSibling(tmp_node);
    if (convertStringBool((char *)xmlNodeGetContent(tmp_node)))
        ptr_csu_struct->config.first_way=1;
    else
        ptr_csu_struct->config.first_way=-1;

    // Turn by turn
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->config.turn_based=convertStringBool((char *)xmlNodeGetContent(tmp_node));

    // Use distributor
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->config.use_distributor=convertStringBool((char *)xmlNodeGetContent(tmp_node));

    // Decimal place
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->config.decimal_place = convertStringInt((char *)xmlNodeGetContent(tmp_node));

    // Use maximum
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->config.max=convertStringBool((char *)xmlNodeGetContent(tmp_node));

    // Name
    tmp_node = xmlNextElementSibling(tmp_node);
    strncpy(ptr_csu_struct->config.name,(char *)xmlNodeGetContent(tmp_node),SIZE_MAX_NAME);

    // Begin score
    tmp_node = xmlNextElementSibling(tmp_node);
    ptr_csu_struct->config.begin_score=convertStringFloat((char *)xmlNodeGetContent(tmp_node));


    //Memory allocation
    ptr_csu_struct->player_names=(char **)myAlloc(ptr_csu_struct->nb_player*sizeof(char*));
    ptr_csu_struct->total_points=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    ptr_csu_struct->rank=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    ptr_csu_struct->nb_turn=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    ptr_csu_struct->point=(float **)myAlloc(ptr_csu_struct->nb_player*sizeof(float*));


    // Players
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node->parent));
        // Players name
        ptr_csu_struct->player_names[i]=(char *)myAlloc(ptr_csu_struct->size_max_name*sizeof(char));
        strncpy(ptr_csu_struct->player_names[i],(char *)xmlNodeGetContent(tmp_node),ptr_csu_struct->size_max_name);

        // Totals points
        tmp_node = xmlNextElementSibling(tmp_node);
        ptr_csu_struct->total_points[i] = convertStringFloat((char *)xmlNodeGetContent(tmp_node));

        // Rank
        tmp_node = xmlNextElementSibling(tmp_node);
        ptr_csu_struct->rank[i] = convertStringFloat((char *)xmlNodeGetContent(tmp_node));

        // Number of turn
        tmp_node = xmlNextElementSibling(tmp_node);
        ptr_csu_struct->nb_turn[i] = convertStringFloat((char *)xmlNodeGetContent(tmp_node));

        // Points
        ptr_csu_struct->point[i]=(float *)myAlloc(ptr_csu_struct->nb_turn[i]*sizeof(float));
        xmlNodePtr tmp_node_2 = xmlFirstElementChild(xmlNextElementSibling(tmp_node));
        for (j=0 ; j<ptr_csu_struct->nb_turn[i] ; j++)
        {
            ptr_csu_struct->point[i][j] = convertStringFloat((char *)xmlNodeGetContent(tmp_node_2));
            tmp_node_2 = xmlNextElementSibling(tmp_node_2);
        }
    }

    xmlFreeDoc(doc);

    return ptr_csu_struct;
}
