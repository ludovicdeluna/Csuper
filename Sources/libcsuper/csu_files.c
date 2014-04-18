/*!
 * \file    csu_files.c
 * \brief   Files management
 * \author  Remi BERTHO
 * \date    16/04/14
 * \version 2.2.0
 */

 /*
 * csu_files.c
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
    csuStruct *ptr_csu_struct=NULL;
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
        printf(_("\nError the file's version is the %1.1f while the software only support files with versions"
               " higher than the %1.1f.\n"),ptr_csu_struct->version,VERSION);
        closeFile(ptr_file);
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
    ptr_csu_struct->point=(float **)malloc(ptr_csu_struct->nb_player*sizeof(float*));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        ptr_csu_struct->point[i]=(float *)myAlloc(ptr_csu_struct->nb_turn[i]*sizeof(float));
        check_file_size+=(sizeof(float)*fread(ptr_csu_struct->point[i],sizeof(float),ptr_csu_struct->nb_turn[i],ptr_file));
    }


    closeFile(ptr_file);

    /*Check the size of the file*/
    if (file_size != check_file_size)
    {
        printf(_("\nError : corrupted file.\n"));
        return NULL;
    }

    return ptr_csu_struct;
}

/*!
 * \fn int writeCsuFile(char *file_name, csuStruct *ptr_csu_struct)
 *  Write a csu file
 * \param[in] *file_name the filename
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return TRUE if everything is OK, FALSE otherwise
 */
int writeCsuFile(char *file_name, csuStruct *ptr_csu_struct)
{
    int i;
    FILE *ptr_file;

    libcsuper_initialize();

    ptr_file=openFileCsuExtension(file_name,"w+");

    if (ptr_file == NULL)
    {
        printf(_("\nError while writing file.\n"));
        return FALSE;
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

    return TRUE;
}

/*!
 * \fn void writeFileNewTurn(char *file_name, csuStruct *ptr_csu_struct)
 *  Update the file with the new scores
 * \param[in] *file_name the filename
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return TRUE if everything is OK, FALSE otherwise
 */
int writeFileNewTurn(char *file_name, csuStruct *ptr_csu_struct)
{
    char file_name_2[SIZE_MAX_FILE_NAME+4];
    int successful;

    sprintf(file_name_2,"%s_tmp",file_name);

    successful=writeCsuFile(file_name_2,ptr_csu_struct);

    if (successful)
    {
        if(deleteCsuFile(file_name))
        {
            if(renameCsuFile(file_name_2,file_name))
                return TRUE;
        }
    }

    return FALSE;
}

/*!
 * \fn int deleteCsuFile(char *file_name)
 *  Delete a csu file
 * \param[in] *file_name the filename
 * \return TRUE if everything is OK, FALSE otherwise
 */
int deleteCsuFile(char *file_name)
{
    addFileCsuExtension(file_name);

    libcsuper_initialize();

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
}

/*!
 * \fn int renameCsuFile(char *old_name, char *new_name)
 *  Rename a csu file.
 * \param[in] *old_name the old name of the file
 * \param[in] *new_name the new name of the file
 * \return TRUE if everything is OK, FALSE otherwise
 */
int renameCsuFile(char *old_name, char *new_name)
{
    char old_name_2[SIZE_MAX_NAME+8];
    char new_name_2[SIZE_MAX_NAME+4];

    libcsuper_initialize();

    sprintf(old_name_2,"%s",old_name);
    addFileCsuExtension(old_name_2);
    sprintf(new_name_2,"%s",new_name);
    addFileCsuExtension(new_name_2);

    if(rename(old_name_2,new_name_2))
    {
        printf(_("\nThe file %s cannot be renamed.\n"),old_name_2);
        return FALSE;
    }

    else
    {
        printf(_("\nThe file %s was well renamed in %s.\n"),old_name_2,new_name_2);
        return TRUE;
    }
}

