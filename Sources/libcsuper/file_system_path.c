/*!
 * \file    file_system_path.c
 * \brief   Fonctions qui l'emrankment des fichiers sauvegardes
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * file_system_path.c
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

 #include "file_system_path.h"

/*!
 * \fn void createFileSystemPath()
 *  Create the folder and the file which contain the system path
 * \return TRUE if everything is OK, FALSE otherwise
 */
int createFileSystemPath()
{
    char folder[SIZE_MAX_FILE_NAME];
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    /*Read the home directory and create the folder*/
    readHomePath(folder);
    sprintf(folder,"%s/%s",folder,MAIN_FOLDER_NAME);
    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(file_name,"%s/%s",folder,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return FALSE;

    fprintf(ptr_file,"%s",folder);

    closeFile(ptr_file);

    return TRUE;
}

/*!
 * \fn int readFileSystemPath(char *file_name)
 *  Read the system path and the path read to the filename
 * \param[in,out] *file_name the filename
 * \return TRUE if everything is OK, FALSE otherwise
 */
int readFileSystemPath(char *file_name)
{
    char file_name_preferences[SIZE_MAX_FILE_NAME];
    char folder[SIZE_MAX_FILE_NAME];
    int file_size;
    FILE *ptr_file;

    readHomePath(file_name_preferences);
    sprintf(file_name_preferences,"%s/%s/%s",file_name_preferences,MAIN_FOLDER_NAME,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name_preferences,"r");

    if(ptr_file == NULL)
        return FALSE;

    file_size=readFileSize(ptr_file);
    fgets(folder,file_size+1,ptr_file);
    closeFile(ptr_file);

    sprintf(folder,"%s/%s",folder,file_name);
    strcpy(file_name,folder);

    return TRUE;
}

/*!
 * \fn int readSystemPath(char *file_name)
 *  Add the system path, if the file system path doesn't exist, it create it.
 * \param[in,out] *file_name the filename
 * \return TRUE if everything is OK, FALSE otherwise
 */
int readSystemPath(char *file_name)
{
    libcsuper_initialize();

    if (readFileSystemPath(file_name)==FALSE)
    {
        if(createFileSystemPath()==FALSE)
        {
            printf(_("\nError while reading the file containing the system path.\n"));
            return FALSE;
        }
        if (readFileSystemPath(file_name)==FALSE)
        {
            printf(_("\nError while reading the file containing the system path.\n"));
            return FALSE;
        }
    }
    return TRUE;
}

/*!
 * \fn int changeSystemPath(char *new_path)
 *  Change the system path
 * \param[in,out] *new_path le nomveau chemin
 * \return TRUE if everything is OK, FALSE otherwise
 */
int changeSystemPath(char *new_path)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    if (createFileSystemPath()==FALSE)
        return FALSE;

    readHomePath(file_name);

    sprintf(file_name,"%s/%s/%s",file_name,MAIN_FOLDER_NAME,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return FALSE;

    fprintf(ptr_file,"%s",new_path);

    closeFile(ptr_file);

    return TRUE;
}

/*!
 * \fn void readHomePath(char *path)
 *  Read the home path
 * \param[in,out] path the path
 */
void readHomePath(char *path)
{
    #ifdef __unix__
    strcpy(path,getenv("HOME"));
    #elif _WIN32
    strcpy(path,getenv("USERPROFILE"));
    #endif
}

/*!
 * \fn void readHomePath(char *path)
 *  Read the home path with a slash at the end
 * \param[in,out] path the path
 */
void readHomePathSlash(char *path)
{
    #ifdef __unix__
    strcpy(path,getenv("HOME"));
    #elif _WIN32
    strcpy(path,getenv("USERPROFILE"));
    #endif
    sprintf(path,"%s/",path);
}
